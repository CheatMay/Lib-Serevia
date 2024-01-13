// <ioextend.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_IOEXTEND_H
#define _LIBSEREVIA_IOEXTEND_H 1

/** @file ioextend.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include "formatfwd.h"
#include "localr"
#include "format_locale.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <bits/stl_pair.h>
#include <math.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/shm.h>

extern "C" pid_t fork();

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    extern std::pair<size_t, size_t> area(const std::string &);
    
    // 系统
    class
    {
        public:
        
        // 控制字符ASCII值
        const int K_TAB = 9;
        const int K_ENTER = 10;
        const int K_CTRL = 17;
        const int K_ALT = 18;
        const int K_ESC = 27;
        const int K_BACKSPACE = 127;
        
        // 等待2秒（常用时间）
        void quodo()
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
        // debug
        void debug()
        {
            std::cout << "\n#debug";
            while (1)
                std::this_thread::sleep_for(std::chrono::seconds(999));
        }
    } sys;
    
    // 终端工具
    class
    {
        public:
        void cls()
        { std::cout << "\033[2J\033[1;1H"; }
        
        // 刷新终端
        void refresh(size_t wait_time, bool do_cls)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(wait_time));
            std::cout << "\033[0m";
            if (do_cls)
                cls();
            else
                std::cout << std::endl;
        }
        
        // 逐行消失
        void vanish_by_line(size_t lines, size_t speed)
        {
            std::cout << "\033[" << width << "D";
            for (int i = 0; i < lines; i++)
            {
                std::cout << "\033[2K\033[1A";
                std::this_thread::sleep_for(std::chrono::microseconds(speed));
            }
            std::cout << "\033[1B";
        }
        
        // 自定义行数清屏
        void clearlines(size_t lines)
        {
            std::cout << "\033[" << width << "D";
            for (int i = 0; i < lines; i++)
                std::cout << "\033[2K\033[1A";
            std::cout << "\033[1B";
        }
        
        // 终端滚动
        void scroll_up(size_t n)
        {
            if (!n) return;
            std::cout << "\033[" << n << "S";
        }
        
        void scroll_down(size_t n)
        {
            if (!n) return;
            std::cout << "\033[" << n << "T";
        }
        
        // 光标控制
        class
        {
            public:
            
            // 隐藏光标
            void hide()
            { std::cout << "\033[?25l"; }
            
            // 显示光标
            void show()
            { std::cout << "\033[?25h"; }
            
            // 光标闪烁
            void blink(bool b)
            {
                if (b)
                    std::cout << "\033[?12h";
                else
                    std::cout << "\033[?12l";
            }
            
            // 光标移动
            void up(size_t n)
            {
                if (!n) return;
                std::cout << "\033[" << n << "A";
            }
            
            void down(size_t n)
            {
                if (!n) return;
                std::cout << "\033[" << n << "B";
            }
            
            void left(size_t n)
            {
                if (!n) return;
                std::cout << "\033[" << n << "D";
            }
            
            void right(size_t n)
            {
                if (!n) return;
                std::cout << "\033[" << n << "C";
            }
            
            void move_x(size_t x)
            {
                if (!x) return;
                std::cout << "\033[" << x << "G";
            }
            
            void move_y(size_t y)
            {
                if (!y) return;
                std::cout << "\033[" << y << "d";
            }
            
            void move(size_t x, size_t y)
            {
                std::cout << "\033[" << y << ";" << x << "H";
                // std::cout << "\033[" << y << ";" << x << "f";
            }
            
            void move(std::pair<size_t, size_t> pos)
            { move(pos.first, pos.second); }
            
            // 保存当前位置
            void save()
            { std::cout << "\033[s"; }
            
            // 还原位置
            void restore()
            { std::cout << "\033[u"; }
            
            // 获取鼠标位置
            std::pair<size_t, size_t> pos()
            {
                std::cout << "\033[6n";
                std::string s = "";
                char ch = 0;
                while (ch != 'R')
                {
                    ch = xesstd::getch();
                    s += ch;
                }
                return std::make_pair(stoi(s.substr(s.find(';') + 1, s.size() - 1)), stoi(s.substr(s.find('[') + 1, s.find(';'))));
            }
        } cursor;
        
        // 获取终端大小
        std::pair<size_t, size_t> size()
        {
            cursor.save();
            cursor.move(999, 999);
            std::cout << "\033[6n";
            cursor.restore();
            std::string s = "";
            char ch = 0;
            while (ch != 'R')
            {
                ch = xesstd::getch();
                s += ch;
            }
            return std::make_pair(stoi(s.substr(s.find(';') + 1, s.size() - 1)), stoi(s.substr(s.find('[') + 1, s.find(';'))));
        }
        
        std::pair<size_t, size_t> _size = size();
        size_t width = _size.first;
        size_t height = _size.second;
        
        // 隐藏输出
        void hideprint()
        { std::cout << "\033[8m"; }
        
        // 显示输出
        void showprint()
        { std::cout << "\033[28m"; }
        
        // 区域清屏（从光标位置向左上方向清屏）
        void erase(size_t w, size_t h)
        {
            if (h == 1)
                std::cout << "\033[" << w << "D";
            else
                std::cout << "\033[" << h - 1 << "A\033[" << w << "D";
            for (int i = 0; i < h; i++)
            {
                for (int i = 0; i < w; i++)
                    std::cout << " ";
                if (i != h)
                    std::cout << "\033[" << w << "D" << "\033[1B";
            }
        }
    } terminal;
    
    // 字符串所占终端空间
    std::pair<size_t, size_t> terminal_area(const std::string &str)
    {
        std::pair<size_t, size_t> xy(std::make_pair(0, 0));
        if (str.size() == 0)
        {
            xy.second = 1;
            return xy;
        }
        for (int i = 0; i < str.size(); )
        {
            std::string s;
            while (str[i] != '\n' && xesstd::width(s) <= terminal.width && i < str.size())
                s += str[i++];
            if (str[i] == '\n')
                if (++i > str.size() - 1)
                    xy.second++;
            xy.first = std::max(xy.first, xesstd::width(s)), xy.second++;
        }
        return xy;
    }
    
    // 输入工具
    class
    {
        private:
        std::string __global_input_string;
        
        public:
        __attribute__((deprecated)) void read()
        { system("read anykey"); }
        
        void getstr(const std::string title = "")
        {
            std::cout << title;
            getline(std::cin, __global_input_string);
        }
        
        void input(std::string &str, const std::string title = "")
        {
            std::cout << title;
            getline(std::cin, str);
        }
        
        std::string input_value()
        { return __global_input_string; }
        
        bool inputed(const std::string str)
        { return (__global_input_string == str); }
        
        void getstrch(const std::string title = "")
        {
            std::cout << title;
            system("stty -icanon");
            __global_input_string = getchar();
            system("stty icanon");
        }
        
        void inputch(std::string &str, const std::string title = "")
        {
            std::cout << title;
            struct termios a, b;
            int ch;
            tcgetattr(STDIN_FILENO, &a);
            b = a;
            b.c_lflag &= ~(ICANON);
            b.c_cc[VMIN] = 1;
            b.c_cc[VTIME] = 0;
            ch = tcsetattr(STDIN_FILENO, TCSANOW, &b);
            ::read(STDIN_FILENO, &ch, 1);
            tcsetattr(STDIN_FILENO, TCSANOW, &a);
            str.clear();
            str[0] = ch;
        }
        
        void button()
        {
            struct termios a, b;
            int ch;
            tcgetattr(STDIN_FILENO, &a);
            b = a;
            b.c_lflag &= ~(ICANON);
            b.c_cc[VMIN] = 1;
            b.c_cc[VTIME] = 0;
            ch = tcsetattr(STDIN_FILENO, TCSANOW, &b);
            ::read(STDIN_FILENO, &ch, 1);
            tcsetattr(STDIN_FILENO, TCSANOW, &a);
        }
        
        void pause()
        {
            std::cout << "任意键继续\n";
            button();
        }
        
        int choice(const std::string title, std::vector<std::string> option, bool mode = 0/*0=输入, 1=切换*/)
        {
            if (mode == 0)
            {
                int c;
                std::cout << title << std::endl;
                for (int i = 0; i < option.size(); i++)
                    std::cout << i + 1 << ". " << option[i] << "\n";
                while (1)
                {
                    std::cout << "输入序号：";
                    getstrch();
                    c = input_value()[0] - '0';
                    if (c < 1 || c > option.size())
                    {
                        std::cout << "\n没有这个选项，请重新选择";
                        sys.quodo();
                        terminal.clearlines(2);
                    }
                    else
                        break;
                }
                std::cout << std::endl;
                return c;
            }
            else if (mode == 1)
            {
                char a;
                int c = 1;
                std::cout << title << std::endl << "（Tab切换，Enter确定）\n";
                while (1)
                {
                    for (int i = 0; i < option.size(); i++)
                    {
                        if (i + 1 == c)
                            std::cout << "> ";
                        else
                            std::cout << "  ";
                        std::cout << i + 1 << ". " << option[i] << "\n";
                    }
                    getstrch();
                    a = input_value()[0];
                    if (a == 27)
                    {
                        if (c == 1)
                            c = option.size();
                        else
                            c--;
                        terminal.clearlines(option.size() + 1);
                    }
                    else if (a == sys.K_TAB)
                    {
                        if (c == option.size())
                            c = 1;
                        else
                            c++;
                        terminal.clearlines(option.size() + 1);
                    }
                    else if (a == sys.K_ENTER)
                        break;
                    else
                    {
                        std::cout << "\033[1D \033[1D";
                        terminal.clearlines(option.size() + 1);
                    }
                }
                std::cout << "\033[1A";
                return c;
            }
            return -1;
        }
        
        std::vector<bool> multichoice(const std::string title, std::vector<std::string> option, bool mode = 0/*0=输入, 1=切换*/)
        {
            std::vector<bool> res;
            for (int i = 0; i < option.size(); i++)
                res.push_back(0);
            if (mode == 0)
            {
                int a;
                char c;
                std::cout << title << std::endl;
                while (1)
                {
                    for (int i = 0; i < option.size(); i++)
                    {
                        if (res[i])
                            std::cout << "√ ";
                        else
                            std::cout << "  ";
                        std::cout << i + 1 << ". " << option[i] << "\n";
                    }
                    std::cout << "输入序号选择/取消选择，回车提交：";
                    getstrch();
                    c = input_value()[0];
                    a = c - '0';
                    if (c == sys.K_ENTER)
                    {
                        bool flag = 0;
                        for (int i = 0; i < res.size(); i++)
                            if (res[i])
                                flag = 1;
                        if (!flag)
                        {
                            std::cout << "请选择至少一个选项";
                            sys.quodo();
                            terminal.clearlines(2);
                            terminal.clearlines(option.size() + 1);
                        }
                        else
                            break;
                    }
                    else if (a < 1 || a > option.size())
                    {
                        std::cout << "\n没有这个选项";
                        sys.quodo();
                        terminal.clearlines(2);
                        terminal.clearlines(option.size() + 1);
                    }
                    else
                    {
                        res[a - 1] = !res[a - 1];
                        terminal.clearlines(option.size() + 1);
                    }
                }
                return res;
            }
            else if (mode == 1)
            {
                char a;
                int c = 1;
                std::cout << title << std::endl << "（Tab切换，空格选择/取消选择，Enter确定）\n";
                while (1)
                {
                    for (int i = 0; i < option.size(); i++)
                    {
                        if (i + 1 == c)
                            std::cout << "> ";
                        else
                            std::cout << "  ";
                        if (res[i])
                            std::cout << "√ ";
                        else
                            std::cout << "  ";
                        std::cout << i + 1 << ". " << option[i] << "\n";
                    }
                    getstrch();
                    a = input_value()[0];
                    if (a == 27)
                    {
                        if (c == 1)
                            c = option.size();
                        else
                            c--;
                        terminal.clearlines(option.size() + 1);
                    }
                    else if (a == sys.K_TAB)
                    {
                        if (c == option.size())
                            c = 1;
                        else
                            c++;
                        terminal.clearlines(option.size() + 1);
                    }
                    else if (a == ' ')
                    {
                        res[c - 1] = !res[c - 1];
                        terminal.clearlines(option.size() + 1);
                    }
                    else if (a == sys.K_ENTER)
                    {
                        bool flag = false;
                        for (int i = 0; i < res.size(); i++)
                            if (res[i])
                                flag = true;
                        if (!flag)
                        {
                            std::cout << "\033[1A请选择至少一个选项";
                            sys.quodo();
                            terminal.clearlines(1);
                            terminal.clearlines(option.size() + 1);
                        }
                        else
                            break;
                    }
                    else
                    {
                        std::cout << "\033[1D \033[1D";
                        terminal.clearlines(option.size() + 1);
                    }
                }
                std::cout << "\033[1A";
                return res;
            }
            return res;
        }
    } in;
    
    // 输出工具
    class
    {
        private:
        
        // 逐字输出速度
        size_t display_speed = 5000;
        
        public:
        
        // 设置逐字输出速度
        void set_speed(size_t speed)
        { display_speed = speed; }
        
        // 逐字输出
        void print(const std::string s)
        {
            if (!s.size()) return;
            pid_t pid = fork();
            int shmid = shmget(0x1, 4, 0640 | IPC_CREAT);
            int *wait = (int *)shmat(shmid, 0, 0);
            *wait = 1;
            if (pid < 0)
                throw std::runtime_error(std::string(__func__) + ": bad fork");
            else if (pid == 0)
            {
                while (!xesstd::kbhit()) ;
                xesstd::getch();
                *wait = 0;
                kill(getpid(), SIGKILL);
            }
            else
            {
                for (size_t i = 0; i < s.size(); i++)
                {
                    if (*wait)
                        std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? 20000 : 40000));
                    if (s[i] >= 0)
                        std::cout << s[i];
                    else if (s[i] == -62 && s[i + 1] == -73)
                    {
                        std::cout << s[i] << s[i + 1];
                        i++;
                    }
                    else
                    {
                        std::cout << s[i] << s[i + 1] << s[i + 2];
                        i += 2;
                    }
                }
            }
        }
        
        void display(const std::string s)
        {
            for (int i = 0; i < s.size(); i++)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? display_speed : display_speed * 2));
                if (s[i] >= 0)
                    std::cout << s[i];
                else if (s[i] == -62 && s[i + 1] == -73)
                {
                    std::cout << s[i] << s[i + 1];
                    i++;
                }
                else
                {
                    std::cout << s[i] << s[i + 1] << s[i + 2];
                    i += 2;
                }
            }
        }
        void display(const std::string s, size_t speed)
        {
            for (size_t i = 0; i < s.size(); i++)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? speed : speed * 2));
                if (s[i] >= 0)
                    std::cout << s[i];
                else if (s[i] == -62 && s[i + 1] == -73)
                {
                    std::cout << s[i] << s[i + 1];
                    i++;
                }
                else
                {
                    std::cout << s[i] << s[i + 1] << s[i + 2];
                    i += 2;
                }
            }
        }
        
        // 自定义格式逐字输出
        void form(const std::string str, size_t head, size_t tail)
        {
            std::string len;
            int hanz = 0;
            terminal.cursor.right(head);
            for (size_t i = 0; i < str.size(); i++)
            {
                std::cout << str[i];
                len += str[i];
                if (str[i] == '\n')
                    len = "";
                std::this_thread::sleep_for(std::chrono::microseconds(display_speed));
                if (!xesstd::isvisible(str[i]))
                    hanz++;
                else
                    std::this_thread::sleep_for(std::chrono::microseconds(display_speed * 2));
                if (str[i] == -73 && str[i - 1] == -62)
                    hanz++;
                if (hanz % 3 == 0
                    && (xesstd::width(len) == terminal.width - head - tail
                        || (xesstd::width(len) == terminal.width - head - tail - 1 && (!xesstd::isvisible(str[i + 1])) && !(str[i + 1] == -73 && str[i + 2] == -62))))
                {
                    len = "";
                    std::cout << std::endl;
                    terminal.cursor.right(head);
                }
            }
        }
        void form(const std::string str, size_t head, size_t tail, size_t speed)
        {
            std::string len;
            int hanz = 0;
            terminal.cursor.right(head);
            for (size_t i = 0; i < str.size(); i++)
            {
                std::cout << str[i];
                len += str[i];
                if (str[i] == '\n')
                    len = "";
                std::this_thread::sleep_for(std::chrono::microseconds(speed));
                if (!xesstd::isvisible(str[i]))
                    hanz++;
                else
                    std::this_thread::sleep_for(std::chrono::microseconds(speed * 2));
                if (str[i] == -73 && str[i - 1] == -62)
                    hanz++;
                if (hanz % 3 == 0
                    && (xesstd::width(len) == terminal.width - head - tail
                        || (xesstd::width(len) == terminal.width - head - tail - 1 && (!xesstd::isvisible(str[i + 1])) && !(str[i + 1] == -73 && str[i + 2] == -62))))
                {
                    len = "";
                    std::cout << std::endl;
                    terminal.cursor.right(head);
                }
            }
        }
        
        // 文章逐字输出
        void article(const std::string s)
        {
            for (int i = 0; i < s.size(); i++)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? display_speed : display_speed * 2));
                if (s[i] >= 0)
                    std::cout << s[i];
                else if (s[i] == -62 && s[i + 1] == -73)
                {
                    std::cout << s[i] << s[i + 1];
                    i++;
                }
                else
                {
                    std::cout << s[i] << s[i + 1] << s[i + 2];
                    i += 2;
                }
                if (s[i] == '\n')
                    std::cout << "    ";
            }
        }
        void article(const std::string s, size_t speed)
        {
            for (int i = 0; i < s.size(); i++)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? speed : speed * 2));
                if (s[i] >= 0)
                    std::cout << s[i];
                else if (s[i] == -62 && s[i + 1] == -73)
                {
                    std::cout << s[i] << s[i + 1];
                    i++;
                }
                else
                {
                    std::cout << s[i] << s[i + 1] << s[i + 2];
                    i += 2;
                }
                if (s[i] == '\n')
                    std::cout << "    ";
            }
        }
        
        // 换行
        void endline(size_t n)
        {
            for (size_t i = 0; i < n; i++)
                std::cout << std::endl;
        }
        
        // 输出空格
        void whitespace(size_t n)
        {
            for (size_t i = 0; i < n; i++)
                std::cout << " ";
        }
        
        // 输出代码
        class
        {
            private:
            bool line = false;
            bool init = false;
            
            std::string line_number_bg_color;
            std::string bg_color;
            std::string clear_mark;
            std::string keyword_blue_mark;
            std::string keyword_light_blue_mark;
            std::string keyword_green_mark;
            std::string keyword_grey_mark;
            std::string symbol_grey_mark;
            std::string macro_blue_mark;
            std::string macro_red_mark;
            std::string note_green_mark;
            std::string note_blue_mark;
            std::string char_mark;
            std::string escape_char_mark;
            std::string number_blue_mark;
            
            std::string keyword[106] =
            {
                // keyword_blue
                "alignas",
                "alignof",
                "asm",
                "auto",
                "bool",
                "break",
                "case",
                "catch",
                "char",
                "char16_t",
                "char32_t",
                "cin",
                "class",
                "const",
                "constexpr",
                "continue",
                "std::cout",
                "decltype",
                "default",
                "delete",
                "do",
                "double",
                "else",
                "endl",
                "enum",
                "explicit",
                "export",
                "extern",
                "fixed",
                "float",
                "for",
                "friend",
                "goto",
                "if",
                "include",
                "inline",
                "int",
                "iostream",
                "iterator",
                "length",
                "long",
                "map",
                "mutable",
                "new",
                "noexcept",
                "operator",
                "private",
                "protected",
                "public",
                "queue",
                "register",
                "restrict",
                "return",
                "set",
                "setprecision",
                "short",
                "signed",
                "size",
                "stack",
                "static",
                "struct",
                "switch",
                "template",
                "thread_local",
                "throw",
                "try",
                "typedef",
                "typename",
                "union",
                "unsigned",
                "using",
                "virtual",
                "void",
                "volatile",
                "wchar_t",
                "while",
                "__asm__",
                "_Bool",
                "_Complex",
                "_Imaginary",
                "_Pragma",
                
                // keyword_light_blue
                "false",
                "FALSE",
                "NULL",
                "nullptr",
                "true",
                "TRUE",
                
                // keyword_green
                "this",
                
                // keyword_grey
                "and",
                "and_eq",
                "bitand",
                "bitor",
                "compl",
                "const_cast",
                "dynamic_cast",
                "namespace",
                "not",
                "not_eq",
                "or",
                "or_eq",
                "reinterpret_cast",
                "sizeof",
                "static_cast",
                "typeid",
                "xor",
                "xor_eq",
            };
            
            std::string give_keyword_mark(int i)
            {
                if (i <= 81 - 1)
                    return keyword_blue_mark;
                else if (i <= 81 + 6 - 1)
                    return keyword_light_blue_mark;
                else if (i <= 81 + 6 + 1 - 1)
                    return keyword_green_mark;
                else
                    return keyword_grey_mark;
                return clear_mark;
            }
            
            char symbol[13] =
            {
                '~',
                '!',
                '%',
                '^',
                '&',
                '*',
                '-',
                '+',
                '=',
                '|',
                '<',
                '>',
                '/',
            };
            
            /*
            std::string macro_grey[] =
            {
                "nan",
            };
            */
            
            std::string macro_blue[10] =
            {
                "#define",
                "#undef",
                "#ifdef",
                "#ifndef",
                "#if",
                "#elif",
                "#endif",
                "#include",
                "#include_next"
                "#pragma",
            };
            
            std::string macro_red[5] =
            {
                "#include",
                "#include_next"
                "#define",
                "#undef",
                "#pragma",
            };
            
            bool is_indenpendent_word(std::string str, int begin, int len)
            {
                int a = 0;
                if (begin > clear_mark.size() && str[begin - 1] == 'm')
                    if (str.substr(begin - clear_mark.size(), clear_mark.size()) == clear_mark)
                        a = clear_mark.size();
                bool b1 = (str[begin - 1 - a] != '$');
                bool b2 = (!isdigit(str[begin + len]));
                bool b3 = (!(isalpha(str[begin - 1 - a]) || isalpha(str[begin + len])));
                bool b4 = (!(str[begin - 1 - a] == '_' || str[begin + len] == '_'));
                return b1 && b2 && b3 && b4;
            }
            
            int distinguish_num(std::string str, int begin)
            {
                bool sn = 1;
                int a = begin;
                if (begin != 0)
                {
                    if (str[begin] != '+' && str[begin] != '-' && (isalpha(str[begin - 1]) || str[begin - 1] == '_' || str[begin - 1] == '$'))
                    {
                        while ((isdigit(str[begin]) || isalpha(str[begin]) || str[begin] == '_') && begin != str.size() - 1)
                            begin++;
                        return -1 * begin;
                    }
                }
                scientific_notation:
                int dot = 0, loc = begin;
                if (str[begin] == '+' || str[begin] == '-')
                    begin++;
                int end;
                int num = 0;
                if (str[begin] == '.')
                    return -1 * begin;
                while ((str[begin] == '.' || isdigit(str[begin])) && begin != str.size() - 1)
                {
                    if (str[begin] == '.')
                    {
                        dot++;
                        loc = begin;
                    }
                    else
                        num++;
                    if (dot > 1)
                        return -1 * begin;
                    begin++;
                }
                if (num == 0 && (str[a] == '+' || str[a] == '-'))
                    return -1 * (a + 1);
                if (sn)
                {
                    if ((str[begin] == 'e' || str[begin] == 'E') && (str[begin + 1] == '+' || str[begin + 1] == '-' || isdigit(str[begin + 1])))
                    {
                        sn = 0;
                        begin++;
                        goto scientific_notation;
                    }
                }
                std::string ss = "uUfFlL";
                if (begin != str.size() - 1)
                {
                    if (ss.find(str[begin]) != -1 && str[begin + 1] != '_' && !isalpha(str[begin + 1]) && !isdigit(str[begin + 1]))
                        return begin + 1;
                }
                if ((str[begin] == 'x' || str[begin] == 'X') && str[begin - 1] == '0')
                    return -1 * (begin - 1);
                else if (isalpha(str[begin]) || str[begin] == '_')
                {
                    if (loc == a)
                        return -1 * begin;
                    else
                        return loc;
                }
                else
                    return begin;
                return 0;
            }
            
            int distinguish_hex(std::string str, int begin)
            {
                bool flag = 0;
                if (isalpha(str[begin - 1]) || str[begin - 1] == '_' || str[begin - 1] == '$')
                    flag = 1;
                int i = begin + 2;
                std::string ss = "1234567890AaBbCcDdEeFf", ss2 = "uUfFlL";
                while (ss.find(str[i]) != -1 && i != str.size() - 1)
                    i++;
                if (flag)
                    return -1 * i;
                if (ss2.find(str[i]) != -1)
                    i++;
                if (isalpha(str[i]) || str[i] == '_' || isdigit(str[i]))
                    return -1 * i;
                else
                    return i;
                return 0;
            }
            
            bool is_backslash(std::string str, int pos)
            {
                int sum = 0;
                while (str[pos] == '\\')
                {
                    pos--;
                    sum++;
                }
                return (sum % 2 == 1);
            }
            
            bool is_backslash_and_next_line(std::string str, int pos)
            {
                pos--;
                while (str[pos] == ' ')
                    pos--;
                return str[pos] == '\\';
            }
            
            std::string marker(std::string code)
            {
                bool str = 0, note = 0, ch = 0, macro_ = 0;
                for (int i = 0; i <= code.size() - 1; i++)
                {
                    if (code.substr(i, 2) == "//")
                    {
                        code = code.insert(i, note_green_mark);
                        i += note_green_mark.size() + 2;
                        while (code[i] != '\n' && i != code.size() - 1)
                            i++;
                        code = code.insert(i, clear_mark);
                        i += clear_mark.size() - 1;
                    }
                    else if (code.substr(i, 3) == "/**")
                    {
                        code = code.insert(i, note_blue_mark);
                        i += note_blue_mark.size() + 2;
                        while (code.substr(i, 2) != "*/" && i != code.size() - 1)
                            i++;
                        i += 2;
                        code = code.insert(i, clear_mark);
                        i += clear_mark.size() - 1;
                    }
                    else if (code.substr(i, 2) == "/*")
                    {
                        code = code.insert(i, note_green_mark);
                        i += note_green_mark.size() + 2;
                        while (code.substr(i, 2) != "*/" && i != code.size() - 1)
                            i++;
                        i += 2;
                        code = code.insert(i, clear_mark);
                        i += clear_mark.size() - 1;
                    }
                    else if (code[i] == '\'')
                    {
                        int j = i + 1, k = 0;
                        while (!((code[j] == '\'' && code[j - 1] != '\\') || (code[j] == '\'' && code[j - 1] == '\\' && code[j + 1] != '\'')))
                        {
                            if (i == code.size() - 1)
                                break;
                            j++;
                            if (code[j] == '\\')
                                k++;
                        }
                        if (j - i <= 2 || (j - i == 3 && code[i + 1] == '\\'))
                        {
                            code = code.insert(i, char_mark);
                            i = j + char_mark.size() + 1;
                            code = code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                        }
                        else
                        {
                            if (k == 0)
                                i = j;
                            else
                                i = j - 1;
                        }
                    }
                    else if (code[i] == '\"')
                    {
                        code.insert(i, char_mark);
                        i += char_mark.size() + 1;
                        if (code[i] == '\n')
                            i++;
                        while (!((code[i] == '\"' && !is_backslash(code, i - 1)) || (code[i] == '\n' && !is_backslash_and_next_line(code, i))))
                        {
                            if (i == code.size() - 1)
                                break;
                            if (code[i] == '\\' && code[i + 1] != ' ' && code[i + 1] != '\n')
                            {
                                code.insert(i, escape_char_mark);
                                i += escape_char_mark.size() + 2;
                                if (code[i] >= '0' && code[i] <= '7')
                                    i++;
                                if (code[i] >= '0' && code[i] <= '7')
                                    i++;
                                code.insert(i, char_mark);
                                i += char_mark.size() - 1;
                            }
                            i++;
                        }
                        i++;
                        code.insert(i, clear_mark);
                        i += clear_mark.size() - 1;
                    }
                    else if (code[i] == '0' && (code[i + 1] == 'x' || code[i + 1] == 'X'))
                    {
                        int res = distinguish_hex(code, i);
                        if (res > 0)
                        {
                            code.insert(i, number_blue_mark);
                            i = res + number_blue_mark.size();
                            code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                        }
                        else
                            i = (-1 * res) - 1;
                    }
                    else if (isdigit(code[i]) || code[i] == '+' || code[i] == '-')
                    {
                        int res = distinguish_num(code, i);
                        if (res > 0)
                        {
                            code.insert(i, number_blue_mark);
                            i = res + number_blue_mark.size();
                            code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                        }
                        else
                            i = (-1 * res) - 1;
                    }
                    for (int j = 0; j <= arrlen(keyword) - 1; j++)
                    {
                        if (code.substr(i, keyword[j].size()) == keyword[j] && is_indenpendent_word(code, i, keyword[j].size()))
                        {
                            std::string mark = give_keyword_mark(j);
                            code = code.insert(i, mark);
                            i += mark.size() + keyword[j].size();
                            code = code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                            break;
                        }
                    }
                    for (int j = 0; j <= arrlen(symbol) - 1; j++)
                    {
                        if (code[i] == symbol[j])
                        {
                            code = code.insert(i, symbol_grey_mark);
                            i += symbol_grey_mark.size() + 1;
                            code = code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                            break;
                        }
                    }
                    for (int j = 0; j <= arrlen(macro_blue) - 1; j++)
                    {
                        if (code.substr(i, macro_blue[j].size()) == macro_blue[j] && is_indenpendent_word(code, i, macro_blue[j].size()))
                        {
                            code = code.insert(i, macro_blue_mark);
                            i += macro_blue_mark.size() + macro_blue[j].size();
                            code = code.insert(i, clear_mark);
                            i += clear_mark.size() - 1;
                            for (int k = 0; k <= arrlen(macro_red) - 1; k++)
                            {
                                if (macro_blue[j] == macro_red[k])
                                {
                                    i++;
                                    code = code.insert(i, macro_red_mark);
                                    i += macro_red_mark.size();
                                    if (macro_blue[j] == "#include")
                                    {
                                        while (((code[i] == '\\' && code[i + 1] == '\n') || (code[i] == ' ' && code[i + 1] != '\n') || (code[i] == '\n' && (code[i - 1] == '\\' || code[i - 1] == '\n'))) && i != code.size() - 1)
                                            i++;
                                        int left_sign = 0;
                                        bool first_left_sign = 0, flag = 0;
                                        if (code[i] == '<')
                                            first_left_sign = 1;
                                        while (code[i] != '\n' && i != code.size() - 1)
                                        {
                                            if (code[i] == '<')
                                                left_sign++;
                                            else if (code[i] == '>' && left_sign == 1 && first_left_sign && code[i - 1] != '<')
                                            {
                                                i++;
                                                flag = 1;
                                                break;
                                            }
                                            i++;
                                        }
                                        if (flag == 0)
                                        {
                                            while (!(code[i] == '\n' && code[i - 1] != '\\' && code[i - 1] != '\n'))
                                                i++;
                                        }
                                        code = code.insert(i, clear_mark);
                                        i += clear_mark.size() - 1;
                                    }
                                    else
                                    {
                                        if (code[i] == '\n')
                                            i++;
                                        while (!(code[i] == '\n' && (code[i - 1] != '\\' && code[i - 1] != '\n')) && i != code.size() - 1)
                                            i++;
                                        code = code.insert(i, clear_mark);
                                        i += clear_mark.size() - 1;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                return code;
            }
            
            void _printer(std::string s, size_t t)
            {
                for (size_t i = 0; i < s.size(); i++)
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(s[i] > 0 ? t : t * 2));
                    if (s[i] >= 0)
                        std::cout << s[i];
                    else if (s[i] == -62 && s[i + 1] == -73)
                    {
                        std::cout << s[i] << s[i + 1];
                        i++;
                    }
                    else
                    {
                        std::cout << s[i] << s[i + 1] << s[i + 2];
                        i += 2;
                    }
                }
            }
            
            void printer(std::string code)
            {
                if (!init)
                {
                    setstyle(0);
                    init = true;
                }
                code = marker(code);
                std::cout << bg_color << clear_mark;
                int sum = 0, a = 0, num = 1;
                if (line)
                {
                    for (auto &&i : code)
                        if (i == '\n')
                            sum++;
                    for (; sum >= std::pow(10, a); a++) {}
                    std::cout << line_number_bg_color << std::setw(a) << num << " " << bg_color;
                    num++;
                }
                std::string c = "";
                for (int i = 0; i < code.size(); i++)
                {
                    std::cout << code[i];
                    std::this_thread::sleep_for(std::chrono::microseconds(128));
                    if (line)
                    {
                        if (code.substr(i, note_green_mark.size()) == note_green_mark)
                            c = note_green_mark;
                        else if (code.substr(i, note_blue_mark.size()) == note_blue_mark)
                            c = note_blue_mark;
                        else if (code.substr(i, macro_red_mark.size()) == macro_red_mark)
                            c = macro_red_mark;
                        else if (code.substr(i, char_mark.size()) == char_mark)
                            c = char_mark;
                        else if (c.size() != 0 && code.substr(i, clear_mark.size()) == clear_mark)
                            c = "";
                        if (code[i] == '\n')
                        {
                            std::string s, s1;
                            int b = 0;
                            for (; num >= std::pow(10, b); b++) {}
                            for (int n = 0; n < a - b; n++)
                                s1 += ' ';
                            s = clear_mark + line_number_bg_color + s1 + std::to_string(num) + " " + bg_color;
                            _printer(s, 128);
                            if (c.size() != 0)
                                _printer(c, 128);
                            num++;
                        }
                    }
                }
                std::cout << "\033[0m";
            }
            
            public:
            void operator ()(const std::string &code)
            { printer(code); }
            
            void operator ()(std::vector<std::string> code)
            {
                std::string s;
                for (int i = 0; i < code.size() - 1; i++)
                    s += code[i] + "\n";
                s += code[code.size() - 1];
                printer(s);
            }
            
            // 设置颜色风格
            void setstyle(int a)
            {
                switch (a)
                {
                    case 0:
                    line_number_bg_color    = "\033[48;2;247;242;231m";
                    bg_color                = "\033[48;2;250;250;250m";
                    clear_mark              = "\033[38;2;0;0;0m";
                    keyword_blue_mark       = "\033[38;2;0;0;255m";
                    keyword_light_blue_mark = "\033[38;2;88;92;246m";
                    keyword_green_mark      = "\033[38;2;49;132;149m";
                    keyword_grey_mark       = "\033[38;2;104;118;135m";
                    symbol_grey_mark        = "\033[38;2;104;118;135m";
                    macro_blue_mark         = "\033[38;2;0;0;255m";
                    macro_red_mark          = "\033[38;2;197;6;11m";
                    note_green_mark         = "\033[38;2;76;136;107m";
                    note_blue_mark          = "\033[38;2;0;102;255m";
                    char_mark               = "\033[38;2;3;106;7m";
                    escape_char_mark        = "\033[38;2;88;92;246m";
                    number_blue_mark        = "\033[38;2;0;0;255m";
                    break;
                    
                    case 1:
                    line_number_bg_color    = "\033[48;2;60;60;60m";
                    bg_color                = "\033[48;2;40;40;40m";
                    clear_mark              = "\033[38;2;255;255;255m";
                    keyword_blue_mark       = "\033[38;2;0;120;255m";
                    keyword_light_blue_mark = "\033[38;2;88;200;246m";
                    keyword_green_mark      = "\033[38;2;49;132;149m";
                    keyword_grey_mark       = "\033[38;2;120;130;150m";
                    symbol_grey_mark        = "\033[38;2;120;130;150m";
                    macro_blue_mark         = "\033[38;2;0;120;255m";
                    macro_red_mark          = "\033[38;2;197;50;11m";
                    note_green_mark         = "\033[38;2;76;150;0m";
                    note_blue_mark          = "\033[38;2;100;150;255m";
                    char_mark               = "\033[38;2;3;120;7m";
                    escape_char_mark        = "\033[38;2;80;150;255m";
                    number_blue_mark        = "\033[38;2;0;120;255m";
                    break;
                    
                    default:
                    break;
                }
            }
            
            //是否显示行号
            void line_number(bool b/*是或否*/)
            {
                line = b;
            }
        } printcode;
    } out;
    
    // 绘制工具
    class
    {
        public:
        
        // 输出图案
        void image(const std::string &str, size_t speed = 0, bool bright = false, bool do_line_feed = true)
        {
            for (int i = 0; i < str.size(); i++)
            {
                if (str[i] == ' ')
                {
                    if (str[i - 1] != ' ')
                        std::cout << "\033[0m";
                    std::cout << " ";
                }
                else if (str[i] >= '0' && str[i] <= '7')
                {
                    if (str[i - 1] != str[i])
                    {
                        if (bright)
                            std::cout << "\033[10";
                        else
                            std::cout << "\033[4";
                        std::cout << str[i] - '0' << "m";
                    }
                    std::cout << " ";
                    if (speed)
                        std::this_thread::sleep_for(std::chrono::microseconds(speed));
                }
                else
                    std::cout << str[i];
            }
            std::cout << "\033[0m";
            if (do_line_feed)
                std::cout << std::endl;
        }
        
        // 彩虹输出
        void colorful(const std::string &str, size_t frequency, size_t last)
        {
            std::pair<size_t, size_t> a = area(str);
            for (size_t i = 0; i * frequency <= last; i++)
            {
                std::cout << "\033[" << 29 + i % 9 << "m" << str;
                std::this_thread::sleep_for(std::chrono::microseconds(frequency));
                terminal.erase(a.first, a.second);
                if (a.second == 1)
                    std::cout << "\033[" << a.first << "D";
                else
                    std::cout << "\033[" << a.second - 1 << "A\033[" << a.first << "D";
                std::cout << "\033[" << 89 + i % 9 << "m" << str;
                std::this_thread::sleep_for(std::chrono::microseconds(frequency));
                terminal.erase(a.first, a.second);
                if (a.second == 1)
                    std::cout << "\033[" << a.first << "D";
                else
                    std::cout << "\033[" << a.second - 1 << "A\033[" << a.first << "D";
            }
        }
    } paint;
}

#endif