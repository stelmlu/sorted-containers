/* sorted_map.hpp - v0.1 - public domain data structures - Stefan Elmlund 2024
*
*  This is a single-header-file C++11 compatible library that using sorted std::vector to implement std::map
*  to make it more cpu cache friendly.
*
*  INSTALL
*
*  The easiest way to install the library to your C/C++ project is to copy 'n' paste the sorted_map.hpp
*  to your C++ project and include it.
*
*    #include "sorted_map.hpp"
*
*  USAGE
*
*  This map support the same functionalty as [std::map](https://en.cppreference.com/w/cpp/container/map) but
*  using the namespace sel instead of std i.e. sel.sorted_map.
*
*  LICENSE
*
*  Placed in the public domain and also MIT licensed.
*  See end of file for detailed license information.
*/


#pragma once

#include <memory>
#include <vector>
#include <algorithm>

namespace sel
{
    template <class Key, class T, class Allocator = std::allocator<std::pair<Key,T>>>
    class sorted_map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<Key,T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Allocator allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename std::allocator_traits<Allocator>::pointer pointer;
        typedef typename std::allocator<Allocator>::const_pointer const_pointer;
        typedef typename std::vector<value_type>::iterator iterator;
        typedef typename std::vector<value_type>::const_iterator const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        template <class K, class V, class A>
        friend bool operator==(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool operator!=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool operator<(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool operator<=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool operator>(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool operator>=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs);
        template <class K, class V, class A>
        friend bool swap(sorted_map<K,V,A> &lhs, sorted_map<K,V,A> &rhs);
        std::vector<std::pair<Key,T>,allocator_type> m_container;

    public:

        sorted_map() : m_container({}) {}

        explicit sorted_map(const Allocator &alloc) : m_container(alloc) {}

        template <class InputIt>
        sorted_map(InputIt first, InputIt last, const Allocator &alloc = Allocator())
            : m_container(std::distance(first, last), std::pair<Key,T>(), alloc)
        {
            m_container.clear();
            for (auto itr = first; itr != last; ++itr)
            {
                insert(*itr);
            }
        }

        sorted_map(std::initializer_list<std::pair<Key,T>> init, const Allocator &alloc = Allocator())
            : m_container(std::distance(init.begin(), init.end()), std::pair<Key,T>(), alloc)
        {
            m_container.clear();
            for (auto itr = init.begin(); itr != init.end(); ++itr)
            {
                insert(*itr);
            }
        }

        sorted_map(const sorted_map &other) = default;

        sorted_map(const sorted_map &other, Allocator &alloc) : m_container(other.m_container, alloc) {}

        sorted_map(sorted_map &&other) = default;

        sorted_map(sorted_map &&other, Allocator &alloc) : m_container(other.m_container, alloc) {}

        ~sorted_map() = default;

        sorted_map &operator=(const sorted_map &other)
        {
            return m_container.operator=(other);
        }

        sorted_map &operator=(sorted_map &&other)
        {
            return m_container.operator=(other);
        }

        sorted_map &operator=(std::initializer_list<value_type> ilist)
        {
            m_container.clear();
            for (auto itr = std::begin(ilist); itr != std::end(ilist); ++itr)
            {
                insert(*itr);
            }
            return *this;
        }

        allocator_type get_allocator() const noexcept
        {
            return m_container.get_allocator();
        }

        T& at(const Key& key)
        {
            auto find_result = find(key);
            if(find_result == end()) {
                throw std::out_of_range("failed to find key in sorted_map");
            }
            return find_result->second;
        }

        const T& at(const Key& key) const
        {
            auto find_result = find(key);
            if(find_result == end()) {
                throw std::out_of_range("failed to find key in sorted_map");
            }
            return find_result->second;
        }

        T& operator[](const Key& key)
        {
            auto find_result = find(key);
            if(find_result == end()) {
                return insert(std::pair<Key,T>(key,T())).first->second;
            }
            return find_result->second;
        }

        T& operator[](Key&& key)
        {
            auto find_result = find(key);
            if(find_result == end()) {
                return insert(std::pair<Key,T>(key,T())).first->second;
            }
            return find_result->second;
        }


        iterator begin() noexcept
        {
            return m_container.begin();
        }

        const_iterator cbegin() const noexcept
        {
            return m_container.cbegin();
        }

        iterator end() noexcept
        {
            return m_container.end();
        }

        const_iterator cend() const noexcept
        {
            return m_container.cend();
        }

        reverse_iterator rbegin() noexcept
        {
            return m_container.rbegin();
        }

        const_reverse_iterator crbegin() const noexcept
        {
            return m_container.crbegin();
        }

        reverse_iterator rend() noexcept
        {
            return m_container.rend();
        }

        const_reverse_iterator crend() const noexcept
        {
            return m_container.crend();
        }

        bool empty() const noexcept
        {
            return m_container.empty();
        }

        size_type size() const noexcept
        {
            return m_container.size();
        }

        size_type max_size() const noexcept
        {
            return m_container.max_size();
        }

        void clear() noexcept
        {
            m_container.clear();
        }

        std::pair<iterator, bool> insert(const value_type &value)
        {
            auto first = std::lower_bound(std::begin(m_container), std::end(m_container), value);
            if (!(first == m_container.end()) && !(value < *first))
            {
                return std::make_pair(first, false);
            }
            else
            {
                auto itr = m_container.insert(first, value);
                return std::make_pair(itr, true);
            }
        }

        std::pair<iterator, bool> insert(value_type &&value)
        {
            auto first = std::lower_bound(std::begin(m_container), std::end(m_container), value);
            if (!(first == m_container.end()) && !(value < *first))
            {
                return std::make_pair(first, false);
            }
            else
            {
                auto itr = m_container.insert(first, value);
                return std::make_pair(itr, true);
            }
        }

        iterator insert(const_iterator pos, const value_type &value)
        {
            for (const_iterator it = (pos - 1); it != (m_container.cbegin() - 1); --it)
            {
                if (*it == value)
                {
                    return m_container.begin() + std::distance(m_container.cbegin(), it);
                }
                else if (*it < value)
                {
                    return m_container.insert(it + 1, value);
                }
            }
            return insert(value).first;
        }

        iterator insert(const_iterator pos, value_type &&value)
        {
            for (const_iterator it = (pos - 1); it != (m_container.cbegin() - 1); --it)
            {
                if (*it == value)
                {
                    m_container.begin() + std::distance(m_container.cbegin(), it);
                }
                else if (*it < value)
                {
                    return m_container.insert(it + 1, value);
                }
            }
            return insert(value).first;
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            for (auto it = first; it != last; ++it)
            {
                insert(*it);
            }
        }

        void insert(std::initializer_list<value_type> ilist)
        {
            insert(std::begin(ilist), std::end(ilist));
        }

        template <class... Args>
        std::pair<iterator, bool> emplace(Args &&...args)
        {
            auto value = value_type{args...};
            auto first = std::lower_bound(std::begin(m_container), std::end(m_container), value);
            if (!(first == m_container.end()) && !(value < *first))
            {
                return std::make_pair(first, false);
            }
            else
            {
                auto itr = m_container.emplace(first, value);
                return std::make_pair(itr, true);
            }
        }

        template <class... Args>
        iterator emplace_hint(const_iterator hint, Args &&...args)
        {
            auto value = value_type{args...};
            for (const_iterator it = (hint - 1); it != (m_container.begin() - 1); --it)
            {
                if (*it == value)
                {
                    return m_container.begin() + std::distance(m_container.cbegin(), it);
                }
                else if (*it < value)
                {
                    return m_container.emplace(it + 1, value);
                }
            }
            return emplace(value).first;
        }

        iterator erase(const_iterator pos)
        {
            return m_container.erase(pos);
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            return m_container.erase(first, last);
        }

        size_type erase(const Key &key)
        {
            auto find_result = find(key);
            if (find_result == m_container.end())
                return 0;
            m_container.erase(find_result);
            return 1;
        }

        void swap(sorted_map &other)
        {
            m_container.swap(other);
        }

        size_type count(const Key &key) const
        {
            return std::binary_search(m_container.begin(), m_container.end(), key) ? 1 : 0;
        }

        iterator find(const Key &key)
        {
            auto find_result = std::lower_bound(m_container.begin(), m_container.end(), key, [](const value_type& vt, const Key& k) {
                return vt.first < k;
            });
            if (!(find_result == m_container.end()) && !(key < find_result->first))
            {
                return find_result;
            }
            return m_container.end();
        }

        const_iterator find(const Key &key) const
        {
            auto find_result = std::lower_bound(m_container.begin(), m_container.end(), key, [](const value_type& vt, const Key& k) {
                return vt.first < k;
            });
            if (!(find_result == m_container.cend()) && !(key < find_result->first))
            {
                return find_result;
            }
            return m_container.cend();
        }

        iterator lower_bound(const Key &key)
        {
            return std::lower_bound(m_container.begin(), m_container.end(), key, [](const value_type& vt, const Key& k) {
                return vt.first < k;
            });
        }

        const_iterator lower_bound(const Key &key) const
        {
            return std::lower_bound(m_container.cbegin(), m_container.cend(), key, [](const value_type& vt, const Key& k) {
                return vt.first < k;
            });
        }

        std::pair<iterator, iterator> equal_range(const Key &key)
        {
            return std::make_pair(lower_bound(key), upper_bound(key));
        }

        std::pair<const_iterator, const_iterator> equal_range(const Key &key) const
        {
            return std::make_pair(lower_bound(key), upper_bound(key));
        }

        iterator upper_bound(const Key &key)
        {
            return std::upper_bound(m_container.begin(), m_container.end(), key, [](const Key& k, const value_type& vt) {
                return k < vt.first;
            });
        }

        const_iterator upper_bound(const Key &key) const
        {
            return std::upper_bound(m_container.cbegin(), m_container.cend(), key, [](const Key& k, const value_type& vt) {
                return k < vt.first;
            });
        }
    };

    template <class K, class V, class A>
    bool operator==(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container == rhs.m_container;
    }

    template <class K, class V, class A>
    bool operator!=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container != rhs.m_container;
    }

    template <class K, class V, class A>
    bool operator<(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container < rhs.m_container;
    }

    template <class K, class V, class A>
    bool operator<=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container <= rhs.m_container;
    }

    template <class K, class V, class A>
    bool operator>(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container > rhs.m_container;
    }

    template <class K, class V, class A>
    bool operator>=(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        return lhs.m_container >= rhs.m_container;
    }

    template <class K, class V, class A>
    void swap(const sorted_map<K,V,A> &lhs, const sorted_map<K,V,A> &rhs)
    {
        lhs.m_container.swap(rhs.m_container);
    }
}

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2023 Stefan Elmlund
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
