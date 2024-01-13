// <real.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_REAL_H
#define _LIBSEREVIA_REAL_H 1

/** @file real.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "fraction.h"

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class radical;
    
    class real
    {
        public:
        using val_type = fraction;
        
        friend class radical;
        
        private:
        static const std::string _superscript[10];
        
        // Data members
        val_type _rational;
        std::vector<radical> _irrational;
        
        inline void _sort();
        
        void _literal(const std::string &_s);
        
        void _simplify();
        
        real _intpow(const real &_base, unsigned _LIBSEREVIA_LONG_LONG _index)
        {
            if (_index == 0)
                return real(1);
            if (_index == 1)
                return _base;
            real _ret(1), __base(_base);
        	while (_index)
        	{
        		if (_index & 1)
        		    _ret *= __base;
        		_index >>= 1;
        		__base *= __base;
        	}
        	return _ret;
        };
        
        public:
        real(): _rational(), _irrational()
        { }
        
        real(long double _n): _rational(_n), _irrational()
        { }
        
        real(const val_type &_n): _rational(_n), _irrational()
        { }
        
        real(const val_type &_n, const std::vector<radical> &__irrational):
        _rational(_n), _irrational(__irrational)
        { _simplify(); }
        
        real(const std::string &_s)
        {
            _literal(_s);
            _simplify();
        }
        
        real &val(const val_type &__rational, const std::vector<radical> &__irrational)
        {
            _rational = __rational;
            _irrational = __irrational;
            _simplify();
            return *this;
        }
        
        std::string type() const
        {
            if (irrational().empty())
                return rational().type();
            return "R";
        }
        
        long double digit() const;
        
        inline val_type rational() const
        { return _rational; }
        
        inline std::vector<radical> irrational() const
        { return _irrational; }
        
        real &operator +=(const real &_rhs)
        {
            _rational += _rhs.rational();
            for (int i = 0; i < _rhs.irrational().size(); i++)
                _irrational.push_back(_rhs.irrational()[i]);
            _simplify();
            return *this;
        }
        
        real &operator -=(const real &_rhs);
        
        real &operator *=(const real &_rhs);
        
        real &operator /=(const real &_rhs);
        
        real &operator ++()
        {
            ++_rational;
            return *this;
        }
        
        real &operator --()
        {
            --_rational;
            return *this;
        }
        
        real &operator ++(int)
        {
            ++_rational;
            return *this;
        }
        
        real &operator --(int)
        {
            --_rational;
            return *this;
        }
        
        explicit operator long double()
        { return digit(); }
        
        explicit operator bool()
        { return static_cast<bool>(irrational().size()) || static_cast<bool>(rational()); }
        
        real recip() const
        { return real(1) /= *this; }
        
        friend bool operator ==(const real &, const real &);
        friend real operator -(const real &);
        friend real pow(const fraction &, const fraction &);
        friend real pow(const real &_base, const real &_index);
        friend real sqrt(const real &);
        friend std::string to_string(const real &);
    };
    
    // class radical
    // @{
    class radical
    {
        public:
        using coeff_type = fraction;
        using index_type = int;
        using rad_type = real;
        
        friend class real;
        
        private:
        // Data members
        coeff_type _coefficient;
        index_type _index;
        rad_type _radicand;
        
        radical(): _coefficient(0), _index(2), _radicand(real())
        { }
        
        radical(coeff_type __coefficient, index_type __index, rad_type __radicand):
        _coefficient(__coefficient), _index(__index), _radicand(__radicand)
        { }
        
        void _simplify()
        {
            if (_radicand.rational() == 0 && _radicand.irrational().size() == 1
                && _radicand.irrational()[0]._radicand.irrational().empty())
            {
                if (_index % 2 && _radicand.irrational()[0]._coefficient < 0)
                {
                    _radicand.irrational()[0]._coefficient = -_radicand.irrational()[0]._coefficient;
                    _coefficient = -_coefficient;
                }
                _index *= _radicand.irrational()[0]._index;
                _radicand._rational = _radicand.irrational()[0]._radicand._rational
                    * fraction(pow(_radicand.irrational()[0]._coefficient.mol(), _radicand.irrational()[0]._index),
                    pow(_radicand.irrational()[0]._coefficient.den(), _radicand.irrational()[0]._index));
                _radicand._irrational.clear();
            }
            if (_radicand.irrational().empty())
            {
                if (_index % 2 && _radicand.rational() < 0)
                {
                    _radicand._rational = -_radicand._rational;
                    _coefficient = -_coefficient;
                }
                int _a = _radicand._rational.den();
                _radicand._rational.val(_radicand._rational.mol() * std::pow(_a, _index - 1), 1);
                _coefficient /= _a;
                if (_radicand._rational.mol() != 1)
                {
                    std::vector<unsigned _LIBSEREVIA_LONG_LONG> _factors = factorize(std::abs(_radicand._rational.mol()));
                    for (int i = 0; i <= static_cast<_LIBSEREVIA_LONG_LONG>(_factors.size()) - _index; i++)
                    {
                        if (_factors[i] == _factors[i + _index - 1])
                        {
                            _coefficient *= _factors[i];
                            _radicand._rational /= std::pow(_factors[i], _index);
                            i += _index - 1;
                        }
                    }
                }
            }
            else if (_radicand.rational() > 0 && _radicand.irrational().size() == 1
                && _radicand.irrational()[0]._radicand.irrational().empty())
            {
                real _res = sqrt(_radicand);
                if (_res._rational)
                {
                    _index /= 2;
                    _radicand = _res;
                }
            }
        }
        
        long double digit() const
        { return _coefficient.digit() * std::pow(_radicand.digit(), 1 / static_cast<long double>(_index)); }
        
        friend bool operator ==(const radical &, const radical &);
        friend real operator -(const real &_n);
        friend real sqrt(const real &_n);
        friend std::string to_string(const real &_n);
    };
    
    inline bool operator ==(const radical &_lhs, const radical &_rhs)
    {
        return _lhs._coefficient == _rhs._coefficient
            && _lhs._index == _rhs._index && _lhs._radicand == _rhs._radicand;
    }
    
    inline bool operator !=(const radical &_lhs, const radical &_rhs)
    { return !(_lhs == _rhs); }
    // @}
    
    const std::string real::_superscript[10] = {"", "", "", "?", "?", "?", "?", "?", "?", "?"};
    
    inline bool operator ==(const real &_lhs, const real &_rhs)
    {
        if (_lhs._rational != _rhs._rational)
            return false;
        int _len1 = _lhs.irrational().size(), _len2 = _rhs.irrational().size();
        if (_len1 != _len2)
            return false;
        for (int i = 0; i < _len1; i++)
            if (_lhs.irrational()[i] != _rhs.irrational()[i])
                return false;
        return true;
    }
    
    inline bool operator !=(const real &_lhs, const real &_rhs)
    { return !(_lhs == _rhs); }
    
    inline bool operator <(const real &_lhs, const real &_rhs)
    { return _lhs.digit() < _rhs.digit(); }
    
    inline bool operator <=(const real &_lhs, const real &_rhs)
    { return _lhs < _rhs || _lhs == _rhs; }
    
    inline bool operator >(const real &_lhs, const real &_rhs)
    { return !(_lhs <= _rhs); }
    
    inline bool operator >=(const real &_lhs, const real &_rhs)
    { return !(_lhs < _rhs); }
    
    inline void real::_sort()
    {
        std::sort(_irrational.begin(), _irrational.end(),
            [](const radical &_lhs, const radical &_rhs)
            { return _lhs._index < _rhs._index || _lhs._radicand < _rhs._radicand; });
    }
    void real::_literal(const std::string &_s)
    {
        val_type __rational;
        std::vector<radical> __irrational;
        std::string _svaln;
        int i = 1;
        _svaln += _s[0];
        for (; i < _s.size(); i++)
        {
            if (isdigit(_s[i]) || _s[i] == '.' || _s[i] == '|')
                _svaln += _s[i];
            else
                break;
        }
        if (_s[i] == '+' || _s[i] == '-' || i >= _s.size())
            __rational = stofrac(_svaln);
        else
            i = 0, __rational = 0;
        for (int j = 0; i < _s.size(); j++)
        {
            radical _tmp;
            std::string _s2;
            for (; i < _s.size(); i++)
            {
                if (isdigit(_s[i]) || _s[i] == '.' || _s[i] == '+' || _s[i] == '-' || _s[i] == '|')
                    _s2 += _s[i];
                else
                    break;
            }
            if (_s2 == "+" || i == 0)
                _tmp._coefficient = 1;
            else if (_s2 == "-")
                _tmp._coefficient = -1;
            else
                _tmp._coefficient = stofrac(_s2);
            std::string _s3;
            for (; i < _s.size(); i++)
            {
                if (_s[i] == '(')
                {
                    i++;
                    break;
                }
                _s3 += _s[i];
            }
            if (_s3 == "¡Ì")
                _tmp._index = 2;
            else
                for (int k = 3; k < 10; k++)
                    if (_s3 == _superscript[k] + "¡Ì")
                        _tmp._index = k;
            std::string _s4;
            int parentheses = 1;
            for (; i < _s.size(); i++)
            {
                _s4 += _s[i];
                if (_s[i] == '(')
                    parentheses++;
                else if (_s[i] == ')')
                    parentheses--;
                if (parentheses == 0)
                    break;
            }
            _s4.pop_back();
            int _flag = _s4.find("¡Ì");
            if (_flag != -1)
                _tmp._radicand = real(_s4);
            else
                _tmp._radicand = stofrac(_s4);
            __irrational.push_back(_tmp);
            i++;
        }
        _rational = __rational, _irrational = __irrational;
    }
    
    void real::_simplify()
    {
        int _len1 = _irrational.size(), _len2 = 0;
        for (int i = 0; i < _len1; i++)
            _irrational[i]._simplify();
        val_type __rational = _rational;
        std::vector<radical> __irrational;
        for (int i = 0; i < _len1; i++)
        {
            if (_irrational[i]._coefficient == 0 || _irrational[i]._radicand == 0) ;
            else if (_irrational[i]._index == 1)
            {
                __rational += _irrational[i]._coefficient * _irrational[i]._radicand._rational;
                for (int j = 0; j < _irrational[i]._radicand._irrational.size(); i++)
                {
                    _irrational[i]._radicand._irrational[j]._coefficient *= _irrational[i]._coefficient;
                    bool _flag = true;
                    for (int k = 0; k < _len2; k++)
                    {
                        if (__irrational[k]._index == _irrational[j]._index
                            && __irrational[k]._radicand == _irrational[j]._radicand)
                        {
                            __irrational[k]._coefficient += _irrational[j]._coefficient;
                            _flag = false;
                        }
                    }
                    if (_flag)
                    {
                        __irrational.push_back(_irrational[j]);
                        _len2++;
                    }
                }
            }
            else if (_irrational[i]._radicand == 1)
                __rational += _irrational[i]._coefficient;
            else
            {
                bool _flag = true;
                for (int j = 0; j < _len2; j++)
                {
                    if (__irrational[j]._index == _irrational[i]._index
                        && __irrational[j]._radicand == _irrational[i]._radicand)
                    {
                        __irrational[j]._coefficient += _irrational[i]._coefficient;
                        _flag = false;
                    }
                }
                if (_flag)
                {
                    __irrational.push_back(_irrational[i]);
                    _len2++;
                }
            }
        }
        int _len3 = __irrational.size();
        std::vector<radical> _tmp;
        for (int i = 0; i < _len3; i++)
            if (!(__irrational[i]._coefficient == 0 || __irrational[i]._radicand == 0
                || __irrational[i]._index == 0))
                _tmp.push_back(__irrational[i]);
        _rational = __rational, _irrational = _tmp;
    }
    
    long double real::digit() const
    {
        long double _ret = _rational.digit();
        int _len = _irrational.size();
        for (int i = 0; i < _len; i++)
            _ret += _irrational[i].digit();
        return _ret;
    }
    
    real &real::operator -=(const real &_rhs)
    {
        _rational -= _rhs.rational();
        for (int i = 0; i < _rhs.irrational().size(); i++)
        {
            radical _tmp(_rhs.irrational()[i]);
            _tmp._coefficient = -_tmp._coefficient;
            _irrational.push_back(_tmp);
        }
        _simplify();
        return *this;
    }
    
    real &real::operator *=(const real &_rhs)
    {
        real _res;
        _res._rational = rational() * _rhs.rational();
        for (int i = 0; i < _rhs.irrational().size(); i++)
        {
            radical _tmp(_rhs.irrational()[i]);
            _tmp._coefficient *= rational();
            _res._irrational.push_back(_tmp);
        }
        for (int i = 0; i < irrational().size(); i++)
        {
            radical _tmp(irrational()[i]);
            _tmp._coefficient *= _rhs.rational();
            _res._irrational.push_back(_tmp);
        }
        for (int i = 0; i < irrational().size(); i++)
        {
            for (int j = 0; j < _rhs.irrational().size(); j++)
            {
                int _a = lcm(irrational()[i]._index, _rhs.irrational()[j]._index);
                radical _tmp;
                _tmp._coefficient = irrational()[i]._coefficient * _rhs.irrational()[j]._coefficient;
                _tmp._index = _a;
                // Infinite loop?
                _tmp._radicand = _intpow(irrational()[i]._radicand, _a / irrational()[i]._index);
                _tmp._radicand *= _intpow(_rhs.irrational()[j]._radicand, _a / _rhs.irrational()[j]._index);
                _res._irrational.push_back(_tmp);
            }
        }
        _res._simplify();
        return *this = _res;
    }
    
    real &real::operator /=(const real &_rhs)
    {
        real _res(*this);
        real _sum(1);
        real _divisor(_rhs);
        for (int i = _divisor.irrational().size() - 1; i >= 0; i--)
        {
            real _tmp;
            _tmp._irrational.push_back(_divisor.irrational()[i]);
            _tmp = -_tmp;
            real _tmp2 = _divisor;
            _tmp2 += _tmp;
            int _tmp3 = _tmp.irrational()[0]._index - 1;
            real _tmp4;
            for (int k = 0; k <= _tmp3; k++)
            {
                real _tmp5 = _intpow(_tmp2, k);
                _tmp5 *= _intpow(_tmp, _tmp3 - k);
                _tmp4 += _tmp5;
            }
            _sum *= _tmp4;
            _divisor *= _tmp4;
        }
        _res._rational /= _divisor.rational();
        for (int i = 0; i < _res.irrational().size(); i++)
            _res._irrational[i]._coefficient /= _divisor.rational();
        _res *= _sum;
        _res._simplify();
        return *this = _res;
    }
    
    inline real operator +(const real &_lhs, const real &_rhs)
    {
        real _ret(_lhs);
        _ret += _rhs;
        return _ret;
    }
    
    inline real operator -(const real &_lhs, const real &_rhs)
    {
        real _ret(_lhs);
        _ret -= _rhs;
        return _ret;
    }
    
    inline real operator *(const real &_lhs, const real &_rhs)
    {
        real _ret(_lhs);
        _ret *= _rhs;
        return _ret;
    }
    
    inline real operator /(const real &_lhs, const real &_rhs)
    {
        real _ret(_lhs);
        _ret /= _rhs;
        return _ret;
    }
    
    inline real operator -(const real &_n)
    {
        real::val_type _rational = _n.rational();
        std::vector<radical> _irrational = _n.irrational();
        for (auto && i : _irrational)
            i._coefficient = -i._coefficient;
        return real(-_rational, _irrational);
    }
    
    real abs(const real &_n)
    { return _n < 0 ? -_n : _n; }
    
    _LIBSEREVIA_LONG_LONG floor(const real &_n)
    { return std::floor(_n.digit()); }
    
    _LIBSEREVIA_LONG_LONG ceil(const real &_n)
    { return std::ceil(_n.digit()); }
    
    real pow(const fraction &_base, const fraction &_index)
    {
        if (_index == 0)
            return real(1);
        if (_index == 1)
            return real(_base);
        if (_index == -1)
            return real(_base.recip());
        if (_index.type() == "Z")
        {
            real _res(1), __base(_base);
            _LIBSEREVIA_LONG_LONG i = std::abs(_index.mol());
        	while (i)
        	{
        		if (i & 1)
        		    _res *= __base;
        		i >>= 1;
        		__base = __base * __base;
        	}
        	if (_index < 0)
        	    _res = _res.recip();
        	return _res;
        }
        real _res(1);
        real __base = real::_superscript[static_cast<size_t>(_index.den())] + "¡Ì(" + to_string(_base) + ")";
        _LIBSEREVIA_LONG_LONG i = std::abs(_index.mol());
        while (i)
        {
            if (i & 1)
                _res *= __base;
            i >>= 1;
            __base = __base * __base;
        }
        if (_index < 0)
            _res = _res.recip();
        return _res;
    }
    
    real pow(const real &_base, const real &_index)
    {
        if (_index.type() != "R")
        {
            if (_index == 0)
                return real(1);
            if (_index == 1)
                return _base;
            if (_index == -1)
                return _base.recip();
            real _res(1), __base(_base);
            _LIBSEREVIA_LONG_LONG i = std::abs(_index.rational().mol());
            while (i)
            {
                if (i & 1)
                    _res *= __base;
                i >>= 1;
                __base = __base * __base;
            }
            if (_index.type() == "Q")
                _res = real(real::_superscript[_index.rational().den()] + "¡Ì(" + to_string(_res) + ")");
            if (_index < 0)
                _res = _res.recip();
            return _res;
        }
        throw std::underflow_error(__func__);
        return real(nan("transcendental"));
    }
    
    real sqrt(const fraction &_n)
    { return real("¡Ì(" + to_string(_n) + ")"); }
    
    std::string to_string(const real &_n)
    {
        real _tmp(_n);
        std::string _ret;
        _tmp._sort();
        int i = 0;
        if (_tmp.rational() != 0)
            _ret += to_string(_tmp.rational());
        else
        {
            if (_tmp.irrational().size() == 0)
                return "0";
            if (_tmp.irrational()[0]._coefficient == 1) ;
            else if (_tmp.irrational()[0]._coefficient == -1)
                _ret += "-";
            else
                _ret += to_string(_tmp.irrational()[0]._coefficient);
            _ret += real::_superscript[_tmp.irrational()[i]._index] + "¡Ì(";
            _ret += to_string(_tmp.irrational()[i]._radicand) + ")";
            i++;
        }
        for (; i < _tmp.irrational().size(); i++)
        {
            if (_tmp.irrational()[i]._coefficient == 1)
                _ret += "+";
            else if (_tmp.irrational()[i]._coefficient == -1)
                _ret += "-";
            else
            {
                if (_tmp.irrational()[i]._coefficient > 0)
                    _ret += "+";
                _ret += to_string(_tmp.irrational()[i]._coefficient);
            }
            _ret += real::_superscript[_tmp.irrational()[i]._index] + "¡Ì(";
            _ret += to_string(_tmp.irrational()[i]._radicand) + ")";
        }
        return _ret;
    }
    
    real sqrt(const real &_n)
    {
        if (_n == 0)
            return real(std::sqrt(0));
        if (_n.type() != "R")
            return real("¡Ì(" + to_string(_n) + ")");
        if (_n.irrational().size() == 1)
        {
            if (_n.rational() == 0)
            {
                radical _tmp = _n.irrational()[0];
                _tmp._radicand *= pow(_tmp._coefficient, _tmp._index).rational();
                _tmp._coefficient = 1;
                _tmp._index *= 2;
                return real(0, {_tmp});
            }
            if (_n.irrational()[0]._index == 2)
            {
                fraction _tmp(_n.rational());
                real _irrational(0, _n.irrational());
                char _sign = _irrational > 0 ? '+' : '-';
                fraction _rational = (_irrational * _irrational).rational();
                real _res1 = (_tmp + sqrt(_tmp * _tmp - _rational)) / 2;
                real _res2 = (_tmp - sqrt(_tmp * _tmp - _rational)) / 2;
                if (_res1.type() != "R" && _res2.type() != "R")
                    return real("¡Ì(" + to_string(_res1) + ")" + _sign + "¡Ì(" + to_string(_res2) + ")");
            }
        }
        return real("¡Ì(" + to_string(_n) + ")");
    }
    
    real cbrt(const fraction &_n)
    { return real("?¡Ì(" + to_string(_n) + ")"); }
    
    real cbrt(const real &_n)
    { return real("?¡Ì(" + to_string(_n) + ")"); }
    
    real stor(std::string _s)
    { return real(_s); }
    
    template<typename _CharT, typename _Traits>
    inline std::basic_istream<_CharT, _Traits> &
    operator >>(std::basic_istream<_CharT, _Traits> &_is, real &_rhs)
    {
        std::basic_string<_CharT> _val;
        if (_is >> _val)
            _rhs = stor(_val);
        return _is;
    }
    
    template<typename _CharT, typename _Traits>
    inline std::basic_ostream<_CharT, _Traits> &
    operator <<(std::basic_ostream<_CharT, _Traits> &_os, const real &_rhs)
    { return _os << to_string(_rhs); }
    
_GLIBCXX_END_NAMESPACE_VERSION
}

inline serevia::real operator ""_r(const char * _str, size_t _len)
{ return serevia::real(_str); }

#endif