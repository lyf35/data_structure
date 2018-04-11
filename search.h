#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"BinTree.h"

template<typename K, typename V> struct Entry
{
	K key;
	V value;
	Entry(K k = K(), V v = V()) :key(k), value(v) {};
	Entry<const Entry<K, V>> e):key(e.key), value(e.value){};
	bool operator<(const Entry < K, V >> e)return (key < e.key);
	bool operator>(const Entry < K, V >> e)return (key > e.key);
	bool operator==(const Entry < K, V >> e)return (key == e.key);
	bool operator!=(const Entry < K, V >> e)return (key != e.key);
};

template<typename T> class BST :public BinTree<T> //binary search tree
{
protected:
	BinNode<T>* _hot;
	BinNode<T>* connect34(
		BinNode<T>*, BinNode<T>*, BinNode<T>*,
		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
	BinNode<T>* rotateAt(BinNode<T>* x);
public:
	virtual BinNode<T>*& search(const T& e);
	virtual BinNode<T>* insert(const T& e);
	virtual bool remove(const T& e);
};
template<typename T> static BinNode<T>*& searchIn(BinNode<T>*& v, const T& e, BinNode<T>* hot)
{
	if (!v || (e == v->data))
	{
		return v;
	}
	hot = v;
	return searchIn(((e < v->data) ? v->leftchildren, v->rightchildren), e, hot);
}
template<typename T> BinNode<T>*& BST<T>::search(const T& e)
{
	return searchIn(_root, e, _hot = NULL);
}
template<typename T> BinNode<T>* BST<T>::insert(const T& e)
{
	BinNode<T>*& x = search(e);
	if (x) //x should not be exist 
	{
		return x;
	}
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}
template<typename T> bool BST<T>::remove(const T& e)
{
	BinNode<T>*& x = search(e);
	if (!x)
	{
		return false;
	}
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return true;
}
template<typename T> static BinNode<T>* removeAt(BinNode<T>*& x, BinNode<T>*& hot)
{
	BinNode<T>* w = x;
	BinNode<T>* next = NULL;
	if (!HasLChild(*x))
	{
		next = x = x->rightchildren;
	}
	else if (!HasRChild(*x))
	{
		next = x = x->leftchildren;
	}
	else
	{
		w = w->next;
		swap(x->data, w->data);
		BinNode<T>* u = w->parent;
		((u == x) ? u->rightchildren, u->leftchildren) = next = w->rightchildren;
	}
	hot = w->parent;
	if (next)
	{
		next->parent = hot;
	}
	release(w->data);
	release(w);
	return next;
}

template<typename T> class AVL : public BST<T>
{
public:
	BinNode<T>* insert(const T& e);
	bool remove(const T& e);
};

template<typename T>bool balanced(BinNode<T> x)
{
	return (stature((x).leftchildren) == stature((x).rightchildren);
}
template<typename T>bool balFac(BinNode<T> x)
{
	return stature((x).leftchildren) - stature((x).rightchildren;
}
template<typename T>bool AvlBalanced(BinNode<T> x)
{
	return (balFac(x) > -2 && balFac(x) < 2);
}
template<typename T> BinNode<T>* tallerchild(BinNode<T>* x)
{
	return (stature(x->leftchildren) > stature(x->rightchildren) ? x->leftchildren :
		stature(x->leftchildren) < stature(x->rightchildren) ? x->rightchildren :
		IsLChild(*x) ? x->leftchildren : x->rightchildren);
}
template<typename T>BinNode<T>* AVL<T>::insert(const T& e)
{
	BinNode<T>*& x = search(e);
	if (x)
	{
		return x;
	}
	BinNode<T>* xx = x = new BinNode<T>(e, _hot);
	_size++;
	for (BinNode<T>* g = _hot;g;g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else
		{
			updateHeight(g);
		}
	}
	return xx;
}
template<typename T> bool AVL<T>::remove(const T& e)
{
	BinNode<T>*& x = search(e);
	if (!x)
	{
		return false;
	}
	removeAt(x, _hot);
	size--;
	for (BinNode<T>* g = _hot;g;g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		}
		updateHeight(g);
	}
	return true;
}
template<typename T>BinNode<T>* BST<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3)
{
	a->leftchildren = T0;
	if (T0)
	{
		T0->parent = a;
	}
	a->rightchildren = T1;
	if (T1)
	{
		T1->parent = a;
		updateHeight(a);
	}
	c->leftchildren = T2;
	if (T2)
	{
		T2->parent = c;
	}
	c->rightchildren = T3;
	if (T3)
	{
		T3->parent = c;
		updateHeight(c);
	}
	b->leftchildren = a;
	a->parent = b;
	b->rightchildren = c;
	c->parent = b;
	updateHeight(b);
	return b;
}
template<typename T>BinNode<T>* BST<T>::rotateAt(BinNode<T>* v)
{
	BinNode<T>* p = v->parent;
	BinNode<T>* g = p->parent;
	if (IsLChild(*p))
	{
		if (IsLChild(*v))
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->leftchildren, v->rightchildren, p->rightchildren, g->rightchildren);
		}
		else
		{
			p->parent = g->parent;
			return connect34(p, v, g, p->leftchildren, v->leftchildren, v->rightchildren, g->rightchildren);
		}
	}
	else
	{
		if (IsRChild(*v))
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->leftchildren, p->leftchildren, v->leftchildren, v->rightchildren);
		}
		else
		{
			p->parent = g->parent;
			return connect34(g, v, p, g->leftchildren, v->leftchildren, v->rightchildren, p->rightchildren);
		}
	}
}

