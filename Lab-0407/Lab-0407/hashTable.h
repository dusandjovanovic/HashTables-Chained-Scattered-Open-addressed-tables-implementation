#include "hashObject.h"

class scatteredTable {
protected:
	unsigned int length;
	unsigned int count;

	hashObject* array;

	unsigned int f(char* key) {
		unsigned int i = 0, result = 0;
		while (key[i] != 0) {
			result += pow(2, i)*key[i];
			i++;
		}
		return result;
	}

	/* primary transformation */
	unsigned int h(hashObject object) {
		return f(object.getKey()) % length;
	}

	/* secondary transformation */
	unsigned int g(unsigned int i) {
		return (i * 7) % length;
	}
public:
	scatteredTable(int newLength) {
		length = newLength;
		count = 0;
		array = new hashObject[length];
	}

	~scatteredTable() {
		delete[] array;
	}

	unsigned int findUnoccupied(hashObject object) {
		unsigned int hash = h(object);
		unsigned int probe = hash;
		if (array[probe].status < 2)
			return probe;
		else
			probe = g(probe);
		while (probe != hash)
			if (array[probe].status < 2)
				return probe;
			else
				probe = g(probe);
		if (probe != hash)
			return probe;
		else
			throw new std::exception();
	}

	long findMatch(char* key) {
		unsigned int hash = f(key) % length;
		unsigned int probe = hash;
		for (unsigned int i = 0; i < length; i++) {
			if (array[probe].status == 0)
				return -1;
			else if (array[probe].isEqualKey(key))
				return probe;
			probe = g(probe);
		}
		return -1;
	}

	hashObject find(char* key) {
		long offset = findMatch(key);
		if (offset != -1)
			return array[offset];
		else
			throw new std::exception();
	}

	void insert(hashObject object) {
		if (count == length)
			return;
		unsigned int offset = findUnoccupied(object);
		if (offset >= 0) {
			array[offset] = object;
			array[offset].status = 2;
			count++;
		}
	}

	void withdraw(hashObject object) {
		if (count == 0)
			return;
		unsigned int offset = findMatch(object.getKey());
		if (offset >= 0) {
			array[offset].deleteRecord();
			array[offset].status = 1;
			count--;
		}
	}

	unsigned int getLength() {
		return length;
	}

	double getLoadFactor() {
		return (double)count / (double)length;
	}

	void showAll() {
		for (unsigned int i = 0; i < length; i++)
			if (array[i].status == 2) {
				cout << ":" << i << " ";
				array[i].showHashObject();
				cout << endl;
			}
		cout << endl;
	}
};