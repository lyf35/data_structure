#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Vector.h"

template<typename T> struct BTNode
{
	BTNode<T>* parent;
	Vector<T> key;
	Vector<BTNode<T>*> child;
	BTNode() 
	{ 
		parent = NULL;
		child.insert(0, NULL);
	}
	BTNode(T e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL)
	{
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc);
		child.insert(1, rc);
		if (lc)
		{
			lc->parent = this;
		}
		if (rc)
		{
			rc->parent = this;
		}
	}
};
template<typename T> class BTree
{
protected:
	int _size;
	int _order;
	BTNode<T>* _root;
	BTNode<T>* _hot;
	void solveOverflow(BTNode<T>*);
	void solveUnderflow(BTNode<T>*);
public:
	BTNode<T>* search(const T& e);
	bool insert(const T& e);
	bool remove(const T& e);
};
template<typename T> BTNode<T>* BTree<T>::search(const T& e)
{
	BTNode<T>* v = _root;
	_hot = NULL;
	while (v)
	{
		int r = v->key.search(e);
		if (r >= 0 && e == v->key[r])
		{
			return v;
		}
		_hot = v;
		v = v->child[r + 1];
	}
	return NULL;
}
template<typename T> bool BTree<T>::insert(const T& e)
{
	BTNode<T>* v = search(e);
	if (v)
	{
		return false;
	}
	int r = _hot->key.search(e);
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, NULL);
	_size++;
	solveOverflow(_hot);
	return true;
}
template<typename T> bool BTree<T>::remove(const T& e)
{
	BTNode<T>* v = search(e);
	if (!v)
	{
		return false;
	}
	int r = v->key.search(e);
	if (v->child[0])
	{
		BTNode<T> u = v->child[r + 1];
		while (u->child[0])
		{
			u = u->child[0];
		}
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1);
	_size--;
	solveUnderflow(v);
	return true;
}
template<typename T> void BTree<T>::solveOverflow(BTNode<T>* v)
{
	if (_order >= v->child.size())
	{
		return;
	}
	int s = _order / 2;
	BTNode<T>* u = new BTNode<T>();
	for (int j = 0;j < _order - s - 1;j++)
	{
		u->child.insert(j, v->child.remove(s + 1));
		u->key.insert(j, v->key.remove(s + 1));
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);
	if (u->child[0])
	{
		for (int j = 0;j < _order - s;j++)
		{
			u->child[j]->parent = u;
		}
	}
	BTNode<T>* p = v->parent;
	if (!p)
	{
		_root = p = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}
	int r = 1 + p->key.search(v->key[0]);
	p->key.insert(r, v->key.remove(s));
	p->child.insert(r + 1, u);
	u->parent = p;
	solveOverflow(p);
}
template<typename T>void BTree<T>::solveUnderflow(BTNode<T>* v)
{
	if ((_order + 1) / 2 <= v->child.size())
	{
		return;
	}
	BTNode<T>* p = v->parent;
	if (!p)
	{
		if (!v->key.size() && v->child[0])
		{
			_root = v->child[0];
			_root->parent = NULL;
			v->child[0] = NULL;
			release(v);
		}
		return;
	}
	int r = 0;
	while (p->child[r] != v)
	{
		r++;
	}
	if (r > 0)
	{
		BTNode<T>* ls = p->child[r - 1];
		if ((_order + 1) / 2 < ls->child.size())
		{
			v->key.insert(0, p->key[r - 1]);
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
			if (v->child[0])
			{
				v->child[0]->parent = v;
			}
			return;
		}
	}
	if (r < p->child.size() - 1)
	{
		BTNode<T>* rs = p->child[r + 1];
		if ((_order + 1) / 2 < rs->child.size())
		{
			v->key.insert(v->key.size(), p->key[r]);
			p->key[r] = rs->key.remove(0);
			v->child.insert(v->child.size(), rs->child.remove(0));
			if (v->child[v->child.size() - 1])
			{
				v->child[v->child.size() - 1]->parent = v;
			}
			return;
		}
	}
	if (r > 0)
	{
		BTNode<T>* ls = p->child[r - 1];
		ls->key.insert(ls->key.size(), p->key.remove(r - 1));
		p->child.remove(r);
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if (ls->child[ls->child.size() - 1])
		{
			ls->child[ls->child.size() - 1]->parent = ls;
		}
		while (!v->key.empty())
		{
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if (ls->child[ls->child.size() - 1])
			{
				ls->child[ls->child.size() - 1]->parent = ls;
			}
		}
		release(v);
	}
	else
	{
		BTNode<T>* rs = p->child[r + 1];
		rs->key.insert(0, p->key.remove(r));
		p->child.remove(r);
		rs->child.insert(0, v->child.remove(v->child.size() - 1));
		if (rs->child[0])
		{
			rs->child[0]->parent = rs;
		}
		while (!v->key.empty())
		{
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if (rs->child[0])
			{
				rs->child[0]->parent = rs;
			}
		}
		release(v);
	}
	solveUnderflow(p);
	return;
}