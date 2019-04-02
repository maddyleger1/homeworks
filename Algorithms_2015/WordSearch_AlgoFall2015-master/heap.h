/*
 * heap.h
 *
 *  Created on: Oct 19, 2015
 *      Author: maddy
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <string>

template <typename T>

class heap {
public:

	//getters for heap members
	inline int get_parent(int n) {return n/2;}
	inline int get_left_child(int n) {return 2*n;}
	inline int get_right_child(int n) {return 2*n+1;}
	inline T getItem(int n) {return heap_data[n];}

	void initializeMaxHeap(std::vector<T> &heap_data)
	{
		//initialize da heap
		this->heap_data = heap_data;
		buildMaxHeap(heap_data);
	}

	void buildMaxHeap(std::vector <T> &heap_data)
	{
		int size = heap_data.size();

		//use maxHeapify to create your heap
		for (int i = size/2; i >= 1; i--)
			maxHeapify(heap_data, i, size);
	}

	void maxHeapify(std::vector <T> &heap_data, int i, int size)
	{
		int left, right, largest;
		left = get_left_child(i);
		right = get_right_child(i);

		if (left < (size - 1) && heap_data[left] > heap_data[i])
			largest = left; //if value at left is out of place and is last
		else
			largest = i; //largest is index

		if (right < (size - 1) && heap_data[right] > heap_data[largest])
			largest = right;

		if (largest != i)
		{
			std::swap(heap_data[i], heap_data[largest]);
			maxHeapify(heap_data, largest, size);
		}
	}

	void initializeMinHeap(std::vector<T> &heap_data)
	{
		//initialize da heap
		this->heap_data = heap_data;
		buildMinHeap(heap_data);
	}

	void buildMinHeap(std::vector <T> &heap_data)
	{
		int size = heap_data.size();

		//use minHeapify to create your heap
		for (int i = (int)size/2; i >= 1; i--)
			minHeapify(heap_data, i, size);
	}

	void minHeapify(std::vector <T> &heap_data, int i, int size)
	{
		int left, right, smallest;
		left = get_left_child(i);
		right = get_right_child(i);

		if (left > (size - 1) && heap_data[left] > heap_data[i])
			smallest = left; //if value at left is out of place and is last
		else
			smallest = i; //largest is index

		if (right > (size - 1) && heap_data[right] > heap_data[smallest])
			smallest = right;
		else
			smallest = i; //do the same thing again

		if (smallest != i)
		{
			std::swap(heap_data[i], heap_data[smallest]);
			minHeapify(heap_data, smallest, size);
		}
	}


private:
	std::vector <T> heap_data;
};

#endif /* HEAP_H_ */
