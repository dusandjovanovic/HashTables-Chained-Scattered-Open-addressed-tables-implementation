#pragma  once
#include <iostream>
using namespace std;

class hashObject {
protected:
	char* key;
	char* record;
public:
	int status;
	int next;	/* linking elements */
public:
	hashObject() {
		key = 0;
		next = -1;
		status = 0;
		record = nullptr;
	}

	hashObject(char* newKey) {
		key = newKey;
		next = -1;
		status = 0;
		record = nullptr;
	}

	hashObject(char* newKey, char* newRecord) {
		key = newKey;
		record = newRecord;
		status = 0;
		next = -1;
	}

	hashObject(char* newKey, char* newRecord, int newNext) {
		key = newKey;
		record = newRecord;
		status = 0;
		next = newNext;
	}

	~hashObject() {
		//delete record;
	}

	bool operator==(hashObject const& object) {
		return record == object.record;
	}

	hashObject& operator=(hashObject const& object) {
		key = object.key;
		record = object.record;
		return *this;
	}

	void deleteRecord() {

	}

	bool free() {
		return status == 0;
	}

	bool isEqualKey(char* keyEqual) {
		return key == keyEqual;
	}

	char* getKey() {
		return key;
	}

	void showHashObject() {
		cout << " > " << key << " | " << record << " ";
	}
};