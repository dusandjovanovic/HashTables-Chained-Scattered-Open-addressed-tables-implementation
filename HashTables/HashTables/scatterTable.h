#pragma once
#include "hashTable.h"
#include "linkedList.h"

template <type, Record>
class scatterObject : public hashObject<type, Record> {
protected:
	int status;
public:
	scatterObject() : hashObject<type, Record>() {
		status = 0;
	}
	scatterObject(type key) : hashObject<type, Record>(key) {
		status = 0;
	}
	scatterObject(type key, Record* element) : hashObject<type, Record>(key, element) {
		status = 0;
	}
};