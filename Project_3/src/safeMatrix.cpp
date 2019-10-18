#include<iostream>
#include "safeArray.cpp"

using namespace std;

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

    safeMatrix<T> & operator = (const safeMatrix<T> & sm) {
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
