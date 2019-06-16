#include <iostream>
#include <fstream>
#include "Address.h"
#include "AddressTree.h"
using namespace std;

//-----------------------------------------------------------
// BinaryTree data node definition
//-----------------------------------------------------------
class Node
{
public:
	string street;
	AddressBinaryTree tree;
	Node *Left;
	Node *Right;
};

//-----------------------------------------------------------
// Define the BinaryTree class interface 
//-----------------------------------------------------------
class BinaryTree
{
public:
	// Constructor functions
	BinaryTree();
	BinaryTree(const BinaryTree & tree);
	~BinaryTree();

	// General binary tree operations
	bool Search(AddressBinaryTree &AddressTree, string street);
	bool Search(AddressBinaryTree &AddressTree, string street, Node * &Tree2);
	bool Insert(Address address, string street);
	bool Delete(string street);
	void Print();
	void Print(ofstream & dout);
	AddressBinaryTree getTree(AddressBinaryTree &AddressTree, string street);

private:
	// Helper functions
	void CopyHelper(Node * Tree1, Node * &Tree2);
	void DestroyHelper(Node * Tree);
	bool SearchHelper(AddressBinaryTree &AddressTree, string street, Node * Tree);
	bool SearchHelper(AddressBinaryTree &AddressTree, string street, Node * Tree, Node *& Tree2);
	bool InsertHelper(Address address, string street, Node * &Tree);
	bool DeleteNode(Node * &Tree);
	bool DeleteHelper(string street, Node * &Tree);
	void PrintHelper(Node * Tree);
	void PrintHelper(Node * Tree, ofstream & dout);
	AddressBinaryTree getTreeHelper(AddressBinaryTree &AddressTree, string street, Node * Tree);

	// Tree pointer
	Node *Root;
};