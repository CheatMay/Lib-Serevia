// <fraction.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_FRACTION_H
#define _LIBSEREVIA_FRACTION_H 1

/** @file fraction.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "mathextend.h"

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class fraction
    {
        private:
        using val_type = _LIBSEREVIA_LONG_LONG;
        
        // Data members
        val_type _mol, _den;
        
        // »¯¼ò
        void _simplify()
        {
            if (den() == 0)
            {
                _mol = 0, _den = 1;
                return;
            }
            bool _sign = false;
            if (mol() < 0 xor den() < 0)
                _sign = true;
            val_type __mol = std::abs(mol()), __den = std::abs(den());
            _LIBSEREVIA_LONG_LONG _a = gcd(__mol, __den);
            __mol /= _a;
            if (_sign)
                __mol = -__mol;
            __den /= _a;
            _mol = __mol, _den = __den;
        }
        
        public:
        fraction(): _mol(0), _den(1)
        { }
        
        fraction(long double _val)
        { val(_val, 1); }
        
        fraction(long double __mol, long double __den)
        { val(__mol, __den); }
        
        fraction(const fraction &__mol, const fraction &__den)
        { val(__mol, __den); }
        
        val_type mol() const
        { return _mol; }
        
        val_type mol(long double __mol)
        {
            val_type _old = mol();
            val(__mol, den());
            return _old;
        }
        
        val_type mol(const fraction &__mol)
        {
            val_type _old = mol();
            mol(__mol.mol());
            den(den() * __mol.den());
            return _old;
        }
        
        val_type den() const
        { return _den; }
        
        val_type den(long double __den)
        {
            val_type _old = den();
            val(mol(), __den);
            return _old;
        }
        
        val_type den(const fraction &__den)
        {
            val_type _old = den();
            den(__den.mol());
            mol(mol() * __den.den());
            return _old;
        }
        
        fraction &val(long double __mol, long double __den)
        {
            while (__mol != static_cast<long double>(std::floor(__mol))
                || __den != static_cast<long double>(std::floor(__den)))
                __mol *= 10, __den *= 10;
            _mol = static_cast<val_type>(__mol);
            _den = static_cast<val_type>(__den);
            _simplify();
            return *this;
        }
        
        fraction &val(const fraction &__mol, const fraction &__den)
        {
            _LIBSEREVIA_LONG_LONG _a = gcd(std::abs(__mol.mol()), std::abs(__den.mol()));
            _LIBSEREVIA_LONG_LONG _b = gcd(std::abs(__mol.den()), std::abs(__den.den()));
            _mol = __mol.mol() / _a * (__den.den() / _b);
            _den = __mol.den() / _b * (__den.mol() / _a);
            // Necessary?
            _simplify();
            return *this;
        }
        
        std::string type() const
        {
            if (den() == 1)
                return "Z";
            return "Q";
        }
        
        long double digit() const
        { return static_cast<long double>(mol()) / static_cast<long double>(den()); }
        
        fraction recip() const
        {
            if (mol() < 0)
                return fraction(-den(), -mol());
            return fraction(den(), mol());
        }
        
        friend bool operator ==(const fraction &, const fraction &);
        friend bool operator <(const fraction &, const fraction &);
        
        fraction &operator +=(const fraction &_rhs)
        {
            _LIBSEREVIA_LONG_LONG _d1 = den(), _d2 = _rhs.den(), _m1 = mol(), _m2 = _rhs.mol();
            _den = lcm(_d1, _d2);
            _m1 *= den() / _d1, _m2 *= den() / _d2;
            mol(_m1 + _m2);
            return *this;
        }
        
        fraction &operator -=(const fraction &_rhs)
        {
            _LIBSEREVIA_LONG_LONG _d1 = den(), _d2 = _rhs.den(), _m1 = mol(), _m2 = _rhs.mol();
            _den = lcm(_d1, _d2);
            _m1 *= den() / _d1, _m2 *= den() / _d2;
            mol(_m1 - _m2);
            return *this;
        }
        
        fraction &operator *=(const fraction &_rhs)
        {
            if (_rhs.mol() == 0)
            {
                _mol = 0;
                _den = 1;
                return *this;
            }
            val(*this, _rhs.recip());
            return *this;
        }
        
        fraction &operator /=(const fraction &_rhs)
        {
            val(*this, _rhs);
            return *this;
        }
        
        fraction &operator ++()
        {
            _mol += den();
            return *this;
        }
        
        fraction &operator --()
        {
            _mol -= den();
            return *this;
        }
        
        fraction &operator ++(int)
        { return ++*this; }
        
        fraction &operator --(int)
        { return --*this; }
        
        explicit operator long double()
        { return digit(); }
        
        explicit operator bool()
        { return static_cast<bool>(mol()); }
    };
    
    inline bool operator ==(const fraction &_lhs, const fraction &_rhs)
    { return _lhs.mol() == _rhs.mol() && _lhs.den() == _rhs.den(); }
    
    inline bool operator !=(const fraction &_lhs, const fraction &_rhs)
    { return !(_lhs == _rhs); }
    
    inline bool operator <(const fraction &_lhs, const fraction &_rhs)
    { return _lhs.mol() * _rhs.den() < _rhs.mol() * _lhs.den(); }
    
    inline bool operator <=(const fraction &_lhs, const fraction &_rhs)
    { return _lhs < _rhs || _lhs == _rhs; }
    
    inline bool operator >(const fraction &_lhs, const fraction &_rhs)
    { return !(_lhs <= _rhs); }
    
    inline bool operator >=(const fraction &_lhs, const fraction &_rhs)
    { return !(_lhs < _rhs); }
    
    inline fraction operator +(const fraction &_lhs, const fraction &_rhs)
    {
        fraction _tmp(_lhs);
        _tmp += _rhs;
        return _tmp;
    }
    
    inline fraction operator -(const fraction &_lhs, const fraction &_rhs)
    {
        fraction _tmp(_lhs);
        _tmp -= _rhs;
        return _tmp;
    }
    
    inline fraction operator *(const fraction &_lhs, const fraction &_rhs)
    {
        fraction _tmp(_lhs);
        _tmp *= _rhs;
        return _tmp;
    }
    
    inline fraction operator /(const fraction &_lhs, const fraction &_rhs)
    {
        fraction _tmp(_lhs);
        _tmp /= _rhs;
        return _tmp;
    }
    
    fraction operator -(const fraction &_n)
    { return fraction(-_n.mol(), _n.den()); }
    
    fraction abs(const fraction &_n)
    { return _n < 0 ? -_n : _n; }
    
    _LIBSEREVIA_LONG_LONG floor(const fraction &_n)
    { return static_cast<_LIBSEREVIA_LONG_LONG>(_n.mol()) / static_cast<_LIBSEREVIA_LONG_LONG>(_n.den()); }
    
    _LIBSEREVIA_LONG_LONG ceil(const fraction &_n)
    {
        _LIBSEREVIA_LONG_LONG _m = static_cast<_LIBSEREVIA_LONG_LONG>(_n.mol()), _d = static_cast<_LIBSEREVIA_LONG_LONG>(_n.den());
        return _m % _d == 0 ? _m / _d : _m / _d + 1;
    }
    
    fraction stofrac(const std::string &_s)
    {
        int _mode = _s.find('|');
        if (_mode == -1)
            return fraction(stold(_s), 1);
        return fraction(stold(_s.substr(0, _mode)), stold(_s.substr(_mode + 1)));
    }
    
    std::string to_string(const fraction &_n)
    {
        if (_n.den() == 1)
            return std::to_string(_n.mol());
        else if (_n.mol() == 0)
            return "0";
        return std::to_string(_n.mol()) + "|" + std::to_string(_n.den());
    }
    
    template<typename _CharT, typename _Traits>
    inline std::basic_istream<_CharT, _Traits> &
    operator >>(std::basic_istream<_CharT, _Traits> &_is, fraction &_rhs)
    {
        std::basic_string<_CharT> _val;
        if (_is >> _val)
            _rhs = stofrac(_val);
        return _is;
    }
    
    template<typename _CharT, typename _Traits>
    inline std::basic_ostream<_CharT, _Traits> &
    operator <<(std::basic_ostream<_CharT, _Traits> &_os, const fraction &_rhs)
    { return _os << to_string(_rhs); }
    
    typedef class fraction frac;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif