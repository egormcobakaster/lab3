#pragma once
#include"Header.h"
template <class T>
class DynamicArray
{
private:
	T* arr;
	int size;
public:
	DynamicArray(T* items, const int size)
	{
        if (size >= 0)
        {
		this->arr = new T[size];
		this->size = size;
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = *(items + i);
		}
        }
		
	}
	DynamicArray(const int size) 
	{
        if (size >= 0)
        {
		this->arr = new T[size]; 
		this->size = size;
        }

	}
	DynamicArray(const DynamicArray<T>& array) 
	{	
		this->size = array->GetSize();
		this->arr = new T[this->size];
        for (int i = 0; i < array->GetSize(); i++)
		{
			this->Set(array->Get(i));
		}
	}; 
public:
	int GetSize() 
	{
		return this->size;
	}

	T Get(const int index)
	{
        if (index >= 0 && index < this->size)
            return this->arr[index];
	}

	void Set(int index, T value)
	{
        if (index >= 0 && index < this->size)
            this->arr[index] =  T(value);
	}

	void resize(int newsize)
	{
        if (newsize >= 0){
		T* arrtemp = new T[newsize];
		if (newsize <= this->size)
		{
			for (int i = 0; i < newsize; i++)
			{
				arrtemp[i] = this->arr[i];
			}
			this->size = newsize;
			delete[] this->arr;
			this->arr = arrtemp;
		}
		else 
		{
			for (int i = 0; i < this->size; i++)
			{
				arrtemp[i] = this->arr[i];
			}


			this->size = newsize;
			delete[] this->arr;
			this->arr = arrtemp;
		}
        }
		
	}

	~DynamicArray()
	{
		delete[] arr;
	}
};
