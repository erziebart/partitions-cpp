#include "partition.h"
#include "factorial.h"
#include <algorithm>
#include <iostream>

using namespace std;

namespace partition
{
	Partition::Partition(unsigned int arr[], size_t size) {
		// add elements
		for (unsigned int i = 0; i < size; i++) {
			if (arr[i] != 0) {
				this->arr.push_back(arr[i]);
			}
		}

		// sort elements
		sort(this->begin(), this->end());
	}

	unsigned int Partition::sum() const {
		unsigned int sum = 0;
		for (auto e : this->arr) {
			sum += e;
		}
		return sum;
	}

	unsigned int Partition::prod() const {
		// not valid for zero partition
		if (isZero()) {
			throw ZeroPartitionException();
		}
		else {
			unsigned int prod = 1;
			for (auto e : this->arr) {
				prod *= e;
			}
			return prod;
		}
	}

	unsigned int Partition::min() const {
		// not valid for zero partition
		if (isZero()) {
			throw ZeroPartitionException();
		}
		else {
			return this->arr.front();
		}
	}

	unsigned int Partition::max() const {
		// not valid for zero partition
		if (isZero()) {
			throw ZeroPartitionException();
		}
		else {
			return this->arr.back();
		}
	}

	bool operator==(const Partition& lhs, const Partition& rhs) {
		int c1, c2;
		c1 = lhs.count();
		c2 = rhs.count();

		if (c1 != c2) {
			return false;
		}

		for (int i = 0; i < c1; i++) {
			if (lhs.arr[i] != rhs.arr[i]) {
				return false;
			}
		}

		return true;
	}

	Partition& Partition::operator+=(const Partition& rhs) {
		for (auto e : rhs.arr) {
			this->arr.push_back(e);
		}

		sort(this->arr.begin(), this->arr.end());

		return *this;
	}

	Partition& Partition::operator+=(unsigned int rhs) {
		Elements result;
		unsigned int i = 0;
		
		unsigned int e;
		while (i < this->arr.size() && (e = this->arr[i]) < rhs) {
			result.push_back(e);
			i++;
		}

		result.push_back(rhs);
		
		while (i < this->arr.size()) {
			result.push_back(this->arr[i++]);
		}
		
		// swap refs - correct one deleted
		swap(this->arr, result);

		return *this;
	}

	ostream& operator<<(ostream& os, const Partition& p) {
		os << "{ ";
		for (auto e : p.arr) {
			os << e << " ";
		}
		os << "}";
		return os;
	}

	Partition operator+(const Partition& lhs, const Partition& rhs) {
		Partition result;

		for (auto e : lhs.arr) {
			result.arr.push_back(e);
		}

		for (auto e : rhs.arr) {
			result.arr.push_back(e);
		}

		sort(result.arr.begin(), result.arr.end());

		return result;
	}

	Partition fact(const Partition& p) {
		Partition result = p;
		for (auto it = result.begin(); it != result.end(); ++it) {
			*it = combinatorics::factorial(*it);
		}
		return result;
	}

	Partition add(const Partition& p, unsigned int value) {
		Partition result = p;
		for (auto it = result.begin(); it != result.end(); ++it) {
			*it += value;
		}
		return result;
	}

	Partition mult(const Partition& p, unsigned int value) {
		if (value == 0) {
			Partition result;
			return result;
		}

		Partition result = p;
		for (auto it = result.begin(); it != result.end(); ++it) {
			*it *= value;
		}
		return result;
	}

	Partition forEach(const Partition& p, Rule fn) {
		Partition result = p;
		for (auto it = result.begin(); it != result.end(); ++it) {
			*it = fn(*it);
		}
		return result;
	}
}