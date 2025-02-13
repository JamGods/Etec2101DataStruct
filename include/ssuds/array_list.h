#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace ssuds {

    template <typename T>
    class ArrayList {
    private:
        T* data; ///< The template variable
        unsigned int mSize; ///< Temporary size variable
        unsigned int mCapacity; ///< Temporary capacity variable
        /// <summary>
        /// Resizes the array to a new capacity if needed
        /// </summary>
        /// <param name="new_capacity">The new capacity of the array</param>
        void resize(unsigned int new_capacity) {
            if (new_capacity < mSize) return;
            T* new_data = new T[new_capacity];
            for (unsigned int i = 0; i < mSize; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            mCapacity = new_capacity;
        }
    public:
        /// <summary>
        /// Constructor for the ArrayList class
        /// </summary>
        /// <param name="capacity">Initial capacity of the array</param>
        ArrayList(unsigned int capacity = 2)
            : mSize(0), mCapacity(capacity), data(new T[capacity]) {}
        /// <summary>
        /// Destructor to free allocated memory
        /// </summary>
        ~ArrayList() { delete[] data; }
        /// <summary>
        /// Gets the current size of the array list
        /// </summary>
        /// <returns>Number of elements in the list</returns>
        unsigned int size() const { return mSize; }
        /// <summary>
        /// Gets the current capacity of the array list
        /// </summary>
        /// <returns>Maximum number of elements the list can hold</returns>
        unsigned int capacity() const { return mCapacity; }
        /// <summary>
        /// Reserves additional capacity if needed
        /// </summary>
        /// <param name="new_capacity">The new capacity to reserve</param>
        void reserve(unsigned int new_capacity) {
            if (new_capacity > mCapacity) {
                resize(new_capacity);
            }
        }
        /// <summary>
        /// Appends an item to the end of the list
        /// </summary>
        /// <param name="item">The item to append</param>
        void append(const T& item) {
            if (mSize == mCapacity) resize(mCapacity * 2);
            data[mSize++] = item;
        }
        /// <summary>
        /// Prepends an item to the beginning of the list
        /// </summary>
        /// <param name="item">The item to prepend</param>
        void prepend(const T& item) {
            insert(item, 0);
        }
        /// <summary>
        /// Inserts an item at a given index
        /// </summary>
        /// <param name="item">The item to insert</param>
        /// <param name="index">The position to insert at</param>
        void insert(const T& item, unsigned int index) {
            if (index > mSize) throw std::out_of_range("Index out of bounds");
            if (mSize == mCapacity) resize(mCapacity * 2);
            for (unsigned int i = mSize; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = item;
            mSize++;
        }
        /// <summary>
        /// Gets the item at a given index
        /// </summary>
        /// <param name="index">The index to access</param>
        /// <returns>Reference to the item at the given index</returns>
        T& at(unsigned int index) {
            if (index >= mSize) throw std::out_of_range("Index out of range");
            return data[index];
        }
        /// <summary>
        /// Removes an item at a given index
        /// </summary>
        /// <param name="index">The index of the item to remove</param>
        /// <returns>The removed item</returns>
        T remove(unsigned int index) {
            if (index >= mSize) throw std::out_of_range("Index out of range");
            T removed_value = data[index];
            for (unsigned int i = index; i < mSize - 1; i++) {
                data[i] = data[i + 1];
            }
            mSize--;
            if (mSize < mCapacity / 4) resize(mCapacity / 2);
            return removed_value;
        }
        /// <summary>
        /// Removes all occurrences of a given value
        /// </summary>
        /// <param name="value">The value to remove</param>
        /// <returns>The number of removed occurrences</returns>
        int remove_all(const T& value) {
            int count = 0;
            for (int i = 0; i < mSize; i++) {
                if (data[i] == value) {
                    remove(i);
                    i--;
                    count++;
                }
            }
            return count;
        }
        /// <summary>
        /// Finds the index of a given value
        /// </summary>
        /// <param name="value">The value to find</param>
        /// <param name="start_index">The index to start searching from</param>
        /// <returns>Index of the first occurrence, or -1 if not found</returns>
        int find(const T& value, unsigned int start_index = 0) const {
            for (unsigned int i = start_index; i < mSize; i++) {
                if (data[i] == value) return i;
            }
            return -1;
        }
        /// <summary>
        /// Outputs the list contents to an output stream
        /// </summary>
        /// <param name="os">The output stream</param>
        void output(std::ostream& os) const {
            os << "[";
            for (unsigned int i = 0; i < mSize; i++) {
                os << data[i];
                if (i < mSize - 1) os << ", ";
            }
            os << "]";
        }
    };
    /// <summary>
    /// Overloads the output stream operator for ArrayList
    /// </summary>
    /// <param name="os">The output stream</param>
    /// <param name="list">The ArrayList to print</param>
    /// <returns>The modified output stream</returns>
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
        list.output(os);
        return os;
    }
} // namespace ssuds
#endif
