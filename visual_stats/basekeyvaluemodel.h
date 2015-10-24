#pragma once

#include <QAbstractTableModel>
#include <vector>

template <class TKey, class TValue>
class BaseKeyValueModel
{
public:
    typedef std::pair<TKey, TValue> Item;
    typedef std::vector<Item> ItemArray;
    typedef typename ItemArray::iterator iterator;
    typedef typename ItemArray::const_iterator const_iterator;

    TKey const& key(size_t i) const
    {
        return m_items[i].first;
    }

    void setKey(size_t i, TKey const& key)
    {
        m_items[i].first = key;
    }

    TValue value(size_t i) const
    {
        return m_items[i].second;
    }

    void setValue(size_t i, TValue const& value)
    {
        m_items[i].second = value;
    }

    size_t size() const
    {
        return m_items.size();
    }

    const_iterator begin() const
    {
        return m_items.begin();
    }

    iterator begin()
    {
        return m_items.begin();
    }

    const_iterator end() const
    {
        return m_items.end();
    }

    iterator end()
    {
        return m_items.end();
    }

    void append(TKey const& key, TValue const& value)
    {
        m_items.push_back(Item(key, value));
    }

    void insert(int index, TKey const& key, TValue const& value)
    {
        m_items.insert(m_items.begin() + index, Item(key, value));
    }

    bool operator == (const BaseKeyValueModel& other) const
    {
        if (m_items.size() != other.size())
        {
            return false;
        }
        for (unsigned int i = 0; i < m_items.size(); ++i)
        {
            if (key(i) != other.key(i) ||
                value(i) != other.value(i))
            {
                return false;
            }
        }
        return true;
    }

    bool operator != (const BaseKeyValueModel& other) const
    {
        return !(*this == other);
    }

protected:
    ItemArray m_items;
};
