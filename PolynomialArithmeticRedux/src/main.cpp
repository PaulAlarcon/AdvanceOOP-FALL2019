/*
 * Paul Alarcon
 * CSCI 381 - Adv C++
 * 12/13/2019
 *
 *********************** P O L Y N O M A L  A R I T H M E T I C  R E D U X *********************
 *#include <map>
 * map<int,int> poly1,poly2,sum;
 *
 * Where the key value is the exponent and the mapped value is the coefficient
 *
 ***********************************************************************************************
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <iterator>
#include <cstring>

using namespace std;

enum Operations {SUM, SUB, MULT};

void doOperation(const map<int,int> & poly1, const map<int,int> & poly2, map<int, int> & res, Operations op){
	map<int,int>::const_iterator itr;
	map<int,int>::const_iterator sec_itr;

	switch(op){
	case SUM:
		cout << "SUM \n";
		res = poly1;
		for(itr = poly2.begin(); itr != poly2.end(); itr++ ){
			int exp = itr->first;
			int coef = itr->second;
			if(res.count(exp) > 0) res.at(exp) = res.at(exp) + coef;
			else res.insert(pair<int,int>(exp, coef));
		}

		break;
	case SUB:
		cout << "SUB \n";
		res = poly1;
		for(itr = poly2.begin(); itr != poly2.end(); itr++ ){
			int exp = itr->first;
			int coef = itr->second;
			if(res.count(exp) > 0) res.at(exp) = res.at(exp) - coef;
			else res.insert(pair<int,int>(exp, coef));
		}
		break;
	case MULT:{
		cout << "MULT \n";
		for(itr = poly2.begin(); itr != poly2.end(); itr++ ){
			int exp = itr->first;
			for(sec_itr = poly1.begin(); sec_itr != poly1.end(); sec_itr++ ){
			int mult_exp = exp * sec_itr->first;
			int mult_coef = exp * sec_itr->second;

		if(res.count(mult_exp) > 0) res.at(mult_exp) = res.at(mult_exp) + mult_coef;
		else res.insert(pair<int,int>(mult_exp, mult_coef));
		}
		}
	}
		break;
	default:
		break;

	}
}

void print(map<int,int> & poly, map<int,int>::reverse_iterator & itr){
	for(itr = poly.rbegin(); itr != poly.rend(); ++itr){
		cout<<itr->second << "X^" << itr->first << " ";
	}
	cout << endl;
}

void str_to_polynomial(string & str, map<int,int> & poly){
	stringstream ss{str};
	while (1) {
		int c = 0, e = 0;
		ss >> c >> e;
		if (c == 0 && e == 0)
			break;
	}
}

int main(){
	map<int, int> poly1, poly2, sum, sub, mult;

	string s1 = "2 3 2 9 -1 0 -1 3"; // -5X9 2X^4 1X^3 -1X^0
	string s2 = "3 9 8 2 3 8 9 1"; // 3X^9  8X^2  3X^8  9X^1

	str_to_polynomial(s1, poly1);
	str_to_polynomial(s2, poly2);

	map<int,int>::reverse_iterator itr;

	print(poly1, itr);
	print(poly2, itr);
	doOperation(poly1, poly2, sum, SUM);
	print(sum, itr);
	doOperation(poly1, poly2, sub, SUB);
	print(sub, itr);
	doOperation(poly1, poly2, mult, MULT);
	print(mult, itr);


	return 0;
}
