// <equation.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_EQUATION_H
#define _LIBSEREVIA_EQUATION_H 1

/** @file equation.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "real.h"
#include <iostream>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class
    {
        private:
        using default_coeff_type = real;
        using default_ans_type = real;
        
        const std::string subscript[9] = {"?", "?", "?", "?", "?", "?", "?", "?", "?"};
        const std::string superscript[9] = {"", "?", "?", "?", "?", "?", "?", "?", "?"};
        const std::string reference_zh[5] = {"一", "二", "三", "四", "五"};
        
        public:
        template<typename coeff_type>
        std::vector<coeff_type> input_coefficient(size_t var, size_t degree)
        {
            std::cout << "请将方程化简为ax" << superscript[degree - 1];
            char ch = 'b';
            for (int i = degree - 2; i >= 0; i--)
            {
                std::cout << "+" << ch << "x" << superscript[i];
                ch++;
            }
            std::cout << "+" << ch << "=0的最简形式\n";
            ch = 'a';
            for (int i = 0; i <= degree; i++)
            {
                std::cout << ch << "=\n";
                ch++;
            }
            coeff_type a;
            std::vector<coeff_type> a2;
            std::cout << "\033[" << degree + 1 << "A";
            for (int i = 0; i <= degree; i++)
            {
                std::cout << "\033[2C";
                std::cin >> a;
                a2.push_back(a);
            }
            return a2;
        }
        
        template<typename ans_type>
        void print_ans(size_t var, size_t degree, std::vector<ans_type> ans)
        {
            for (int i = 0; i < degree; i++)
            {
                std::cout << "x" << subscript[i] << "=";
                std::cout << ans[i];
                if (var == 2)
                {
                    std::cout << "x" << subscript[i] << "=";
                    std::cout << ans[i * 2];
                    std::cout << ", y" << subscript[i] << "=";
                    std::cout << ans[i * 2 + 1];
                }
                else if (var == 3)
                {
                    std::cout << "x" << subscript[i] << "=";
                    std::cout << ans[i * 3];
                    std::cout << ", y" << subscript[i] << "=";
                    std::cout << ans[i * 3 + 1];
                    std::cout << ", z" << subscript[i] << "=";
                    std::cout << ans[i * 3 + 2];
                }
                std::cout << "\n";
            }
        }
        
        // 一元方程
        class
        {
            private:
            #define a coefficient[0]
            #define b coefficient[1]
            #define c coefficient[2]
            #define d coefficient[3]
            #define e coefficient[4]
            #define f coefficient[5]
            
            #define x1 ans[0]
            #define x2 ans[1]
            #define x3 ans[2]
            #define x4 ans[3]
            #define x5 ans[4]
            
            // 一元一次方程 ax+b=0
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_1(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(1);
                
                x1 = -b / a;
                
                return ans;
            }
            
            // 一元二次方程 ax?+bx+c=0
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_2(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(2);
                
                x1 = (-b + sqrt(b * b - ans_type(4) * a * c)) / (ans_type(2) * a);
                x2 = (-b - sqrt(b * b - ans_type(4) * a * c)) / (ans_type(2) * a);
                
                return ans;
            }
            
            // 一元三次方程 ax?+bx?+cx+d=0
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_3(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(3);
                
                ans_type p = (3 * a * c - b * b) / (3 * a * a);
                ans_type q = (27 * a * a * d - 9 * a * b * c + 2 * b * b * b) / (27 * a * a * a);
                
                ans_type u = cbrt(-q / ans_type(2) + sqrt(q * q / ans_type(4) + p * p * p / ans_type(27)));
                ans_type v = cbrt(-q / ans_type(2) - sqrt(q * q / ans_type(4) + p * p * p / ans_type(27)));
                std::complex<ans_type> omega(-0.5, sqrt(ans_type(3)) / 2);
                
                x1 = -b / (3 * a) + u + v;
                // x2 = -b / (3 * a) + omega * u + omega * omega * v;
                // x3 = -b / (3 * a) + omega * omega * u + omega * v;
                
                return ans;
            }
            
            // 一元四次方程 ax?+bx?+cx?+dx+e=0
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_4(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(4);
                
                b /= a, c /= a, d /= a, e /= a, a = 1;
                
                std::vector<ans_type> cubicr = {1, -1 * c, b * d - 4 * e, 4 * c * e - d * d - b * b * e};
                ans_type y = formula_3<ans_type, ans_type>(cubicr)[0];
                
                std::vector<ans_type> quadraticr[2];
                if (b * b - 4 * c + 4 * y == 0)
                {
                    quadraticr[0] = {2, b, static_cast<ans_type>(y + sqrt(y * y - 4 * e))};
                    quadraticr[1] = {2, b, static_cast<ans_type>(y - sqrt(y * y - 4 * e))};
                }
                else
                {
                    quadraticr[0] = {2, static_cast<ans_type>(b + sqrt(b * b - 4 * c + 4 * y)), static_cast<ans_type>(y - (b * y - 2 * d) / sqrt(b * b - 4 * c + 4 * y))};
                    quadraticr[1] = {2, static_cast<ans_type>(b - sqrt(b * b - 4 * c + 4 * y)), static_cast<ans_type>(y + (b * y - 2 * d) / sqrt(b * b - 4 * c + 4 * y))};
                }
                
                std::vector<ans_type> ans12 = formula_2<ans_type, ans_type>(quadraticr[0]);
                std::vector<ans_type> ans34 = formula_2<ans_type, ans_type>(quadraticr[1]);
                
                x1 = ans12[0];
                x2 = ans12[1];
                x3 = ans34[0];
                x4 = ans34[1];
                
                return ans;
            }
            
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_4_2(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(4);
                
                ans_type P = (c * c + 12 * a * e - 3 * b * d) / 9;
                ans_type Q = (27 * a * d * d + 2 * c * c * c + 27 * b * b * e - 72 * a * c * e - 9 * b * c * d) / 54;
                ans_type D = sqrt(Q * Q - P * P * P);
                
                ans_type u;
                if (abs(cbrt(Q + D)) > abs(cbrt(Q - D)))
                    u = cbrt(Q + D);
                else
                    u = cbrt(Q - D);
                ans_type v;
                if (u == 0)
                    v = 0;
                else
                    v = P / u;
                
                std::complex<ans_type> omega(-0.5, sqrt(3) / 2);
                ans_type m[3], S[3];
                for (int k = 1; k <= 3; k++)
                {
                    ans_type temp1 = 4 * a * (pow(omega, k - 1) * u + pow(omega, 4 - k) * v);
                    m[k - 1] = sqrt(b * b - 8 / 3 * a * c + temp1);
                    S[k - 1] = 2 * b * b - 16 / 3 * a * c - temp1;
                }
                int temp2 = (((abs(m[0]) > abs(m[1])) ? abs(m[0]) : abs(m[1])) > abs(m[2])) ? ((abs(m[0]) > abs(m[1])) ? 0 : 1) : 2;
                ans_type T = (8 * a * b * c - 16 * a * a * d - 2 * b * b * b) / m[temp2];
                if (m[temp2] == 0)
                {
                    S[temp2] = b * b - 8 / 3 * a * c;
                    T = 0;
                }
                
                for (int n = 1; n <= 4; n++)
                    ans[n - 1] = (-b + pow(-1, ceil(n / 2)) * m[temp2] + pow(-1, n + 1) * sqrt(S[temp2] + pow(-1, ceil(n / 2)) * T)) / (4 * a);
                
                return ans;
            }
            
            public:
            template<typename coeff_type, typename ans_type = default_ans_type>
            std::vector<ans_type> solve(std::vector<coeff_type> coefficient)
            {
                switch (coefficient.size())
                {
                    case 2:
                    return formula_1<coeff_type, ans_type>(coefficient);
                    break;
                    
                    case 3:
                    return formula_2<coeff_type, ans_type>(coefficient);
                    break;
                    
                    case 4:
                    return formula_3<coeff_type, ans_type>(coefficient);
                    break;
                    
                    case 5:
                    return formula_4<coeff_type, ans_type>(coefficient);
                    break;
                    
                    default:
                    break;
                }
                throw std::invalid_argument(__func__);
                return std::vector<ans_type>(coefficient.size());
            }
            
            template<typename coeff_type, typename ans_type = default_ans_type>
            std::vector<ans_type> solve(std::initializer_list<coeff_type> coefficient)
            {
                std::vector<coeff_type> _c = coefficient;
                return solve<coeff_type, ans_type>(_c);
            }
            
            /*
            // 一元五次方程 ax?+bx?+cx?+dx?+ex+f=0
            template<typename coeff_type, typename ans_type>
            std::vector<ans_type> formula_5(std::vector<coeff_type> coefficient)
            {
                std::vector<ans_type> ans(5);
                
                ans_type L = 2 * b * b - 5 * a * c;
                ans_type M = 4 * b * b * b - 15 * a * b * c + 25 * a * a * d;
                ans_type N = 7 * b * b * b * b + 25 * a * a * c * c - 35 * a * b * b * c + 50 * a * a * b * d - 125 * a * a * a * e;
                ans_type P = 4 * b * b * b * b * b - 25 * a * b * b * b * c + 125 * a * a * b * b * d - 625 * a * a * a * b * e + 3125 * a * a * a * a * f;
                
                ans_type G = 4 * L * L * L - 9 * M * M + 8 * L * N;
                ans_type H = 10 * L * L * M - 6 * M * N + L * P;
                ans_type J = 4 * L * L * L * L - 4 * L * L * N + 3 * M * P;
                ans_type K = M * M * M * M + N * N * N - M * N * P;
                
                ans_type E = 2 * G * G * L * L - 2 * G * G * N + 3 * G * H * M - 4 * H * H * L - G * J * L;
                ans_type F = G * G * P + 3 * G * J * M - 4 * H * J * L;
                
                ans_type A = F * F - 12 * E * E * L;
                ans_type B = 6 * F * F * F - 64 * E * E * F * L - 72 * E * E * E * M;
                ans_type C = 3 * F * F * F * F - 24 * E * E * F * F * L - 48 * E * E * E * F * M - 80 * E * E * E * E * L * L;
                ans_type D = F * F * G + 4 * E * F * H - 4 * E * E * J;
                
                ans_type delta1 = B * B - 4 * A * C;
                ans_type delta2 = P * P - 4 * L * L * L * L * L;
                
                std::complex<ans_type> i(0, 1);
                
                if (L == 0 && M == 0 && N == 0 && P == 0)
                    x1 = -1 * b / (5 * a), x2 = x1, x3 = x1, x4 = x1, x5 = x1, isr = 1;
        
                else if (L != 0 && G == 0 && H == 0 && J == 0)
                {
                    if (7 * L * L == 4 * N)
                    {
                        x1 = -1 * (b * L + 2 * M) / (5 * a * L);
                        x2 = (-2 * b * L + M) / (10 * a * L), x3 = x2, x4 = x2, x5 = x2;
                    }
                    else
                    {
                        x1 = -1 * (2 * b * L + 9 * M) / (10 * a * L), x2 = x1;
                        x3 = (-1 * b * L + 3 * M) / (5 * a * L), x4 = x3, x5 = x3;
                    }
                }
                
                else if (G != 0 && E == 0 && F == 0)
                {
                    if (H * H + G * J == 0)
                    {
                        x1 = (-2 * b * G - 3 * H + sqrt(20 * G * G * L - 15 * H * H)) / (10 * a * G);
                        x2 = (-2 * b * G - 3 * H - sqrt(20 * G * G * L - 15 * H * H)) / (10 * a * G);
                        x3 = (-1 * b * G + H) / (5 * a * G), x4 = x3, x5 = x3;
                    }
                    else
                    {
                        x1 = -1 * (b * G + 4 * H) / (5 * a * G);
                        x2 = (-1 * b * G + H + sqrt(H * H + G * J)) / (5 * a * G), x4 = x2;
                        x3 = (-1 * b * G + H - sqrt(H * H + G * J)) / (5 * a * G), x5 = x3;
                    }
                }
        
                else if (E != 0 && D == 0)
                {
                    x4 = -1 * (2 * b * E + F) / (10 * a * E), x5 = x4;
                    if (abs(delta1) > 0)
                    {
                        ans_type y1 = 10 * A * F + 7.5 * (-1 * B + sqrt(B * B - 4 * A * C));
                        ans_type y2 = 10 * A * F + 7.5 * (-1 * B - sqrt(B * B - 4 * A * C));
                        x1 = (-6 * b * E + 2 * F - (cbrt(y1) + cbrt(y2))) / (30 * a * E);
                        x2 = (-12 * b * E + 4 * F + (cbrt(y1) + cbrt(y2))) / (60 * a * E) + (sqrt(3) * (cbrt(y1) - cbrt(y2))) / (60 * a * E) * i;
                        x3 = (-12 * b * E + 4 * F + (cbrt(y1) + cbrt(y2))) / (60 * a * E) - (sqrt(3) * (cbrt(y1) - cbrt(y2))) / (60 * a * E) * i;
                    }
                    else // if (abs(delta1) < 0)
                    {
                        var theta = acos((3 * B - 4 * A * F) / (2 * A * sqrt(-5 * A)));
                        x1 = (-3 * b * E + F - sqrt(-5 * A) * cos(theta / 3)) / (15 * a * E);
                        x2 = (-6 * b * E + 2 * F + sqrt(-5 * A) * (cos(theta / 3) + sqrt(3) * sin(theta / 3))) / (30 * a * E);
                        x3 = (-6 * b * E + 2 * F + sqrt(-5 * A) * (cos(theta / 3) - sqrt(3) * sin(theta / 3))) / (30 * a * E);
                    }
                }
        
                else if (D != 0 && M == 0 && N == 0 && abs(delta2) > 0)
                {
                    ans_type y1 = (P + sqrt(P * P - 4 * L * L * L * L * L)) / 2;
                    ans_type y2 = (P - sqrt(P * P - 4 * L * L * L * L * L)) / 2;
                    x1 = (-1 * b - (aroot(y1, 5) + aroot(y2, 5))) / (5 * a);
                    x2 = (-1 * b + (1 - sqrt(5)) / 4 * (aroot(y1, 5) + aroot(y2, 5))) / (5 * a) + (sqrt(10 + 2 * sqrt(5) / 4) * (aroot(y1, 5) - aroot(y2, 5))) / (5 * a) * i;
                    x3 = (-1 * b + (1 - sqrt(5)) / 4 * (aroot(y1, 5) + aroot(y2, 5))) / (5 * a) - (sqrt(10 + 2 * sqrt(5) / 4) * (aroot(y1, 5) - aroot(y2, 5))) / (5 * a) * i;
                    x4 = (-1 * b + (1 + sqrt(5)) / 4 * (aroot(y1, 5) + aroot(y2, 5))) / (5 * a) + (sqrt(10 - 2 * sqrt(5) / 4) * (aroot(y1, 5) - aroot(y2, 5))) / (5 * a) * i;
                    x5 = (-1 * b + (1 + sqrt(5)) / 4 * (aroot(y1, 5) + aroot(y2, 5))) / (5 * a) - (sqrt(10 - 2 * sqrt(5) / 4) * (aroot(y1, 5) - aroot(y2, 5))) / (5 * a) * i;
                }
        
                else if (D != 0 && M == 0 && N == 0 && abs(delta2) < 0)
                {
                    var theta = acos(P / (2 * L * L * sqrt(L)));
                    x1 = (-1 * b - 2 * sqrt(L) * cos(theta / 5)) / (5 * a);
                    x2 = (-1 * b + sqrt(L) * ((1 - sqrt(5) / 2) * cos(theta / 5) + sqrt(10 + 2 * sqrt(5)) / 2) * sin(θ / 5)) / (5 * a);
                    x3 = (-1 * b + sqrt(L) * ((1 - sqrt(5) / 2) * cos(theta / 5) - sqrt(10 + 2 * sqrt(5)) / 2) * sin(θ / 5)) / (5 * a);
                    x4 = (-1 * b + sqrt(L) * ((1 + sqrt(5) / 2) * cos(theta / 5) + sqrt(10 - 2 * sqrt(5)) / 2) * sin(θ / 5)) / (5 * a);
                    x5 = (-1 * b + sqrt(L) * ((1 + sqrt(5) / 2) * cos(theta / 5) - sqrt(10 - 2 * sqrt(5)) / 2) * sin(θ / 5)) / (5 * a);
                }
        
                else if (D != 0 && M * N != 0 && L == 0 && K == 0)
                {
                    x1 = (-1 * b - aroot(N * N / M, 5) - aroot(M * M * M / N, 5)) / (5 * a);
                    x2 = ((1 - sqrt(5)) / 4 * aroot(N * N / M, 5) + (1 + sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) + (sqrt(10 + 2 * sqrt(5)) / 4 * aroot(N * N / M, 5) + sqrt(10 - 2 * sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) * i;
                    x3 = ((1 - sqrt(5)) / 4 * aroot(N * N / M, 5) + (1 + sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) - (sqrt(10 + 2 * sqrt(5)) / 4 * aroot(N * N / M, 5) + sqrt(10 - 2 * sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) * i;
                    x4 = ((1 + sqrt(5)) / 4 * aroot(N * N / M, 5) + (1 - sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) + (sqrt(10 - 2 * sqrt(5)) / 4 * aroot(N * N / M, 5) + sqrt(10 + 2 * sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) * i;
                    x5 = ((1 + sqrt(5)) / 4 * aroot(N * N / M, 5) + (1 - sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) - (sqrt(10 - 2 * sqrt(5)) / 4 * aroot(N * N / M, 5) + sqrt(10 + 2 * sqrt(5)) / 4 * aroot(M * M * M / N, 5)) / (5 * a) * i;
                }
                
                else
                    x1 = ans_type(nan), x2 = x1, x3 = x1, x4 = x1, x5 = x1;
                
                return ans;
            }
            */
            
            #undef a
            #undef b
            #undef c
            #undef d
            #undef e
            #undef f
            
            #undef x1
            #undef x2
            #undef x3
            #undef x4
            #undef x5
        } univariate;
    } equation;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif