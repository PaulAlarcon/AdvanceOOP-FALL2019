#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

template<typename T>
class LinkedList;

template<typename T>
class Node{
	friend class LinkedList<T>;
	T data;
	Node<T>* next;


	Node(T d, Node<T> * n = 0){
		data = d;
		next = n;
	}

	template <typename U>
	    friend ostream & operator<<(ostream & os, LinkedList<U> ll);

};


template<typename T>
class LinkedList{
	Node<T> * head, * tail;
	int size;

public:
	LinkedList(){
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void add(T d){
		Node<T> * n = new Node<T>(d, head);
		head = n;
		if(tail == NULL)
			tail = head;

		size++;
	}

	void push_back(T d){
		Node<T> * n = new Node<T>(d);
		if(tail == NULL){
			tail = head = n;
		}
		else{
			tail->next = n;
			tail = tail->next;
		}
	}

	int indexOf(T d){
		Node<T> * current = head;
		int i = 0;
		while(current != NULL){
			if(current->data == d){
				return i;
			}
			current = current->next;
			i++;
		}
		return -1;
	}

	T & get(int index){
		Node<T> * current = head;
		T * ans = 0;
		while(current != NULL){
			if(indexOf(current->data) == index){
				ans =  & current->data;
			}
			current = current->next;
		}
		return * ans;
	}

	T & pop_back(){
		if(tail == NULL){
			cerr << "\nEmpty List\n";
			exit(1);
		}

		T * ans = &tail->data;
		Node<T> * current = head;
		while(current->next != tail){
			current = current->next;
		}
		current->next = NULL;
		tail = current;
		if(tail == NULL){
			head = NULL;
		}
		size--;
		return * ans;

	}

	T & pop_front(){
		if(head == NULL){
			cerr << "\nEmpty List\n";
			exit(1);
		}
		T * ans = & head->data;
		head = head->next;
		if(head == NULL){
			tail = NULL;
		}
		size--;

		return * ans;
	}

	bool contains(T d){
		Node<T> * current = head;
		while(current != NULL){
			if(current->data == d){
				return true;
			}
			current = current->next;
		}
		return false;
	}

	T remove(int index){
		if(size == 0){
			cerr << "\nEmpty list\n";
			exit(1);
		}
		else if(size == 1 || index == 0)
			return pop_front();
		else if(index >= size || index < 0){
			cerr << "\nOut of bound\n";
			exit(1);
		}
		else if(index == (size-1))
			return pop_back();

		Node<T> * current = head->next;
		T ans = 0;

		while(current != tail){
			if(indexOf(current->data) == (index - 1)){
				ans = current->next->data ;
				current->next = current->next->next; // a b c = a->next(b) = a->next->next(c) === a c
				size--;
			}
			else{
				current = current->next;
			}
		}

		return ans;
	}

	int getSize(){
		return size;
	}

	~LinkedList(){

	}

	template <typename U>
	friend ostream & operator<<(ostream & os, LinkedList<U> ll);

};
template <typename T>
ostream & operator<<(ostream & os, LinkedList<T> ll){
	for(int i = ll.size - 1; i >= 0; i--){
		os << ll.get(i) << " ";
	}
	return os;
}

class Monomial{
	int coef, exp;
public:
	Monomial(int c = 0, int e = 0){
		coef = c;
		exp = e;
	}

	int & exponent(){
		return exp;
	}

	int & coefficient(){
		return coef;
	}

	~Monomial(){

	}

	bool operator==(const Monomial & n){
		if(coef == n.coef && exp == n.exp){
			return true;
		}
		return false;
	}

	friend ostream & operator<<(ostream & os, Monomial m);

};

ostream & operator<<(ostream & os, Monomial m){
	os << m.coef << "X^" << m.exp;
	return os;
}

class Polynomial{

private:
	LinkedList<Monomial> raw_list, canonical_form;
public:

	Polynomial(){

	}

	Polynomial(string str){
		LinkedList<Monomial> tempLL;
		stringstream ss{str};
			while (1) {
				int c = 0, e = 0;
				ss >> c >> e;
				if (c == 0 && e == 0)
					break;
				raw_list.add(Monomial(c,e));
				addMonomial(c, e);
				sort();
			}
	}

	Polynomial(const Polynomial & p){
		raw_list = p.raw_list;
		canonical_form = p.canonical_form;
	}

