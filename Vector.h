#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>
template<typename T> class Vector
{
protected:
	int Size;
	int capacity;
	T* element;
	void copy(const T* a, int beg, int end);
	void expand();
	void shrink();
	bool bubble(int low, int high);
	void bubble_sort(int beg, int end);
	//int max(int beg, int end);
	//void selection_sort(int beg, int end);
	void merge(int low, int mid, int high);
	void merge_sort(int beg, int end);
	//int partition(int beg, int end);
	//void quicksort(int beg, int end);
	//void heapsort(int beg, int end);
public:
	Vector(int cap = 1, int s = 0, T v = 0)
	{
		capacity = cap;
		element = new T[capacity];
		for (Size = 0;Size < s;Size++)
		{
			element[Size] = v;
		}
	};
	Vector(const T* A, int n)
	{
		copy(A, 0, n);
	};
	Vector(const T* A, int beg, int end)
	{
		copy(A, beg, end);
	};
	Vector(const Vector<T>& v)
	{
		copy(v.element, 0, v.Size);
	};
	Vector(const Vector<T>& v, int low, int high)
	{
		copy(v.element, low, high);
	};
	~Vector()
	{
		delete[] element;
	}
	int size() const
	{
		return Size;
	}
	bool empty() const
	{
		return !Size;
	}
	int disordered() const;
	int find(const T e) const//for unodered
	{
		return find(e, 0, Size);
	}
	int find(const T e, int beg, int end) const;//for unordered
	T& operator[](int r) const;
	Vector<T> operator=(const Vector<T>& Vec);
	T remove(int r);
	int remove(int low, int high);
	int insert(const T e, int pos);
	int insert(const T e)
	{
		return insert(e, Size);
	}
	//void sort(int beg, int end);
	/*
	void sort()
	{
		sort(0, Size);
	}
	*/
	void unsort(int beg, int end);
	void unsort()
	{
		unsort(0, Size);
	}
	int deduplicate();//for unordered vector
	int uniquify();//for ordered vector
	int search(const T e, int beg, int end) const;//for ordered vector
	//void traverse(void(*)(T&));
	template<typename S> void traverse(S&);
};

