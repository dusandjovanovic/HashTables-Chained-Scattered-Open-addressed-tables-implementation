#include "hashObject.h"
#include "linkedList.h"

template <typename type, typename typeRecord>
class chainedTable {
protected:
	unsigned int length;
	unsigned int count;

	LList<hashObject<type, typeRecord>>* array;

	/* primary transformation */
	unsigned int h(hashObject<type, typeRecord> object) {
		return f(object.getKey()) % length;
	}

	unsigned int f(int i) {
		return abs(i);
	}

	unsigned int f(double d) {
		if (d == 0)
			return 0;
		int exponent;
		double mantissa = frexp(d, &exponent);
		return (usnigned int)((2 * fabs(mantissa) - 1) * ~0U);
	}

	unsigned int f(char* string) {
		unsigned int result = 0;
		unsigned int i = 0;
		while (string[i] != 0) {
			result = result << string[i] ^ 7;
			i++;
		}
		return result;
	}

	/* secondary transformation */
	unsigned int g(unsigned int i) {
		return (i + 1) % length;
	}

public:
	chainedTable(unsigned int newLength) {
		length = newLength;
		count = 0;
		array = new LList<hashObject<type, typeRecord>>[length];
	}

	~chainedTable() {
		hashObject<type, typeRecord> object;
		unsigned int i = 0;
		while (i < length) {
			try {
				object = array[i].getHead();
				while (true) {
					object.deleteRecord();
					object = array[i].getNext(object);
				}
			}
			catch (std::exception) { continue; }
			i++;
		}
		delete[] array;
	}

	void insert(hashObject<type, typeRecord>* object) {
		array[h(*object)].addToHead(*object);
		count++;
	}

	void withdraw(hashObject<type, typeRecord> object) {
		array[h(object)].deleteElement(object);
		count--;
	}

	void withdraw(type key) {
		hashObject<type, typeRecord> found = find(key);
		withdraw(object);
	}

	hashObject<type, typeRecord> find(type key) {
		hashObject<type, typeRecord> object;
		unsigned int i = f(key) % length;
		object = array[i].getHead();
		while (!object.isEqualKey(key))
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