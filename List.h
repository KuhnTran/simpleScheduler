#ifndef LIST_H
#define LIST_H

#include "ControlBlocks.h"
#include<iostream>
using namespace std;

template <class T>
class Node
{
	public:
		Node(T* newContent)
		{
			content = newContent;	
			next = NULL;
		}

		Node(T* newContent, Node* newNext, Node* newPrev)
		{
			content = newContent;
			next = newNext;
		}

		Node& operator=(const Node& newNode)
		{
			next = newNode.getNext();
			content = newNode.getContent();
		}

		void setNext(Node* newNext) { next = newNext; }
		Node* getNext() const { return next; }
		T* getContent() const { return content; }
	
		~Node()
		{
			content = NULL;
			next = NULL;
		}
			
	private:
		T* content;
		Node* next;
};

template <class T>
class List
{
	public:
		List()
		{
			first = NULL;
			last = NULL;
			numOfElem = 0;
		}
		int getNumOfElem() const;

		Node<T>* getFirst() const;
		Node<T>* getLast() const;

		void setFirst(Node<T>*);
		void setLast(Node<T>*);
		void insertFront(T*);
		void insertFront(Node<T>*);
		void insertBack(T*);
		void insertBack(Node<T>*);	
		void insertNth(T*, int);

		void pushFirstToEnd();	
		
		void remove(T*);

		bool search(T*) const;
		bool search(T*, Node<T>* &) const;
		bool search(const string&, T* &) const;
		bool search(const string&) const;

		List<T>& operator=(const List<T>&);
		
		template <class H>
		friend ostream& operator<<(ostream&, const List<H>&);
		
		void destroyPointerInsideNode();
		void destroyList();
		~List();	

	private:
		int numOfElem;
		Node<T>* first;
		Node<T>* last;
};
#endif
