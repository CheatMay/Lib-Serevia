// <mathextend.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_MATHEXTEND_H
#define _LIBSEREVIA_MATHEXTEND_H 1

/** @file mathextend.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

// #include "random.h"
#include <istream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <math.h>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    const constexpr double error = 10e-10;
    
    struct
    {
        const long double inf = 1.7976931348623157e+308;
        
        const long double pi = 3.14159265358979323846264338327950288;

        const long double e = 2.71828182845904523536028747135266249;
        
        const long double gamma = 0.57721566490153286060651209008240243;
        
        const long double phi = 0.61803398874989484820458683436563811;
        
        const long double beta_star = 0.70258;
        
        const long double delta = 4.66920160910299067185320382046620161;
        
        const long double alpha = 2.50290787509589282228390287321821578;
        
        const long double C2 = 0.66016181584686957392781211001455577;
        
        const long double M1 = 0.26149721284764278375542683860869585;
        
        const long double B2 = 1.9021605823;
        
        const long double B4 = 0.8705883800;
        
        const long double B_L = 1.08366;
        
        const long double miu = 1.451369234883381050283968485892027;
        
        const long double EB = 1.606695152415291763;
    } Maths;
    
    struct
    {
        const long double c = 299792458; // m ， s ^ -1
        
        const long double miu0 = Maths.pi * 4e-7; // N ， A ^ -2
        
        const long double epsilon0 = 8.854187817e-12; // F ， m ^ -1
        
        const long double G = 6.67259e-11; // m ^ 3 ， kg ^ -1 ， s ^ -2
        
        const long double h = 6.6260755e-34; // J ， s
        
        const long double e = 1.60217733e-19; // C
        
        const long double Phi0 = 2.06783461e-19; // Wb
        
        const long double miuE = 9.2740154e-24; // J ， T ^ -1
        
        const long double miuN = 5.0507866e-27; // J ， T ^ -1
        
        const long double NA = 6.021367e23; // mol ^ -1
        
        const long double AMU = 1.6605402e-27; // kg
        
        const long double kE = 1.380658e-23; // J ， K ^ -1
        
        const long double sigma = 5.67051e-8; // W ， m ^ -2 ， K ^ -4
        
        const long double alpha = 7.29735308e-3;
        
        const long double R = 10973731.534; // m ^ -1
        
        const long double a0 = 0.529177249e-10; // m
        
        const long double Eh = 4.3597482e-18; // J
        
        const long double me = 9.1093897e-31; // kg
        
        const long double e_me = -1.75881962e11; // C ， kg ^ -1
        
        const long double re = 2.81794092e-15; // m
        
        const long double miue = 928.47701e-26; // J ， T ^ -1
        
        const long double mium = 1.8835327e-28; // kg
        
        const long double mP = 1.6726231e-27; // kg
        
        const long double mP_me = 1836.152701;
        
        const long double miuP = 1.41060761e-26; // J ， T ^ -1
        
        const long double mn = 1.6749286e-27; // kg
    } Physics;
    
    __int128 pow128(__int128 x, __int128 y)
    {
        if (y == 0)
            return 1;
        if (y == 1)
            return x;
        __int128 res = 1, base = x;
    	while (y)
    	{
    		if (y & 1)
    		    res *= base;
    		y >>= 1;
    		base = base * base;
    	}
    	return res;
    }
    
    template<typename _CharT, typename _Traits>
    std::basic_istream<_CharT, _Traits> &operator >>
    (std::basic_istream<_CharT, _Traits> &is, __int128 &n)
    {
        __int128 temp = 0;
        bool sign = 0;
        std::basic_string<_CharT> s;
        is >> s;
        if (s[0] == is.widen('-'))
        {
            sign = 1;
            s.erase(0, 1);
        }
        for (auto &&i : s)
            if (!isdigit(i))
                throw std::runtime_error(std::string(__func__) + ": invalid input");
        std::reverse(s.begin(), s.end());
        for (size_t i = 0; i < s.size(); i++)
            temp += pow128(10, i) * (static_cast<int>(s[i]) - 48);
        if (sign)
            temp = -temp;
        n = temp;
        return is;
    }
    
    template<typename _CharT, typename _Traits>
    std::basic_ostream<_CharT, _Traits> &operator <<
    (std::basic_ostream<_CharT, _Traits> &os, __int128 n)
    {
        if (!n)
            return os << 0;
        if (n < 0)
        {
            os << os.widen('-');
            n = -n;
        }
        std::basic_string<_CharT> s;
        while (n)
        {
            s += static_cast<_CharT>(n % 10 + 48);
            n /= 10;
        }
        std::reverse(s.begin(), s.end());
        return os << s;
    }
    
    typedef __int128 int128;
    
    unsigned _LIBSEREVIA_LONG_LONG gcd(unsigned _LIBSEREVIA_LONG_LONG a, unsigned _LIBSEREVIA_LONG_LONG b)
    { return std::__gcd(a, b); }
    
    unsigned _LIBSEREVIA_LONG_LONG lcm(unsigned _LIBSEREVIA_LONG_LONG a, unsigned _LIBSEREVIA_LONG_LONG b)
    { return a / std::__gcd(a, b) * b; }
    
    unsigned _LIBSEREVIA_LONG_LONG ullabs(_LIBSEREVIA_LONG_LONG x)
    { return x < 0LL ? static_cast<unsigned _LIBSEREVIA_LONG_LONG>(-x) : static_cast<unsigned _LIBSEREVIA_LONG_LONG>(x); }
    
    std::vector<std::complex<long double> > complex_root(std::complex<long double> radicand, unsigned _LIBSEREVIA_LONG_LONG n)
    {
        /*
        z = r * (cos(theta) + i * sin(theta))
        r = abs(z) = sqrt(pow(a, 2) + pow(b, 2)), r > 0
        theta = arctan(b / a)
        W(k) = pow(r, (cos(thata + 2 * k * pi) / n + i * sin(theta + 2 * k * pi) / n) / n)
        k = 0, 1, 2, ... , n - 1
        */
        
        std::vector<std::complex<long double> > ans;
        std::complex<long double> root;
        long double a = radicand.real(), b = radicand.imag(), pi = M_PI;
        long double r = std::sqrt(std::pow(a, 2) + std::pow(b, 2));
        long double theta = atan(b / a);
        for (unsigned _LIBSEREVIA_LONG_LONG k = 0; k <= n - 1; k++)
        {
            root.real(std::pow(r, 1 / (n * 1.0)) * std::cos((theta + 2 * k * pi) / (n * 1.0)));
            root.imag(std::pow(r, 1 / (n * 1.0)) * std::sin((theta + 2 * k * pi) / (n * 1.0)));
            if (std::abs(root.real()) < std::pow(10, -15))
                root.real(0);
            if (std::abs(root.imag()) < std::pow(10, -15))
                root.imag(0);
            ans.push_back(root);
        }
        return ans;
    }
    
    std::string __digit = "0123456789ABCDEF";
    
    _LIBSEREVIA_LONG_LONG base_to_ten(size_t base, const std::string num)
    {
    	_LIBSEREVIA_LONG_LONG res = 0;
    	for (int i = num.size() - 1; i >= 0; i--)
    	{
    		int temp;
    		if (__digit.find(num[i]) == -1)
    		    temp = __digit.find(num[i] - 32);
    		else
    		    temp = __digit.find(num[i]);
    		res += temp * std::pow(base, num.size() - 1 - i);
    	}
    	return res;
    }
    
    std::string base_transform(size_t origin, size_t target, const std::string num)
    {
        std::string res;
        _LIBSEREVIA_LONG_LONG num2 = base_to_ten(origin, num);
        if (!num2)
            res = "0";
        while (num2)
        {
            res += __digit[num2 % target];
            num2 /= target;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    std::string base_transform(size_t target, _LIBSEREVIA_LONG_LONG num2)
    {
        std::string res;
        if (!num2)
            res = "0";
        while (num2)
        {
            res += __digit[num2 % target];
            num2 /= target;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    template<typename T>
    std::vector<T> intersection(std::vector<T> set1, std::vector<T> set2)
    {
        std::sort(set1.begin(), set1.end());
        std::sort(set2.begin(), set2.end());
        std::vector<T> common_set(set1.size() + set2.size());
        // vector<T>::iterator pos;
        // pos = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), common_set.begin());
        common_set.erase(set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), common_set.begin()), common_set.end());
        return common_set;
    }
    
    template<typename T>
    std::vector<T> intersection(T *_set1, size_t len1, T *_set2, size_t len2)
    {
        std::vector<T> set1, set2;
        for (int i = 0; i <= len1 - 1; i++)
            set1.push_back(_set1[i]);
        for (int i = 0; i <= len2 - 1; i++)
            set2.push_back(_set2[i]);
        return intersection(set1, set2);
    }
    
    unsigned _LIBSEREVIA_LONG_LONG ksc(unsigned _LIBSEREVIA_LONG_LONG a, unsigned _LIBSEREVIA_LONG_LONG b, unsigned _LIBSEREVIA_LONG_LONG p)
    {
        unsigned _LIBSEREVIA_LONG_LONG res = 0;
        while (b)
        {
            if (b & 1)
            {
                res = res + a;
                if (res >= p)
                    res -= p;
            }
            a = a + a;
            if (a >= p)
                a -= p;
            b >>= 1;
        }
        return res;
    }
    
    unsigned _LIBSEREVIA_LONG_LONG ksm(unsigned _LIBSEREVIA_LONG_LONG a, unsigned _LIBSEREVIA_LONG_LONG b, unsigned _LIBSEREVIA_LONG_LONG p)
    {
        unsigned _LIBSEREVIA_LONG_LONG res = 1;
        while (b)
        {
            if (b & 1)
                res = ksc(res, a, p);
            a = ksc(a, a, p);
            b >>= 1;
        }
        return res;
    }
    
    bool miller_rabbin(unsigned _LIBSEREVIA_LONG_LONG x)
    {
        if (x == 2 || x == 3)
            return 1;
        if (x == 1)
            return 0;
        unsigned _LIBSEREVIA_LONG_LONG n = x - 1, res, lastres;
        int r = 0, r1, t = 10;
        while (!(n & 1))
        {
            n >>= 1;
            r++;
        }
        while (t--)
        {
            unsigned _LIBSEREVIA_LONG_LONG a = 2; // rand() % (x - 1) + 1
            res = ksm(a, n, x);
            if (res == 1)
                continue;
            r1 = r;
            while (res != 1 && r1 > 0)
            {
                lastres = res;
                res = ksc(res, res, x);
                r1--;
                if (res == 1 && lastres != x - 1)
                    return 0;
            }
            if (res != 1)
                return 0;
        }
        return 1;
    }
    
    unsigned _LIBSEREVIA_LONG_LONG pollard_rho(unsigned _LIBSEREVIA_LONG_LONG x)
    {
        while (1)
        {
            unsigned _LIBSEREVIA_LONG_LONG a = serevia::random.template integer<unsigned _LIBSEREVIA_LONG_LONG>(0, x - 2);
            unsigned _LIBSEREVIA_LONG_LONG c = serevia::random.template integer<unsigned _LIBSEREVIA_LONG_LONG>(0, x - 2);
            unsigned _LIBSEREVIA_LONG_LONG b = a, d;
            unsigned _LIBSEREVIA_LONG_LONG cnt = 0, k = 2;
            while (1)
            {
                b = (ksc(b, b, x) + c) % x;
                d = gcd(x, ullabs(a - b));
                if (d != 1 && d != x)
                    return d;
                else if (d == x)
                    break;
                cnt++;
                if (k == cnt)
                {
                    a = b;
                    k <<= 1;
                }
            }
        }
    }
    
    bool is_prime(unsigned _LIBSEREVIA_LONG_LONG x)
    {
        for (int i = 1; i <= 4; i++)
            if (miller_rabbin(x))
                return 1;
        return 0;
    }
    
    void factorize(std::vector<unsigned _LIBSEREVIA_LONG_LONG> &ans, unsigned _LIBSEREVIA_LONG_LONG x)
    {
        while (!is_prime(x))
        {
            unsigned _LIBSEREVIA_LONG_LONG factor = pollard_rho(x);
            x /= factor;
            if (is_prime(factor))
                ans.push_back(factor);
            else
                factorize(ans, factor);
        }
        ans.push_back(x);
    }
    
    std::vector<unsigned _LIBSEREVIA_LONG_LONG> factorize(unsigned _LIBSEREVIA_LONG_LONG x)
    {
        std::vector<unsigned _LIBSEREVIA_LONG_LONG> ans;
        factorize(ans, x);
        std::sort(ans.begin(), ans.end());
        return ans;
    }
    
    template<typename _T>
    class coordinate
    {
        public:
        using val_type = _T;
        
        _T x, y;
        
        coordinate(): x(val_type()), y(val_type())
        { }
        
        coordinate(val_type _x, val_type _y): x(_x), y(_y)
        { }
        
        coordinate(val_type _xy[2]): x(_xy[0]), y(_xy[1])
        { }
        
        coordinate(const coordinate<val_type> &val): x(val.x), y(val.y)
        { }
    };
    
    template<typename _T>
    class line
    {
        public:
        using val_type = _T;
        
        val_type k, b, x;
        bool is_perpendicular;
        
        line(): k(val_type()), b(val_type()), is_perpendicular(false)
        { }
        
        line(val_type _k, val_type _b): k(_k), b(_b), is_perpendicular(false)
        { }
        
        line(val_type _x): x(_x), is_perpendicular(true)
        { }
        
        template<typename _T2>
        line(coordinate<_T2> A, coordinate<_T2> B)
        {
            if (A.x == B.x)
            {
                is_perpendicular = true;
                x = static_cast<val_type>(A.x);
            }
            else
            {
                is_perpendicular = false;
                k = static_cast<val_type>((B.y - A.y) / (B.x - A.x));
                b = static_cast<val_type>(A.y - k * A.x);
            }
        }
        
        template<typename _T2>
        line(val_type _k, coordinate<_T2> A):
        k(_k), b(static_cast<val_type>(A.y - k * A.x))
        { }
        
        line(const line &val):
        k(val.k), b(val.b), x(val.x), is_perpendicular(val.is_perpendicular)
        { }
    };
    
    template<typename _T>
    long double mod(const coordinate<_T> A)
    { return std::sqrt(std::pow(A.x, 2) + std::pow(A.y, 2)); }
    
    template<typename _T>
    long double distance(const coordinate<_T> A, const coordinate<_T> B)
    { return std::sqrt(std::pow(A.x - B.x, 2) + std::pow(A.y - B.y, 2)); }
    
    template<typename _T>
    coordinate<_T> midpoint(const coordinate<_T> A, const coordinate<_T> B)
    { return coordinate<_T>((A.x + B.x) / 2, (A.y + B.y) / 2); }
    
    template<typename _T>
    bool is_parallel(const line<_T> l1, const line<_T> l2)
    {
        if (l1.is_perpendicular)
            return l2.is_perpendicular;
        return (l1.k == l2.k);
    }
    
    template<typename _T>
    coordinate<_T> intersection(const line<_T> l1, const line<_T> l2)
    {
        if (is_parallel(l1, l2))
            return NULL;
        if (l1.is_perpendicular)
            return coordinate<_T>(l1.x, l2.k * l1.x + l2.b);
        if (l2.is_perpendicular)
            return coordinate<_T>(l2.x, l1.k * l2.x + l1.b);
        return coordinate<_T>((l2.b - l1.b) / (l1.k - l1.b), (l1.k * l2.b - l1.b * l1.b) / (l1.k - l1.b));
    }
    
    template<typename _T>
    bool is_collinear(const coordinate<_T> A, const coordinate<_T> B, const coordinate<_T> C)
    { return ((A.x - B.x) * (A.y - C.y) == (A.y - B.y) * (A.x - C.x)); }
    
    template<typename _T>
    bool is_in_a_circle(coordinate<_T> A, coordinate<_T> B, coordinate<_T> C, coordinate<_T> D)
    {
        return std::abs(distance(A, B) * distance(C, D) + distance(B, C) * distance(A, D) - distance(A, C) * distance(B, D)) < error
            || std::abs(distance(A, C) * distance(B, D) + distance(A, B) * distance(C, D) - distance(A, D) * distance(B, C)) < error
            || std::abs(distance(A, D) * distance(B, C) + distance(A, C) * distance(B, D) - distance(A, B) * distance(C, D)) < error;
    }
    
    using ::pow;
    using ::sqrt;
    using ::cbrt;
    using ::abs;
    using ::floor;
    using ::ceil;
    using ::tan;
    using ::sin;
    using ::cos;
    using ::atan;
    using ::asin;
    using ::acos;
    using ::log;
    using ::log2;
    using ::log10;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif