#pragma once
#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* next;
	node() {
		next = NULL;
		data = 0;
		//////////
	}
};


class List {
public:
	node* head;
	node* tail;
	int sizee; // store total nodes
	List() {
		head = nullptr;
		tail = nullptr;
		sizee = 0;
	}
	bool isEmpty() {
		return (head == NULL);
	}

	void Insert(int data) {

		if (isEmpty()) { // if list is empty then make new node
			node* newnode = new node;
			newnode->data = data;
			head = newnode;
			head->next = NULL;
			tail = newnode;
			sizee++; // increase l
			return;
		}
		/// <summary>
		/// /////////////////
		/// </summary>
		/// <param name="data"></param>
		node* newnode = new node;
		newnode->data = data;
		tail->next = newnode;
		tail = newnode;
		tail->next = NULL;
		sizee++;
		return;
		
	}

	/*void Delete(int index) {
		node* temp = head;
		for (int i = 0; i < index; i++)
			temp = temp->next;

		node* del = temp->next;
		temp->next = temp->next->next;
		delete del;
		ssize--;
	}*/

	int mean() {
		node* temp = head;
		int sum = 0;
		for (int i = 0; i < sizee; i++) {
				sum += temp->data;
				temp = temp ->next;
		}
		int mean = sum / sizee;

		return mean;

	}

	void clearClusters() {
		node* temp = head;
		while (head->next != NULL)
		{
			head = head->next;
			delete temp;
			temp = head;
		}
		delete temp;
	}

	int sum() {
		node* temp = head;
		int sum = 0;
		for (int i = 0; i < sizee; i++) {
			sum += temp->data;
			temp = temp->next;
		}
		return sum;
	}

	void display() {
		node* temp = head;
		cout << "{ ";
		while (temp != NULL) {
			cout <<temp->data;
			if (temp->next != NULL)
				cout << ", ";
			temp = temp->next;
		}
		cout << " }";
		cout << endl;
	}

	bool Search(int pixel) {
		node* temp = head;
		int index = 0;
		bool flag = false;
		while (temp->next != NULL) {
			if (temp->data = pixel) {
				flag = true;
				break;
			}
			temp = temp->next;
			index++;
		}
		return flag;
	}

	int * intoarray() {
		int* ptr = new int[sizee];
		int i = 0;
		node* temp = head;
		while (temp != NULL) {
			ptr[i]=temp->data;
			temp = temp->next;
			i++;
		}

		return ptr;
	}

	void set(int value) {
		node* temp = head;
		while (temp != NULL) {
			temp->data = value;
			temp = temp->next;
		}
	}

	~List() {
		node* temp = head;
		for (int i = 0; i < sizee; i++) {
			head = head->next;
			delete temp;
			temp = head;
		}
	}
};

