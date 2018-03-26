#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Vector.h"

template<typename T> class Queue :public List<T>
{
public:
	void enqueue(const T e)
	{
		insert_last(e);
	}
	T dequeue()
	{
		return remove(first());
	}
	T& front()
	{
		return first()->data;
	}
};