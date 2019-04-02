/*
 * hashTable.h
 *
 *  Created on: Oct 19, 2015
 *      Author: maddy
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <functional>
#include <vector>
#include <string>

template <typename T>

class hashTable {
public:
	hashTable()
	{
		hash_buckets.resize(size); //alocate space
	}

	static const size_t size = 30001; //about 1/3 the word list

	void populateHash(std::vector<T> &list)
	{
		for (int i = 0; i < (int)list.size(); i++)
			addHashItem(list.at(i)); //add values to hashtable
	}

	void addHashItem(T &value)
	{
		int idx = hash(value);
		hash_buckets[idx].push_back(value);
	}

	void deleteHashItem(T &value)
	{
		int idx = hash(value);

		for (int i = 0; i < hash_buckets.at(idx).size(); i++)
		{
			if (hash_buckets.at(idx).at(i) == value)
			{
				for (i; i < hash_buckets.at(idx).size()-1; i++)
					hash_buckets.at(idx).at(i) = hash_buckets.at(idx).at(i+1);

				hash_buckets.at(idx).pop_back();
			}
			else
				throw(3); //value to delete not found
		}
	}

	static size_t hash(T& value)
	{
		static std::hash<T> hasher;
		return hasher(value) % hashTable::size;
	}

	bool inlist(T &value)
	{
		int idx = hash(value);

		for (int i = 0; i < (int)hash_buckets.at(idx).size(); i++)
		{
			if (hash_buckets.at(idx).at(i) == value)
				return true;
		}

		return false;
	}



private:
	std::vector <std::vector <T> > hash_buckets;
};

#endif /* HASHTABLE_H_ */
