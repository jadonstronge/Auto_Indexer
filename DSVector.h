//
// Created by jadon on 6/9/2021.
//

#ifndef DSVECTOR_DSVECTOR_H
#define DSVECTOR_DSVECTOR_H
#include <algorithm>
#include <iostream>

// generic meta data type
template<typename T> class DSVector {
private:
    T* data;
    int capacity;
    int size;

    // doubles the capacity of vector
    void resize() {
        T* temp = new T[capacity * 2];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        capacity *= 2;
        delete[] data;
        data = temp;
    }

    //sorting related functions
    void swap(T *first, T *second) {
        T temp = *first;
        *first = *second;
        *second = temp;
    }

    int partition(T array[], int low, int high) {
        T pivot = array[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; ++j) {
            if (array[j] <= pivot) {
                ++i;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[high]);
        return (i + 1);
    }

    void quick_sort(T array[], int low, int high) {
        if (low < high) {
            int pivot = partition(array, low, high);
            quick_sort(array, low, pivot - 1);
            quick_sort(array, pivot + 1, high);
        }
    }

public:
    DSVector<T>() {
        size = 0; //number of elements
        capacity = 10;
        data = new T[capacity];
    }
    //copy constructor
    DSVector<T>(const DSVector<T> &rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = rhs[i];
    }

    //overloaded assignment operator
    DSVector<T>& operator=(const DSVector<T>& rhs) {
        delete[] data;
        size = rhs.size;
        capacity = rhs.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = rhs[i];
        return *this;
    }

    ~DSVector<T>() { delete[] data; }

    // inserts element at back of vector
    void push_back(const T &arg) {
        if (size == capacity) {
            resize();
        }
        data[size] = arg;
        size++;
    }

    // inserts element at front of vector
    void push_front(const T& arg) {
        if (size == capacity) {
            resize();
        }
        T* temp = new T[capacity];
        // instantiates vector 0 w/ new element
        temp[0] = arg;

        // copies everything after index 0 into new vector
        for (int i = 0; i < size; i++) {
            temp[i + 1] = data[i];
        }
        size++;
        delete[] data;
        data = temp;
    }

    //inserts in front of given location
    void insert(int location, const T& arg) {
        if (size == capacity) {
            resize();
        }
        T* temp = new T[capacity];
        // copies everything up until location into new vector
        for (int i = 0; i < location; i++) {
            temp[i] = data[i];
        }
        temp[location] = arg;
        // copies everything after location into new vector
        for (int i = location; i < size; i++) {
            temp[i+1] = data[i];
        }
        size++;
        delete[] data;
        data = temp;
    }

    // returns bool is there's nothing stored in vector
    bool is_clear() const {
        return (size == 0);
    }

    //returns number of elements in vector
    int the_size() const {
        return size;
    }

//    void sort(){
//        quick_sort();
//    }

    // returns data at index
    T& operator[](int index) const  {
        if ((index < 0) || (index > the_size() - 1)) {
            throw std::out_of_range("vector::out of range");
        }
        return data[index];
    }

    T& at (int index) {
        if ((index < 0) || (index > the_size() - 1)) {
            throw std::out_of_range("vector::out of range");
        }
        return data[index];
    }

    // returns index of data the program is searching for
    // if it exists
    int find(const T &arg) {
        for (int i = 0; i < size; i++) {
            if (data[i] == arg) {
                return i;
            }
        }
        // todo: do i want to throw? won't that end my program
        // eg. throw "element not found!" ???
        return -1;
    }

    // deletes all elements of a vector
    // todo: research how to write a clear function
    // should it create a new blank vector and return that?
//    void clear() {
//        delete[] data;
//    }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin( )
    { return &data[0]; }
    const_iterator begin( ) const
    { return &data[0]; }
    iterator end( )
    { return &data[the_size()]; }
    const_iterator end( ) const
    { return &data[the_size()]; }

};

#endif //DSVECTOR_DSVECTOR_H
