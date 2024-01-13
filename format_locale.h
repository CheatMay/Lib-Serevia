// <format_locale.h> -*- C++ -*-

// Copyright (C) 2023-2024  CheatMay
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

#ifndef _LIBSEREVIA_FORMAT_LOCALE_H
#define _LIBSEREVIA_FORMAT_LOCALE_H 1

// This header is an internal header included by other library
// headers. Never include this file directly.
#ifndef _LIBSEREVIA_FORMATSTREAM_H
#error do not include this file directly
#endif

#include "formatfwd.h"
#include "localr.h"
#include <termios.h>
#include <unistd.h>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    template<typename _CharT = char, typename _Traits = std::char_traits<_CharT>>
    bool kbhit(std::basic_streambuf<_CharT, _Traits> *sb = &buf_cin_sync)
    {
        struct termios a, b;
        int ch;
        tcgetattr(STDIN_FILENO, &a);
        b = a;
        b.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &b);
        ch = sb->sgetc();
        tcsetattr(STDIN_FILENO, TCSANOW, &a);
        return ch != std::char_traits<_CharT>::eof();
    }
    
    template<typename _CharT = char, typename _Traits = std::char_traits<_CharT>>
    int getch(std::basic_streambuf<_CharT, _Traits> *sb = &buf_cin_sync)
    {
        struct termios a, b;
        int ch;
        tcgetattr(STDIN_FILENO, &a);
        b = a;
        b.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &b);
        ch = sb->sbumpc();
        tcsetattr(STDIN_FILENO, TCSANOW, &a);
        return ch;
    }
    
    template<typename _CharT>
    bool isvisible(_CharT c)
    { return static_cast<int>(c) >= 32 && static_cast<int>(c) <= 126; }
    
    bool iszh(wchar_t c)
    {
        int u = static_cast<int>(c);
        auto check = [u](int a, int b)->bool
        { return u >= a && u <= b; };
        return check(0x4E00,  0x9FA5)
            || check( 0x9FA6,  0x9FFF)
            || check( 0x3400,  0x4DBF)
            || check(0x20000, 0x2A6DF)
            || check(0x2A700, 0x2B739)
            || check(0x2B740, 0x2B81D)
            || check(0x2B820, 0x2CEA1)
            || check(0x2CEB0, 0x2EBE0)
            || check(0x30000, 0x3134A)
            || check(0x31350, 0x323AF)
            || check( 0x2F00,  0x2FD5)
            || check( 0x2E80,  0x2EF3)
            || check( 0xF900,  0xFAD9)
            || check(0x2F800, 0x2FA1D)
            || check( 0x31C0,  0x31E3)
            || check( 0x2FF0,  0x2FFB)
            || check( 0x3105,  0x312F)
            || check( 0x31A0,  0x31BF)
            || u == 0x3007;
    }
    
    bool iszh(char c[3])
    { return iszh(localr::codecvt<char, wchar_t>::in(c)); }
    
    bool iszhpunct(wchar_t c)
    {
        int u = static_cast<int>(c);
        return u == 0x3002
            || u == 0xFF1F
            || u == 0xFF01
            || u == 0x3010
            || u == 0x3011
            || u == 0xFF0C
            || u == 0x3001
            || u == 0xFF1B
            || u == 0xFF1A
            || u == 0x300C
            || u == 0x300D
            || u == 0x300E
            || u == 0x300F
            || u == 0x2019
            || u == 0x201C
            || u == 0x201D
            || u == 0x2018
            || u == 0xFF08
            || u == 0xFF09
            || u == 0x3014
            || u == 0x3015
            || u == 0x2026
            || u == 0x2013
            || u == 0xFF0E
            || u == 0x2014
            || u == 0x300A
            || u == 0x300B
            || u == 0x3008
            || u == 0x3009;
    }
    
    bool iszhpunct(char c[3])
    { return iszhpunct(localr::codecvt<char, wchar_t>::in(c)); }
    
    bool isonewidthzhpunct(wchar_t c)
    {
        int u = static_cast<int>(c);
        return u == 0x2026
            || u == 0x2013
            || u == 0x2014
            || u == 0x2019
            || u == 0x201C
            || u == 0x201D
            || u == 0x2018;
    }
    
    bool isonewidthzhpunct(char c[3])
    { return isonewidthzhpunct(localr::codecvt<char, wchar_t>::in(c)); }

    bool isjp(wchar_t c)
    {
        int u = static_cast<int>(c);
        auto check = [u](int a, int b)->bool
        { return u >= a && u <= b; };
        return check(0x3040, 0x309F)
            || check(0x30A0, 0x30FF)
            || check(0x31F0, 0x31FF);
    }
    
    bool isjp(char c[3])
    { return isjp(localr::codecvt<char, wchar_t>::in(c)); }
    
    // ÅÐ¶Ï×Ö·û´®ÊÇ·ñÈ«Îª×ÖÄ¸
    bool isalpha(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (!std::isalpha(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÖÐ×ÖÄ¸ÊÇ·ñÈ«ÎªÐ¡Ð´
    bool isalphalower(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (std::isupper(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÖÐ×ÖÄ¸ÊÇ·ñÈ«Îª´óÐ´
    bool isalphaupper(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (std::islower(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÊÇ·ñÈ«ÎªÐ¡Ð´×ÖÄ¸
    bool islower(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (!std::islower(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÊÇ·ñÈ«Îª´óÐ´×ÖÄ¸
    bool isupper(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (!std::isupper(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶ÏÃ¿¸ö´ÊµÄÊ××ÖÄ¸ÊÇ·ñ´óÐ´
    bool istitle(const std::string str, char split = ' ')
    {
        for (int i = 1; i < str.size(); i++)
            if (std::islower(str[i]) && str[i - 1] == split)
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÖÐÊÇ·ñÈ«ÎªÊý×Ö
    bool isdigit(const std::string str)
    {
        for (int i = 0; i < str.size(); i++)
            if (!std::isdigit(str[i]))
                return false;
        return true;
    }
    
    // ÅÐ¶Ï×Ö·û´®ÊÇ·ñÎªÊý×Ö
    bool isnum(const std::string str)
    {
        bool dot = false;
        int start = 0;
        if (str[0] == '+' || str[0] == '-')
            start++;
        for (int i = start; i <= str.size() - 1; i++)
        {
            if (!(std::isdigit(str[i]) || str[i] == '.'))
                return false;
            if (str[i] == '.')
            {
                if (i == start || i == str.size() - 1 || dot)
                    return false;
                dot = true;
            }
        }
        return true;
    }
    
    // Í³¼Æ´ÊÊý
    size_t countwords(const std::string str, char split = ' ')
    {
        if (str.size() == 0)
            return 0;
        int t = str.size() - 1, cnt = 0;
        for (int i = t; i >= 0; i--)
        {
            if (str[i] != split)
            {
                t = i;
                break;
            }
        }
        for (int i = 0; i <= t; )
        {
            while (str[i] != split)
                i++;
            cnt++;
        }
        return cnt;
    }
    
    std::wstring width_temp_ch;
    std::vector<unsigned char> width_temp_len;
    
    template<typename _CharT = wchar_t, typename _Traits = std::char_traits<_CharT> >
    size_t width(std::wstring str,
        std::basic_streambuf<_CharT, _Traits> *sb = &buf_wcout_sync,
        bool do_acc = false)
    {
        size_t len = 0;
        bool tab = false;
        size_t w = 63;
        int t = -1;
        std::wstring emoji;
        for (auto &&i : str)
        {
            if (static_cast<int>(i) == 9)
            {
                size_t x = len % w;
                size_t x2 = x;
                if (tab)
                    x2 = std::max(std::min(x, w - 1), std::min(x + 8, w - 1));
                else
                {
                    tab = true;
                    x2 = std::max(std::min(x, w - 1), std::min(x + 8, w - 2));
                }
                len = len + x2 - x;
            }
            if (isvisible(i) || isonewidthzhpunct(i))
                len++;
            else if (iszh(i) || isjp(i) || iszhpunct(i))
                len += 2;
            else if (!do_acc)
                len++;
            else
            {
                t = width_temp_ch.find(i);
                if (t == -1)
                {
                    sb->sputn(L"\033[?1049h\033[8m\033[?25l\033[2J\033[1;1H", 28);
                    sb->sputn(&i, 1);
                    sb->sputn(L"1", 1);
                    sb->sputn(L"\033[6n", 4);
                    std::string s;
                    char ch = 0;
                    while (ch != 'R')
                    {
                        ch = getch();
                        s += ch;
                    }
                    sb->sputn(L"\033[?25h\033[?1049l", 14);
                    unsigned char tl = stoi(s.substr(s.find(';') + 1, s.size() - 1)) - 2;
                    width_temp_ch += i;
                    width_temp_len.push_back(tl);
                }
                else
                    len += static_cast<size_t>(width_temp_len[t]);
            }
        }
        return len;
    }
    
    template<typename _CharT = wchar_t, typename _Traits = std::char_traits<_CharT> >
    size_t width(std::string str,
        std::basic_streambuf<_CharT, _Traits> *sb = &buf_wcout_sync,
        bool do_acc = false)
    { return width(localr::string_convert<localr::codecvt<char, wchar_t> >::in(str), sb, do_acc); }
    
    template<typename _CharT, typename _OutIter>
    class format_num_put : std::num_put<_CharT, _OutIter>
    {
        public:
        using char_type = _CharT;
        using iter_type = _OutIter;
        
        explicit
        format_num_put(): std::num_put<_CharT, _OutIter>()
        { }
        
        ~format_num_put() = default;
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, bool __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, short __v) const
        { return this->do_put(__s, __io, __fill, static_cast<long>(__v)); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, unsigned short __v) const
        { return this->do_put(__s, __io, __fill, static_cast<unsigned long>(__v)); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, int __v) const
        { return this->do_put(__s, __io, __fill, static_cast<long>(__v)); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, unsigned __v) const
        { return this->do_put(__s, __io, __fill, static_cast<unsigned long>(__v)); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, long __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, unsigned long __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, long long __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, unsigned long long __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, float __v) const
        { return this->do_put(__s, __io, __fill, static_cast<double>(__v)); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, double __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, long double __v) const
        { return this->do_put(__s, __io, __fill, __v); }
        
        iter_type
        put(iter_type __s, std::ios_base& __io, char_type __fill, const void *__v) const
        { return this->do_put(__s, __io, __fill, __v); }
    };

_GLIBCXX_END_NAMESPACE_VERSION
}

#endif