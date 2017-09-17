#pragma  once
#include <iostream>
using namespace std;

class hashObject {
protected:
	int key;
	char* record;
public:
	int status;
public:
	hashObject() {
		key = 0;
		status = 0;
		record = nullptr;
	}

	hashObject(int newKey) {
		key = newKey;
		status = 0;
		record = nullptr;
	}

	hashObject(int newKey, char* newRecord) {
		key = newKey;
		record = newRecord;
		status = 0;
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

	bool isEqualKey(int keyEqual) {
		return key == keyEqual;
	}

	int getKey() {
		return key;
	}

	void showHashObject() {
		cout << " > " << key << " | " << record << " ";
	}
};