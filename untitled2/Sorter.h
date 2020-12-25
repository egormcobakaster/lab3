#pragma once
#include "Sequence.h"
#include"Header.h"
#include <string>
template<typename T>
int comp(T x, T y)
{
    if (x > y)
        return(1);
    else
        if (x < y)
            return(-1);
        else
            return(0);
};

template <typename T>
void quickSort(Sequence<T> * input, int (*cmp)(T, T), int left, int right)
{
	T pivot; 
    int lhold = left;
    int rhold = right;
	int x = left + rand() % (right-left);
	pivot = input->Get(x);
	
	while (left <right)
	{
		while (cmp(input->Get(right), pivot) == 1)
		{
			
				right--; 
		}
		while (cmp(input->Get(left), pivot) ==-1)
		{
			
				left++;
		};
		if (left <= right) {
			input->swap(left, right);
		};
				
		left++;
		right--;
		

	
	};
	

    if (lhold < right){
        quickSort(input, cmp, lhold, right);
    }
    if (left < rhold){
        quickSort(input, cmp, left, rhold);
    }
}
template <typename  T>
class ISorter
{
public:
	virtual void Sort(Sequence<T>* input, int (*cmp)(T, T)) = 0;

	
	
};

template <typename T>
class  InsertSorter : ISorter<T>
{
public:
	virtual void Sort(Sequence<T>* input,int (*cmp)(T, T)) override
	{
		for (int i = 1; i < input->GetLength(); i++)
			for (int j = i; j > 0 && cmp(input->Get(j - 1) , input->Get(j))==1; j--)
				input->swap(j - 1, j);
		
	}
	
};

template <typename T>
class shell_sort : ISorter<T>
{
public:
	virtual void Sort(Sequence<T>* input, int (*cmp)(T, T)) override
	{
		int length = input->GetLength();
		int d = input->GetLength() / 2;
		while (d >= 1)
		{
			bool isSw = false;
			for (int i = 0; i < input->GetLength() - d; ++i)
			{
				if ((cmp)(input->Get(i), input->Get(i + d)) == 1)
				{
					shell_sort::Swap(input, i, (i + d));
					isSw = true;
				}
			}
			if (isSw == false)
			{
				d = d / 2;
			}
		}
		
	}
	void Swap(Sequence<T>* seq, int index1, int index2)
	{
		seq->swap(index1, index2);
	}
};
template <typename T>
class q_sort : ISorter<T>
{
public:
	virtual void Sort(Sequence<T>* input, int (*cmp)(T, T)) override
	{
        quickSort(input, cmp, 0, input->GetLength() - 1);
		
	};
};
