// <search.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_SEARCH_H
#define _LIBSEREVIA_SEARCH_H 1

/** @file search.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include <iostream>
#include <vector>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    struct search_result
    {
        std::string text, target;
        bool result;
        std::vector<std::pair<int, int> > matched_words;
        double precision;
    };
    
    class
    {
        private:
        bool letter_cmp(char ch1, char ch2)
        {
            return ch1 == ch2 ? true : (isalpha(ch1) && isalpha(ch2) ? (islower(ch1) ? ch1 - ch2 == 32 : ch2 - ch1 == 32) : false);
        }
        
        std::pair<int, int> weakened_find(const std::string &text, const std::string &keyword)
        {
            int start = -1, len = 0;
            int text_len = text.size(), keyword_len = keyword.size();
            if (text_len == 0 || keyword_len == 0 || text_len < keyword_len)
                return std::make_pair(-1, 0);
            for (int i = 0; i <= text_len - keyword_len; i++)
            {
                if (text[i] == ' ')
                    continue;
                int j = i, k = 0, flag = i;
                while (j < text_len && k < keyword_len)
                {
                    if (text[j] == ' ')
                        j++;
                    /*
                    if (keyword[k] == ' ')
                        k++;
                    */
                    if (letter_cmp(text[j], keyword[k]))
                        j++, k++;
                    else
                        break;
                }
                if (k == keyword_len)
                {
                    start = flag;
                    len = j - flag;
                    break;
                }
            }
            return std::make_pair(start, len);
        }
        
        double precision = 0.5;
        
        public:
        
        // ÉèÖÃËÑË÷¾«¶È
        void set_search_precision(double val)
        { precision = val; }
        
        // ÐÇÕ¶ËÑË÷ÒýÇæ
        search_result search(const std::string &text, const std::string &target)
        {
            search_result res;
            res.text = text, res.target = target;
            res.result = 0;
            res.precision = 0;
            
            int text_len = text.size(), target_len = target.size();
            if (text_len == 0 || target_len == 0)
                return res;
            std::vector<std::string> keywords(1);
            for (int i = 0, j = 0; i < target_len; i++)
            {
                if (target[i] == ' ')
                    continue;
                else if (i > 0)
                {
                    if (target[i - 1] == ' ')
                    {
                        keywords.push_back("");
                        j++;
                    }
                }
                keywords[j] += target[i];
            }
            int prec = 0;
            
            for (int i = 0; i <= keywords.size() - 1; i++)
            {
                std::string keyword = keywords[i], _text = text;
                int len = keyword.size();
                int temp = 0;
                while (1)
                {
                    std::pair<int, int> _res = weakened_find(_text, keyword);
                    if (_res.first == -1)
                        break;
                    else
                    {
                        res.matched_words.push_back(std::make_pair(temp + _res.first, _res.second));
                        _text = _text.substr(_res.first + _res.second, _text.size() - 1);
                        prec += len;
                        temp += _res.first + _res.second;
                    }
                }
            }
            
            if (prec != 0)
            {
                std::sort(res.matched_words.begin(), res.matched_words.end(), [](std::pair<int, int> a, std::pair<int, int> b){return a.first < b.first;});
                res.result = 1;
                res.precision = (prec * 1.0) * (prec * 1.0) / (text_len * 1.0) / (target_len * 1.0);
                if (res.precision < precision)
                    res.result = 0;
            }
            return res;
        }
        
        // Êä³ö¹Ø¼ü×Ö
        void print_match(const search_result res, bool clear/*ÊÇ·ñÊä³öÆ¥Åä×´Ì¬*/)
        {
            if (res.precision < precision)
            {
                if (clear)
                    std::cout << "precision too low";
                return;
            }
            else if (res.result == 0)
            {
                if (clear)
                    std::cout << "no keywords found";
                return;
            }
            for (int i = 0, j = 0; i < res.text.size(); i++)
            {
                if (i == res.matched_words[j].first)
                {
                    std::cout << "\033[31m";
                    while (i != res.matched_words[j].first + res.matched_words[j].second)
                    {
                        std::cout << res.text[i];
                        i++;
                    }
                    std::cout << "\033[0m";
                    j++;
                }
                std::cout << res.text[i];
            }
        }
    } search_engine;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif