#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Vector.h"

template<typename T> struct PQ
{
	virtual void insert(T) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};
template<typename T> class PQ_ComplHeap :public PQ<T>, public Vector<T>
{
protected:
	int percolateDown(int n, int i);
	int percolateUp(int i);
	void heapify(int n);
public:
	PQ_ComplHeap(T* A, int n)
	{
		copyFrom(A, 0, n);
		heapify(n);
	}
	void insert(T);
	T getMax()
	{
		return element[0];
	}
	T delMax();
};

template<typename T> void PQ_ComplHeap<T>::insert(T e)
{
	Vector<T>::insert(e);
	percolateUp(Size - 1);
}
template<typename T> int PQ_ComplHeap<T>::percolateUp(int i)
{
	while (ParentValid(i))
	{
		int j = Parent(i);
		if (lt(element[i], element[j]))
		{
			break;
		}
		swap(element[i], element[j]);
		i = j;
	}
	return i;
}
template<typename T> T PQ_ComplHeap<T>::delMax()
{
	T maxElem = element[0];
	element[0] = element[--size];
	percolateDown(Size, 0);
	return maxElem;
}
template<typename T> int PQ_ComplHeap<T>::percolateDown(int n, int i)
{
	int j;
	while (i != (j = ProperParent(element, n, i)))
	{
		swap(elememt[i], element[j]);
		i = j;
	}
	return i;
}
