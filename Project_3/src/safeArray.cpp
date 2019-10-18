#include<iostream>

using namespace std;
template<typename T>
//template<typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
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
    	if (s.arr[i] == INT_MAX){
    		os << "- ";
    	}
    	else{
            os << s.arr[i]<< " ";
    	}
    }
     os << endl;
    return os;
};
