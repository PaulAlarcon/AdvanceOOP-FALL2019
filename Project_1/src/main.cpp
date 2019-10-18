/*
 * Paul Alarcon
 * Safe Matrix
 * CSCI381
 * Prof. Waxman.
 *
 * Templates should work fine as long you only declared arithmetic types, otherwise an error will be thrown
 *
 */

#include <iostream>
#include <string>

using namespace std;
template<typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class safeArray{
private:
    int lowerb, upperb;
    T *arr;
public:
    //default constructor
    safeArray(){
        lowerb = 0; upperb = -1;
        arr = NULL;
    }

    // one parameter 0 -> n-1
    safeArray(int n){
        lowerb = 0;
        upperb = n-1;
        arr = new T[upperb - lowerb + 1];
    }

    // two parameters n -> m
    safeArray(int n, int m){
        lowerb = n;
        upperb = m;
        arr = new T[upperb - lowerb + 1];
    }

    //copy constructor
    safeArray(const safeArray<T> &s){
     int size= s.upperb - s.lowerb + 1;
     arr = new T[size];
     for(int i=0; i<size; i++)
     arr[i]=s.arr[i];
     lowerb = s.lowerb;
     upperb = s.upperb;
     }

    //destructor
    ~safeArray(){
        delete[] arr;
    }

    //operators overload

    //arr[n] returns a value of type T;
    T& operator[](int n){
        if( n < lowerb || n > upperb){
            cout << "\nIndex out of range.\n";
            exit(1);
        }
     return arr[n - lowerb];
    }

    //returns a safeArray
     safeArray & operator=(const safeArray<T> & s){
     if(this==&s)return *this;
     delete [] arr;
     int size = s.upperb - s.lowerb + 1;
     arr = new T[size];
     for(int i=0; i<size; i++)
     arr[i]=s.arr[i];
     upperb = s.upperb;
     lowerb = s.lowerb;
     return *this;
     }

    template <typename U>
    friend ostream& operator<<(ostream& os, const safeArray<U> &s);
};

template<class T>
ostream & operator<<(ostream & os, const safeArray<T> & s){
    int size = s.upperb - s.lowerb+1;
    for(int i = 0 ; i < size; i++){
        os << s.arr[i]<< " ";
    }
     os << endl;
    return os;
};

template<typename T>
class safeMatrix{
private:
    int lowerbx, upperbx, lowerby, upperby;
    safeArray<T>* matrix;
public:
    //default constructor
    safeMatrix(){
        lowerbx = lowerby = 0;
        upperbx = upperby = -1;
        matrix = NULL;
    }

    safeMatrix(int lwx, int upx, int lwy, int upy){

        if(lwx > upx || lwx > upy){
            cout << "Impossible array, check your bounds" << endl;
            exit(1);
        }

        lowerbx = lwx;
        upperbx = upx;

        lowerby = lwy;
        upperby = upy;

        int size = upperbx - lowerbx + 1;

        matrix = new safeArray<T>[size];

        for(int i = 0; i < size ; i++){
            matrix[i] = safeArray<T>(lowerby, upperby);
        }
    }

    safeMatrix(const safeMatrix<T> & sm){

         lowerbx = sm.lowerbx;
         upperbx = sm.upperbx;
         lowerby = sm.lowerby;
         upperby = sm.upperby;

         int n = sm.upperbx - sm.lowerbx + 1;
         matrix = new safeArray<T>[n];

        for(int i = 0; i < n ; i++){
            matrix[i] = safeArray<T>(sm.matrix[i]);
        }

    }

    safeMatrix(int upx, int upy){
        lowerbx = lowerby = 0;
        upperbx = upx -1 ;
        upperby = upy -1;

        int size = upperbx - lowerbx + 1;

        matrix = new safeArray<T>[size];

        for(int i = 0; i < size ; i++){
            matrix[i] = safeArray<T>(upperby - lowerby + 1);
        }
    }

    ~safeMatrix(){
        delete[] matrix;
    }

    safeArray<T> & operator[]( int i ){
        return matrix[i - lowerbx];
    }

    safeMatrix<double> operator*(double scalar){

        int resX = upperbx - lowerbx + 1;
        int resY = upperby - lowerby + 1;

        safeMatrix<double> res(resX, resY);

        for(int i = 0; i < resX; i++){
            for(int j = 0; j < resY; j++){
                res[i][j] = matrix[i][j + lowerby]*scalar;
            }
        }
        return res;
    }

    safeMatrix<T> operator*(const safeMatrix<T> & sm){

    int Acolumns = upperby - lowerby + 1; // number of columns
    int Arows = upperbx - lowerbx + 1;
    int Bcolumns = sm.upperby - sm.lowerby + 1; // number of rows
    int Brows = sm.upperbx - sm.lowerby + 1;

    if(Acolumns != Brows){
        cout << "\nConsidering AxB \nNumber of colums of A should be the same as the number of rows of B \n ";
        exit(1);
    }

    safeMatrix<T> res(Arows, Bcolumns);

        for (int i = 0; i < Arows; i++) {
            for (int j = 0; j < Bcolumns; j++) {
                res[i][j] = 0;
                    for (int k = 0; k < Acolumns; k++){
                    res[i][j] += matrix[i][k + lowerby]*sm.matrix[k][j + sm.lowerby];
                }

            }
        }

        return res;
    }

    safeMatrix<T> & operator = (safeMatrix<T> & sm) {
        if(this==&sm) return *this;
        delete [] matrix;
        int size = sm.upperbx - sm.lowerbx + 1;
        matrix = new safeArray<T>[size];
        for(int i=0; i < size; i++){
            matrix[i]=sm.matrix[i];
        }
        upperbx = sm.upperbx;
        lowerbx = sm.lowerbx;
        upperby = sm.upperby;
        lowerby = sm.lowerby;
        return *this;
    }

    template <typename U>
    friend ostream & operator<<(ostream & os, const safeMatrix<U> & sm);

};
    template <typename T>
    ostream & operator<<(ostream & os, const safeMatrix<T> & sm){
        int size = sm.upperbx - sm.lowerbx + 1;
        for(int i = 0; i < size; i++){
            cout << sm.matrix[i];
        }
        return os;
    };

int main(){

    safeMatrix<int> a(9,11,11,12), b(2,1);

    a[9][11] = 3;
    a[10][11] = 9;
    a[11][11] = 3;
    a[9][12] = 7;
    a[10][12] = 2;
    a[11][12] = 1;


    b[0][0] = 3;
    b[1][0] = 2;

    cout << "printing a : " << endl << a << endl;
    cout << "printing b : " << endl << b << endl;

    safeMatrix<double> c(2,2), d(2,2);

    c[0][0] = 2.1;
    c[0][1] = 3.2;
    c[1][0] = 8.8;
    c[1][1] = 7.2;

    d[0][0] = 3.1;
    d[0][1] = 6.2;
    d[1][0] = 9.7;
    d[1][1] = 0.2;

    cout << "printing c : " << endl << c << endl;
    cout << "printing d : " << endl << d << endl;

    cout << "multiplying a x b : " << endl << a*b <<endl;
    cout << "multiplying c x d : " << endl << c*d << endl;

    cout << "multiplying a by 3 :" << endl << a*3.5 << endl;

    cout << "multiplying c by 4 :" << endl << c*4 << endl;

    return 0;
}
