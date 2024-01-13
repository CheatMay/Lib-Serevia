// <fileparser.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_FILEPARSER_H
#define _LIBSEREVIA_FILEPARSER_H 1

/** @file fileparser.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class
    {
        private:
        std::vector<std::string> __text__;
        std::string __a__;
        
        std::string font[8] =
        {
            "\\GREY",
            "\\RED",
            "\\GREEN",
            "\\YELLOW",
            "\\BLUE",
            "\\PURPLE",
            "\\CYAN",
            "\\WHITE"
        };
        std::string font_bright[8] =
        {
            "\\B_GREY",
            "\\B_RED",
            "\\B_GREEN",
            "\\B_YELLOW",
            "\\B_BLUE",
            "\\B_PURPLE",
            "\\B_CYAN",
            "\\B_WHITE"
        };
        std::string BG[8] =
        {
            "\\BG_GREY",
            "\\BG_RED",
            "\\BG_GREEN",
            "\\BG_YELLOW",
            "\\BG_BLUE",
            "\\BG_PURPLE",
            "\\BG_CYAN",
            "\\BG_WHITE"
        };
        std::string BG_bright[8] =
        {
            "\\BG_B_GREY",
            "\\BG_B_RED",
            "\\BG_B_GREEN",
            "\\BG_B_YELLOW",
            "\\BG_B_BLUE",
            "\\BG_B_PURPLE",
            "\\BG_B_CYAN",
            "\\BG_B_WHITE"
        };
        
        void replace_all(std::string &basic, std::string find, std::string replace)
        {
        	while (1)
        	{
                int len = basic.find(find);
                if (len == basic.npos)
                    break;
                basic.replace(len, find.size(), replace);
            }
        }
        
        void fillin(std::string sign, std::string file, bool skip_empty_line)
        {
            __text__.clear();
            std::string begin = "<" + sign + ">";
            std::string end = "</" + sign + ">";
            bool flag = false;
            std::ifstream fin;
            fin.open(file, std::ios_base::in);
            std::string temp;
            while(getline(fin, temp))
            {
                if (temp == end)
                    break;
                if (flag && (!skip_empty_line || temp != ""))
                    __text__.push_back(temp);
                if (temp == begin)
                    flag = true;
            }
        }
        
        void fillin(std::string begin, std::string end, std::string file, bool skip_empty_line)
        {
            __text__.clear();
            bool flag = false;
            std::ifstream fin;
            fin.open(file, std::ios_base::in);
            std::string temp;
            while(getline(fin, temp))
            {
                if (temp == end)
                    break;
                if (flag && (!skip_empty_line || temp != ""))
                    __text__.push_back(temp);
                if (temp == begin)
                    flag = true;
            }
        }
        
        void _printer()
        {
            for (std::vector<std::string>::iterator it = __text__.begin(); it != __text__.end(); it++)
            {
                for (auto &&i : *it)
                {
                    std::cout << i;
                    std::this_thread::sleep_for(std::chrono::microseconds(128));
                }
                std::cout << std::endl;
            }
        }
        
        void replace_sign()
        {
            for (int i = 0; i < 8; i++)
            {
                char ch = '0' + i;
                std::string s1 = "\033[";
                s1 += "3";
                s1 += ch;
                s1 += "m";
                std::string s2 = "\033[";
                s2 += "9";
                s2 += ch;
                s2 += "m";
                std::string s3 = "\033[";
                s3 += "4";
                s3 += ch;
                s3 += "m";
                std::string s4 = "\033[";
                s4 += "10";
                s4 += ch;
                s4 += "m";
                for (std::vector<std::string>::iterator it = __text__.begin(); it != __text__.end(); it++)
                {
                    replace_all(*it, font[i], s1);
                    replace_all(*it, font_bright[i], s2);
                    replace_all(*it, BG[i], s3);
                    replace_all(*it, BG_bright[i], s4);
                }
            }
            for (std::vector<std::string>::iterator it = __text__.begin(); it != __text__.end(); it++)
            {
                replace_all(*it, "\\RESET", "\033[0m");
                replace_all(*it, "\\I", "\033[3m");
                replace_all(*it, "\\U", "\033[4m");
                replace_all(*it, "\\ML", "\033[9m");
            }
        }
        
        bool makefile()
        {
            std::ofstream ofs;
            ofs.open("cxes11965826.cpp", std::ios_base::out);
            if (!ofs.is_open())
                return false;
            auto len = __text__.size();
            for (auto i = 0; i < len; i++)
                ofs << __text__[i] << std::endl;
            ofs.close();
            return true;
        }
        
        bool makeexe()
        {
            system("g++ -std=c++11 cxes11965826.cpp -o cxes11965826.exe");
            return true;
        }
        
        bool runfile()
        {
            std::ifstream fin;
            fin.open("cxes11965826.exe", std::ios_base::in);
            if (!fin.is_open())
                return false;
            std::cout << "\033[2J\033[1;1H";
            std::cout << "\033[32m编译成功\033[0m\n\n";
            system("./cxes11965826.exe");
            std::cout << "\n\n\033[93m代码运行结束\033[0m\n";
            return true;
        }
        
        public:
        
        // 初始化
        void init(char **a)
        {
            __a__ = a[0];
            __a__.replace(__a__.find("exe"), 3, "cpp");
        }
        
        // 提取文本
        std::vector<std::string> extract(const std::string title, bool skip_empty_line = false)
        {
            fillin(title, __a__, skip_empty_line);
            // replace_sign();
            return __text__;
        }
        
        std::vector<std::string> extract(const std::string begin, const std::string end, bool skip_empty_line = false)
        {
            fillin(begin, end, __a__, skip_empty_line);
            // replace_sign();
            return __text__;
        }
        
        // 输出文本
        void print(const std::string title, bool skip_empty_line = false)
        {
            fillin(title, __a__, skip_empty_line);
            // replace_sign();
            _printer();
            __text__.clear();
        }
        
        void print(const std::string begin, const std::string end, bool skip_empty_line = false)
        {
            fillin(begin, end, __a__, skip_empty_line);
            // replace_sign();
            _printer();
            __text__.clear();
        }
        
        // 编译器内编译器，返回值0=运行成功, 1=程序创建失败, 2=程序启动失败
        int run(std::string name)
        {
            fillin(name, __a__, true);
            if (!makefile())
                return 1;
            makeexe();
            __a__ = __a__.substr(0, __a__.find_last_of('\\'));
            if (!runfile())
                return 2;
            __text__.clear();
            return 0;
        }
    } fileparser;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif