#ifndef JJM_LIB_MAP
#define JJM_LIB_MAP 1

#define MAX_SIZE 1000000

#include <climits>
#include <string>

using std::string;

template<typename T>
struct Node {
	string key;
	T data;
	Node<T>* next = nullptr;
};


template<typename T>
struct NodeElement {
	Node<T>* first = nullptr;
	unsigned int childCount = 0;
};


template<typename T>
class JJM_Map {
	NodeElement<T>** nodeArray;
	unsigned int arraySize, elementCount;
	bool* primeArray;
	Node<T>* internptr;

	void SetupPrimeArray() {
		primeArray = new bool[MAX_SIZE];
		for (unsigned int i{ 0 }; i < MAX_SIZE; i++)
			primeArray[i] = true;

		unsigned int spot{ 2 };
		while (spot < MAX_SIZE) {
			while (primeArray[spot] == false) spot++;
			for (unsigned int i{ spot * 2 }; i < MAX_SIZE; i += spot)
				primeArray[i] = false;
			spot++;
		}
	}

	void ReHash() {
		// Create a new Node in the new nodearray with the key and data

		// Get the next prime number size up
		unsigned int newSize{ arraySize + 1 };
		while (primeArray[newSize] == false) newSize++;

		// Create a new nodeArray of the new size
		NodeElement<T>** tempArr{ new NodeElement<T>*[newSize]() };
		for (int i{ 0 }; i < newSize; i++)
			tempArr[i] = new NodeElement<T>;

		for (int i{ 0 }; i < arraySize; i++) {
			// Navigate through each node, and get the new hash value of the key
			for (int j{ 0 }; j < nodeArray[i]->childCount; j++) {
				Node<T>* trav{ nodeArray[i]->first };
				unsigned int newHash{ GetHash(trav->key, newSize) };

				Node<T>* temp{ new Node<T> };
				temp->key = trav->key;
				temp->data = trav->data;
				temp->next = tempArr[newHash]->first;
				tempArr[newHash]->first = temp;
				tempArr[newHash]->childCount++;

				nodeArray[i]->first = trav->next;
				delete trav;
			}
			delete[] nodeArray[i];
		}
		delete[] nodeArray;
		nodeArray = tempArr;
		arraySize = newSize;
	}

	unsigned int GetHash(string key, unsigned int i) {
		unsigned int hash{ 0 };
		for (int c{ 0 }; c < key.size(); c++) {
			int val{ static_cast<int>(key.at(c)) };
			hash = (hash * i) + val;
		}
		return hash % i;
	}

public:
	JJM_Map() : JJM_Map(11) { }

	JJM_Map(unsigned int size) : elementCount{ 0 }, internptr{ nullptr } {
		SetupPrimeArray();
		while (primeArray[size] == false) size++;
		arraySize = size;
		nodeArray = new NodeElement<T>*[arraySize];
		for (int i{ 0 }; i < arraySize; i++)
			nodeArray[i] = new NodeElement<T>;
	}

	~JJM_Map() {
		delete[] primeArray;
		for (int i{ 0 }; i < arraySize; i++) {
			for (int j{ 0 }; j < nodeArray[i]->childCount; j++) {
				Node<T>* temp = nodeArray[i]->first;
				nodeArray[i]->first = temp->next;
				delete temp;
			}
			delete nodeArray[i];
		}
		delete[] nodeArray;
	}

	T& operator [] (string key) {
		// Check to see if we need to grow?
		if (elementCount >= arraySize / 2)
			ReHash();

		unsigned int bin{ GetHash(key, arraySize) };
		Node<T>* trav = nodeArray[bin]->first;
		for (int i{ 0 }; i < nodeArray[bin]->childCount; i++) {
			if (trav->key == key)
				return trav->data;
			trav = trav->next;
		}
		if (nodeArray[bin]->childCount >= 5) {
			ReHash();
			bin = GetHash(key, arraySize);
		}
		Node<T>* temp = new Node<T>;
		temp->key = key;
		temp->next = nodeArray[bin]->first;
		nodeArray[bin]->first = temp;
		elementCount++;
		nodeArray[bin]->childCount++;
		return temp->data;
	}

	string KeyValue() {
		if (internptr == nullptr) {
			if (First()) return internptr->key;
			else return "null";
		}
		else
			return internptr->key;
	}

	T DataValue() {
		if (internptr == nullptr) {
			if (First()) return internptr->data;
			else return T{};
		}
		else
			return internptr->data;
	}

	bool First() {
		for (int i{ 0 }; i < arraySize; i++) {
			if (nodeArray[i]->first != nullptr) {
				internptr = nodeArray[i]->first;
				return true;
			}
		}
		return false;
	}

	bool Next() {
		if (internptr == nullptr)
			if (!First()) return false;

		if (internptr->next != nullptr) {
			internptr = internptr->next;
			return true;
		}
		unsigned int pos = GetHash(internptr->key, arraySize);
		for (unsigned int i{ pos + 1 }; i < arraySize; i++) {
			if (nodeArray[i]->first != nullptr) {
				internptr = nodeArray[i]->first;
				return true;
			}
		}
		return false;
	}

	bool Find(string key) {
		unsigned int pos = GetHash(key, arraySize);
		Node<T>* trav = nodeArray[pos]->first;

		while (trav != nullptr) {
			if (trav->key == key) return true;
			trav = trav->next;
		}
		return false;
	}

	bool Remove(string key) {
		unsigned int pos = GetHash(key, arraySize);
		Node<T>* trav = nodeArray[pos]->first;

		if (trav == nullptr) return false;

		if (trav->key == key) {
			nodeArray[pos]->first = trav->next;
			delete trav;
			nodeArray[pos]->childCount--;
			elementCount--;
			return true;
		}

		while (trav->next != nullptr) {
			if (trav->next->key == key) {
				Node<T>* temp = trav->next;
				trav->next = temp->next;
				delete temp;
				nodeArray[pos]->childCount--;
				elementCount--;
				return true;
			}
			trav = trav->next;
		}
		return false;
	}
};

#endif