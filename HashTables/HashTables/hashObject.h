#pragma once
#include <iostream>
using namespace std;

template <typename type, typename typeRecord >
class hashObject {
protected:
	type key;
	typeRecord* record;
public:
	hashObject() {
		key = 0;
		record = nullptr;
	}

	hashObject(type newKey) {
		key = newKey;
		record = nullptr;
	}

	hashObject(type newKey, typeRecord* newRecord) {
		key = newKey;
		record = newRecord;
	}

	~hashObject() {
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
		if (record != nullptr)
			delete record;
		record = nullptr;
	}

	bool isEqualKey(type keyEqual) {
		return key == keyEqual;
	}

	type getKey() {
		return key;
	}

	void showHashObject() {
		cout << endl << key << " | " << *record;
	}
};