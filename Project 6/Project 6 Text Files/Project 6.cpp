#include <iostream>
#include <fstream>
#include <vector>
#include "Address.h"
#include "tree.h"
#include "AddressTree.h"
using namespace std;

int main()
{
	// Local variables
	float lat = 0;
	float lon = 0;
	int num = 0;
	int command = 0;
	int SearchHouse = 0;
	int StreetCount = 0;
	string street = "";
	string SearchStreet = "";
	string StreetTree = "";
	string PreviousStreet = "";
	Address address;
	Address SearchAddress;
	char ch = ' ';
	BinaryTree streets;
	AddressBinaryTree HouseTree;
	int count = 0;

	// Open input file
	ifstream din;
	din.open("input2.txt");

	// Loop reading address information
	while (din >> lat >> lon >> num)
	{
		// Skip space after num
		din.get(ch);

		// Read rest of line 
		getline(din, street);
		StreetTree = street;
		address.setLatitude(lat);
		address.setLongitude(lon);
		address.setHouseNumber(num);
		address.setStreetName(street);

		// Add to end of street vector
		if (StreetTree != PreviousStreet)
		{
			streets.Insert(address, StreetTree);
		}
		streets.getTree(HouseTree, StreetTree).AddressInsert(address, address.getHouseNumber());
		PreviousStreet = StreetTree;
		
	}

	while (command != 1)
	{
		command = 0;
		cout << "Please enter 1 if you would like to exit the program." << endl;
		cin >> command;
		if (command == 1)
		{
			return 0;
		}
		cout << "Please enter the street of the address you would like to find." << endl;
		getline(cin, street);
		while (streets.Search(HouseTree, street) == 0)
		{
			cout << "That street is not in our database please enter another one." << endl;
			getline(cin, street);
		}
		cout << "Please enter the house number of the address you would like to find." << endl;
		cin >> SearchHouse;
		while ((streets.getTree(HouseTree, street).AddressSearch(SearchHouse)) == 0)
		{
			cout << "That address is not in our database please enter another one." << endl;
			cin >> SearchHouse;
		}
		cout << "Here is the address you have searched for." << endl;
		streets.getTree(HouseTree, street).AddressSearchPrinter(SearchHouse);
	}
	
	
}