template<typename T> class Splay :public BST<T>
{
protected:
	BinNode<T>* splay(BinNode<T>* v);
public:
	BinNode<T>* search(const T& e);
	BinNode<T>* insert(const T& e);
	bool remove(const T& e);
};

template<typename T> inline void attachAsLC(T p, T lc)
{
	p->leftchildren = lc;
	if (lc)
	{
		lc->parent = p;
	}
}

template<typename T> inline void attachAsRC(T p, T lc)
{
	p->rightchildren = rc;
	if (rc)
	{
		rc->parent = p;
	}
}

template<typename T> BinNode<T>* Splay<T>::splay(BinNode<T>* v)
{
	if (!v)
	{
		return NULL;
	}
	BinNode<T>* p, g;
	while ((p = v->parent) && (g = p->parent))
	{
		BinNode<T>* gg = g->parent;
		if (IsLChild(*v))
		{
			if (IsLChild(*p))
			{
				attachAsLC(g, p->rightchildren);
				attachAsLC(p, v->rightchildren);
				attachAsRC(p, g);
				attachAsRC(v, p);
			}
			else
			{
				attachAsLC(p, v->rightchildren);
				attachAsRC(g, v->leftchildren);
				attachAsLC(v, g);
				attachAsRC(v, p);
			}
		}
		else if (IsRChild(*p))
		{
			attachAsRC(p, v->leftchildren);
			attachAsLC(g, v->rightchildren);
			attachAsRC(v, g);
			attachAsLC(v, p);
		}
		else
		{
			attachAsRC(p, v->leftchildren);
			attachAsLC(g, v->rightchildren);
			attachAsRC(v, g);
			attachAsLC(v, p);
		}
		if (!gg)
		{
			v->parent = NULL;
		}
		else
		{
			(g == gg->lc) ? attachAsLC(gg, v) : attachAsRC(gg, v);
		}
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}
	if (p = v->parent)
	{
		v->parent = NULL;
		return v;
	}
}

template<typename T> BinNode<T>* Splay<T>::search(const T& e)
{
	BinNode<T>* p = searchIn(_root, e, _hot = NULL);
	_root = splay(p ? p : _hot);
	return _root;
}

template<typename T> BinNode<T>* Splay<T>::insert(const T& e)
{
	if (!_root)
	{
		_size++;
		return _root = new BinNode<T>(e);
	}
	if (e == search(e)->data)
	{
		return _root;
	}
	_size++;
	BinNode<T>* t = _root;
	if (_root->data < e)
	{
		t->parent = _root = new BinNode<T>(e, NULL, t, t->rightchildren);
		if (HasRChild(*t))
		{
			t->rightchildren->parent = _root;
			t->rightchildren = NULL;
		}
	}
	else
	{
		t->parent = _root = new BinNode<T>(e, NULL, t->leftchildren, t);
		if (HasLChild(*t))
		{
			t->leftchildren->parent = _root;
			t->leftchildren = NULL;
		}
	}
	updateHeightAbove(t);
	return _root;
}

