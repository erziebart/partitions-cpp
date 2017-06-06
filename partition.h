#pragma once

#include<vector>

using namespace std;

namespace partition
{
	// instantiable Partition class
	class Partition {

	private:
		typedef vector<unsigned int> Elements;
		Elements arr;

	public:
		Partition(unsigned int arr[] = {});

		~Partition();

		Partition(const Partition& p);

		Partition& operator=(const Partition& p);


		// returns true if the Partition is the zero partition
		bool isZero() const { return count() == 0; }

		// the number of elements in the Partition
		unsigned int count() const { return arr.size(); }

		// sum of the Partition
		unsigned int sum() const;

		// product of the Partition
		unsigned int prod() const;

		// maximum element
		unsigned int max() const;

		// minimum element
		unsigned int min() const;


		// comparison
		friend bool operator==(const Partition& p1, const Partition& p2);

		// appending
		Partition& operator+=(Partition& p);

		// printing
		friend ostream& operator<<(ostream& os, const Partition& p);

		// concatenation
		friend Partition operator+(const Partition& p1, const Partition& p2);


		// factorial of each element
		void fact();

		// add a non-negative integer to each element
		void add(unsigned int value);

		// multiply each element by a non-negative integer
		void mult(unsigned int value);

		// change each element of the Partition according to some rule
		void forEach(unsigned int(*fn)(unsigned int e));


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


	struct ZeroPartitionException : public exception {
		const char* what() const throw() {
			return "Invalid Operation for Zero Partition";
		}
	};


	// partition of a Partition
	static Partition& part(Partition& p);

	// partition of an array
	template <typename T>
	static Partition& part(const T[]);

	// partition of a container
	template <typename Iter>
	static Partition& part(Iter it, Iter end);
}