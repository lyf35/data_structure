#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
#include"Vector.h"

template<typename T> class Stack :public Vector<T>
{
public:
	void push(const T e)
	{
		insert(Size(), e);
	}
	T pop()
	{
		return remove(Size() - 1);
	}
	T& top()
	{
		return (*this)[Size() - 1];
	}
};

void convert(Stack<char>& s, int n, int base)
{
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		int remainder = (int)(n%base);
		s.push(digit[remainder]);
		n /= base;
	}
}

struct queen
{
	int x, y;
	queen(int pos_x, int pos_y) :x(pos_x), y(pos_y) {};
	bool operator==(const queen q) const
	{
		if (x == q.x || y == q.y || (x + y) == (q.x + q.y) || (x - y) == (q.x - q.y))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	bool operator !=(const queen q) const
	{
		return !(*this == q);
	}
};
void placequeens(int n)
{
	Stack<queen> solution;
	queen q(0, 0);
	int nCheck = 0;
	int nSolution = 0;
	while (q.x > 0 || q.y < n)
	{
		if (solution.size() >= n || n <= q.y)//����ǰ���������
		{
			q = solution.pop();//����
			q.y++;//��̽ǰһ�е���һ��
		}
		else//�ڵ�ǰ������δ����
		{
			while (q.y < n&&solution.find(q) >= 0)//����find������ʱ���Ѿ��൱�ڱȽϹ��ˣ�������Է��ûʺ���find�ķ���ֵ��-1
			{
				q.y++;
				nCheck++;
			}
			if (n > q.y)
			{
				solution.push(q);
				if (n <= solution.size())
				{
					nSolution++;
				}
				q.x++;
				q.y = 0;
			}
		}
	}
}