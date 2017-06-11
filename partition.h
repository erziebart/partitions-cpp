#pragma once

#include <vector>
#include <algorithm>

using namespace std;

namespace partition
{
	// instantiable Partition class
	class Partition {

	private:
		typedef vector<unsigned int> Elements;
		Elements arr;

	public:
		// constructor
		Partition(unsigned int arr[] = {}, size_t size = 0);

		// implicit destructor, copy constructor, and copy assignment have desired behavior


		// returns true if the Partition is the zero partition
		bool isZero() const { return count() == 0; }

		// the number of elements in the Partition
		unsigned int count() const { return arr.size(); }

		// sum of the Partition
		unsigned int sum() const;

		// product of the Partition
		unsigned int prod() const;

		// minimum element
		unsigned int min() const;

		// maximum element
		unsigned int max() const;


		// comparison
		friend bool operator==(const Partition& lhs, const Partition& rhs);

		// negated comparison
		friend bool operator!=(const Partition& lhs, const Partition& rhs) { return !(lhs == rhs); }

		// appending
		Partition& operator+=(const Partition& rhs);

		Partition& operator+=(unsigned int rhs);

		// printing
		friend ostream& operator<<(ostream& os, const Partition& p);

		// concatenation
		friend Partition operator+(const Partition& lhs, const Partition& rhs);


		// returns the order of the Partition
		unsigned int order() const;


		//iterator - delegate to container member
		typedef Elements::iterator iterator;
		typedef Elements::reverse_iterator reverse_iterator;
		typedef Elements::const_iterator const_iterator;
		typedef Elements::const_reverse_iterator const_reverse_iterator;

		iterator begin() { return arr.begin(); }
		iterator end() { return arr.end(); }
		reverse_iterator rbegin() { return arr.rbegin(); }
		reverse_iterator rend() { return arr.rend(); }
		const_iterator cbegin() { return arr.cbegin(); }
		const_iterator cend() { return arr.cend(); }
		const_reverse_iterator crbegin() { return arr.crbegin(); }
		const_reverse_iterator crend() { return arr.crend(); }
	};


	class ZeroPartitionException : public runtime_error {
		public:
			ZeroPartitionException(const char* what_arg = "Invalid Operation for Zero Partition") 
				: runtime_error(what_arg) {}
	};


	// new Partition with factorial of each element
	Partition fact(const Partition& p);

	// new Partition with non-negative integer added to each element
	Partition add(const Partition& p, unsigned int value);

	// new Partition with each element multiplied by a non-negative integer
	Partition mult(const Partition& p, unsigned int value);

	// new Partition with each element of the Partition changed according to some rule
	typedef unsigned int(*Rule) (unsigned int e);
	Partition forEach(const Partition& p, Rule fn);


	// partition of a Partition
	Partition part(Partition& p);

	// partition of an array
	template <typename T>
	Partition part(const T arr[], size_t size) {
		if (arr == NULL || !size) {
			Partition result;
			return result;
		}
		else {
			unsigned int *freq = new unsigned int[size];
			memset(freq, 0, size * sizeof(unsigned int));

			vector<T> vals;
			for (unsigned int i = 0; i < size; i++) {
				T cur = arr[i];
				unsigned int index;

				// check if already found
				auto it = find(vals.begin(), vals.end(), cur);
				if (it != vals.end()) { // found
					index = distance(vals.begin(), it);
				}
				else { // not found
					vals.push_back(cur);
					index = vals.size() - 1;
				}

				freq[index]++;
			}

			Partition result(freq, size);
			delete[] freq;
			return result;
		}
	}

	// partition of a container
	template <typename Iterator>
	Partition part(Iterator begin, Iterator end) {
		if (begin == NULL || end == NULL || begin == end) {
			Partition result;
			return result;
		}
		else {
			size_t size = distance(begin, end);
			unsigned int *freq = new unsigned int[size];
			memset(freq, 0, size * sizeof(unsigned int));
			
			vector<Iterator> vals;
			for (auto i = begin; i != end; ++i) {
				unsigned int index;

				// check if already found
				bool found = false;
				auto j = vals.begin();
				for (; j != vals.end(); ++j) {
					if (**j == *i) {
						found = true;
						break;
					}
				}
				
				if (found) {
					index = distance(vals.begin(), j);
				}
				else {
					vals.push_back(i);
					index = vals.size() - 1;
				}

				freq[index]++;
			}

			Partition result(freq, size);
			delete[] freq;
			return result;
		}
	}
}