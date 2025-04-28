#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>

namespace ssuds
{
    template<typename KeyType, typename ValueType>
    class Map
    {
    protected:
        struct Entry
        {
            KeyType m_key;
            ValueType m_value;
            bool m_active;

            Entry(const KeyType& key, const ValueType& value)
                : m_key(key), m_value(value), m_active(true)
            {}
        };

        Entry** m_table;
        size_t m_size;
        size_t m_capacity;
        static constexpr float LOAD_FACTOR_THRESHOLD = 0.7f;
        static constexpr size_t INITIAL_CAPACITY = 8;

        size_t hash(const KeyType& key) const
        {
            return std::hash<KeyType>{}(key);
        }

        void grow()
        {
            size_t old_capacity = m_capacity;
            m_capacity *= 2;
            Entry** old_table = m_table;
            m_table = new Entry * [m_capacity]();
            m_size = 0;

            for (size_t i = 0; i < old_capacity; ++i)
            {
                if (old_table[i] != nullptr && old_table[i]->m_active)
                {
                    (*this)[old_table[i]->m_key] = old_table[i]->m_value;
                }
                delete old_table[i];
            }
            delete[] old_table;
        }

        size_t find_index(const KeyType& key) const
        {
            size_t idx = hash(key) % m_capacity;
            size_t start_idx = idx;

            while (m_table[idx] != nullptr)
            {
                if (m_table[idx]->m_active && m_table[idx]->m_key == key)
                    return idx;

                idx = (idx + 1) % m_capacity;
                if (idx == start_idx)
                    break;  // table full, avoid infinite loop
            }
            return m_capacity;  // not found
        }

        size_t find_insert_index(const KeyType& key)
        {
            size_t idx = hash(key) % m_capacity;
            while (m_table[idx] != nullptr && m_table[idx]->m_active)
            {
                idx = (idx + 1) % m_capacity;
            }
            return idx;
        }

    public:
        Map()
            : m_size(0), m_capacity(INITIAL_CAPACITY)
        {
            m_table = new Entry * [m_capacity]();
        }

        ~Map()
        {
            for (size_t i = 0; i < m_capacity; ++i)
            {
                delete m_table[i];
            }
            delete[] m_table;
        }

        ValueType& operator[](const KeyType& key)
        {
            size_t idx = find_index(key);

            if (idx != m_capacity)
            {
                return m_table[idx]->m_value;
            }
            else
            {
                if (static_cast<float>(m_size + 1) / m_capacity > LOAD_FACTOR_THRESHOLD)
                {
                    grow();
                }

                size_t insert_idx = find_insert_index(key);

                if (m_table[insert_idx] != nullptr)
                    delete m_table[insert_idx];

                m_table[insert_idx] = new Entry(key, ValueType{});
                ++m_size;
                return m_table[insert_idx]->m_value;
            }
        }

        bool contains(const KeyType& key) const
        {
            return find_index(key) != m_capacity;
        }

        bool remove(const KeyType& key)
        {
            size_t idx = find_index(key);
            if (idx != m_capacity)
            {
                m_table[idx]->m_active = false;
                --m_size;
                return true;
            }
            return false;
        }

        size_t size() const
        {
            return m_size;
        }

        friend std::ostream& operator<<(std::ostream& os, const Map& m)
        {
            for (size_t i = 0; i < m.m_capacity; ++i)
            {
                if (m.m_table[i] != nullptr && m.m_table[i]->m_active)
                {
                    os << m.m_table[i]->m_key << ":" << m.m_table[i]->m_value << "\n";
                }
            }
            return os;
        }
    };
}
