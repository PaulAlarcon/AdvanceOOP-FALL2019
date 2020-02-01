
/*
 * Paul Alarcon
 * CSCI 381 - Adv C++
 * 12/13/2019
 */


#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

#include <map>
#include <vector>

using namespace std;


int main(){

	map <string , vector< pair<int, int> > > dict;

	ifstream input;
	input.open("gettysburg_address.txt");

	int lineNum, wordNum;
	string line, token;
	if (input){
		lineNum = 1;
		while ( getline (input , line ) )
		{
			wordNum = 1;
			stringstream temp(line);
			while(getline(temp, token, ' ')){

				if(dict.count(token) > 0){
					dict.at(token).push_back(pair<int,int>(lineNum, wordNum));
				}
				else{
					dict[token];
					dict.at(token).push_back(pair<int,int> (lineNum, wordNum));
				}
				wordNum++;
			}
			lineNum++;
		}
		input.close();
	}
	else cout << "Unable to open input file";

	map<string, vector< pair<int, int>>>::iterator it;
	vector<pair<int, int>>::iterator vector_it;

	for(it = dict.begin(); it != dict.end(); it++){
		cout << it->first << " " << it->second.size() << " ";
		cout << "[";
		for(vector_it = it->second.begin(); vector_it != it->second.end(); vector_it++){
			cout << "(" << vector_it->first << "," << vector_it->second << ")";
		}
		cout << "]" << endl;

	}

	return 1;
}
