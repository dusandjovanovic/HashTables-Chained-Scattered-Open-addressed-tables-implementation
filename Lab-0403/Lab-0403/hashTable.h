#include "hashObject.h"

class chainedTable {
protected:
	unsigned int length;
	unsigned int count;

	hashObject* array;

	unsigned int f(char* key) {
		unsigned int result = 0, i = 0;
		while (key[i] != 0) {
			result += key[i]*pow(2, i);
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
		return (i + 1) % length;
	}
public:
	chainedTable(int newLength) {
		length = newLength;
		count = 0;
		array = new hashObject[length];
	}

	~chainedTable() {
		delete[] array;
	}

	void insert(hashObject object) {
		if (count == length) {
			cout << "Table full..";
			return;
		}
			
		long probe = h(object);

		if (!array[probe].free()) {
			while (array[probe].next != -1)
				probe = array[probe].next;
			long tail = probe;	/* last element in line of synonyms linked :: call second transformation for it */

			probe = g(probe);
			while (!array[probe].free() && probe != tail)
				probe = g(probe);
			if (probe == tail) {
				cout << "Bad secondary transformation..";
				return;
			}
			array[tail].next = probe;
		}
		array[probe] = object;
		array[probe].status = 2;
		array[probe].next = -1;
		count++;
	}

	hashObject find(char* key) {
		long probe = f(key) % length;
		while (probe != -1) {
			if (!array[probe].isEqualKey(key))
				probe = array[probe].next;
			else
				return array[probe];
		}
		cout << "Not found..";
		return NULL;
	}

	void withdraw(char* key) {
		if (count == 0)
			return;

		long probe = f(key) % length;
		long prev = -1;
		while (probe != -1 && !array[probe].isEqualKey(key)) {
			prev = probe;
			probe = array[probe].next;
		}
		if (probe == -1)
			return;
		else if (prev != -1) {	/* in betweeen all synonyms */
			array[prev].next = array[probe].next;
			array[probe].deleteRecord();
			array[probe].status = 1;
		}
		else {	/* first of synonyms */
			if (array[probe].next == -1) {
				array[probe].deleteRecord();
				array[probe].status = 1;
				return;
			}

			long nextEl = array[probe].next;
			array[probe].deleteRecord();
			array[probe] = array[nextEl];
			array[probe].next = array[nextEl].next;
			array[nextEl] = hashObject();
			array[nextEl].status = 1;
		}
	}

	void showAll() {
		unsigned long i = 0;

		while (i < length) {
			if (array[i].status == 2 && array[i].next != -1) {
				long probe = i;
				while (probe != -1) {
					cout << i << " "; array[i].showHashObject();
					probe = array[probe].next;
				}
				cout << endl;
			}
			else if (array[i].status == 2 && array[i].next == -1) {
				if (existsPrevious(i)) {
					i++;
					continue;
				}
				cout << i << " "; array[i].showHashObject();
				cout << endl;
			}
			i++;
		}

		cout << endl;
	}

	unsigned int getLength() {
		return length;
	}

	double getLoadFactor() {
		return (double)count / (double)length;
	}

	bool existsPrevious(int index) {
		for (unsigned int i = 0; i < length; i++)
			if (array[i].next == index)
				return true;
		return false;
	}
};