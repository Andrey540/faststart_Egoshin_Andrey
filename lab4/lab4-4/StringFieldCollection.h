#include "StringField.h"
#include <memory>
#include <algorithm>

#pragma once

template <class CStringField>
class CStringFieldCollection
{
    typedef std::shared_ptr<CStringField> StringFieldPtr;

public:
    CStringFieldCollection(void){};
    ~CStringFieldCollection(void){};

    bool Add(const std::string& element)
    {
        if (IsContain(element) || element.length() == 0)
        {
            return false;
        }
        m_Collection.push_back(std::make_shared<CStringField>(CStringField(element)));
        return true;
    }

    bool Add(const CStringField& element)
    {
        if (IsContain(element) || element.GetValue().length() == 0)
        {
            return false;
        }
        m_Collection.push_back(std::make_shared<CStringField>(element));
        return true;
    }

    bool Delete(CStringField& element)
    {
        StringFieldPtr elementPtr = std::make_shared<CStringField>(element);
        auto i = std::find_if(m_Collection.begin(), m_Collection.end(),
            [elementPtr](StringFieldPtr itemPtr)
            {
                CStringField element = *elementPtr;
                CStringField item = *itemPtr;
                return element == item;                
            });

        if (i == m_Collection.end())
        {
            return false;
        }

        m_Collection.erase(i);
        return true;
    }    

    bool Delete(unsigned index)
    {
        if (index >= m_Collection.size())
        {
            return false;
        }
        m_Collection.erase(m_Collection.begin() + index);
        return true;
    }

    bool Change(unsigned index, const CStringField& element)
    {
        if (IsContain(element, index) || element.GetValue().length() == 0 || index >= m_Collection.size())
        {
            return false;
        }
        m_Collection[index] = std::make_shared<CStringField>(element);
        return true;
    }

    unsigned GetSize() const
    {
        return m_Collection.size();
    }

    int GetIndex(CStringField& value) const
    {
        int count = 0;
        for(auto &item : m_Collection)
        {
            if (item->GetValue() == value.GetValue())
            {
                return count;
            }
            ++count;
        }

        return -1;
    }

    std::vector<StringFieldPtr> GetMatches(const std::string& str) const
    {
        std::vector<StringFieldPtr> result;
        for(StringFieldPtr elementPtr : m_Collection)
        {
            CStringField element = *elementPtr;
            if (element.IsMatches(str))
            {
                result.push_back(std::make_shared<CStringField>(element));
            }
        }
        return result;
    }

    std::vector<StringFieldPtr> GetCollection() const
    {
        std::vector<StringFieldPtr> result;
        for(StringFieldPtr elementPtr : m_Collection)
        {
            CStringField element = *elementPtr;
            result.push_back(std::make_shared<CStringField>(element));
        }
        return result;
    }

    bool IsMatches(const std::string& str) const
    {
        for(auto element : m_Collection)
        {
            if (element->IsMatches(str))
            {
                return true;
            }
        }

        return false;
    }

    bool IsContain(const std::string& str, int withoutElement = -1) const
    {
        int count = 0;
        for(auto element : m_Collection)
        {
            if (element->IsEqual(str) && count != withoutElement)
            {
                return true;
            }
            ++count;
        }

        return false;
    }

    void Print(std::string ident = "") const
    {
        for(auto item : m_Collection)
        {
            item->Print(ident);
        }
    }

    bool IsContain(const CStringField& other, int withoutElement = -1) const
    {
        return IsContain(other.GetValue(), withoutElement);
    }

    bool const operator == (const CStringFieldCollection& other)
    {
        std::vector<StringFieldPtr> otherCollection = other.GetCollection();

        if (m_Collection.size() != otherCollection.size())
        {
            return false;
        }

        for(unsigned i = 0; i < m_Collection.size(); ++i)
        {
            if (*m_Collection[i] != *otherCollection[i])
            {
                return false;
            }
        }
        return true;
    }    

    CStringFieldCollection operator = (const CStringFieldCollection& other)
    {
        m_Collection.clear();
        auto collection = other.GetCollection();
        for(unsigned i = 0; i < collection.size(); ++i)
        {
            CStringField item = *collection[i];
            Add(item);
        }
    }    

private:
    std::vector<StringFieldPtr> m_Collection;
};

