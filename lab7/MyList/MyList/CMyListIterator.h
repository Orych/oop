#pragma once

#include "CMyListNode.h"
#include <iterator>
#include <stdexcept>

template <typename T>
class CMyListConstIterator;

template <typename T>
class CMyList;

template <typename T>
class CMyListIteratorBase
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    bool operator!=(const CMyListIteratorBase& other) const
    {
        return m_nodePtr != other.m_nodePtr;
    }

    bool operator==(const CMyListIteratorBase& other) const
    {
        return m_nodePtr == other.m_nodePtr;
    }

    reference operator*() const
    {
        return m_nodePtr->m_data;
    }

    pointer operator->() const
    {
        return &m_nodePtr->m_data;
    }

    CMyListIteratorBase& operator++()
    {
        m_nodePtr = m_nodePtr->m_next;
        return *this;
    }

    CMyListIteratorBase& operator--()
    {
        m_nodePtr = m_nodePtr->m_prev;
        return *this;
    }

    CMyListIteratorBase operator++(int)
    {
        CMyListIteratorBase tmp(*this);
        ++(*this);
        return tmp;
    }

    CMyListIteratorBase operator--(int)
    {
        CMyListIteratorBase tmp(*this);
        --(*this);
        return tmp;
    }

public:
    CMyListNode<T>* m_nodePtr;

    CMyListIteratorBase(CMyListNode<T>* node)
        : m_nodePtr(node)
    {
    }
};

template <typename T>
class CMyListIterator : public CMyListIteratorBase<T>
{
    friend class CMyList<T>;

public:
    CMyListIterator(CMyListNode<T>* node)
        : CMyListIteratorBase<T>(node)
    {
    }
};

template <typename T>
class CMyListConstIterator : public CMyListIteratorBase<T>
{
    friend class CMyList<T>;

public:
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;

    CMyListConstIterator(CMyListNode<T>* node)
        : CMyListIteratorBase<T>(node)
    {
    }

    CMyListConstIterator(const CMyListIterator<T>& other)
        : CMyListIteratorBase<T>(other.m_nodePtr)
    {
    }
};