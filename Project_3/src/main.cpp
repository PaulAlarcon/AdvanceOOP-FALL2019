/*
 * Paul Alarcon
 * 10-18-2019
 * Project 3 - "VNT"
 * CSCI 381 Advanced c++
 * Prof. Waxman
 */

#include <iostream>
#include <iterator>
#include "vnt.cpp"
#include <time.h>
#include <math.h>

using namespace std;


//function takes a VNT and a number as a parameter and fills out
//roughly that number in percentage

void generateVNT(VNT & v, int n, int m, int percentage = 100){
	srand(time(NULL));
	int num_elements = ceil(n*m*(percentage/100.0));


	cout << "Generating " << percentage << "% elements of the VNT " << "\n";

	for(int i = 0; i < num_elements ; i++)
			v.add(rand());
}

void get_num_mins(VNT & v, int n){

	cout << "Displaying " << n << " mins. \n";

	while(n != 0){
		cout << "The min of the current VNT is " << v.getMin() << "\n";
		n--;
	}
}

int main(){

	VNT a(10, 5);
	//generateVNT takes the VNT m, n,
	//and an number which will represent
	//	the percentage of how full the matrix should be
	generateVNT(a, 10, 5, 10);
	cout << a << "\n";

	//get_num_mins takes the VNT and a number
	// which will indicate how many mins are wanted
	get_num_mins(a, 5);
	cout << "\n-Printing VNT-\n\n";
	cout << a << "\n";

	//FIND
//	cout << "Using find method\n";
//	cout << a.find(222) << "\n";

	//SORTING
	cout << "Sorting Algorithm using VNT \n\n";
	cout << "1-D array: \n\n";

	int arr[] = {9999, 10, 2, 4, 5 ,6 ,7 ,11, -12 , 3 , 55, 67, 89, -245, 767, 789 , -999 };

	for (int n : arr)
		cout << n << " ";

	cout << "\n\n1-D array: after sorting \n";
	a.sort(arr, sizeof(arr)/sizeof(arr[0]));

	for (int n : arr)
		cout << n << " ";

	return 0;
}
