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

	unsigned int f(char* string) {
		unsigned int result = 0;
		unsigned int i = 0;
		while (string[i] != 0) {
			result = result << string[i] ^ 7;
			i++;
		}
		return result;
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
			try {
				if (array[i].isEmpty()){
						i++;
						continue;
					}
				object = array[i].getHead();
				while (true) {
					object.deleteRecord();
					Node<hashObject>* tmpPointer = array[i].getNodePtr(object);
					if (!tmpPointer->nextExists())
						break;
					object = array[i].getNext(object);
				}
			}
			catch (std::exception* e) { continue; }
			i++;
		}
		delete[] array;
	}

	void showAll() {
		hashObject* tmp;
		unsigned int i = 0;
		while (i < length) {
			if (!array[i].isEmpty()) {
				tmp = &array[i].getHead();
				while (tmp != nullptr) {
					tmp->showHashObject();
					Node<hashObject>* tmpPointer = array[i].getNodePtr(*tmp);
					if (!tmpPointer->nextExists())
						break;
					tmp = &array[i].getNext(*tmp);
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

	void withdraw(char* key) {
		hashObject found = find(key);
		withdraw(found);
	}

	hashObject find(char* key) {
		hashObject object;
		unsigned int i = f(key) % length;
		object = array[i].getHead();
		while (!object.isEqualKey(key)) {
			Node<hashObject>* tmpPointer = array[i].getNodePtr(object);
			if (!tmpPointer->nextExists())
				break;
			object = array[i].getNext(object);
		}
		return object;
	}

	unsigned int getLength() {
		return length;
	}

	double getLoadFactor() {
		return (double)count / (double)length;
	}
};