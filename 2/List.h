#pragma once

template <class T>
class List {
public:
	List(int size = 10);
	~List();
	const int size() const;
	void clear();
	void add(T& item);
	void add(T* item);
	void remove(int index);
	void remove(const T& item);
	int getIndex(const T& item);
	T* get(int index);
	T* getArr();

private:
	int nrOf;
	int maxSize;
	T** arr;

	void expandArr();
};

template<class T>
inline List<T>::List(int size) {
	maxSize = size;
	nrOf = 0;
	arr = new T*[maxSize]();
}

template<class T>
inline List<T>::~List() {
	for (int i = 0; i <nrOf; ++i) {
		delete arr[i];
	}
	delete[] arr;
}

template<class T>
inline const int List<T>::size() const {
	return nrOf;
}

template<class T>
inline void List<T>::clear() {
	for (int i = 0; i < nrOf; ++i) {
		delete arr[i];
	}
	nrOf = 0;
}

template<class T>
inline void List<T>::add(T& item) {
	add(&item);
}

template<class T>
inline void List<T>::add(T* item) {
	if (nrOf == maxSize) {
		expandArr();
	}

	arr[nrOf++] = item;
}

template<class T>
inline void List<T>::remove(int index) {
	arr[index] = arr[nrOf];
	arr[--nrOf] = nullptr;
}

template<class T>
inline void List<T>::remove(const T& item) {
	remove(getIndex(item));
}

template<class T>
inline int List<T>::getIndex(const T& item) {
	for (int i = 0; i < nrOf; ++i) {
		if (item == arr[i]) {
			return i;
		}
	}
	return -1;
}

template<class T>
inline T* List<T>::get(int index) {
	return arr[index];
}

template<class T>
inline T* List<T>::getArr() {
	return arr;
}

template<class T>
inline void List<T>::expandArr() {
	maxSize *= 2;
	T** tmp = new T * [maxSize];
	for (int i = 0; i < nrOf; ++i) {
		tmp[i] = arr[i];
	}
	delete[] arr;
	arr = tmp;
}