	void addMonomial(int c, int e){
		for(int i = 0; i < canonical_form.getSize(); i++){
			if(canonical_form.get(i).exponent() == e){
				canonical_form.get(i).coefficient() = canonical_form.get(i).coefficient() + c;
				if(canonical_form.get(i).coefficient() == 0){
					canonical_form.remove(i);
				}
				return;
			}
		}
		canonical_form.add(Monomial(c, e));

	}

	~Polynomial(){

	}


	Polynomial & operator+(const Polynomial & p){
		Polynomial temp(p);
		Polynomial * ans = new Polynomial();

		for(int i = 0; i < canonical_form.getSize(); i++){
			int tempc = canonical_form.get(i).coefficient();
			int tempe = canonical_form.get(i).exponent();
			ans->addMonomial( tempc, tempe );
		}

		for(int i = 0; i < temp.canonical_form.getSize(); i++){
			int tempc = temp.canonical_form.get(i).coefficient();
			int tempe = temp.canonical_form.get(i).exponent();
			ans->addMonomial( tempc, tempe );
		}
		ans->sort();
		return *ans;
	}

	Polynomial & operator-(const Polynomial & p){
		Polynomial temp(p);
		Polynomial * ans = new Polynomial();

		for(int i = 0; i < canonical_form.getSize(); i++){
			int tempc = canonical_form.get(i).coefficient();
			int tempe = canonical_form.get(i).exponent();
			ans->addMonomial( tempc, tempe );
		}

		for(int i = 0; i < temp.canonical_form.getSize(); i++){
			int tempc = temp.canonical_form.get(i).coefficient();
			int tempe = temp.canonical_form.get(i).exponent();
			ans->addMonomial( (-1)*tempc, tempe );
		}
		ans->sort();
		return *ans;
	}

	Polynomial & operator*(const Polynomial & p){
		Polynomial * ans = new Polynomial();
		Polynomial temp(p);
		for(int i = 0; i < temp.canonical_form.getSize(); i++){
			for(int j = 0; j < canonical_form.getSize(); j++){
				int tempc = temp.canonical_form.get(i).coefficient() * canonical_form.get(j).coefficient();
				int tempe = temp.canonical_form.get(i).exponent() + canonical_form.get(j).exponent();
				ans->addMonomial(tempc, tempe);
			}
		}
		ans->sort();
		return *ans;

	}

	template <typename T>
	void swap(T *xp, T *yp){
	    T temp = *xp;
	    *xp = *yp;
	    *yp = temp;
	}

	//using bubble sort
	void sort(){
	    int i, j;
	    int n = canonical_form.getSize();
	    for (i = 0; i < n-1  ; i++)
	    // Last i elements are already in place
	    for (j = 0; j < n-i-1; j++)
	        if (canonical_form.get(j).exponent() > canonical_form.get(j+1).exponent())
	            swap(&canonical_form.get(j), &canonical_form.get(j+1));
	}

//	void printRawForm(){
//		cout << showpos << raw_list << endl;
//	}

	void printRawForm(ofstream & f){
		f << showpos << raw_list << endl;
	}

	friend ostream & operator<<(ostream & os, const Polynomial & p);

};

 ostream & operator<<(ostream & os, const Polynomial & p){
	 os << p.canonical_form << endl;
	return os;
};

void run_interface(string str1, string str2, ofstream & f){
		Polynomial m(str1);
		Polynomial n(str2);
		f << showpos;
		f << endl << "print m before consolidation: " << endl;
		m.printRawForm(f);
		f << "print n before consolidation: " << endl;
		n.printRawForm(f);
		f << "printing m: " << m;
		f << "printing n: " << n;
		f << "m+n = " << m+n;
		f << "m-n = " << m-n;
		f << "m*n = " << m*n;
		f << "=========================================================================================";
}

int main(){
	ifstream input;
	ofstream output;
	input.open("input.txt");
	output.open("output.txt");
	string line;
	string a, b;
	int i = 0;
	if (input){
		while ( getline (input,line) )
		{
			  if(a == ""){
				  a = line;
			  }
			  else{
				  b = line;
				  if (b == ""){
					  output << noshowpos << "\n\nError!  operations on ( line "<< i << ") were not perfomed due to an odd number of lines\n\n";
					  cerr << "ERROR! odd number of lines";
				  }
				  else{
					  run_interface(a, b, output);
					  a = "";
					  b = "";
				  }

			  }
			  i++;
		}
		input.close();
		output.close();
	}
	else cout << "Unable to open input file";

	return 0;
}
