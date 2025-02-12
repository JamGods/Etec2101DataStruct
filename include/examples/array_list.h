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
        T* data;
        unsigned int mSize;
        unsigned int mCapacity;

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
        ArrayList(unsigned int capacity = 2)
            : mSize(0), mCapacity(capacity), data(new T[capacity]) {}

        ~ArrayList() { delete[] data; }

        unsigned int size() const { return mSize; }
        unsigned int capacity() const { return mCapacity; }

        void reserve(unsigned int new_capacity) {
            if (new_capacity > mCapacity) {
                resize(new_capacity);
            }
        }

        void append(const T& item) {
            if (mSize == mCapacity) resize(mCapacity * 2);
            data[mSize++] = item;
        }

        void prepend(const T& item) {
            insert(item, 0);
        }

        void insert(const T& item, unsigned int index) {
            if (index > mSize) throw std::out_of_range("Index out of bounds");
            if (mSize == mCapacity) resize(mCapacity * 2);
            for (unsigned int i = mSize; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = item;
            mSize++;
        }

        T& at(unsigned int index) {
            if (index >= mSize) throw std::out_of_range("Index out of range");
            return data[index];
        }

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

        int find(const T& value, unsigned int start_index = 0) const {
            for (unsigned int i = start_index; i < mSize; i++) {
                if (data[i] == value) return i;
            }
            return -1;
        }

        void output(std::ostream& os) const {
            os << "[";
            for (unsigned int i = 0; i < mSize; i++) {
                os << data[i];
                if (i < mSize - 1) os << ", ";
            }
            os << "]";
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
        list.output(os);
        return os;
    }

} // namespace ssuds

#endif