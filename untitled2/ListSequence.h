#pragma once 
#include"Sequence.h"
#include "LinkedList.h"

template <class T >
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T>* items;
	int count ;
public:
	ListSequence() 
	{
		this->items = new LinkedList<T>();
		this->count = 0;
	}
	ListSequence(LinkedList<T>* items, int count)
	{
		this->count = count;
		this->items = new LinkedList<T>();
		for (int i = 0; i < count; i++)
		{
			this->Prepend(items->Get(i));
		}
	};
	ListSequence(const ListSequence<T>& other)
	{	
		this->count = other.count;
		this->items = new LinkedList<T>(*(other.items));
	
		
	};
public:
	virtual void swap(int index1, int index2) override
	{
		
		T item = this->Get(index1);
		this->InsertAt(index1, this->Get(index2));
		this->RemoveAt(index1 + 1);
		this->InsertAt(index2, item);
		this->RemoveAt(index2 + 1);
	}
	virtual int GetLength() const override
	{
		return this->items->Getsize();
	}
	virtual T GetFirst() const override
	{
		return this->items->GetFirst();
	}
	virtual T GetLast() const override
	{
		return this->items->GetLast();
	}
	virtual T Get(const int index) const override
	{	

		return this->items->Get(index);
	}
public:
	virtual void Append(T const value)  override
	{
		this->items->Apend(value);
		this->count++;
	}
	virtual void Prepend(T const value)  override
	{
		this->items->Prepend(value);
		this->count++;
	}
	virtual void InsertAt(const int index, T const value)  override
	{
		this->items->InsertAt(value, index);
		this->count++;
	}
	///////////////////////////////////////////////////
	virtual void Remove(T value)  override
	{
		int size = this->GetLength();
		for (int i = 0; i < size; i++)
		{
			if (this->items->Get(i) == value)
			{
				this->items->Remove(i);
				break;
			}
		}
		this->count--;
	}
	virtual void RemoveAt(const int index)  override
    {

        this->items->Remove(index);
		this->count--;
	}
	virtual void RemoveAll(T value)  override
	{
		int size = this->GetLength();
		int j = 0;
		while (j < this->count)
		{
			if (this->items->Get(j) == value)
			{
				RemoveAt(j);
				j--;
			}
			j++;
		}
	}
	///////////////////////////////////////////////////////
	virtual Sequence<T>* GetSubsequence(const int start, const int end)  override
	{	

		ListSequence<T>* itemsSub;
		itemsSub = new ListSequence<T>();

		itemsSub->items = this->items->GetSubList(start, end);	
		itemsSub->count = itemsSub->GetLength();
		return itemsSub;
	}
	virtual Sequence<T>* Concat(Sequence<T>* other)  override
	{
		int thissize = this->GetLength();
		int othersize = other->GetLength();
		ListSequence<T>* itemsconcat;
		itemsconcat = new ListSequence<T>();
		T* arrtemp; 
		arrtemp = new T[thissize + othersize];
		for (int i = 0; i < this->GetLength(); i++)
		{
			arrtemp[i] = this->Get(i);
		}
		for (int i = 0; i < other->GetLength(); i++)
		{
			arrtemp[thissize + i] = other->Get(i);
		}
		for (int i = 0; i < thissize + othersize; i++)
		{
			itemsconcat->Prepend(arrtemp[i]);
		}

		return itemsconcat;
	}
	virtual Sequence<T>* Copy()  override
	{
		ListSequence<T>* itemstemp;
		itemstemp = new ListSequence<T>();
		for (int i = 0; i < this->count; i++)
		{
			itemstemp->items->Prepend(this->Get(i));
		}

		return itemstemp;
	}
	virtual Sequence<T>* CopyTo(Sequence<T>* target, int startIndex)  override
	{

		ListSequence<T>* itemstemp;
		itemstemp = new ListSequence<T>();
		for (int i = startIndex; i < target->GetLength(); i++)
		{
			itemstemp->items->Prepend(target->Get(i));
		}
		
		return itemstemp;
	}
	~ListSequence()
	{
		while (this->count)
		{
			this->items->PopFront();
			count--;
		}
	}
};
