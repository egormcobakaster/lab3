#pragma once
#include"Header.h"
#include<utility>

using namespace std;
template<typename Key, typename Value>
class SparsedVector
{
private:
	DataSparsedVector<Key, Value>* Data;
	int Length;
public:
    SparsedVector(ArraySequence<pair<Key, Value>>* seq)
	{
        ArraySequence<pair<Key, Value>>* seqtemp;
        seqtemp=new ArraySequence<pair<Key, Value>>;
        for(int i=0;i<seq->GetLength();i++)
        {
            if (istrue(seq->Get(i).first))
            {
                seqtemp->Append(seq->Get(i));
            }
        }
        this->Data =new ISortedSequence<Key, Value>(seqtemp);
		this->Length = Data->GetLength();
	};

    SparsedVector(int Size)
    {
        this->Data = new IDictionary<Key, Value>(Size);
		this->Length = Data->GetLength();

	};
	bool istrue(int value)
	{
		if (value == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	void Add(Key key, Value value)
	{
		if (this->istrue(value))
		{
			this->Data->Add(key, value);
            this->Length++;
		}
		
	}
    void Remove(Key key)
    {
        this->Data->Remove(key);
    }
	Value Get(Key key)
	{
		return this->Data->Get(key);
	}
    bool ContainsKey(Key key)
    {
         return this->Data->ContainsKey(key);
    }
	int GetLength()
	{
		return this->Length;
	}
	~SparsedVector()
	{
		delete Data;
	}
};
