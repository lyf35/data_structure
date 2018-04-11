#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Stack.h"
#include"Queue.h"

typedef enum {RB_red,RB_black} RBcolor;

template<typename T> struct BinNode
{
	T data;
	BinNode<T>* parent;
	BinNode<T>* leftchildren;
	BinNode<T>* rightchildren;
	int height;
	int npl;//Null path length 左式堆
	RBcolor color;
	BinNode() : parent(NULL), leftchildren(NULL), rightchildren(NULL), height(0), npl(1), color(RB_red) {};
	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0, int l = 1, RBcolor c = RB_red) :data(e), parent(p), leftchildren(lc), rightchildren(rc), height(h), npl(l), color(c) {};
	int size();
	BinNode<T>* insertAsLc(const T);// insert left children
	BinNode<T>* insertAsRc(const T);// insert right children
	BinNode<T>* next();
	template<typename R> void travLevel(R&); //子树层次遍历
	template<typename R> void travPre(R&); //子树先序遍历
	template<typename R> void travIn(R&); //子树中序遍历
	template<typename R> void travPost(R&); //子树后序遍历
	bool operator<(const BinNode bn)
	{
		return data < bn.data;
	}
	bool operator==(const BinNode bn)
	{
		return data == bn.data;
	}
};

template<typename T> int stature(BinNode<T>* p)
{
	return (p) ? p->height : -1;
}

template<typename T> bool IsRoot(BinNode<T> p)
{
	return (!(p.parent));
}

template<typename T> bool IsLChild(BinNode<T> p)
{
	return (!IsRoot(p)&&(&(p)==p.parent->leftchildren));
}

template<typename T> bool IsRChild(BinNode<T> p)
{
	return (!IsRoot(p) && (&(p) == p.parent->rightchildren));
}

template<typename T> bool HasParent(BinNode<T> p)
{
	return (!IsRoot(p));
}

template<typename T> bool HasLChild(BinNode<T> p)
{
	return (p.leftchildren);
}

template<typename T> bool HasRChild(BinNode<T> p)
{
	return (p.rightchildren);
}

template<typename T> bool HasChild(BinNode<T> p)
{
	return (HasLChild(p) || HasRChild(p));
}

template<typename T> bool HasBothChild(BinNode<T> p)
{
	return (HasLChild(p) && HasRChild(p));
}

template<typename T> bool IsLeaf(BinNode<T> p)
{
	return (!HasChild(p));
}

template<typename T> bool sibling(BinNode<T> p)
{
	return (IsLChild(p) ? p.parent->rightchildren : p.parent->leftchildren);
}

template<typename T> bool uncle(BinNode<T> p)
{
	return (IsLChild(*(p.parent)) ? p.parent->parent->rightchildren : p.parent->parent->leftchildren);
}

template<typename T> BinNode<T>* FromParentTo(BinNode<T> p)
{
	IsRoot(p) ? _root : (IsLChild(p) ? p.parent->leftchildren : p.parent->rightchildren);
}

template<typename T> BinNode<T>* BinNode<T>::insertAsLc(const T e)
{
	return leftchildren = new BinNode<T>(e, this);
}
template<typename T> BinNode<T>* BinNode<T>::insertAsRc(const T e)
{
	return rightchildren = new BinNode<T>(e, this);
}


template<typename T> class BinTree
{
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);
	void updateHeightAbove(BinNode<T>* x);
