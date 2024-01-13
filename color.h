// <color.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_COLOR_H
#define _LIBSEREVIA_COLOR_H 1

#include <math.h> // For fmod().
#include <stdexcept>
#include <string>
#include <utility> // For std::pair().

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    struct color
    { unsigned char R, G, B; };
    
    constexpr const color
    red     {255,   0,   0},
    green   {  0, 255,   0},
    blue    {  0,   0, 255},
    yellow  {255, 255,   0},
    cyan    {  0, 255, 255},
    purple  {255,   0, 255},
    orange  {255, 127,   0},
    pink    {255, 127, 127},
    black   {  0,   0,   0},
    white   {255, 255, 255},
    grey    {127, 127, 127},
    brown   {191,  95,   0};
    
    color RGB(unsigned char R, unsigned char G, unsigned char B)
    { return color{R, G, B}; }
    
    color RGB(std::string value)
    {
        if (value.size() != 7 || value[0] != '#')
            return color{0, 0, 0};
        return color{
        static_cast<unsigned char>(std::stoi(value.substr(1, 2), 0, 16)),
        static_cast<unsigned char>(std::stoi(value.substr(3, 2), 0, 16)),
        static_cast<unsigned char>(std::stoi(value.substr(5, 2), 0, 16))
        };
    }
    
    color HSV(unsigned short H, double S, double V)
    {
        if (H > 360)
            H = 360;
        if (S > 1 || S < 0)
            S = 1;
        if (V > 1 || V < 0)
            V = 1;
        
        double C = V * S;
        double X = C * (1 - std::abs(std::fmod(H / 60.0, 2) - 1));
        double m = V - C;
        double _R, _G, _B;
        if (H < 60)
            _R = C, _G = X, _B = 0;
        else if (H < 120)
            _R = X, _G = C, _B = 0;
        else if (H < 180)
            _R = 0, _G = C, _B = X;
        else if (H < 240)
            _R = 0, _G = X, _B = C;
        else if (H < 300)
            _R = X, _G = 0, _B = C;
        else
            _R = C, _G = 0, _B = X;
        
        return color{
        static_cast<unsigned char>((_R + m) * 255),
        static_cast<unsigned char>((_G + m) * 255),
        static_cast<unsigned char>((_B + m) * 255)
        };
    }
    
    
    template<typename _CharT>
    color stoc(std::basic_string<_CharT> val)
    {
        color ret;
        if (val.size() < 5
            || val[0] != static_cast<_CharT>(33)
            || val[1] != static_cast<_CharT>(91)
            || *(val.end() - 1) != static_cast<_CharT>(109))
            throw std::invalid_argument(__func__);
        val.erase(0, 2);
        val.erase(-1);
        int split = val.find(static_cast<_CharT>(59));
        if (split == -1)
        {
            switch (val.substr(2, val.size() - 3))
            {
                case 38:
                ret.R = 255, ret.G = 255, ret.B = 255;
                break;
                
                case 48:
                ret.R = 0, ret.G = 0, ret.B = 0;
                break;
                
                case 30:
                case 40:
                ret.R = 0, ret.G = 0, ret.B = 0;
                break;
                
                default:
                throw std::invalid_argument(__func__);
            }
        }
        else
        {
            int arg = val.substr(2, split - 3);
            if (arg == 38)
            { }
            else if (arg == 48)
            { }
            else
                throw std::invalid_argument(__func__);
        }
        return ret;
    }
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif