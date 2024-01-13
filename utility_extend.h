// <utility_extend.h> -*- C++ -*-

// Copyright (C) 2022-2024  CheatMay
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef _LIBSEREVIA_UTILITY_EXTEND_H
#define _LIBSEREVIA_UTILITY_EXTEND_H 1

/** @file utility_extend.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include <vector>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    std::vector<std::size_t> range(const std::size_t &_n)
    {
        if (_n == 0)
            return std::vector<std::size_t>();
        std::vector<std::size_t> _seq(_n);
        for (int i = 0; i < _n; i++)
            _seq[i] = i;
        return _seq;
    }
    
    std::vector<std::size_t>
    range(const std::size_t &_begin, const std::size_t &_end, const long &_step = 1)
    {
        if (_begin == _end)
            return std::vector<std::size_t>();
        std::vector<std::size_t> _seq((_end - _begin - 1) / _step + 1);
        for (int i = _begin; _begin < _end ? i < _end : i > _end; i += _step)
            _seq[i] = i;
        return _seq;
    }
    
    template<typename T>
    int find(T *_arr, std::size_t _len, T _tar)
    {
        for (int i = 0; i < _len; i++)
            if (_arr[i] == _tar)
                return i;
        return -1;
    }
    
    template<typename _Tp1, typename _Tp2>
    inline bool is_same()
    { return std::is_same<_Tp1, _Tp2>::value; }
    
    template<typename _Tp1, typename _Tp2>
    inline bool is_not_same()
    { return !std::is_same<_Tp1, _Tp2>::value; }
    
    template<typename _Tp1, typename _Tp2>
    inline bool is_same(_Tp1 _x, _Tp2 _y)
    { return std::is_same<_Tp1, _Tp2>::value; }
    
    template<typename _Tp1, typename _Tp2>
    inline bool is_not_same(_Tp1 _x, _Tp2 _y)
    { return !std::is_same<_Tp1, _Tp2>::value; }
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif