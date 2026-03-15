#ifndef JJM_LIB_LIST
#define JJM_LIB_LIST 1

#include <iostream>
#include <initializer_list>

template <typename T>
class JJM_List
{
private:
	typedef unsigned long l_size;
	l_size size;
	T* iter;
	T* data;

	void Heapify(l_size n, l_size i) {
		l_size largest = i;
		l_size left = 2 * largest + 1;
		l_size right = 2 * largest + 2;
		if (left < n && data[left] > data[largest])
			largest = left;
		if (right < n && data[right] > data[largest])
			largest = right;
		if (largest != i) {
			Swap(i, largest);
			Heapify(n, largest);
		}
	}

	void Swap(l_size item1, l_size item2) {
		T temp = data[item2];
		data[item2] = data[item1];
		data[item1] = temp;
	}

	template <typename X>
	friend std::ostream& operator << (std::ostream& out, const JJM_List<X>& source);
public:
	// Creates an empty data container with a size of zero.
	JJM_List() : size{ 0 }, iter{ nullptr } {
		data = new T[size];
	}

	// Creates a new data container using a defined initializer list.
	JJM_List(std::initializer_list<T> items) : size{ items.size() } {
		data = new T[size];
		for (int i{ 0 }; i < size; i++)
			data[i] = *(items.begin() + i);
		iter = &data[0];
	}

	// Creates a copy of an existing JJM_List object of the same type.
	JJM_List(const JJM_List<T>& source) : size{ source.size } {
		data = new T[size];
		for (int i{ 0 }; i < size; i++)
			data[i] = source.data[i];
		iter = &data[0];
	}

	~JJM_List() {
		delete[] data;
	}

	// Returns the size of the data container.
	inline l_size Size() { return size; }

	// Appends a new item to the data container.
	void Add(T item) {
		T* temp = new T[size + 1];
		for (int i{ 0 }; i < size; i++)
			temp[i] = data[i];
		temp[size++] = item;
		delete[] data;
		data = temp;

		if (iter == nullptr)
			iter = &data[0];
	}

	// Removes an existing item from the data container.
	// Returns false if the specified item does not exist.
	bool Remove(T item) {
		if (!Find(item)) return false;

		T* temp = new T[size - 1];
		unsigned short offset = 0;
		for (l_size i{ 0 }; i < size; i++) {
			if (&data[i] == iter) {
				offset = 1;
				continue;
			} temp[i - offset] = data[i];
		}
		delete[] data;
		size--;
		data = temp;
		if (size == 0)
			iter = nullptr;
		else
			iter = &data[0];
		return true;
	}

	// Searches for a specified item, setting the internal iterator to that item.
	// Returns false if the specified item does not exist.
	bool Find(T item) {
		for (l_size i{ 0 }; i < size; i++) {
			if (data[i] == item) {
				iter = &data[i];
				return true;
			}
		} return false;
	}

	// Returns the item that the internal iterator points to.
	// Returns a default value if the data container is empty.
	T At() {
		if (size == 0) {
			std::cout << "List contains no data\n";
			return data[0];
		} return *iter;
	}

	// Returns the item at the specified index.
	// Returns a default value if the index is out of range.
	T At(l_size index) {
		if (index >= size) {
			std::cout << "Index out of range\n";
			return data[0];
		} return data[index];
	}

	void Sort() {
		for (l_size i{ size / 2 - 1 }; i >= 0; i--)
			Heapify(size, i);
		for (l_size i{ size - 1 }; i > 0; i--) {
			Swap(0, i);
			Heapify(i, 0);
		}
	}

	T& operator [] (l_size index) {
		return data[index];
	}
};

template <typename T>
std::ostream& operator << (std::ostream& out, const JJM_List<T>& source) {
	out << "[ ";
	for (int i{ 0 }; i < source.size; i++) {
		if (i == source.size - 1)
			out << source.data[i] << ' ';
		else
			out << source.data[i] << ", ";
	}
	out << ']';
	return out;
}

#endif