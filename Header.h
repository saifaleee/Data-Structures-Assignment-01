#pragma once
#include <iostream>

using namespace std;

class Node {
public:
	double data;
	Node* next;

	Node(double val = 0) {
		data = val;
		next = NULL;
	}

};
class LinkedList {
public:

	Node* head;
	LinkedList() {
		head = NULL;
	}
	~LinkedList() {
		Node* current = head;
		while (current != NULL) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}

	bool isEmpty() {
		if (head != NULL)
			return false;
		else
			return true;
	}

	int Size() {
		Node* current = head;
		int size = 0;
		while (current->next != NULL) {
			size++;
			current = current->next;
		}
		return size;

	}
	//AT END
	void Insert(double data, int index) {



		if (index == 0) {
			Node* newnode = new Node;
			newnode->data = data;
			newnode->next = head;
			head = newnode;
		}

		else {
			Node* currentnode;
			currentnode = head;
			int currentindex = 1;
			while (currentnode && currentindex < index) {
				currentnode = currentnode->next;
				currentindex++;
			}
			Node* newnode = new Node;
			newnode->next = currentnode->next;
			currentnode->next = newnode;
			newnode->data = data;
		}

	}

	int  Search(double data) {
		Node* current = head;
		int index = 0;
		while (current->data != data && current->next != NULL) {
			current = current->next;
			index++;
		}
		return index;
	}

	void Update(double oldval, double newval) {
		int index = Search(oldval);
		Node* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		current->data = newval;

	}

	bool Delete(int data) {
		if (head == NULL)
			return false;


		Node* current = head;
		Node* previous = head;

		int index = Search(data);

		if (index == 0) {
			current = head;
			head = head->next;
			delete current;
		}
		else {

			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			for (int i = 0; i < index - 1; i++) {
				previous = previous->next;
			}

			previous->next = current->next;

			delete current;

		}

	}

	void display() {
		Node* temp = head;
		cout << "{ ";
		while (temp != NULL) {
			cout << temp->data;
			if (temp->next != NULL)
				cout << ", ";
			temp = temp->next;
		}
		cout << " }";
		cout << endl;
	}

};

//void MergeLists(LinkedList& L1, LinkedList& L2) {
//	Node* current;
//	current = L1.head;
//	while (current->next != NULL) {
//		current = current->next;
//	}
//	int index = L1.Search(current->data);
//	Node* current2 = L2.head;
//	while (current2) {
//		L1.Insert(current2->data, index + 1);
//		index++;
//		current2 = current2->next;
//	}
//
//	int size = L1.Size();
//
//
//	for (int i = 0; i < size; i++) {
//		current = L1.head;
//		while (current->next != NULL) {
//			double temp;
//			if (current->next->data < current->data) {
//				temp = current->data;
//				current->data = current->next->data;
//				current->next->data = temp;
//			}
//
//			current = current->next;
//
//		}
//
//	}
//
//
//
//
//	L1.display();
//
//}