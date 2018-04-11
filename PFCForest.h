#pragma once
#include<iostream>
#include<fstream>
#include<memory>
#include"BinTree.h"
#include"Vector.h"

typedef BinTree<char> PFCTree;
typedef Vector<PFCTree*> PFCForest;


/*
PFCForest* forest = initforest();
PFCTree* tree = generateTree(forest);
release(forest);
PFCTable* table = generateTable(tree);
for (int i = 0;i < argc;i++)
{
Bitmap codeString;
int n = encode(table, codeString, argv[i]);
decode(tree, codeString, n);
}
release(table);
release(tree);
*/