public:
	BinTree() :_size(0), _root(NULL) {};
	~BinTree()
	{
		if (_size > 0)
		{
			remove(_root);
		}
	}
	int size() const
	{
		return _size;
	}
	bool empty() const
	{
		return !root;
	}
	BinNode<T>* root() const
	{
		return _root;
	}
	BinNode<T>* insertAsRoot(const T e);
	BinNode<T>* insertAsLC(BinNode<T>* p, const T e);
	BinNode<T>* insertAsRC(BinNode<T>* p, const T e);
	BinNode<T>* attachAsLC(BinNode<T>* p, BinTree<T>* &t);
	BinNode<T>* attachAsRC(BinNode<T>* p, BinTree<T>* &t);
	int remove(BinNode<T>* x);
	BinTree<T>* secede(BinNode<T>* x);
	template<typename R> void travLevel(R& visit)
	{
		if (_root)
		{
			_root->travLevel(visit);
		}
	}
	template<typename R> void travPre(R& visit)
	{
		if (_root)
		{
			_root->travPre(visit);
		}
	}
	template<typename R> void travPre(R& visit)
	{
		if (_root)
		{
			_root->travPre(visit);
		}
	}
	template<typename R> void travPost(R& visit)
	{
		if (_root)
		{
			_root->travPost(visit);
		}
	}
	bool operator<(const BinTree<T> t)
	{
		return _root&&t._root && (_root < t.root);
	}
	bool operator==(const BinTree<T> t)
	{
		return _root&&t._root && (_root == t.root);
	}
};
template<typename T> int BinTree<T>::updateHeight(BinNode<T>* x)
{
	return x->height = 1 + max(stature(x->leftchildren), stature(x->rightchildren));
}
template<typename T> void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}
template<typename T> BinNode<T>* BinTree<T>::insertAsRoot(const T e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}
template<typename T> BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* p, const T e)
{
	size++;
	p->insertAsLC(e);
	updateHeightAbove(p);
	return p->leftchildren;
}
template<typename T> BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* p, const T e)
{
	size++;
	p->insertAsRC(e);
	updateHeightAbove(p);
	return p->rightchildren;
}
template<typename T> BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* p, BinTree<T>*& s)
{
	if (p->leftchildren == s->_root)
	{
		p->leftchildren->parent = p;
	}
	_size += s->_size;
	updateHeightAbove(p);
	s->_root = NULL;
	s->_size = 0;
	release(s);
	s = NULL;
	return x;
}
template<typename T> BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* p, BinTree<T>*& s)
{
	if (p->rightchildren == s->_root)
	{
		p->rightchildren->parent = p;
	}
	_size += s->_size;
	updateHeightAbove(p);
	s->_root = NULL;
	s->_size = 0;
	release(s);
	s = NULL;
	return x;
}
template<typename T> int BinTree<T>::remove(BinNode<T>* x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
template<typename T> static int removeAt(BinNode<T>* x)
{
	if (!x)
	{
		return 0;
	}
	int n = 1 + removeAt(x->leftchildren) + removeAt(x->rightchildren);
	release(x->data);
	release(x);
	return n;
}
template<typename T> BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T>* s = new BinTree<T>;
	s->_root = x;
	x->parent = NULL;
	s->_size = x->size();
	_size -= s->_size;
	return s;
}
template<typename T, typename R> void travPre_R(BinNode<T>* x, R& visit)
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->leftchildren, visit);
	travPre_R(x->rightchildren, visit);
}
template<typename T, typename R> void travPost_R(BinNode<T>* x, R& visit)
{
	if (!x)
	{
		return;
	}
	travPost_R(x->leftchildren, visit);
	travPost_R(x->rightchildren, visit);
	visit(x->data);
}
template<typename T, typename R> void travIn_R(BinNode<T>* x, R& visit)
{
	if (!x)
	{
		return;
	}
	travIn_R(x->leftchildren, visit);
	visit(x->data);
	travIn_R(x->rightchildren, visit);
}
template<typename T, typename R> static void visitAlongLeftBranch_Pre(BinNode<T>* x, R& visit, Stack<BinNode<T>*>& s)
{
	while (x)
	{
		visit(x->data);
		s.push(x->rightchildren);
		x = x->leftchildren;
	}
}
template<typename T, typename R> void travPre_I2(BinNode<T>* x, R& visit)
{
	Stack<BinNode<T>*> s;
	while (true)
	{
		visitAlongLeftBranch_Pre(x, visit, s);
		if (s.empty())
		{
			break;
		}
		x = s.pop();
	}
}
template<typename T> static void goAlongLeftBranch_In(BinNode<T>* x, Stack<BinNode<T>*>& s)
{
	while (x)
	{
		s.push(x);
		x = x->leftchildren;
	}
}
template<typename T, typename R> void travIn_I1(BinNode<T>* x, R& visit)
{
	Stack<BinNode<T>*> s;
	while (true)
	{
		goAlongLeftBranch_In(x,s);
		if (s.empty())
		{
			break;
		}
		x = s.pop();
		visit(x->data);
		x = x->rightchildren;
	}
}
template<typename T>BinNode<T>* BinNode<T>::next()//中序遍历序列中的直接后继
{
	BinNode<T>* s = this;
	if (rightchildren)
	{
		s = rightchildren;
		while (HasLChild(*s))
		{
			s = s->leftchildren;
		}
	}
	else
	{
		while (IsRChild(*s))
		{
			s = s->parent;
		}
		s = s->parent;
	}
	return s;
}
template<typename T, typename R> void travIn_I2(BinNode<T>* x, R& visit)
{
	Stack<BinNode<T>*> s;
	while (true)
	{
		if (x)
		{
			s.push(x);
			x = x->leftchildren;
		}
		else if (!s.empty)
		{
			x = s.pop();
			visit(x->data);
			x = x->rightchildren;
		}
		else
		{
			break;
		}
	}
}
template<typename T, typename R> void travIn_I3(BinNode<T>* x, R& visit)
{
	bool backtrack = false;
	while (true)
	{
		if (!backtrack&&HasLChild(*x))
		{
			x = x->leftchildren;
		}
		else
		{
			visit(x->data);
			if (HasRChild(*x))
			{
				x = x->rightchildren;
				backtrack = false;
			}
			else
			{
				if (!(x = x->next()))
				{
					break;
				}
				backtrack = true;
			}
		}
	}
}
template<typename T>static void gotoHLVFL(Stack<BinNode<T>*>& s)
{
	while (BinNode<T>* x = s.top())
	{
		if (HasLChild(*x))
		{
			if (HasRChild(*x))
			{
				s.push(x->rightchildren);
			}
			s.push(x->leftchildren);
		}
		else
		{
			s.push(x->rightchildren);
		}
	}
	s.pop();
}
template<typename T, typename R>void travPost_I(BinNode<T>* x, R& visit)
{
	Stack<BinNode<T>*> s;
	if (x)
	{
		s.push(x);
	}
	while (!s.empty())
	{
		if (s.top() != x->parent)
		{
			gotoHLVFL(s);
		}
		x = s.pop();
		visit(x->data);
	}
}
template<typename T> template<typename R> void BinNode<T>::travLevel(R& visit)
{
	Queue<BinNode<T>*> q;
	q.enqueue(this);
	while (!q.empty())
	{
		BinNode<T>* x = q.dequeue();
		visit(x->data);
		if (HasLChild(*x))
		{
			q.enqueue(x->leftchildren);
		}
		if (HasRChild(*x))
		{
			q.enqueue(x->rightchildren);
		}
	}
}

