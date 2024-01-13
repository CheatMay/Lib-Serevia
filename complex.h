// <complex.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_COMPLEX_H
#define _LIBSEREVIA_COMPLEX_H

/** @file complex.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "real.h"
#include <complex>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class complex
    {
        public:
        using val_type = real;
        
        private:
        // Data members
        val_type _real;
        val_type _imag;
        
        public:
        complex(): _real(), _imag()
        { }
        
        complex(real _Real, real _Imag): _real(_Real), _imag(_Imag)
        { }
        
        complex(std::string _Real, std::string _Imag): _real(_Real), _imag(_Imag)
        { }
        
        complex(fraction _Real, fraction _Imag): _real(_Real), _imag(_Imag)
        { }
        
        complex(long double _Real, long double _Imag): _real(_Real), _imag(_Imag)
        { }
        
        complex(real _Real): _real(_Real), _imag(0)
        { }
        
        complex(std::string _Real): _real(_Real), _imag(0)
        { }
        
        complex(fraction _Real): _real(_Real), _imag(0)
        { }
        
        complex(long double _Real): _real(_Real), _imag(0)
        { }
        
        inline real real() const
        { return _real; }
        
        class real real(const class real &_Real)
        {
            const class real _old = _real;
            _real = _Real;
            return _old;
        }
        
        class real real(const std::string &_Real)
        {
            const class real _old = _real;
            _real = _Real;
            return _old;
        }
        
        class real real(const fraction &_Real)
        {
            const class real _old = _real;
            _real = _Real;
            return _old;
        }
        
        class real real(long double _Real)
        {
            const class real _old = _real;
            _real = _Real;
            return _old;
        }
        
        inline class real imag() const
        { return _imag; }
        
        class real imag(const class real &_Imag)
        {
            const class real _old = _imag;
            _imag = _Imag;
            return _old;
        }
        
        class real imag(const std::string &_Imag)
        {
            const class real _old = _imag;
            _imag = _Imag;
            return _old;
        }
        
        class real imag(const fraction &_Imag)
        {
            const class real _old = _imag;
            _imag = _Imag;
            return _old;
        }
        
        class real imag(long double _Imag)
        {
            const class real _old = _imag;
            _imag = _Imag;
            return _old;
        }
        
        std::string type() const
        {
            if (!imag())
                return real().type();
            if (!real())
                return "I";
            return "C";
        }
        
        inline complex &operator +=(const complex &_rhs)
        {
            _real += _rhs._real;
            _imag += _rhs._imag;
            return *this;
        }
        
        inline complex &operator -=(const complex &_rhs)
        {
            _real -= _rhs._real;
            _imag -= _rhs._imag;
            return *this;
        }
        
        inline complex &operator *=(const complex &_rhs)
        {
            _real = _real * _rhs._real - _imag * _rhs._imag;
            _imag = _real * _rhs._imag + _imag * _rhs._real;
            return *this;
        }
        
        inline complex &operator /=(const complex &_rhs)
        {
            // 1 / (a + bi) = (a - bi) / (a ^ 2 + b ^ 2)
            _real = (_rhs._real * _real + _rhs._imag * _imag)
                / (_rhs._real * _rhs._real + _rhs._imag * _rhs._imag);
            _imag = (_rhs._real * _imag - _rhs._imag * _real)
                / (_rhs._real * _rhs._real + _rhs._imag * _rhs._imag);
            return *this;
        }
        
        inline complex &operator ++()
        {
            _real++;
            return *this;
        }
        
        inline complex &operator --()
        {
            _real--;
            return *this;
        }
        
        inline complex &operator ++(int)
        {
            _real++;
            return *this;
        }
        
        inline complex &operator --(int)
        {
            _real--;
            return *this;
        }
        
        template<typename T>
        explicit operator std::complex<T>()
        { return std::complex<T>(static_cast<T>(real()), static_cast<T>(imag())); }
        
        explicit operator bool()
        { return static_cast<bool>(real()) || static_cast<bool>(imag()); }
        
        complex recip() const
        { return complex(1) /= *this; }
    };
    
    inline bool operator ==(const complex &_lhs, const complex &_rhs)
    { return (_lhs.real() == _rhs.real()) && (_lhs.imag() == _rhs.imag()); }
    
    inline bool operator !=(const complex &_lhs, const complex &_rhs)
    { return !(_lhs == _rhs); }
    
    inline complex operator +(const complex &_lhs, const complex &_rhs)
    {
        complex _ret(_lhs);
        _ret += _rhs;
        return _ret;
    }
    
    inline complex operator -(const complex &_lhs, const complex &_rhs)
    {
        complex _ret(_lhs);
        _ret -= _rhs;
        return _ret;
    }
    
    inline complex operator *(const complex &_lhs, const complex &_rhs)
    {
        complex _ret(_lhs);
        _ret *= _rhs;
        return _ret;
    }
    
    inline complex operator /(const complex &_lhs, const complex &_rhs)
    {
        complex _ret(_lhs);
        _ret /= _rhs;
        return _ret;
    }
    
    inline complex operator -(const complex &_x)
    { return complex(-_x.real(), -_x.imag()); }
    
    inline real abs(const complex &_x)
    { return sqrt(_x.real() * _x.real() + _x.imag() * _x.imag()); }
    
    inline long double arg(const complex &_x)
    {
        if (_x.real() > 0)
            return std::atan(static_cast<long double>(_x.imag() / _x.real()));
        if (_x.real() < 0)
        {
            if (_x.imag() >= 0)
                return std::atan(static_cast<long double>(_x.imag() / _x.real())) + M_PI;
            return std::atan(static_cast<long double>(_x.imag() / _x.real())) - M_PI;
        }
        if (_x.imag() > 0)
            return M_PI / 2;
        if (_x.imag() < 0)
            return M_PI / -2;
        throw std::invalid_argument(__func__);
        return nan("arg0");
    }
    
    inline complex stoc(const std::string &_str)
    {
        // a, bi, a + bi
        complex::val_type _real, _imag;
        int _has_imag = _str.find('i');
        if (_has_imag == -1)
        {
            _real = stor(_str);
            _imag = 0;
        }
        else
        {
            bool _imag_sign = false;
            int _parentheses = 1;
            int i = _str.size() - 3;
            for (; i >= 0; i--)
            {
                if (_str[i] == ')')
                    _parentheses++;
                else if (_str[i] == '(')
                    _parentheses--;
                if (_parentheses == 0)
                    break;
            }
            if (_str[i - 1] == '-')
                _imag_sign = true;
            _real = stor(_str.substr(0, i - 1));
            _imag = stor(_str.substr(i + 1, _str.size() - 3 - i));
            if (_imag_sign)
                _imag = -_imag;
        }
        return complex(_real, _imag);
    }
    
    inline std::string to_string(const complex &_x)
    {
        std::string _ret;
        if (_x.real())
        {
            _ret += to_string(_x.real());
            if (_x.imag() > 0)
                _ret += '+';
        }
        if (_x.imag())
        {
            if (_x.imag() != 1 && _x.imag() != -1)
                _ret += to_string(_x.imag());
            _ret += 'i';
        }
        return _ret;
    }
    
    template<class _CharT, class _Traits>
    inline std::basic_istream<_CharT, _Traits> &
    operator >>(std::basic_istream<_CharT, _Traits> &_is, complex &_rhs)
    {
        std::basic_string<_CharT, _Traits> _val;
        if (_is >> _val)
            _rhs = stor(_val);
        return _is;
    }
    
    template<class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits> &
    operator <<(std::basic_ostream<_CharT, _Traits> &_os, const complex &_rhs)
    { return _os << to_string(_rhs); }
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif