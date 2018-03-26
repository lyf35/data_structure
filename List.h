#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>

template<typename T> struct Listnode
{
	T data;
	Listnode<T>* prev;
	Listnode<T>* next;
	Listnode() {};
	Listnode(T e, Listnode<T>* p = NULL, Listnode<T>* n = NULL) :data(e), prev(p), next(n) {};
	Listnode<T>* insertPrev(const T e);
	Listnode<T>* insertNext(const T e);
};
template<typename T> class List
{
private:
	int Size;
	Listnode<T>* header;
	Listnode<T>* trailer;
protected:
	void init();
	int clear();
	void copyNodes(Listnode<T>*, int);
	void merge(Listnode<T>*&, int, List<T>&, Listnode<T>*, int);
	void mergesort(Listnode<T>*&, int);
	void selectionsort(Listnode<T>*, int);
	void insertionsort(Listnode<T>*, int);
public:
	List() { init(); }
	List(const List<T> L);
	List(const List<T> l, int r, int n);
	List(Listnode<T>* p, int n);
	~List();
	int size() const
	{
		return Size;
	}
	bool empty() const
	{
		return Size <= 0;
	}
	T& operator[](int r) const;
	Listnode<T>* first() const
	{
		return header->next;
	}
	Listnode<T>* last() const
	{
		return trailer->prev;
	}
	bool valid(Listnode<T>* p)
	{
		return p && (trailer != p&&header != p);
	}
	//int disordered() const;
	Listnode<T>* find(const T e) const//disordered
	{
		return find(e, Size, trailer);
	}
	Listnode<T>* find(const T e, int n, Listnode<T>* p) const;
	Listnode<T>* search(const T e) const
	{
		return search(e, Size, trailer);
	}
	Listnode<T>* search(const T e, int n, Listnode<T>* p) const;
	Listnode<T>* selectmax(Listnode<T>* p, int n);
	Listnode<T>* selectmax()
	{
		return selectmax(header->next, Size);
	}
	Listnode<T>* insert_first(const T e);
	Listnode<T>* insert_last(const T e);
	Listnode<T>* insert_before(Listnode<T>* p, const T e);
	Listnode<T>* insert_after(Listnode<T>* p, const T e);
	T remove(Listnode<T>* p);
	void merge(List<T>& l)
	{
		merge(first(), Size, l, l.first(), l.Size);
	}
	//void sort(Listnode<T>* p, int n);
	/*
	void sort()
	{
		sort(first(), Size);
	}
	*/
	int deduplicate();
	void traverse(void(*visit)(T &));
	int uniquify();
	//void reverse();
	template<typename W> void traverse(W&);
};

template<typename T> void List<T>::init()
{
	header = new Listnode<T>;
	trailer = new Listnode<T>;
	header->next = trailer;
	header->prev = NULL;
	trailer->prev = header;
	trailer->next = NULL;
	Size = 0;
}
template<typename T> T& List<T>::operator[](int r) const
{
	Listnode<T>* p = first();
	while (r > 0)
	{
		p = p->next;
		r--;
	}
	return p->data;
}
template<typename T> Listnode<T>* List<T>::find(const T e, int n, Listnode<T>* p) const
{
	while (n > 0)
	{
		if (e == ((p = p->prev)->data))
		{
			return p;
		}
		n--;
	}
	return NULL;
}
template<typename T> Listnode<T>* List<T>::insert_first(const T e)
{
	Size++;
	return header->insertNext(e);
}
template<typename T> Listnode<T>* List<T>::insert_last(const T e)
{
	Size++;
	return trailer->insertPrev(e);
}
template<typename T> Listnode<T>* List<T>::insert_after(Listnode<T>* p, const T e)
{
	Size++;
	return p->insertNext(e);
}
template<typename T> Listnode<T>* List<T>::insert_before(Listnode<T>* p, const T e)
{
	Size++;
	return p->insertPrev(e);
}
template<typename T> Listnode<T>* Listnode<T>::insertPrev(const T e)
{
	Listnode<T>* x = new Listnode<T>(e, prev, this);
	prev->next = x;
	prev = x;
	return x;
}
template<typename T> Listnode<T>* Listnode<T>::insertNext(const T e)
{
	Listnode<T>* x = new Listnode<T>(e, this, next);
	next->prev = x;
	next = x;
	return x;
}
template<typename T> void List<T>::copyNodes(Listnode<T>* p, int n)//n is the number of nodes after p
{
	init();
	while (n--)
	{
		insert_last(p->data);
		p = p->next;
	}
}
template<typename T> List<T>::List(Listnode<T>* p, int n) { copyNodes(p, n); };
template<typename T> List<T>::List(const List<T> l) { copyNodes(l.first(), l.Size()); };
template<typename T> List<T>::List(const List<T> l,int r, int n) { copyNodes(l[r], n); };
template<typename T> T List<T>::remove(Listnode<T>* p)
{
	T e = p->data;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	Size--;
	return e;
}
template<typename T> List<T>::~List<T>()
{
	clear();
	delete header;
	delete trailer;
}
template<typename T> int List<T>::clear()
{
	int oldsize = Size;
	while (Size > 0)
	{
		remove(header->next);
	}
	return oldsize;
}
template<typename T> int List<T>::deduplicate()//for unordered list
{
	if (Size < 2)
	{
		return 0;
	}
	int oldsize = Size;
	Listnode<T>* p = header;
	int r = 0;
	while (trailer != (p = (p->next)))
	{
		Listnode<T>* q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldsize - Size;
}
template<typename T> void List<T>::traverse(void(*visit)(T&))
{
	for (Listnode<T>* p = header->next;p != trailer;p = p->next)
	{
		visit(p->data);
	}
}
template<typename T> template<typename W> void List<T>::traverse(W& visit)
{
	for (Listnode<T>* p = header->next;p != trailer;p = p->next)
	{
		visit(p->data);
	}
}
template<typename T> int List<T>::uniquify()//for ordered list
{
	if (Size < 0)
	{
		return 0;
	}
	int oldsize = Size;
	Listnode<T>* p = first();
	Listnode<T>* q;
	while (trailer != (q = p->next))
	{
		if (p->data != q->data)
		{
			p = q;
		}
		else
		{
			remove(q);
		}
	}
	return oldsize - Size;
}
template<typename T> Listnode<T>* List<T>::search(const T e, int n, Listnode<T>* p) const //search n elements before pointer p 
{
	while (n >= 0)
	{
		if (((p = p->prev)->data) <= e)
		{
			break;
		}
	}
	return p;
}
template<typename T> void List<T>::insertionsort(Listnode<T>* p, int n)//p is starting position
{
	for (int r = 0;r < n;r++)
	{
		insert_before(search(p->data, r, p), p->data);
		p = p->next;
		remove(p->prev);
	}
}
template<typename T> void List<T>::selectionsort(Listnode<T>* p, int n)//p is starting position
{
	Listnode<T>* head = p->prev;
	Listnode<T>* tail = p; //the position to be inserted before
	for (int i = 0;i < n;i++)
	{
		tail = tail->next;
	}
	while (n > 1)
	{
		Listnode<T>* max = selectmax(head->next, n);
		insert_before(tail, remove(max));
		tail = tail->prev;
		n--;
	}
}
template<typename T> Listnode<T>* List<T>::selectmax(Listnode<T>* p, int n)
{
	Listnode<T>* max = p;
	for (Listnode<T>* curr = p, n > 1, n--)
	{
		if ((curr = curr->next)->data >= max->data)
		{
			max = curr;
		}
	}
	return max;
}
template<typename T> void List<T>::merge(Listnode<T>*& p, int n, List<T>& l, Listnode<T>* q, int m)
{
	Listnode<T>* pp = p->prev;
	while (m > 0)
	{
		if (n > 0 && (p->data <= q->data))
		{
			if ((q == (p == p->next)))
			{
				break;
			}
			n--;
		}
		else
		{
			insert_after(p, l.remove((q = q->next)->prev));
			m--;
		}
	}
}
template<typename T> void List<T>::mergesort(Listnode<T>*& p, int n)
{
	if (n < 2)
	{
		return;
	}
	int m = n >> 1;
	Listnode<T>* q = p;
	for (int i = 0;i < m;i++)
	{
		q = q->next;
	}
	mergesort(p, m);
	mergesort(q, n - m);
	merge(p, m, *this, q, n - m);
}