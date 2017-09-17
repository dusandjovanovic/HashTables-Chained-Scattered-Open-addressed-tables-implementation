#include "hashObject.h"

class chainedTable {
protected:
	unsigned int length;
	unsigned int count;

	LList<hashObject>* array;

	/* primary transformation */
	unsigned int h(hashObject object) {
		return f(object.getKey()) % length;
	}

	unsigned int f(int key) {
		/* extraction method.. */
		int lower = key % 1000;
		int higher = key / 1000;
		return (lower + higher);
	}

public:
	chainedTable(unsigned int newLength) {
		length = newLength;
		count = 0;
		array = new LList<hashObject>[length];
	}

	~chainedTable() {
		hashObject object;
		unsigned int i = 0;
		while (i < length) {
				if (array[i].isEmpty()) {
					i++;
					continue;
				}
				object = array[i].getHead();
				while (array[i].nextExists(object)) {
					object.deleteRecord();
					object = array[i].getNext(object);
				}
			i++;
		}
		delete[] array;
	}

	void showAll() {
		hashObject tmp;
		unsigned int i = 0;
		while (i < length) {
			if (!array[i].isEmpty()) {
				tmp = array[i].getHead();
				tmp.showHashObject();

				while (array[i].nextExists(tmp)) {
					tmp = array[i].getNext(tmp);
					tmp.showHashObject();
				}
				cout << endl;
			}
			i++;
		}
	}

	void insert(hashObject object) {
		array[h(object)].addToHead(object);
		count++;
	}

	void withdraw(hashObject object) {
		array[h(object)].deleteElement(object);
		count--;
	}

	void withdraw(int key) {
		hashObject found = find(key);
		withdraw(found);
	}

	hashObject find(int key) {
		hashObject object;
		unsigned int i = f(key) % length;
		if (array[i].isEmpty())
			throw new std::exception();

		object = array[i].getHead();
		while (!object.isEqualKey(key) && array[i].nextExists(object))
			object = array[i].getNext(object);
		return object;
	}

	unsigned int getLength() {
		return length;
	}

	double getLoadFactor() {
		return (double)count / (double)length;
	}
};