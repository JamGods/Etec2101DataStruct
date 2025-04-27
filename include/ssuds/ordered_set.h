// ordered_set.h
#pragma once

#include <iostream>
#include <vector>
#include <optional>

namespace ssuds
{
    enum class Traversal { PRE_ORDER, IN_ORDER, POST_ORDER };

    template<typename T>
    class OrderedSet
    {
    protected:
        struct Node
        {
            T m_data;
            Node* m_left;
            Node* m_right;

            Node(const T& val) : m_data(val), m_left(nullptr), m_right(nullptr) {}

            void insert(const T& val)
            {
                if (val < m_data)
                {
                    if (m_left)
                        m_left->insert(val);
                    else
                        m_left = new Node(val);
                }
                else if (val > m_data)
                {
                    if (m_right)
                        m_right->insert(val);
                    else
                        m_right = new Node(val);
                }
                // If val == m_data, do nothing (no duplicates)
            }

            void traverse(std::vector<T>& out, Traversal order) const
            {
                if (order == Traversal::PRE_ORDER)
                    out.push_back(m_data);
                if (m_left)
                    m_left->traverse(out, order);
                if (order == Traversal::IN_ORDER)
                    out.push_back(m_data);
                if (m_right)
                    m_right->traverse(out, order);
                if (order == Traversal::POST_ORDER)
                    out.push_back(m_data);
            }

            bool contains(const T& val) const
            {
                if (val == m_data)
                    return true;
                if (val < m_data && m_left)
                    return m_left->contains(val);
                if (val > m_data && m_right)
                    return m_right->contains(val);
                return false;
            }

            int get_height() const
            {
                int left_height = m_left ? m_left->get_height() : 0;
                int right_height = m_right ? m_right->get_height() : 0;
                return 1 + std::max(left_height, right_height);
            }

            void clear()
            {
                if (m_left) { m_left->clear(); delete m_left; m_left = nullptr; }
                if (m_right) { m_right->clear(); delete m_right; m_right = nullptr; }
            }

            int size() const
            {
                int count = 1;
                if (m_left) count += m_left->size();
                if (m_right) count += m_right->size();
                return count;
            }

            std::optional<T> get_parent(const T& val, const Node* parent = nullptr) const
            {
                if (val == m_data)
                    return parent ? std::optional<T>(parent->m_data) : std::nullopt;
                else if (val < m_data && m_left)
                    return m_left->get_parent(val, this);
                else if (val > m_data && m_right)
                    return m_right->get_parent(val, this);
                else
                    return std::nullopt;
            }
        };

        Node* m_root;

    public:
        OrderedSet() : m_root(nullptr) {}

        ~OrderedSet() { clear(); }

        void insert(const T& val)
        {
            if (m_root)
                m_root->insert(val);
            else
                m_root = new Node(val);
        }

        bool contains(const T& val) const
        {
            if (!m_root) return false;
            return m_root->contains(val);
        }

        void clear()
        {
            if (m_root)
            {
                m_root->clear();
                delete m_root;
                m_root = nullptr;
            }
        }

        int size() const
        {
            return m_root ? m_root->size() : 0;
        }

        int get_height() const
        {
            return m_root ? m_root->get_height() : 0;
        }

        std::vector<T> traversal(Traversal order) const
        {
            std::vector<T> output;
            if (m_root)
                m_root->traverse(output, order);
            return output;
        }

        std::optional<T> get_parent(const T& val) const
        {
            if (!m_root) return std::nullopt;
            return m_root->get_parent(val);
        }

        void rebalance()
        {
            if (!m_root) return;

            std::vector<T> nodes = traversal(Traversal::IN_ORDER);
            clear();
            m_root = rebalance_helper(nodes, 0, nodes.size() - 1);
        }

    protected:
        Node* rebalance_helper(const std::vector<T>& nodes, int start, int end)
        {
            if (start > end)
                return nullptr;
            int mid = (start + end) / 2;
            Node* node = new Node(nodes[mid]);
            node->m_left = rebalance_helper(nodes, start, mid - 1);
            node->m_right = rebalance_helper(nodes, mid + 1, end);
            return node;
        }
    };

    // Stream operator <<
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const OrderedSet<T>& set)
    {
        std::vector<T> values = set.traversal(Traversal::IN_ORDER);
        for (const auto& val : values)
            os << val << " ";
        return os;
    }
}
