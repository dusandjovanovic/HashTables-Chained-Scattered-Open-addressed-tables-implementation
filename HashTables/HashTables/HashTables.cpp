// HashTables.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hashObject.h"
#include "chainedHashTable.h"

int main()
{
	chainedTable<int, double> table(100);
	hashObject<int, double> hash1(11, new double(22.25));
	table.insert(&hash1);

	system("pause");
    return 0;
}

