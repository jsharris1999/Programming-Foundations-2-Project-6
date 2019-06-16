#include "AddressTree.h"
#include "Address.h"
#include <iostream>
#include <string>
#include <stdlib.h>

//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
AddressBinaryTree::AddressBinaryTree()
{
	Root = NULL;
}

//-----------------------------------------------------------
// Copy constructor helper function.
//-----------------------------------------------------------
void AddressBinaryTree::AddressCopyHelper(AddressNode * Tree1, AddressNode * &Tree2)
{
	// Check terminating condition
	if (Tree1 == NULL)
		Tree2 = NULL;

	// Copy node and it's children
	else
	{
		Tree2 = new AddressNode;
		Tree2->address = Tree1->address;
		AddressCopyHelper(Tree1->Left, Tree2->Left);
		AddressCopyHelper(Tree1->Right, Tree2->Right);
	}
}

//-----------------------------------------------------------
// Copy constructor.
//-----------------------------------------------------------
AddressBinaryTree::AddressBinaryTree(const AddressBinaryTree & B)
{
	// Call tree copy function
	AddressCopyHelper(B.Root, Root);
}

//-----------------------------------------------------------
// Destructor function helper function.
//-----------------------------------------------------------
void AddressBinaryTree::AddressDestroyHelper(AddressNode * Tree)
{
	// Delete node and it's children
	if (Tree != NULL)
	{
		AddressDestroyHelper(Tree->Left);
		AddressDestroyHelper(Tree->Right);
		delete Tree;
	}
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
AddressBinaryTree::~AddressBinaryTree()
{
	// Call tree destroy function
	AddressDestroyHelper(Root);
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressSearchHelper(int HouseNumber, AddressNode * Tree)
{
	// Data value not found 
	if (Tree == NULL)
		return false;

	// Data value found 
	else if (Tree->address.getHouseNumber() == HouseNumber)
	{
		HouseNumber = Tree->address.getHouseNumber();
		return true;
	}

	// Recursively search for data value
	else if (Tree->address.getHouseNumber() > HouseNumber)
		return (AddressSearchHelper(HouseNumber, Tree->Left));
	else if (Tree->address.getHouseNumber() < HouseNumber)
		return (AddressSearchHelper(HouseNumber, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressSearch(int HouseNumber)
{
	// Call tree searching function
	return (AddressSearchHelper(HouseNumber, Root));
}

//-----------------------------------------------------------
// Insert helper function.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressInsertHelper(Address address, int HouseNumber, AddressNode * &Tree)
{
	// Insert key and value into the tree
	if (Tree == NULL)
	{
		Tree = new AddressNode;
		Tree->address = address;
		Tree->Left = NULL;
		Tree->Right = NULL;
		return true;
	}

	// Update value if key found
	else if (Tree->address.getHouseNumber() == HouseNumber)
	{
		Tree->address = address;
		return true;
	}

	// Recursively search for insertion position
	else if (Tree->address.getHouseNumber() > HouseNumber)
		return (AddressInsertHelper(address, HouseNumber, Tree->Left));
	else if (Tree->address.getHouseNumber() <= HouseNumber)
		return (AddressInsertHelper(address, HouseNumber, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Insert data into the binary tree.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressInsert(Address address, int HouseNumber)
{
	// Call tree insertion function
	return (AddressInsertHelper(address, HouseNumber, Root));
}

//-----------------------------------------------------------
// Delete a single node from the binary tree.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressDeleteNode(AddressNode * &Tree)
{
	AddressNode *Temp = Tree;

	// Node has 0 children
	if ((Tree->Left == NULL) && (Tree->Right == NULL))
		Tree = NULL;

	// Node has 1 child
	else if (Tree->Left == NULL)
		Tree = Tree->Right;
	else if (Tree->Right == NULL)
		Tree = Tree->Left;


	// Node has 2 children
	else
	{
		// Find leftmost node in right subtree
		AddressNode *Parent = Tree;
		Temp = Tree->Right;
		while (Temp->Left != NULL)
		{
			Parent = Temp;
			Temp = Parent->Left;
		}

		// Replace deleted data with leftmost value
		if (Parent == Tree)
			Parent->Right = Temp->Right;
		else
			Parent->Left = Temp->Right;
		Tree->address = Temp->address;
	}

	// Delete node
	delete Temp;
	return true;
}

//-----------------------------------------------------------
// Delete helper function.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressDeleteHelper(int HouseNumber, AddressNode * &Tree)
{
	// Data value not found
	if (Tree == NULL)
		return false;

	// Data value found and deleted
	else if (Tree->address.getHouseNumber() == HouseNumber)
		return (AddressDeleteNode(Tree));

	// Recursively search for node to delete
	else if (Tree->address.getHouseNumber() > HouseNumber)
		return (AddressDeleteHelper(HouseNumber, Tree->Left));
	else if (Tree->address.getHouseNumber() < HouseNumber)
		return (AddressDeleteHelper(HouseNumber, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Delete data from the binary tree.
//-----------------------------------------------------------
bool AddressBinaryTree::AddressDelete(int HouseNumber)
{
	// Call tree deletion function
	return (AddressDeleteHelper(HouseNumber, Root));
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void AddressBinaryTree::AddressPrintHelper(AddressNode * Tree)
{
	// Check terminating condition
	if (Tree != NULL)
	{
		// Print left subtree
		AddressPrintHelper(Tree->Left);

		// Print node value
		cout << "(";
		Tree->address.print();
		cout << ")\n";

		// Print right subtree
		AddressPrintHelper(Tree->Right);
	}
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void AddressBinaryTree::AddressPrint()
{
	// Call tree printing function
	AddressPrintHelper(Root);
	cout << endl;
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void AddressBinaryTree::AddressPrintHelper(AddressNode * Tree, ofstream & dout)
{
	// Check terminating condition
	if (Tree != NULL)
	{
		// Print left subtree
		AddressPrintHelper(Tree->Left, dout);

		// Print node value
		dout << "("; 
		Tree->address.print();
		dout << ") ";

		// Print right subtree
		AddressPrintHelper(Tree->Right, dout);
	}
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void AddressBinaryTree::AddressPrint(ofstream & dout)
{
	// Call tree printing function
	AddressPrintHelper(Root, dout);
	dout << endl;
}

bool AddressBinaryTree::AddressSearchHelperPrinter(int HouseNumber, AddressNode * Tree)
{
	// Data value not found 
	if (Tree == NULL)
		return false;

	// Data value found 
	else if (Tree->address.getHouseNumber() == HouseNumber)
	{
		HouseNumber = Tree->address.getHouseNumber();
		Tree->address.print();
		return true;
	}

	// Recursively search for data value
	else if (Tree->address.getHouseNumber() > HouseNumber)
		return (AddressSearchHelperPrinter(HouseNumber, Tree->Left));
	else if (Tree->address.getHouseNumber() < HouseNumber)
		return (AddressSearchHelperPrinter(HouseNumber, Tree->Right));
	else
		return false;
}

bool AddressBinaryTree::AddressSearchPrinter(int HouseNumber)
{
	// Call tree searching function
	return (AddressSearchHelperPrinter(HouseNumber, Root));
}