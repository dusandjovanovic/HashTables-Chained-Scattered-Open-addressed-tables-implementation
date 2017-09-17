#pragma once
#include "hashObject.h"

template <typename type, typename typeRecord>
class hashTable {
protected:
	unsigned int length;
	unsigned int count;

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
	unsigned int getLength() {
		return length;
	}

	double getLoadFactor() {
		return (double)count / (double)length;
	}
};