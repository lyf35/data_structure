#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>

int match(char* p, char* t)
{
	size_t n = strlen(t), i = 0; //文本串的长度
	size_t m = strlen(p), j = 0; //模式串，即待匹配串的长度
	while (j < m&&i < n)
	{
		if (t[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			i -= j - 1;
			j = 0;
		}
	}
	return i - j;
}

int match2(char* p, char* t) 
{
	size_t n = strlen(t), i = 0; //文本串的长度
	size_t m = strlen(p), j; //模式串，即待匹配串的长度
	for (i = 0;i < n - m + 1;i++)
	{
		for (j = 0;j < m;j++)
		{
			if (t[i + j] != p[j])
			{
				break;
			}
		}
		if (j >= m)
		{
			break;
		}
	}
	return i;
}

int match_kmp(char* p, char* t)
{
	int* next = buildnext(p);
	int n = (int)strlen(t), i = 0;
	int m = (int)strlen(p), j = 0;
	while (j < m&&i < n)
	{
		if (j < 0 || t[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	delete[] next;
	return i - j;
}

int* buildnext(char* p)
{
	size_t m = strlen(p), j = 0;
	int* n = new int[m];
	int t = n[0] = -1;
	while (j < m - 1)
	{
		if (t < 0 || p[j] == p[t])
		{
			j++;
			t++;
			n[j] = t;
		}
		else
		{
			t = n[t];
		}
	}
	return n;
}

int* buildnext_mod(char* p)
{
	size_t m = strlen(p), j = 0;
	int* n = new int[m];
	int t = n[0] = -1;
	while (j < m - 1)
	{
		if (t < 0 || p[j] == p[t])
		{
			j++;
			t++;
			n[j] = (p[j] != p[t] ? t : n[t]);
		}
		else
		{
			t = n[t];
		}
	}
	return n;
}

int match_bm(char* p, char* t)
{
	int* bc = buildbc(p);
	int* gs = buildgs(p);
	size_t i = 0;
	while (strlen(t) >= i + strlen(p))
	{
		int j = strlen(p) - 1;
		while (p[j] == t[i + j])
		{
			if (--j < 0)
			{
				break;
			}
		}
		if (j < 0)
		{
			break;
		}
		else
		{
			i += __max(gs[j], j - bc[t[i + j]]);
		}
	}
	delete[] gs;
	delete[] bc;
	return i;
}

int* buildbc(char* p)
{
	int* bc = new int[256];
	for (size_t j = 0;j < 256;j++)
	{
		bc[j] = -1;
	}
	for (size_t m = strlen(p), j = 0;j < m;j++)
	{
		bc[p[j]] = j;
	}
	return bc;
}

int* buildss(char* p)
{
	int m = strlen(p);
	int* ss = new int[m];
	ss[m - 1] = m;
	for (int lo = m - 1, hi = m - 1, j = lo - 1;j >= 0;j--)
	{
		if ((lo < j) && (ss[m - hi + j - 1] <= j - lo))
		{
			ss[j] = ss[m - hi + j - 1];
		}
		else
		{
			hi = j;
			lo = __min(lo, hi);
			while ((lo >= 0) && (p[lo] == p[m - hi + lo - 1]))
			{
				lo--;
			}
			ss[j] = hi - lo;
		}
	}
	return ss;
}

int* buildgs(char* p)
{
	int* ss = buildss(p);
	size_t m = strlen(p);
	int* gs = new int[m];
	for (size_t j = 0;j < m;j++)
	{
		gs[j] = m;
	}
	for (size_t i = 0, j = m - 1;j < UINT_MAX;j--)
	{
		if (j + 1 == ss[j])
		{
			while (i < m - j - 1)
			{
				gs[i++] = m - j - 1;
			}
		}
	}
	for (size_t j = 0;j < m - 1;j++)
	{
		gs[m - ss[j] - 1] = m - j - 1;
	}
	delete[] ss;
	return gs;
}