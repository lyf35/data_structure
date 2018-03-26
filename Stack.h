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
		if (solution.size() >= n || n <= q.y)//代表当前行里面出界
		{
			q = solution.pop();//回溯
			q.y++;//试探前一行的下一列
		}
		else//在当前行里面未出界
		{
			while (q.y < n&&solution.find(q) >= 0)//调用find函数的时候已经相当于比较过了，如果可以放置皇后则find的返回值是-1
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