template<typename T> bool Splay<T>::remove(const T& e)
{
	if (!root || (e != search(e)->data))
	{
		return false;
	}
	BinNode<T>* w = _root;
	if (!HasLChild(*_root))
	{
		_root = _root->rightchildren;
		if (_root)
		{
			_root->parent = NULL;
		}
	}
	else if (!HasRChild(*_root))
	{
		_root = _root->leftchildren;
		if (_root)
		{
			_root->parent = NULL;
		}
	}
	else
	{
		BinNode<T>* ltree = _root->leftchildren;
		ltree->parent = NULL;
		_root->leftchildren = NULL;
		_root = _root->rightchildren;
		_root->parent = NULL;
		search(w->data);
		_root->leftchildren = ltree;
		ltree->parent = _root;
	}
	release(w->data);
	release(w);
	_size--;
	if (_root)
	{
		updateHeight(_root);
	}
	return true;
}

template<typename T> class RedBlack :public BST<T>
{
public:
	BinNode<T>* insert(const T& e);
	bool remove(const T& e);
protected:
	void solveDoubleRed(BinNode<T>* x);
	void solveDoubleBlack(BinNode<T>* x);
	int updateHeight(BinNode<T>* x);
};

template<typename T> BinNode<T>* RedBlack<T>::insert(const T& e)
{
	BinNode<T>*& x = search(e);
	if (x)
	{
		return x;
	}
	x = new BinNode<T>(e, _hot, NULL, NULL, -1);
	_size++;
	solveDoubleRed(x);
	return x ? x : _hot->parent;
}

template<typename T> bool IsBlack(BinNode<T>* p)
{
	return (!p || RB_black == p->color);
}
template<typename T> bool IsRed(BinNode<T>* p)
{
	return !IsBlack(p);
}
template<typename T> bool BlackHeightUpdated(BinNode<T>* x)
{
	return (stature(x->leftchildren) == stature(x->rightchildren)) && (x->height == (IsRed(x) ? stature(x->leftchildren) : stature(x->leftchildren + 1)));
}
template<typename T> int RedBlack<T>::updateHeight(BinNode<T>* x)
{
	x->height = max(stature(x->leftchildren), stature(x->rightchildren));
	return IsBlack(x) ? x->height++ : x->height;
}
template<typename T> bool RedBlack<T>::remove(const T& e)
{
	BinNode<T>*& x = search(e);
	if (!x)
	{
		return false;
	}
	BinNode<T>* r = removeAt(x, _hot);
	if (!(--_size))
	{
		return true;
	}
	if (!_hot)
	{
		_root->color = RB_black;
		updateHeight(_root);
		return true;
	}
	if (BlackHeightUpdated(*_hot))
	{
		return true;
	}
	if (IsRed(r))
	{
		r->color = RB_black;
		r->height++;
		return true;
	}
	solveDoubleBlack(r);
	return true;
}
template<typename T> void RedBlack<T>::solveDoubleRed(BinNode<T>* x)
{
	if (IsRoot(*x))
	{
		_root->color = RB_black;
		_root->height++;
		return;
	}
	BinNode<T>* p = x->parent;
	if (IsBlack(p))
	{
		return;
	}
	BinNode<T>* g = p->parent;
	BinNode<T>* u = uncle(x);
	if (IsBlack(u))
	{
		if (IsLChild(*x) == IsLChild(*p))
		{
			p->color = RB_black;
		}
		else
		{
			x->color = RB_black;
		}
		g->color = RB_red;
		BinNode<T>* gg = g->parent;
		BinNode<T>* r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}
	else
	{
		p->color = RB_black;
		p->height++;
		u->color = RB_black;
		u->height++;
		if (!IsRoot(*g))
		{
			g->color = RB_red;
		}
		solveDoubleRed(g);
	}
}
template<typename T> void RedBlack<T>::solveDoubleBlack(BinNode<T>* r)
{
	BinNode<T>* p = r ? r->parent : _hot;
	if (!p)
	{
		return;
	}
	BinNode<T>* s = (r == p->leftchildren) ? p->rightchildren : p->leftchildren;
	if (IsBlack(s))
	{
		BinNode<T>* t = NULL;
		if (IsRed(s->rightchildren))
		{
			t = s->rightchildren;
		}
		if (IsRed(s->leftchildren))
		{
			t = s->leftchildren;
		}
		if (t)
		{
			RBColor oldColor = p->color;
			BinNode<T>* b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b))
			{
				b->leftchildren->color = RB_black;
				updateHeight(b->leftchildren);
			}
			if (HasRChild(*b))
			{
				b->rightchildren->color = RB_black;
				updateHeight(b->rightchildren);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else
		{
			s->color = RB_red;
			s->height--;
			if (IsRed(p))
			{
				p->color = RB_black;
			}
			else
			{
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else
	{
		s->color = RB_black;
		p->color = RB_red;
		BinNode<T>* t = IsLChild(*s) ? s->leftchildren : s->rightchildren;
	}
}

