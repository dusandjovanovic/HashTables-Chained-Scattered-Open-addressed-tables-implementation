// Lab0401.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hashTable.h"

int main()
{
	chainedTable table(30);
	char* forRecord = new char[20];
	forRecord = "itterative for loop";
	hashObject forObj("for", forRecord);
	hashObject whileObj("while", "itterative while loop");
	hashObject repeatObj("repeat-until", "itterative repeative loop until event happens");
	hashObject breakObj("break", "breaks loops");

	table.insert(forObj);
	table.insert(whileObj);
	table.insert(repeatObj);
	table.insert(breakObj);
	table.showAll();

    return 0;
}

