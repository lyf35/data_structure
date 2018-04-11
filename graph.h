#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Stack.h"
#include"Vector.h"
#include"Queue.h"

typedef enum {UNDISCOVERED,DISCOVERED,VISITED} Vstatus;
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} Etype;
template<typename Tv, typename Te> class Graph
{
private:
	void reset()
	{
		for (int i = 0;i < n;i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0;j < n, j++)
			{
				if (exists(i, j))
				{
					type(i, j) = UNDETERMINED;
				}
			}
		}
	}
	void BFS(int, int&);//广度优先搜索算法
	void DFS(int, int&);//深度优先搜索算法
	void BCC(int, int&, Stack<int>&);//基于dfs的双连通分量分解算法
	bool TSort(int, int&, Stack<Tv*>);//基于dfs的拓扑排序算法
	template<typename PU>void PFS(int, PU);//连通域优先级搜索框架
public:
	int n;
	virtual int insert(const Tv&) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	virtual int nextNbr(int) = 0;
	virtual Vstatus& status(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;
	int e;
	virtual bool exists(int, int) = 0;
	virtual void insert(const Te&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual Etype& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;
	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv*> tSort(int);
	void prim(int);
	void dijkstra(int);
	template<typename PU>void pfs(int, PU);
};

template<typename Tv> struct Vertex
{
	Tv data;
	int inDegree, outDegree;
	Vstatus status;
	int dTime, fTime;
	int parent;
	int priority;
	Vertex(const Tv& d = (Tv)0) :data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template<typename Te> struct Edge
{
	Te data;
	int weight;
	Etype type;
	Edge(const Te& d, int w) :data(d), weight(w), type(UNDETERMINED) {}
};

template<typename Tv, typename Te> class GraphMatrix :public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;
	Vector<Vector<Edge<Te>*>> E;
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix()
	{
		for (int j = 0;j < n;j++)
		{
			for (int k = 0;k < n;k++)
			{
				delete E[j][k];
			}
		}
	}
	virtual Tv& vertex(int i)
	{
		return V[i].data;
	}
	virtual int inDegree(int i)
	{
		return V[i].inDegree;
	}
	virtual int outDegree(int i)
	{
		return V[i].outDegree;
	}
	virtual int firstNbr(int i)
	{
		return nextNbr(i, n);
	}
	virtual int nextNbr(int i, int j)
	{
		while (j > -1 && !exists(i, --j))
		{
			;
		}
		return j;
	}
	virtual int& dTime(int i)
	{
		return V[i].dTime;
	}
	virtual int& fTime(int i)
	{
		return V[i].fTime;
	}
	virtual int& parent(int i)
	{
		return V[i].parent;
	}
	virtual int& priority(int i)
	{
		return V[i].priority;
	}
	virtual int insert(const Tv vertex)
	{
		for (int j = 0;j < n;j++)
		{
			E[j].insert(NULL);
		}
		n++;
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL));
		return V.insert(Vertex<Tv>(vertex));
	}
	virtual Tv remove(int i)
	{
		for (int j = 0;j < n;j++)
		{
			if (exists(i, j))
			{
				delete E[i][j];
				V[j].inDegree--;
			}
		}
		E.remove(i);
		n--;
		Tv vBak = vertex(i);
		V.remove(i);
		for (int j = 0;j < n;j++)
		{
			if (Edge<Te>* e = E[j].remove(i))
			{
				delete e;
				V[j].outDegree--;
			}
		}
		return vBak;
	}
	virtual bool exists(int i, int j)
	{
		return (i >= 0) && (n>i) && (j >= 0) && (n > j) && E[i][j] != NULL;
	}
	virtual Etype& type(int i, int j)
	{
		return E[i][j]->type;
	}
	virtual Te& edge(int i, int j)
	{
		return E[i][j]->data;
	}
	virtual int& weight(int i, int j)
	{
		return E[i][j]->weight;
	}
	virtual void insert(const Te edge, int w, int i, int j)
	{
		if (exists(i, j))
		{
			return;
		}
		E[i][j] = new Edge<Te>(edge, w);
		e++;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
};

