#pragma once
#include"Header.h"
#include<utility>
template<typename Key,typename Value>
class HashTable;
int HashFoo(int Key, int Size)
{
	return Key % Size;
};
template<typename Key,typename Value>
class HashTable
{
private:
	ArraySequence<ListSequence<pair<Key, Value>>*>* Table;
	int Capacity;
	int Count;
public:
	HashTable(int Size)
	{
		this->Capacity = Size;
		Count = 0;
		this->Table = new ArraySequence<ListSequence<pair<Key, Value>>*>;
		for (int i = 0; i < Size; i++)
		{
			ListSequence<pair<Key, Value>>* list = new ListSequence<pair<Key, Value>>;
			Table->Append(list);
		}
	}
	int GetCount()
	{
		return this->Count;
	}
	int GetCapacity()
	{
		return this->Capacity;
	}
	Key Hash(Key index)
	{
		return HashFoo(index, Capacity);
	}
	bool ContainsKey(Key key)
	{
		Key key1 = Hash(key);
		if (Table->Get(key1)->GetLength() == 0)
		{
            return 0;
		}
		else
		{


			for (int i = 0; i < Table->Get(key1)->GetLength(); i++)
			{
				if (Table->Get(key1)->Get(i).first == key)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	void Add(Key key, Value value)
	{
		pair<Key, Value> Pair(key, value);
		Key key1 = Hash(key);
		ListSequence<pair<Key, Value>>* list = new ListSequence<pair<Key, Value>>(*(this->Table->Get(key1)));
		list->Append(Pair);
		this->Table->Get(key1)->Append(Pair);
		Count++;
	}

	void Remove(Key key)
	{
		Key key1 = Hash(key);
		Value value = this->Find(key);
		pair<Key, Value> Pair(key, value);
		this->Table->Get(key1)->Remove(Pair);
		Count--;
	}
	Value Find(Key key)
	{
		Key key1 = Hash(key);
		if (Table->Get(key1)->GetLength() == 0)
		{

		}
		else
		{
			

			for (int i = 0; i < Table->Get(key1)->GetLength(); i++)
			{
				if (Table->Get(key1)->Get(i).first == key)
				{
					return Table->Get(key1)->Get(i).second;
				}
			}
		}
		
	}
};
