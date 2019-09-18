
// by JJeong
// referenced from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
@file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack()
{
	//Dynamically initializing node.
	headPtr = nullptr;
	currentSize = 0;
}  // end default constructor

   // TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
	delete headPtr;
	headPtr = nullptr;
	//Deleting allocated memory for headPtr.
}  // end destructor

   // TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	if (headPtr == nullptr) //If headPtr is empty return true.
		return true;
	else
		return false;
}  // end isEmpty

   // TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	if (headPtr != nullptr) //If headPtr is not empty, return size.
		return currentSize;
	else
		return 0;
}  // end size

   // TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType> *newNode;
	newNode = new Node<ItemType>;
	newNode->setItem(newItem); //Setting new node for adding item.

	newNode->setNext(headPtr); //Pushing newItem by pointing the same object as headPtr.
	headPtr = newNode; //Now headPtr is newNode since newNode is now on the top of stack.

	if (headPtr->getItem() == newItem) //If push was successful, headItem should equal newItem.
	{
		currentSize++; //Increase size then return true.
		return true;
	}
	else
		return false;
}  // end push

   // TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error)
{
	if (!isEmpty()) //If stack is not empty, returns item from headPtr. (item on top of stack.)
	{
		ItemType returnItem = headPtr->getItem();
	}
	else
		throw logic_error("Error! Stack is empty.");
}  // end peek

   // TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty()) //Pops only if not empty.
	{
		Node<ItemType> *tempNodePtr = headPtr; //Create temp node.
		headPtr = headPtr->getNext(); //Copy headPtr.

		tempNodePtr->setNext(nullptr);
		delete tempNodePtr;
		tempNodePtr = nullptr;

		currentSize--;
		result = true;
	}
	return result;
}  // end pop

   // TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	while (!isEmpty()) //Pop until stack is empty.
		pop();
}  // end clear