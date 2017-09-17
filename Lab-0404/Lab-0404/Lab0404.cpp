// Lab0404.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hashTable.h"

int main()
{
	chainedTable table(1000);
	hashObject obj1(1234567, "first person added");
	hashObject obj2(5672310, "second person added");
	hashObject obj3(9921873, "third person added");

	hashObject obj4(1000111, "colision first");
	hashObject obj5(1001110, "colision second");

	table.insert(obj1);
	table.insert(obj2);
	table.insert(obj3);
	table.insert(obj4);
	table.insert(obj5);
	table.showAll();

	cout << endl;
	table.withdraw(1000111);
	table.withdraw(1000111);
	table.showAll();

	cout << endl;
	(table.find(1234567)).showHashObject();

	system("pause");
	return 0;
}

