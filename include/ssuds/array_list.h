#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

namespace ssuds {

    /// <summary>
    /// A dynamic array-based list implementation.
    /// </summary>
    /// <typeparam name="T">The type of elements stored in the list.</typeparam>
    template <typename T>
    class ArrayList {
    private:
        T* data;                  ///< Pointer to the array data.
        unsigned int mSize;       ///< Current number of elements in the list.
        unsigned int mCapacity;   ///< Maximum capacity before resizing.

        /// <summary>
        /// Resizes the array to a new capacity.
        /// </summary>
        /// <param name="new_capacity">The new capacity of the array.</param>
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
        /// Forward iterator for ArrayList.
        /// </summary>
        class ArrayListIterator {
        private:
            T* ptr; ///< Pointer to the current element.
        public:
            /// <summary>
            /// Constructs an iterator starting at a given position.
            /// </summary>
            /// <param name="start">Pointer to the starting element.</param>
            ArrayListIterator(T* start) : ptr(start) {}

            ArrayListIterator& operator++() { ++ptr; return *this; }
            ArrayListIterator operator++(int) { ArrayListIterator temp = *this; ++ptr; return temp; }
            ArrayListIterator operator+(int offset) const { return ArrayListIterator(ptr + offset); }
            T& operator*() const { return *ptr; }
            bool operator==(const ArrayListIterator& other) const { return ptr == other.ptr; }
            bool operator!=(const ArrayListIterator& other) const { return ptr != other.ptr; }
        };

        /// <summary>
        /// Reverse iterator for ArrayList.
        /// </summary>
        class ReverseArrayListIterator {
        private:
            T* ptr; ///< Pointer to the current element.
        public:
            /// <summary>
            /// Constructs a reverse iterator starting at a given position.
            /// </summary>
            /// <param name="start">Pointer to the starting element.</param>
            ReverseArrayListIterator(T* start) : ptr(start) {}

            ReverseArrayListIterator& operator++() { --ptr; return *this; }
            ReverseArrayListIterator operator++(int) { ReverseArrayListIterator temp = *this; --ptr; return temp; }
            ReverseArrayListIterator operator+(int offset) const { return ReverseArrayListIterator(ptr - offset); }
            T& operator*() const { return *ptr; }
            bool operator==(const ReverseArrayListIterator& other) const { return ptr == other.ptr; }
            bool operator!=(const ReverseArrayListIterator& other) const { return ptr != other.ptr; }
        };

        /// <summary>
        /// Constructs an ArrayList with a given initial capacity.
        /// </summary>
        /// <param name="capacity">The initial capacity.</param>
        ArrayList(unsigned int capacity = 20) : mSize(0), mCapacity(capacity), data(new T[capacity]) {}

        /// <summary>
        /// Constructs an ArrayList from an initializer list.
        /// </summary>
        /// <param name="initList">The initializer list.</param>
        ArrayList(std::initializer_list<T> initList) : mSize(initList.size()), mCapacity(initList.size()), data(new T[mCapacity]) {
            unsigned int i = 0;
            for (const T& item : initList) {
                data[i++] = item;
            }
        }

        /// <summary>
        /// Copy constructor.
        /// </summary>
        /// <param name="other">The ArrayList to copy from.</param>
        ArrayList(const ArrayList& other) : mSize(other.mSize), mCapacity(other.mCapacity), data(new T[other.mCapacity]) {
            for (unsigned int i = 0; i < mSize; i++) {
                data[i] = other.data[i];
            }
        }

        /// <summary>
        /// Move constructor.
        /// </summary>
        /// <param name="other">The ArrayList to move from.</param>
        ArrayList(ArrayList&& other) noexcept : data(other.data), mSize(other.mSize), mCapacity(other.mCapacity) {
            other.data = nullptr;
            other.mSize = 0;
            other.mCapacity = 0;
        }

        /// <summary>
        /// Destructor to clean up allocated memory.
        /// </summary>
        ~ArrayList() {/*delete[] data;*/ }

        ArrayList& operator=(const ArrayList& other) {
            if (this == &other) return *this;
            delete[] data;
            mSize = other.mSize;
            mCapacity = other.mCapacity;
            data = new T[mCapacity];
            for (unsigned int i = 0; i < mSize; i++) {
                data[i] = other.data[i];
            }
            return *this;
        }

        ArrayList& operator=(ArrayList&& other) noexcept {
            if (this == &other) return *this;
            delete[] data;
            data = other.data;
            mSize = other.mSize;
            mCapacity = other.mCapacity;
            other.data = nullptr;
            other.mSize = 0;
            other.mCapacity = 0;
            return *this;
        }

        /// <summary>
        /// Returns the number of elements in the list.
        /// </summary>
        /// <returns>The current size of the list.</returns>
        unsigned int size() const { return mSize; }

        /// <summary>
        /// Accesses an element by index.
        /// </summary>
        /// <param name="index">The index to access.</param>
        /// <returns>A reference to the element.</returns>
        T& operator[](unsigned int index) {
            if (index >= mSize) throw std::out_of_range("Index out of bounds");
            return data[index];
        }

        /// <summary>
        /// Appends an item to the end of the list.
        /// </summary>
        /// <param name="item">The item to append.</param>
        void append(const T& item) {
            if (mSize == mCapacity) resize(mCapacity * 2);
            data[mSize++] = item;
        }

        ArrayListIterator begin() { return ArrayListIterator(data); }
        ArrayListIterator end() { return ArrayListIterator(data + mSize); }

        ReverseArrayListIterator rbegin() { return ReverseArrayListIterator(data + mSize - 1); }
        ReverseArrayListIterator rend() { return ReverseArrayListIterator(data - 1); }

        /// <summary>
        /// Finds the first occurrence of a value in the list.
        /// </summary>
        /// <param name="value">The value to find.</param>
        /// <returns>An iterator to the found element, or end() if not found.</returns>
        ArrayListIterator find(const T& value) {
            for (auto it = begin(); it != end(); ++it) {
                if (*it == value) return it;
            }
            return end();
        }

        /// <summary>
        /// Removes the first occurrence of a value from the list.
        /// </summary>
        /// <param name="value">The value to remove.</param>
        void remove(const T& value) {
            int index = -1;
            for (unsigned int i = 0; i < mSize; i++) {
                if (data[i] == value) {
                    index = i;
                    break;
                }
            }
            if (index != -1) {
                for (unsigned int j = index; j < mSize - 1; j++) {
                    data[j] = data[j + 1];
                }
                --mSize;
                data[mSize] = T();
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
            os << "[";
            for (unsigned int i = 0; i < list.mSize; i++) {
                os << list.data[i];
                if (i < list.mSize - 1) os << ", ";
            }
            os << "]";
            return os;
        }
    };
}

#endif