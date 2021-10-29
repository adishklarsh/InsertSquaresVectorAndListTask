// insertSquaresVectorAndListTask.cpp

#include <iostream>						
#include <string>						
#include <vector>
#include <list>

using namespace std;

/*
Write a function which accepts a collection (array or list) of integers and inserts the square of each integer immediately after it. For example:

[1,3,2,5] should become [1,1,3,9,2,4,5,25]

The inserted numbers are highlighted red.

Which data structure (array or list) will give better performance for the above task?
In what way does it depend on how you solve the problem?
*/

// have to pass by reference - no pass by value (copy) of vector or list
void insertSquaresToVector(vector<int>& myVector);
void insertSquaresToList(list<int>& myList);

// if new array is created inside this function's scope - it will be out of scope 
// in main()
// Solution: initialize the new array on the stack and send a reference or use pointers
void insertSquaresToVector_Efficient(vector<int>& myVector, vector<int>& newVector);

void printVector(vector<int>& myVector);
void printList(list<int>& myList);

int main()
{
	vector<int> myVector({ 1, 3, 2, 5 });
	insertSquaresToVector(myVector);
	printVector(myVector);

	list<int> myList({ 1, 3, 2, 5 });
	insertSquaresToList(myList);
	printList(myList);

	//create our vector of values
	vector<int> vector2({ 1, 3, 2, 5 });
	// create an array twice the size in advance
	vector<int> newVector(vector2.size() * 2);
	insertSquaresToVector_Efficient(vector2, newVector);
	printVector(newVector);

	// Remember: "it = vec.insert(it, val)" inserts value, and returns iterator to inserted value. 
	// YOU MUST USE THIS ONE WITH VECTORS!!!
	system("pause");
}

void insertSquaresToVector(vector<int>& numVector) {

	vector<int>::iterator it = numVector.begin();	// iterator to start of vector
	int size = numVector.size();					// get size of vector since it will change

	for (int i = 0; i < size; i++) {
		// advance two indices in each step: read num, advance, write square, advance
		int num = *it;
		it++;
		// Insert on a vector corrupts the iterator (not so for a list) 
		// "it = numVector.insert(it, value)" not just "numVector.insert(i, val)"
		// iterator points at the inserted value. 
		it = numVector.insert(it, num * num);		// insert the squared value and return iterator to inserted value 
		it++;
	}

}

void insertSquaresToList(list<int>& numList) {
	list<int>::iterator it = numList.begin();
	int size = numList.size();

	for (int i = 0; i < size; i++) {
		// can use for loop on the iterator, but then no need to increment at the end
		// for (list<int>::iterator it = numList.begin(); it != numList.end(); ++it) {
			// advance two indices in each step: read num, advance, write square, advance
		int num = *it;
		it++;

		// Unlike the vector, after insert the iterator points at the item *after* the insertion point
		// it = numList.insert(it, value)) returns an iterator pointing at the inserted value
		// so we would need to increment it to point at the next one
		numList.insert(it, num * num);			// iterator points at the value after insertion	

		// can do this instead:
		//it = numList.insert(it, num * num);	// returns iterator pointing at the inserted value
		//it++;									// increment to point at next value
	}


}

void insertSquaresToVector_Efficient(vector<int>& numVector, vector<int>& newVector) {
	for (int i = 0; i < numVector.size(); i++) {
		int num = numVector[i];
		newVector[i * 2] = num;				// index to new array is 2i (all the evens)
		newVector[i * 2 + 1] = num * num;	// index for square is 2i+1 (all the odds)
	}

	numVector = newVector;					// return a reference to the new vector
}

void printVector(vector<int>& myVector) {
	for (int i = 0; i < myVector.size(); i++) {
		cout << myVector[i] << " ";
	}
	cout << endl;
}

void printList(list<int>& myList) {
	for (int i : myList) {
		cout << i << " ";
	}
	cout << endl;
}