template<typename Tv, typename Te> void Graph<Tv, Te>::bfs(int s)//breadth-first search for the whole graph 由于在单连通域的搜索中，一些变量可能没有办法抵达，因此可能需要多次执行搜索。该函数遍历所有顶点，一旦发现没有搜索到的顶点，便从该顶点出发调用BFS函数
{
	reset();
	int clock = 0;
	int v = s;
	do
	{
		if (UNDISCOVERED == status(v));
		{
			BFS(v, clock);
		}
	} while (s != (v = (v++%n)));
}
template<typename Tv, typename Te> void Graph<Tv, Te>::BFS(int v, int& clock)//breadth-first search 单连通域
{
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty())
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v);u > -1;u = nextNbr(v, u))
		{
			if (UNDISCOVERED == status(u))
			{
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(v, u) = TREE; //最后生成一棵以起始顶点作为根节点的广度优先搜索树
				parent(u) = v;
			}
			else
			{
				type(v, u) = CROSS; //顶点已经被访问，这条边不算在广度优先搜索树里面
			}
		}
		status(v) = VISITED;
	}
}
template<typename Tv, typename Te> void Graph<Tv, Te>::dfs(int s)//depth-first search 全局搜索
{
	reset();
	int clock = 0;
	int v = s;
	do 
	{
		if (UNDISCOVERED == status(v))
		{
			DFS(v, clock);
		}
	} while (s != (v = (++v%n)));
}
template<typename Tv, typename Te> void Graph<Tv, Te>::DFS(int s,int& clock)//depth-first search 单连通域
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v);u > -1;u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
}
template<typename Tv, typename Te> Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			if (!TSort(v, clock, S))
			{
				while (!S->empty())
				{
					S->pop();
					break;
				}
			}
		}
	} while (s != (v = (++v%n)));
	return S;
}
template<typename Tv, typename Te> bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S)
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v);u > -1;u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(u, v) = TREE;
			if (!TSort(u, clock, S))
			{
				return false;
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			return false;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));
	return true;
}

template<typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s)
{
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			BCC(v, clock, S);
			S.pop();
		}
	} while (s != (v = (++v%n)));
}

template<typename Tv, typename Te> void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S)
{
	typedef hca(v) = fTime(v);//节点所能连通的最高祖先
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for (int u = firstNbr(v);u > -1;u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);
			if (hca(u) < dTime(v))
			{
				hca(v) = min(hca(u), hca(v));
			}
			else
			{
				while (v != S.pop())
				{
					;
				}
				S.push(v);
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			if (u != parent(v))
			{
				hca(v) = min(hca(v), dTime(u));
				break;
			}
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
}

template<typename Tv, typename Te> template<typename PU> void Graph<Tv, Te>::pfs(int s, PU prioUpdater)//priority由自己输入的函数确定
{
	reset();
	int v = s;
	do
	{
		if (UNDISCOVERED == status(v))
		{
			PFS(v, prioUpdater);
		}
	} while (s != (v = (++v%n)));
}
template<typename Tv, typename Te> template<typename PU> void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	while (1)
	{
		for (int w = firstNbr(s);w > -1;w = nextNbr(s, w))
		{
			prioUpdater(this, s, w);
		}
		for (int shortest = INT_MAX, w = 0;w < n;w++)
		{
			if (UNDISCOVERED == status(w))
			{
				if (shortest > priority(w))
				{
					shortest = priority(w);
					s = w;
				}
			}
		}
		if (VISITED == status(s))
		{
			break;
		}
		status(s) = VISITED;
		type(parent(s), s) = TREE;
	}
}
template<typename Tv, typename Te> struct PrimPU
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v))
		{
			if (g->priority(v) > g->weight(uk, v))
			{
				g->priority(v) = g->weight(uk, v);
				g->parent(v) = uk;
			}
		}
	}
};
template<typename Tv, typename Te> struct DijkstraPU
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v))
		{
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v))
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v);
				g->parent(v) = uk;
			}
		}
	}
};
