#include <iostream>
#include <fstream>
#include "Address.h"
using namespace std;

#ifndef AddressNode_H
#define AddressNode_H

//-----------------------------------------------------------
// BinaryTree data node definition
//-----------------------------------------------------------
class AddressNode
{
public:
	Address address;
	AddressNode *Left;
	AddressNode *Right;
};
#endif


#ifndef AddressBinaryTree_H
#define AddressBinaryTree_H
//-----------------------------------------------------------
// Define the AddressBinaryTree class interface 
//-----------------------------------------------------------
class AddressBinaryTree
{
public:
	// Constructor functions
	AddressBinaryTree();
	AddressBinaryTree(const AddressBinaryTree & tree);
	~AddressBinaryTree();

	// General binary tree operations
	bool AddressSearch(int HouseNumber);
	bool AddressInsert(Address address, int HouseNumber);
	bool AddressDelete(int HouseNumber);
	void AddressPrint();
	void AddressPrint(ofstream & dout);
	bool AddressSearchPrinter(int HouseNumber);

private:
	// Helper functions
	void AddressCopyHelper(AddressNode * Tree1, AddressNode * &Tree2);
	void AddressDestroyHelper(AddressNode * Tree);
	bool AddressSearchHelper(int HouseNumber, AddressNode * Tree);
	bool AddressInsertHelper(Address address, int HouseNumber, AddressNode * &Tree);
	bool AddressDeleteNode(AddressNode * &Tree);
	bool AddressDeleteHelper(int HouseNumber, AddressNode * &Tree);
	void AddressPrintHelper(AddressNode * Tree);
	void AddressPrintHelper(AddressNode * Tree, ofstream & dout);
	bool AddressSearchHelperPrinter(int HouseNumber, AddressNode * Tree);

	// Tree pointer
	AddressNode *Root;
};
#endif