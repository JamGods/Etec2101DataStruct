#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), next(n), prev(p) {}
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    /// Iterator class for LinkedList
    class Iterator {
    private:
        Node* m_current;
    public:
        Iterator(Node* node) : m_current(node) {}

        T& operator*() { return m_current->data; }
        Iterator& operator++() { m_current = m_current->next; return *this; }
        Iterator& operator--() { m_current = m_current->prev; return *this; }
        bool operator==(const Iterator& other) const { return m_current == other.m_current; }
        bool operator!=(const Iterator& other) const { return m_current != other.m_current; }

        friend class LinkedList<T>;
    };

    // Constructors and Destructor
    LinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    LinkedList(std::initializer_list<T> init) : LinkedList() {
        for (const T& val : init) {
            append(val);
        }
    }

    LinkedList(const LinkedList& other) : LinkedList() {
        for (Node* curr = other.m_head; curr; curr = curr->next) {
            append(curr->data);
        }
    }

    LinkedList(LinkedList&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
        other.m_head = other.m_tail = nullptr;
        other.m_size = 0;
    }

    ~LinkedList() {
        clear();
    }

    // Assignment Operators
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            for (Node* curr = other.m_head; curr; curr = curr->next) {
                append(curr->data);
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            other.m_head = other.m_tail = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    // Core Methods
    void append(const T& value) {
        Node* newNode = new Node(value, m_tail, nullptr);
        if (m_tail) m_tail->next = newNode;
        else m_head = newNode;
        m_tail = newNode;
        ++m_size;
    }

    void prepend(const T& value) {
        Node* newNode = new Node(value, nullptr, m_head);
        if (m_head) m_head->prev = newNode;
        else m_tail = newNode;
        m_head = newNode;
        ++m_size;
    }

    void insert(size_t index, const T& value) {
        if (index > m_size) throw std::out_of_range("Index out of bounds");
        if (index == 0) { prepend(value); return; }
        if (index == m_size) { append(value); return; }

        Node* curr = m_head;
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        Node* newNode = new Node(value, curr->prev, curr);
        curr->prev->next = newNode;
        curr->prev = newNode;
        ++m_size;
    }

    T& at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        Node* curr = m_head;
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    T& operator[](size_t index) {
        return at(index);
    }

    size_t size() const {
        return m_size;
    }

    void clear() {
        Node* curr = m_head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        m_head = m_tail = nullptr;
        m_size = 0;
    }

    Iterator begin() const { return Iterator(m_head); }
    Iterator end() const { return Iterator(nullptr); }

    Iterator find(const T& value) const {
        for (Node* curr = m_head; curr; curr = curr->next) {
            if (curr->data == value) {
                return Iterator(curr);
            }
        }
        return end();
    }

    int find_index(const T& value) const {
        Node* curr = m_head;
        int idx = 0;
        while (curr) {
            if (curr->data == value) return idx;
            curr = curr->next;
            ++idx;
        }
        return -1;
    }

    void remove(Iterator it) {
        Node* node = it.m_current;
        if (!node) return;

        if (node->prev) node->prev->next = node->next;
        else m_head = node->next;

        if (node->next) node->next->prev = node->prev;
        else m_tail = node->prev;

        delete node;
        --m_size;
    }

    void remove_at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");

        Node* curr = m_head;
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        remove(Iterator(curr));
    }

    void remove_all(const T& value) {
        for (Node* curr = m_head; curr;) {
            Node* next = curr->next;
            if (curr->data == value) {
                remove(Iterator(curr));
            }
            curr = next;
        }
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "[";
        for (Node* curr = m_head; curr; curr = curr->next) {
            oss << curr->data;
            if (curr->next) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        os << list.to_string();
        return os;
    }
};

#endif // LINKED_LIST_H