template<typename T> void Vector<T>::copy(const T* A, int beg, int end)
{
	capacity = 2 * (end - beg);
	Size = 0;
	element = new T[capacity];
	while (beg != end)
	{
		element[Size++] = A[beg++];
	}
}
template<typename T> Vector<T> Vector<T>::operator=(const Vector<T>& Vec)
{
	if (element)
	{
		delete[] element;
	}
	copy(Vec.element, 0, Vec.Size());
	return *this;
}
template<typename T> void Vector<T>::expand()
{
	if (Size < capacity)
	{
		;
	}
	else
	{
		capacity <<= 1;
		T* oldelem = element;
		element = new T[capacity];
		for (int i = 0;i < Size;i++)
		{
			element[i] = oldelem[i];
		}
		delete[] oldelem;
	}
}
template<typename T> void Vector<T>::shrink()
{
	if (Size < capacity / 4)
	{
		T* oldelem = element;
		element = new T[capacity >>= 1];
		for (int i = 0;i < Size;i++)
		{
			element[i] = oldelem[i];
		}
		delete[] oldelem;
	}
}
template<typename T> T& Vector<T>::operator[](int r) const
{
	return element[r];
}
template<typename T> void Vector<T>::unsort(int beg, int end)
{
	static std::default_random_engine e(time(0));
	static std::uniform_int_distribution<unsigned> ran(beg, end - 1);
	for (int i = end - 1;i >= beg;i--)
	{
		swap(element[i], element[ran(e)]);
	}
}
template<typename T> int Vector<T>::find(const T e, int beg, int end) const//从后往前找，排序最靠后的那个元素首先被找到
{
	for (int i = end - 1;i >= beg;i--)
	{
		if (element[i] == e)
		{
			return i;
		}
	}
	return -1;
}
template<typename T> int Vector<T>::insert(const T e, int pos)
{
	expand();
	Size++;
	for (int i = pos + 1;i < Size;i++)
	{
		elem[i] = elem[i - 1];
	}
	elem[pos] = e;
	return pos;
}
template<typename T> int Vector<T>::remove(int beg, int end)
{
	if (beg == end)
	{
		return 0;
	}
	while (end < Size)
	{
		element[beg++] = element[end++];
	}
	Size = beg;
	shrink();
	return end - beg;
}
template<typename T> T Vector<T>::remove(int r)
{
	T e = element[r];
	remove(r, r + 1);
	return e;
}
template<typename T> int Vector<T>::deduplicate()//used for disordered vector
{
	int oldsize = Size;
	int i = 1;
	while (i < Size)
	{
		(find(element[i], 0, i) < 0) ? i++ : remove(i);
	}
	return oldsize - Size;
}
template<typename T> void Vector<T>::traverse(void(*func)(T&))
{
	for (int i = 0;i < Size;i++)
	{
		func(element[i]);
	}
}
template<typename T> template<typename S> void Vector<T>::traverse(S& func)
{
	for (int i = 0;i < Size;i++)
	{
		func(element[i]);
	}
}
template<typename T> struct Increase
{
	virtual void operator()(T& e) { e++; };
};
template<typename T> void increase(Vector<T>& v)
{
	v.traverse(Increase<T>());
}
template<typename T> int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1;i < Size;i++)
	{
		if (element[i] < element[i - 1])
		{
			n++;
		}
	}
	return n;//n=0:ordered, n>0:disordered
}
/*
template<typename T> int Vector<T>::uniquify()//used for ordered vector, low efficiency
{
int oldsize = Size;
int i = 1;
while (i < Size)
{
element[i] == element[i - 1] ? remove(i) : i++;
}
return oldsize - Size;
}
*/
template<typename T> int Vector<T>::uniquify()//used for ordered vector, high efficiency
{
	int i = 0, j = 0;
	while (j < Size)
	{
		if (element[i] != element[j])
		{
			element[++i] = element[j];
		}
		j++;
	}
	Size = ++i;
	shrink();
	return j - 1;
}
template<typename T> int Vector<T>::search(const T e, int beg, int end) const
{
	static std::default_random_engine e(time(0));
	static std::uniform_int_distribution<unsigned> ran(0, 9);
	return (ran(e) % 2) ? binsearch(element, e, beg, end) : fibsearch(element, e, beg, end);
}
/*
template<typename T> int binsearch(T* elem, const T e, int beg, int end)
{
while (beg < end)
{
int mid = (beg + end) >> 1;
if (elem[mid]>e)
{
end = mid;
}
else if (elem[mid] < e)
{
beg = mid + 1;
}
else
{
return mid;
}
}
return -1;
}

template<typename T> int binsearch(T* elem, const T e, int beg, int end)
{
while (beg - end > 1)
{
int mid = (beg + end) >> 1;
if (elem[mid] > e)
{
end = mid;
}
else
{
beg = mid;
}
}
return (elem[beg] == e) ? beg : -1;
}
*/
template<typename T> int binsearch(T* elem, const T e, int beg, int end)
{
	while (beg<end)
	{
		int mid = (beg + end) >> 1;
		if (elem[mid] > e)
		{
			end = mid;
		}
		else
		{
			beg = mid + 1;
		}
	}
	return --beg;
}
template<typename T> bool Vector<T>::bubble(int beg, int end)
{
	bool sorted = true;
	while (beg < end)
	{
		beg++;
		if (element[beg - 1]>element[beg])
		{
			sorted = false;
			swap(element[beg - 1], element[beg]);
		}
	}
	return sorted;
}
template<typename T> void Vector<T>::bubble_sort(int beg, int end)
{
	while (!bubble(beg, end--));
}
template<typename T> void Vector<T>::merge_sort(int beg, int end)
{
	if (end - beg < 2)
	{
		return;
	}
	int mid = (beg + end) >> 1;
	merge_sort(beg, mid);
	merge_sort(mid, end);
	merge(beg, mid, end);
}
template<typename T> void Vector<T>::merge(int beg, int mid, int end)
{
	T* a = element + beg;
	T* b = new T[mid - beg];
	for (int i = 0;i < mid - beg;i++)
	{
		b[i] = a[i];
	}
	T* c = element + mid;
	for (int i = 0, j = 0, k = 0;j < mid - beg || k < end - mid;)
	{
		if ((j < mid - beg) && (!(k < end - mid) || (b[j] <= c[k])))
		{
			a[i++] = b[j++];
		}
		if ((k < end - mid) && (!(j < mid - beg) || (c[k] < b[j])))
		{
			a[i++] = c[k++];
		}
	}
	delete[] b;
}

