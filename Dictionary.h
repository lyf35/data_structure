#pragma once
#include<iostream>
#include<memory>
#include<random>
#include<ctime>

template<typename K, typename V> struct Entry
{
	K key;
	V value;
	bool removed;
	Entry(K k = K(), V v = V()) :key(k), value(v) {};
	Entry<const Entry<K, V>> e):key(e.key), value(e.value){};
	bool operator<(const Entry < K, V >> e)return (key < e.key);
	bool operator>(const Entry < K, V >> e)return (key > e.key);
	bool operator==(const Entry < K, V >> e)return (key == e.key);
	bool operator!=(const Entry < K, V >> e)return (key != e.key);
};

template<typename K, typename V> struct Dictionary
{
	virtual int size() const = 0;
	virtual bool put(K, V) = 0;
	virtual V* get(K k) = 0;
	virtual bool remove(K k) = 0;
};

template<typename K, typename V> class Hashtable :public Dictionary<K, V>
{
private:
	Entry<K, V>** ht;
	int M;
	int N;
protected:
	int probeHit(const K& k);
	int probeFree(const K& k);
	void rehash();
public:
	Hashtable(int c = 5);
	~Hashtable();
	int size() const
	{
		return n;
	}
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
};

template<typename K, typename V> Hashtable<K, V>::Hashtable(int c)
{
	M = c;
	N = 0;
	ht = new Entry<K, V>*[M];
}
template<typename K, typename V> Hashtable<K, V>::~Hashtable()
{
	for (int i = 0;i < M;i++)
	{
		if (ht[i])
		{
			release(ht[i]);
		}
	}
	release(ht);
}
template<typename K, typename V> V* Hashtable<K, V>::get(K k)
{
	int r = probeHit(k);
	return ht[r] ? &(ht[r]->value) : NULL;
}
template<typename K, typename V> int Hashtable<K, V>::probeHit(const K& k)
{
	int r = hashCode(k) % M;
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && ht[r]->removed))
	{
		r = (r + 1) % M;
	}
	return r;
}
template<typename K, typename V> bool Hashtable<K, V>::remove(K k)
{
	int r = probeHit(k);
	if (!ht[r])
	{
		return false;
	}
	release(ht[r]);
	ht[r] = NULL;
	hr[r]->removed = 1;
	N--;
	return true;
}
template<typename K, typename V> bool Hashtable<K, V>::put(K k, V v)
{
	if (ht[probeHit(k)])
	{
		return false;
	}
	int r = probeFree(k);
	ht[r] = new Entry<K, V>(k, v);
	++N;
	if (N * 2 > M)
	{
		rehash();
	}
	return true;
}
template<typename K, typename V> int Hashtable<K, V>::probeFree(const K& k)
{
	int r = hashCode(k) % M;
	while (ht[r])
	{
		r = (r + 1) % M;
	}
	return r;
}
template<typename K, typename V> void Hashtable<K, V>::rehash()
{
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	M = 2 * M;
	N = 0;
	ht = new Entry<K, V>*[M];
	for (int i = 0;i < old_capacity;i++)
	{
		if (old_ht[i])
		{
			put(old_ht[i]->key, old_ht[i]->value);
		}
	}
	release(old_ht);
}
static size_t hashCode(char c)
{
	return (size_t)c;
}
static size_t hashCode(int k)
{
	return (size_t)k;
}
static size_t hashCode(long long i)
{
	return (size_t)((i >> 32) + (int)i);
}
static size_t hashCode(char s[])
{
	int h = 0;
	for (size_t n = strlen(s), i = 0;i < n;i++)
	{
		h = ((h << 5) | (h >> 27));
		h += (int)s[i];
	}
	return (size_t)h;
}