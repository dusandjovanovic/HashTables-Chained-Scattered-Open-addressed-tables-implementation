// Lab0405.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hashTable.h"

int main()
{
	chainedTable table(100);
	hashObject forObj("for", "itterative for loop");
	hashObject whileObj("while", "itterative while loop");
	hashObject repeatObj("repeat-until", "itterative repeative loop until event happens");
	hashObject breakObj("break", "breaks loops");

	table.insert(forObj);
	table.insert(forObj);
	table.insert(forObj);
	table.insert(whileObj);
	table.insert(repeatObj);
	table.insert(breakObj);
	table.showAll();

	table.withdraw("for");

	cout << endl;
	table.find("while").showHashObject();

	system("pause");
	return 0;
}

