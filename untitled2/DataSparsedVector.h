#pragma once
#include"Header.h"
#include<iostream>
#include<utility>

using namespace std;


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
    int HashFoo(int index, int Capacity)
    {
        return index % Capacity;
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
template<typename Key, typename Value>
class DataSparsedVector
{

public:
	virtual int GetLength() = 0;
	virtual Value Get(Key key) = 0;
	virtual void Add(Key key, Value value) = 0;
	virtual void Remove(Key key) = 0;
    virtual bool ContainsKey(Key key)=0;
	
	virtual ~DataSparsedVector() {};
};
template<class Key, class Value>
class ISortedSequence : public DataSparsedVector<Key, Value>
{
private:

	Sequence<pair<Key, Value>>* Seq;

public:

	ISortedSequence(ArraySequence<pair<Key, Value>>* Arr)
	{
		this->Seq = new ArraySequence<pair<Key, Value>>;
		for (int i = 0; i < Arr->GetLength(); i++)
		{
			this->Add(Arr->Get(i).first, Arr->Get(i).second);
		}
	};
	ISortedSequence(ListSequence<pair<Key, Value>>* Arr)
	{
		this->Seq = new ListSequence<pair<Key, Value>>;
		for (int i = 0; i < Arr->GetLength(); i++)
		{
			this->Add(Arr->Get(i));
		}
	};

	virtual void Add(Key key, Value value) override
	{
		pair<Key, Value> Pair;
		Pair.first = key;
		Pair.second = value;
		if (Seq->GetLength() == 0)
		{
			Seq->Append(Pair);
		}
		else {
			if (Seq->GetLast().first < key) {
				Seq->InsertAt(Seq->GetLength(), Pair);

			}
			else {
				for (int i = 0; i < this->Seq->GetLength(); i++) {
					if (Seq->Get(i).first > key) {
						Seq->InsertAt(i, Pair);
					}
				}

			}
		}


	};
	virtual Value Get(Key key) override
	{
		return this->Find(key, 1, 1, 0, this->GetLength() - 1);
	}
	virtual void Remove(Key key) override
	{
		Value value = this->Get(key);
		pair<Key, Value> Pair(key, value);
		this->Seq->Remove(Pair);
	}
    bool ContainsKey(Key key){
         Contains(key,1,1,0,this->GetLength() - 1);

    }
    bool Contains(Key key, int num1, int num2, int start, int end)
    {
        int LeftLength = start + (end - start + 1) / (num1 + num2) * num1;
        if (start == end) {

            if (Seq->Get(start).first == key) {

                return 1;
            }
            else
            {
                return 0;
            }

        }
        else {
            if (Seq->Get(LeftLength).first > key) {
                this->Find(key, num1, num2, start, LeftLength - 1);
            }
            else {
                this->Find(key, num1, num2, LeftLength, end);
            }

        }

    }
	Value Find(Key key, int num1, int num2, int start, int end) 
	{
		int LeftLength = start + (end - start + 1) / (num1 + num2) * num1;
		if (start == end) {

			if (Seq->Get(start).first == key) {

				return Seq->Get(start).second;
			}

		}
		else {
			if (Seq->Get(LeftLength).first > key) {
				this->Find(key, num1, num2, start, LeftLength - 1);
			}
			else {
				this->Find(key, num1, num2, LeftLength, end);
			}

		}
	}

	virtual int GetLength() override
	{
		return this->Seq->GetLength();
	}

};
template<typename Key,typename Value>
class IDictionary : public DataSparsedVector<Key, Value>
{
private:
    HashTable<Key, Value>* Table;
	int Length;
	int Capacity;
public:
	IDictionary(int Size)
	{
		this->Table = new HashTable<Key, Value>(Size);
		Capacity = Size;
		Length = 0;
	}
	virtual int GetLength() override
	{
		return this->Length;
	}
	int GetCapacity()
	{
		return this->Capacity;
	}
	virtual Value Get(Key key) override
	{
		return this->Table->Find(key);
	}
	bool ContainsKey(Key key)
	{
		return this->Table->ContainsKey(key);
	}
	virtual void Add(Key key, Value value) override
	{
		this->Table->Add(key, value);
		Length++;

	}
	virtual void Remove(Key key) override
	{
		this->Table->Remove(key);
		Length--;
	}
};
template<typename Key, typename Value>
class Tree : public DataSparsedVector<Key, Value>
{
private:
	Key selfkey;
	Value value;
	Tree* left;
	Tree* right;
public:
    Tree(Key key, Value value)
	{
        this->selfkey = key;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
	}
    Tree(Tree<Key,Value>* Tre)
        {
            this->selfkey = Tre->selfkey;
            this->value = Tre->value;
            this->left = Tre->left;
            this->right = Tre->right;
        }
public:
	bool HasLeft()
	{
		return this->right != nullptr;
	}
	bool HasRight()
	{
		return this->left != nullptr;
	}
	bool IsEmpty()
	{
		return this == nullptr;
	}
	bool ContainsKey(Key key)
	{
		Tree* temp = this;
		if (temp == nullptr)
		{
			return false;
		}
		else
		{
			if (temp->selfkey == key)
			{
				return true;
			}
			else
			{
				if (temp->selfkey > key)
				{
                    temp->right->ContainsKey(key);
				}
				else
				{
                    temp->left->ContainsKey(key);
				}
			}
		}
	}
	bool IsLeaf()
	{
		return this->left == nullptr && this->right == nullptr;
	}
	virtual void Add(Key key, Value value) override
	{
		if (this->selfkey > key)
		{
			if (this->left->IsEmpty())
			{
				this->left = new Tree(key, value);
			}
			else
			{
				this->left->Add(key, value);
			}
		}
		else
		{
			if (this->selfkey < key)
			{
				if (this->right->IsEmpty())
				{
					this->right = new Tree(value, key);
				}
				else
				{
					this->right->Add(key, value);
				}
			}
			if (this->selfkey == key) { throw exception(); }
		}
	}
	
	Sequence<pair<Key, Value>>* Thread(string rul)
	{
		if ((rul.size() != 3) && !(rul.find('L') != string::npos && rul.find('R') != string::npos && rul.find('N') != string::npos))
		{
			throw exception();
		}
		Sequence<pair<Key, Value>>* sequence = new ListSequence<pair<Key, Value>>();
		
		if (this->IsLeaf())
		{
			pair<Key, Value> item;
			item.first = this->selfkey;
			item.second = this->value;
			sequence->Prepend(item);
			return sequence;
		}
		for (size_t i = 0; i < rul.size(); i++)
		{
			if (rul[i] == 'N')
			{
				pair<Key, Value> item;
				item.first = this->selfkey;
				item.second = this->value;
				sequence->Prepend(item);
				return sequence;
			}
			else
			{
				if (rul[i] == 'L' && this->HasLeft())
				{
					sequence = sequence->Concat(this->left->Thread(rul));
				}
				if (rul[i] == 'R' && this->HasRight())
				{
					sequence = sequence->Concat(this->right->Thread(rul));
				}
			}
		}
		return sequence;
	}
	Sequence<pair<Key, Value>>* ToSeq()
	{
		return this->Thread("NLR");
	}
	virtual Value Get(Key key) override
	{
        if (this->ContainsKey(key))
		{
			Tree* temp = this;
			if (temp->selfkey == key)
			{
				return this->value;
			}
			else
			{
				if (temp->selfkey > key)
				{
                    return this->left->Get(key);
				}
				else
				{
					if (temp->selfkey < key)
					{
                        return this->right->Get(key);
					}
					else
					{

					}
				}
			}
		}
	}
	virtual int GetLength() override
	{
		return this->ToSeq()->GetLength();
	}
	Sequence<pair<Key, Value>>* GetKeyList()
	{
		Sequence<pair<Key, Value>>* seq = this->ToSeq();
		Sequence<pair<Key, Value>>* seqkey = new ListSequence<pair<Key, Value >>();

		for (size_t i = 0; i < seq->GetLength(); i++)
		{
			seqkey->Prepend(seq->Get(i).first);
		}
		return seqkey;
	}
	virtual void Remove(Key key) override
	{

		if (this == nullptr)
		{
            return;
		}

		bool where;
		Tree<Key, Value>* temp = this;
        Tree<Key, Value>* temp1 = nullptr;

		if (temp->left == nullptr && temp->right == nullptr)
		{
			if (temp->selfkey == key)
			{
				delete temp;

			};

            return;

		}
		while (temp != nullptr && temp->selfkey != key)
		{
            if (key < temp->selfkey)
			{
				where = false;
				temp1 = temp;
				temp = temp->left;
			}
			else
			{
                if (key > temp->selfkey)
				{
					where = true;
					temp1 = temp;
					temp = temp->right;
				}
			}
		}
		if (temp == nullptr)
		{
            return;
		}
		else
		{
			if (temp->right == nullptr && temp->left == nullptr)
			{
				if (!where)
				{
					temp1->left = nullptr;
				}
				else
				{
					temp1->right = nullptr;
				}
				delete temp;
                return;
			}
			else
			{
				if (temp->right != nullptr && temp->left == nullptr)
				{
					if (temp1->left == temp)
					{
						temp1->left = temp->right;
					}
					else
					{
						temp1->right = temp->right;
					}
					delete temp;
                    return;
				}
				else
				{
					if (temp->left != nullptr && temp->right == nullptr)
					{
						if (temp1->left == temp)
						{
							temp1->left = temp->left;
						}
						else
						{
							temp1->right = temp->left;
						}
						delete temp;
                        return;
					}
					else
					{
						if (temp->left != nullptr && temp->right != nullptr)
						{
							Tree<Key, Value>* temp2 = nullptr;
							temp1 = temp;
							temp2 = temp;
							where = true;
							temp = temp->right;
							while (temp->left != nullptr)
							{
								temp2 = temp;
								where = false;
								temp = temp->left;
							}
							temp1->selfkey = temp->selfkey;

							if (temp->right != nullptr)
							{
								if (where)
								{
									temp2->right = temp->right;
								}
								else
								{
									temp2->left = temp->right;
								}

								delete temp;
                                return;
							}
							else
							{
								if (where)
								{
									temp2->right = nullptr;
								}
								else
								{
									temp2->left = nullptr;
								}

								delete temp;
                                return;
							}
						}
					}
				}
			}
		}

	}
	void Destroi(Tree<Key, Value>* Tre)
	{
		Destroi(Tre->left);
		Destroi(Tre->right);
		delete Tre;
	}
	~Tree()
	{
		Destroi(this);
	}
};
