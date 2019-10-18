#include "safeMatrix.cpp"
#include <math.h>

class VNT{
	safeMatrix<int> * matrix;
	int upperBoundX, upperBoundY;

	bool isFull(){
		return (*matrix)[upperBoundY][upperBoundX] < INT_MAX;
	}

	bool isEmpty(){
		return (*matrix)[0][0] == INT_MAX;
	}

	void swap(int y1, int x1, int y2, int x2){
		int temp = (*matrix)[y1][x1];
		(*matrix)[y1][x1] = (*matrix)[y2][x2];
		(*matrix)[y2][x2] = temp;
	}

public:
	VNT(int m, int n){
		matrix = new safeMatrix<int>(m, n);
		upperBoundX = n - 1;
		upperBoundY = m - 1;
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				(*matrix)[i][j] = INT_MAX;

	}

	~VNT(){
		delete matrix;
	}

	void add(int n, bool draw = false){

		if(n >= INT_MAX || n <= -INT_MAX){
			cerr << "\nThe number added is below/above our capacity. \n";
			return;
		}

		if(isFull()){
			cerr << "Full VNT \n";
			return;
		}

		int currentY = upperBoundY;
		int currentX = upperBoundX;
		(*matrix)[currentY][currentX] = n;

		int leftX, leftY, topX, topY;
		int left_current, top_current;

		bool traverse = true;

		while(traverse){

			leftX = currentX - 1;
			leftY = currentY;
			topX = currentX;
			topY = currentY - 1;

			bool left = false;
			bool top = false;

			if(leftX >= 0 && leftY >= 0){
				left_current = (*matrix)[leftY][leftX];
				left = true;
			}

			if(topX >= 0 && topY >= 0){
				top_current = (*matrix)[topY][topX];
				top = true;
			}

			if( left_current > n && left && ((left_current >= top_current) || !top)){
				swap(leftY, leftX, currentY, currentX);
				currentX = leftX;
				currentY = leftY;
			}

			else if(top_current > n && top){
				swap(topY, topX, currentY, currentX);
				currentX = topX;
				currentY = topY;
			}

			else{
				traverse = false;
			}
		}
	}

	bool find(int n){
		bool found = false;
		bool traverse = true;

		if ( n < min() )
			traverse = false;

		int currentY = 0;
		int currentX = upperBoundX;
		int current;

		while(traverse){
			current = (*matrix)[currentY][currentX];
			if( current == n){
				found = true;
				traverse = false;
			}
			else if(current > n && currentX - 1 <= upperBoundX)
				currentX--;

			else if(current < n && currentY + 1 <= upperBoundY)
				currentY++;

			else
				traverse = false;
		}
		return found;
	}

	int min(){
		return (*matrix)[0][0];
	}

	int getMin(bool draw = false){
		if(isEmpty()){
			cout << "Empty VNT \n";
			return INT_MAX;
		}

		int min_value = (*matrix)[0][0];
		(*matrix)[0][0] = INT_MAX;

		int currentY = 0;
		int currentX = 0;
		int current = (*matrix)[currentY][currentX];
		bool traverse = true;

		int downY, downX, rightY, rightX;
		int down_current, right_current;

		while(traverse){

			if(draw){
				cout << *this << "\n";
			}

			downY = currentY + 1;
			downX = currentX;
			rightY = currentY;
			rightX = currentX + 1;

			bool down = false;
			bool right = false;

			if (downY <= upperBoundY){
				down_current = (*matrix)[downY][downX];
				down = true;
			}

			if (rightX <= upperBoundX){
				right_current = (*matrix)[rightY][rightX];
				right = true;
			}

			if (down && down_current <= current && ((right && right_current >= down_current) || !right)){
					swap(downY, downX, currentY, currentX);
					currentX = downX;
					currentY = downY;
			}

			else if(right && right_current < current && ((down && down_current > right_current) || !down)){
					swap(rightY,rightX , currentY, currentX);
					currentX = rightX;
					currentY = rightY;
			}

			else {
				traverse = false;
			}
		}

		return min_value;
	}

	void sort(int arr[], int k){
		VNT temp(ceil(sqrt(k)),ceil(sqrt(k)));
		int i;
		for (i = 0; i < k; i++)
			temp.add(arr[i]);
		for(i = 0 ; i < k; i++)
			arr[i] = temp.getMin();
	}

	friend ostream & operator<<(ostream & os, const VNT & t);

};

	inline ostream & operator<<(ostream & os, const VNT & t){
		os << (*t.matrix);
		return os;
	}
