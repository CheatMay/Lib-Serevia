// <random.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_RANDOM_H
#define _LIBSEREVIA_RANDOM_H 1

/** @file random.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include <random>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class
    {
        public:
        
        template<typename _Tp>
        _Tp integer(_Tp min, _Tp max)
        {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<_Tp> dis(min, max);
            return dis(gen);
        }
        
        template<typename _Tp>
        std::vector<_Tp> integer(size_t n, _Tp min, _Tp max)
        {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<_Tp> dis(min, max);
            std::vector<_Tp> ret;
            for (int i = 0; i < n; i++)
                ret.push_back(dis(gen));
            return ret;
        }
        
        template<typename _Tp>
        _Tp decimal(_Tp min, _Tp max)
        {
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<_Tp> dis(min, max);
            return dis(gen);
        }
        
        template<typename _Tp>
        std::vector<_Tp> decimal(size_t n, _Tp min, _Tp max)
        {
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<_Tp> dis(min, max);
            std::vector<_Tp> ret;
            for (int i = 0; i < n; i++)
                ret.push_back(dis(gen));
            return ret;
        }
        
        int randint(int min, int max)
        { return integer<int>(min, max); }
        
        std::vector<int> randint(size_t n, int min, int max)
        { return integer<int>(n, min, max); }
        
        bool possibility(long double p)
        {
            if (decimal<long double>(0.0, 1.0) <= p)
                return true;
            return false;
        }
        
        char letter(unsigned short caps = 2, char start = 'a', char end = 'z')
        {
            if (start < 97)
                start += 32;
            if (end < 97)
                end += 32;
            char letter = randint(start, end);
            if (caps == 1)
                letter -= 32;
            else if (caps == 2)
                letter -= randint(0, 1) * 32;
            return letter;
        }
        
        std::string password(size_t minlen, size_t maxlen, bool cap)
        {
            std::string pswd, s;
            if (cap)
                s = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_";
            else
                s = "1234567890qwertyuiopasdfghjklzxcvbnm_";
            for (int i = 0; i <= randint(minlen, maxlen) - 1; i++)
                pswd += s[randint(0, s.size() - 1)];
            return pswd;
        }
    } random;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif