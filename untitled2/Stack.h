#pragma once
#include"Header.h"
template<class T>
class Stack
{
private:
	ListSequence<T>* items;
	int size = 0;
public:
	Stack()
	{
		this->items = new ListSequence<T>();
	}
	Stack(const T* items, const int count)
	{

		this->size = count;
		for (int i = 0; i < count; i++)
		{
			this->items->Append(*(items + i));
		}
	}
	Stack(Sequence<T> * items)
	{
		this->items = new ListSequence<T>();
		for (int i = 0; i < items->GetLength(); i++)
			this->items->Append(items->Get(i));
		this->size = items->GetLength();
	}

	Stack(const Stack<T> & other)
	{
		this->items = new ListSequence<T>(*(other.items));

		this->size = other.size;
	}
	Stack<T>& operator=(const Stack<T> & other) {
		if (&other == this)
			return *this;

		
		delete this->items;

	
		this->items = new ListSequence<T>(*other.items);

		this->size = other.size;
		return *this;
	}

	T Get(const int index)
	{
		return this->items->Get(index);
	}
public:
	int GetLength()
	{
		return this->items->GetLength();
	}
	
	T Pop()
	{
		T tmp = this->items->GetLast();
		this->items->RemoveAt(items->GetLength()-1);
		this->size--;
		return tmp;
	}

	void push(T item)
	{
		this->items->Append(item);
		this->size++;

	}
	

	~Stack()
	{

		while (this->size)
		{
			this->Pop();

		}
	}
};
