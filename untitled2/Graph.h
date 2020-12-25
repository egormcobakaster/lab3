#pragma once
#include<utility>
#include"Header.h"
#include"Stack.h"
template<class T>
class Edge {
public:
	Edge(int f, int t, T w)
	{
		from = f;
		to = t;
		wt = w;

	};
	Edge()
	{
		from = -1;
		to = -1;
		wt = -1;

	};
	T wt;
	int from;
	int to;

	
};


template<class T>
class Graph {
	int Vcnt, Ecnt;
	bool digraph;
	struct node {
		ArraySequence<Edge<T>*>* adj;
		int num;
		node(int number)
		{
			num = number;
			adj = new ArraySequence<Edge<T>*>;
		}
	};
	
	ArraySequence<node*>* Nodes;

public:
    Graph(int V,bool digraph = true)
	{
		Vcnt = V;
		Ecnt = 0;
		Nodes = new ArraySequence<node*>;
		for (int i = 0; i < V; i++)
		{
			node* t=new node(i);
			Nodes->Append(t);

		}
		this->digraph = digraph;
	}
		
    ~Graph() {
		for (int v = 0; v < Vcnt; v++) {
			delete (Nodes->Get(v)->adj);
		}
		delete this->Nodes;
	}

	int V() const { return Vcnt; }
	int E() const { return Ecnt; }
	bool directed() const { return digraph; }

	void insert(Edge<T>* e) {
        Edge<T>* e2=new Edge<T>(e->from,e->to,e->wt);
		int f = e->from;
        this->Nodes->Get(f)->adj->Append(e2);
		
		if (!digraph) {
			int f = e->to;
			Edge<T>* e1 = new Edge<T>(e->to, e->from, e->wt);
			this->Nodes->Get(f)->adj->Append(e1);
		}
		Ecnt++;
	}
	void tcR(int v, int w, T dist) {
		if ((v != w)&&(!edge(v,w)))
		{
			Edge<T>* e= new Edge<T>(v,w,dist);

			this->insert(e);
		}
		
		
		for (int t = 0; t < Nodes->Get(w)->adj->GetLength(); t++) {
			Edge<T>* e = Nodes->Get(w)->adj->Get(t);
			tcR(v, e->to, dist+ e->wt);
		}
	}
	void tc(){
		for (int v = 0; v < this->V(); v++) tcR(v, v, 0);
	}
	bool edge(int v, int w) const {
		for (int i = 0; i < Nodes->Get(v)->adj->GetLength(); i++)
		{
			if (w == Nodes->Get(v)->adj->Get(i)->to)
				return true;
		}
		return false;
		
	}
	void insert(node* n)
	{
		this->Nodes->Append(n);
		Vcnt++;
		Ecnt += n->adj->GetLength();
	}
	void insert()
	{
		node* n = new node(Vcnt);
		Nodes->Append(n);
		Vcnt++;
	}
	void RemoveNode(int v)
	{
		this->Nodes->RemoveAt(v);
		Vcnt--;
		for (int i = 0; i < Nodes->GetLength(); i++)
		{
			for (int j = 0; j < Nodes->Get(i)->adj->GetLength(); j++)
			{
				if ((Nodes->Get(i)->adj->Get(j))->to == v)
				{
					Nodes->Get(i)->adj->RemoveAt(j);
					Ecnt--;
				}
			}
		}
	}
	void RemoveEdge(int from, int to)
	{
		for (int i = 0; i < Nodes->Get(from)->adj->GetLength(); i++)
		{
			if (to == Nodes->Get(from)->adj->Get(i)->to)
			{
				Nodes->Get(from)->adj->RemoveAt(i);
				Ecnt--;
			}
		}
		if (!digraph)
		{
			for (int i = 0; i < Nodes->Get(to)->adj->GetLength(); i++)
			{
				if (from == Nodes->Get(to)->adj->Get(i)->to)
				{
					Nodes->Get(to)->adj->RemoveAt(i);
					Ecnt--;
				}
			}
		}
		
	}
    ArraySequence<Edge<T>*>* Get(int v)
	{
        ArraySequence<Edge<T>*>* Ar=new ArraySequence<Edge<T>*>;
		for (int i = 0; i < this->Nodes->Get(v)->adj->GetLength(); i++)
        {
            Ar->Append(this->Nodes->Get(v)->adj->Get(i));
        }
        return Ar;

	}
	
    ArraySequence<T>* Dijkstra(int v)
	{
        ArraySequence<T>* Arr = new ArraySequence<int>;
		int* visited = new int[Vcnt];
		for (int i = 0; i < Vcnt; i++)
		{
			visited[i]=0;
		}
		T* dist = new T[Vcnt];
		for (int i = 0; i < v; i++)
		{
			dist[i]=10000;
		}
		dist[v]=0;
		for (int i = v+1; i < Vcnt; i++)
		{
			dist[i] = 10000;
		}
		int minindex = v;
		while ((dist[minindex]<10000)&&(minindex>=0))
		{
			for (int i = 0; i < Nodes->Get(minindex)->adj->GetLength();i++)
			{
				if (dist[minindex] + Nodes->Get(minindex)->adj->Get(i)->wt < dist[Nodes->Get(minindex)->adj->Get(i)->to])
				{
					dist[Nodes->Get(minindex)->adj->Get(i)->to]= dist[minindex] + Nodes->Get(minindex)->adj->Get(i)->wt;

				}

			}
			visited[minindex]=1;
				int min=10000;
				int index = -1;
			for (int i = 0; i < Vcnt; i++)
			{
				if ((dist[i] < min) && (visited[i] == 0)&&(i!=minindex))
				{
					min = dist[i];
						index = i;
				}
			}
			minindex = index;
		}
		for (int i=0; i < Vcnt; i++)
		{
			if (visited[i] == 1)
			{
                T a=dist[i];
                Arr->Append(dist[i]);
			}
			else
			{
                Arr->Append(-1);
			}
		}
		return Arr;
	}
	bool AllCyclic()
	{
		int* color = new int[Vcnt];
		int cele_st = -1;
		for (int i = 0; i < Vcnt; i++)
		{
			color[i] = 0;
		}
		for (int i = 0; i < Vcnt; i++)
		{
			if (cyclic(i, cele_st, color))
				return true;
		}
		return false;
	}
	bool cyclic(int v, int& cycle_st, int  color[]) { 
		color[v] = 1;
		for (int i = 0; i < this->Nodes->Get(v)->adj->GetLength(); i++) {
			T to = this->Nodes->Get(v)->adj->Get(i)->to;
			if (color[to] == 0) { 
				if (cyclic(to, cycle_st,color))  return true;
			}
			else if (color[to] == 1) { 
				cycle_st = to; 
				return true;
			}
		}
		color[v] = 2; 
		return false;
	}
	void topologicalSortUtil(int v, bool visited[],
		Stack<T>& Stack)
	{
		
		visited[v] = true;

		
		
		for (int i = 0;i<this->Nodes->Get(v)->adj->GetLength(); i++)
			if (!visited[this->Nodes->Get(v)->adj->Get(i)->to])
				topologicalSortUtil(this->Nodes->Get(v)->adj->Get(i)->to, visited, Stack);

		
		Stack.push(v);
	}

	
    Stack<T>* topologicalSort()
	{
        Stack<T>* S= new Stack<T>;

		
		bool* visited = new bool[Vcnt];
		for (int i = 0; i < Vcnt; i++)
			visited[i] = false;

		
		for (int i = 0; i < Vcnt; i++)
			if (visited[i] == false)
                topologicalSortUtil(i, visited, *S);

		
		
        return S;
	}
};
