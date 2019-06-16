#include "tree.h"
#include "Address.h"
#include <iostream>
#include <string>
#include <stdlib.h>

//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
BinaryTree::BinaryTree()
{
	Root = NULL;
}

//-----------------------------------------------------------
// Copy constructor helper function.
//-----------------------------------------------------------
void BinaryTree::CopyHelper(Node * Tree1, Node * &Tree2)
{
	// Check terminating condition
	if (Tree1 == NULL)
		Tree2 = NULL;

	// Copy node and it's children
	else
	{
		Tree2 = new Node;
		Tree2->street = Tree1->street;
		CopyHelper(Tree1->Left, Tree2->Left);
		CopyHelper(Tree1->Right, Tree2->Right);
	}
}

//-----------------------------------------------------------
// Copy constructor.
//-----------------------------------------------------------
BinaryTree::BinaryTree(const BinaryTree & B)
{
	// Call tree copy function
	CopyHelper(B.Root, Root);
}

//-----------------------------------------------------------
// Destructor function helper function.
//-----------------------------------------------------------
void BinaryTree::DestroyHelper(Node * Tree)
{
	// Delete node and it's children
	if (Tree != NULL)
	{
		DestroyHelper(Tree->Left);
		DestroyHelper(Tree->Right);
		delete Tree;
	}
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
BinaryTree::~BinaryTree()
{
	// Call tree destroy function
	DestroyHelper(Root);
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool BinaryTree::SearchHelper(AddressBinaryTree &AddressTree, string street, Node * Tree)
{
	// Data value not found 
	if (Tree == NULL)
		return false;

	// Data value found 
	else if (Tree->street == street)
	{
		street = Tree->street;
		return true;
	}

	// Recursively search for data value
	else if (Tree->street > street)
		return (SearchHelper(AddressTree, street, Tree->Left));
	else if (Tree->street < street)
		return (SearchHelper(AddressTree, street, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Search(AddressBinaryTree &AddressTree, string street)
{
	// Call tree searching function
	return (SearchHelper(AddressTree, street, Root));
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool BinaryTree::SearchHelper(AddressBinaryTree &AddressTree, string street, Node * Tree, Node *& Tree2)
{
	bool Result;
	Tree2 = Tree;
	// Data value not found 
	if (Tree == NULL)
		return false;

	// Data value found 
	else if (Tree->street == street)
	{
		Tree2 = Tree;
		return true;
	}

	// Recursively search for data value
	else if (Tree->street > street)
	{
		Result = (SearchHelper(AddressTree, street, Tree->Left, Tree2));
		return Result;
	}
	else if (Tree->street < street)
	{
		Result = (SearchHelper(AddressTree, street, Tree->Right, Tree2));
		return Result;
	}
	else
		return false;
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Search(AddressBinaryTree &AddressTree, string street, Node *& Tree2)
{
	// Call tree searching function
	return (SearchHelper(AddressTree, street, Root, Tree2));
}

//-----------------------------------------------------------
// Insert helper function.
//-----------------------------------------------------------
bool BinaryTree::InsertHelper(Address address, string street, Node *& Tree)
{
	// Insert key and value into the tree
	if (Tree == NULL)
	{
		Tree = new Node;
		Tree->street = street;
		Tree->tree.AddressInsert(address, address.getHouseNumber());
		Tree->Left = NULL;
		Tree->Right = NULL;
		return true;
	}

	// Update value if key found
	else if (Tree->street == street)
	{
		Tree->street = street;
		Tree->tree.AddressInsert(address, address.getHouseNumber());
		return true;
	}

	// Recursively search for insertion position
	else if (Tree->street > street)
		return (InsertHelper(address, street, Tree->Left));
	else if (Tree->street <= street)
		return (InsertHelper(address, street, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Insert data into the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Insert(Address address, string street)
{
	// Call tree insertion function
	return (InsertHelper(address, street, Root));
}

//-----------------------------------------------------------
// Delete a single node from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::DeleteNode(Node *& Tree)
{
	Node *Temp = Tree;

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
		Node *Parent = Tree;
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
		Tree->street = Temp->street;
	}

	// Delete node
	delete Temp;
	return true;
}

//-----------------------------------------------------------
// Delete helper function.
//-----------------------------------------------------------
bool BinaryTree::DeleteHelper(string street, Node *& Tree)
{
	// Data value not found
	if (Tree == NULL)
		return false;

	// Data value found and deleted
	else if (Tree->street == street)
		return (DeleteNode(Tree));

	// Recursively search for node to delete
	else if (Tree->street > street)
		return (DeleteHelper(street, Tree->Left));
	else if (Tree->street < street)
		return (DeleteHelper(street, Tree->Right));
	else
		return false;
}

//-----------------------------------------------------------
// Delete data from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Delete(string street)
{
	// Call tree deletion function
	return (DeleteHelper(street, Root));
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void BinaryTree::PrintHelper(Node * Tree)
{
	// Check terminating condition
	if (Tree != NULL)
	{
		// Print left subtree
		PrintHelper(Tree->Left);

		// Print node value
		cout << "(" << Tree->street << ")\n";

		// Print right subtree
		PrintHelper(Tree->Right);
	}
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void BinaryTree::Print()
{
	// Call tree printing function
	PrintHelper(Root);
	cout << endl;
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void BinaryTree::PrintHelper(Node * Tree, ofstream & dout)
{
	// Check terminating condition
	if (Tree != NULL)
	{
		// Print left subtree
		PrintHelper(Tree->Left, dout);

		// Print node value
		dout << "(" << Tree->street << ") ";

		// Print right subtree
		PrintHelper(Tree->Right, dout);
	}
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void BinaryTree::Print(ofstream & dout)
{
	// Call tree printing function
	PrintHelper(Root, dout);
	dout << endl;
}

AddressBinaryTree BinaryTree::getTree(AddressBinaryTree &AddressTree, string street)
{
	Node * Tree2 = new Node;
	Tree2 = Root;
	if (Search(AddressTree, street, Tree2) == 1)
	{
		return Tree2->tree;
	}
	else
	{
		return Tree2->tree;
	}
}