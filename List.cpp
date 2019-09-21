#include"List.h"
#include<iostream>

template <class T>
int List<T>::getNumOfElem() const
{
	return numOfElem;
}

template <class T>
Node<T>* List<T>::getFirst() const
{
	return first;
}

template <class T>
Node<T>* List<T>::getLast() const
{
	return last;
}

template <class T>
void List<T>::setFirst(Node<T>* newNode)
{
	first = newNode;
}

template <class T>
void List<T>::setLast(Node<T>* newNode)
{
	last = newNode;
}

template <class T>
void List<T>::insertFront(T* newContent)
{
	Node<T>* newNode = new Node<T>(newContent);
	
	if (numOfElem == 0)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		newNode->setNext(first);
		first = newNode;
	}
	++numOfElem;
}

template <class T>
void List<T>:: insertFront(Node<T>* newNode)
{	
	if (numOfElem == 0)
	{
		first = newNode;
		last = newNode;
	}
	else 
	{
		newNode->setNext(first);
		first = newNode;
	}
	++numOfElem;
}

template <class T>
void List<T>::insertBack(Node<T>* newNode)
{
	if (numOfElem == 0)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->setNext(newNode);
		last = newNode;
	}
	++numOfElem;
}

template <class T>
void List<T>::insertBack(T* newContent)
{
	Node<T>* newNode = new Node<T>(newContent);

	if (numOfElem == 0)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->setNext(newNode);
		last = newNode;
	}
	++numOfElem;
}

template <class T>
void List<T>::insertNth(T* newContent, int place)
{
	Node<T>* newNode = new Node<T>(newContent);
	if (numOfElem == 0)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		if(place == 0)
		{
			newNode->setNext(first);
			first = newNode;
		}
		else
		{
			if (place < numOfElem)
			{
				Node<T>* temp = first;
				while (place > 1)
				{
					temp = temp->getNext();
					place--;
				}
				newNode->setNext(temp->getNext());
				temp->setNext(newNode);
			}
			else 
			{
				last->setNext(newNode);
				last = newNode;
			}
		}
	}
	++numOfElem;
}

template <class T>
void List<T>::pushFirstToEnd()
{
	if (numOfElem > 1)
	{
		last->setNext(first);
		last = first;
		first = first->getNext();
		last->setNext(NULL);
	}

}

template <class T>
bool List<T>::search(T* target) const
{
	bool found = 0;
	Node<T>* temp = first;
	while (temp != NULL && !found)
	{	
		found = (temp->getContent() == 	target);
		temp = temp->getNext();
	}
	return found;
}

template <class T>
bool List<T>::search(T* target, Node<T>* &position) const
{
	bool found = 0;
	Node<T>* temp = first;
	if (temp->getContent() == NULL) return false;
	while (temp != NULL && !found)
	{
		found = (temp->getContent() == target);
		if (found) position = temp;
		temp = temp->getNext();
	}
	return found;
}

template <class T>
bool List<T>::search(const string& target, T* &result) const
{
	bool found = 0;
	Node<T>* temp = first;
	while (temp != NULL && !found)
	{
		found = *(temp->getContent()) == target;
		if (found) result = temp->getContent();
		temp = temp->getNext();
	}
	return found;
}

template <class T>
bool List<T>::search(const string& target) const
{
	bool found = 0;
	Node<T>* temp = first;
	while (temp != NULL && !found)
	{
		found = *(temp->getContent()) == target;
		temp = temp->getNext();
	}
	return found;
}

template <class T>
void List<T>::remove(T* target)
{
	if (numOfElem == 0);
	//	cerr << "Error: Remove: list is empty\n";
	else
	{
		Node<T>* position;
		if (search(target, position))
		{
			if (numOfElem == 1)
			{
				delete first;
				first = NULL;
				last = NULL;
			}
			else if (numOfElem == 2)
			{
				if (position == first)
				{
					delete first;
					first = last;
				}
				else 
				{
					first->setNext(NULL);
					delete last;
					last = first;
				}
			}
			else if (position == last)
			{
				Node<T>* temp = first;
				while (temp->getNext() != last)
					temp = temp->getNext();
				delete last;
				last = temp;
				last->setNext(NULL);
			}
			else if (position == first)
			{
				first = position->getNext();
				delete position;
			}
			else
			{
				Node<T>* temp = first;
				while (temp->getNext() != position)
					temp = temp->getNext();
				temp->setNext(position->getNext());
				delete position;
			}
			--numOfElem;
		}
	//	else cerr << "Error: Remove: Not in list\n";
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& newList)
{
	if (&newList != this)
	{
		Node<T>* temp = newList.getFirst();
		while (temp != NULL)
		{
			this->insertBack(temp->getContent());
			temp = temp->getNext();
		}
		first = newList.getFirst();
		last = newList.getLast();
	}
	//else cerr << "Error: Attemted assingment to self List\n";
	return *this;
}
template <class T>
ostream& operator<<(ostream& o, const List<T>& myList)
{
	Node<T>* temp = myList.first;
	while (temp != NULL)
	{
		o << *(temp->getContent()) << "->";
		temp = temp->getNext();
	}
	cout << "END\n"; 
	return o;
}

template <class T>
void List<T>::destroyList()
{
	Node<T>* temp;
	while (first != NULL)
	{
		temp = first;
		first = first->getNext();
		delete temp;
		temp = NULL;
	}
	numOfElem = 0;
}

template <class T>
void List<T>::destroyPointerInsideNode()
{
	Node<T>* temp = first;
	while (temp != NULL)
	{
		delete temp->getContent();
		temp = temp->getNext();
	}
}

template <class T>
List<T>::~List()
{
	destroyList();
}
