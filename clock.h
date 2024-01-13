// <clock.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_CLOCK_H
#define _LIBSEREVIA_CLOCK_H 1

/** @file clock.h
 *  This is a Serevia Library header.
 *  Copyright (c) 2022 - 2024 CheatMay
 */

#include "libserevia_config.h"
#include <iomanip>
#include <sys/time.h>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    class
    {
        /*
        struct tm
        int tm_sec;   // 秒，正常范围从0到59，但允许至61
        int tm_min;   // 分，范围从0到59
        int tm_hour;  // 小时，范围从0到23
        int tm_mday;  // 一月中的第几天，范围从1到31
        int tm_mon;   // 月，范围从0到11
        int tm_year;  // 自 1900 年起的年数
        int tm_wday;  // 一周中的第几天，范围从0到6，从星期日算起
        int tm_yday;  // 一年中的第几天，范围从0到365，从1月1日算起
        int tm_isdst; // 夏令时
        
        strftime() getstrtime()
        %a 星期几的简写
        %A 星期几的全称
        %b 月分的简写
        %B 月份的全称
        %c 标准的日期的时间串
        %C 年份的后两位数字
        %d 十进制表示的每月的第几天
        %D 月/天/年
        %e 在两字符域中，十进制表示的每月的第几天
        %F 年-月-日
        %g 年份的后两位数字，使用基于周的年
        %G 年分，使用基于周的年
        %h 简写的月份名
        %H 24小时制的小时
        %I 12小时制的小时
        %j 十进制表示的每年的第几天
        %m 十进制表示的月份
        %M 十时制表示的分钟数
        %n 新行符
        %p 本地的AM或PM的等价显示
        %r 12小时的时间
        %R 显示小时和分钟：hh:mm
        %S 十进制的秒数
        %t 水平制表符
        %T 显示时分秒：hh:mm:ss
        %u 每周的第几天，星期一为第一天 （值从0到6，星期一为0）
        %U 第年的第几周，把星期日做为第一天（值从0到53）
        %V 每年的第几周，使用基于周的年
        %w 十进制表示的星期几（值从0到6，星期天为0）
        %W 每年的第几周，把星期一做为第一天（值从0到53）
        %x 标准的日期串
        %X 标准的时间串
        %y 不带世纪的十进制年份（值从0到99）
        %Y 带世纪部分的十制年份
        %z
        %Z 时区名称，如果不能得到时区名称则返回空字符。
        %% 百分号
        */
        
        private:
        char *dt;
        
        tm *tm_now;
        struct timeval tv;
        std::string wday, dtm;
        
        int constructor()
        {
            time_t now = time(0);
            tm_now = localtime(&now);
            
            dt = ctime(&now);
            
            // 微秒
            gettimeofday(&tv, NULL);
            
            switch (tm_now->tm_wday)
            {
                case 0:
                wday = "日";
                case 1:
                wday = "一";
                case 2:
                wday = "二";
                case 3:
                wday = "三";
                case 4:
                wday = "四";
                case 5:
                wday = "五";
                case 6:
                wday = "六";
                default:
                break;
            }
            
            if (tm_now->tm_hour <= 12)
                dtm = "上午";
            else
                dtm = "下午";
            
            return 1;
        }
        
        int constructed = constructor();
        
        public:
        void refresh()
        { constructor(); }
        
        const char *gettime()
        {
            refresh();
            return dt;
        }
        
        int getyear()
        {
            refresh();
            return tm_now->tm_year + 1900;
        }
        
        int getmonth()
        {
            refresh();
            return tm_now->tm_mon + 1;
        }
        
        int getmday()
        {
            refresh();
            return tm_now->tm_mday + 1;
        }
        
        std::string getwday()
        {
            refresh();
            return wday;
        }
        
        int getyday()
        {
            refresh();
            return tm_now->tm_yday + 1;
        }
        
        std::string getdtm()
        {
            refresh();
            return dtm;
        }
        
        int gethour()
        {
            refresh();
            return tm_now->tm_hour;
        }
        
        int getmin()
        {
            refresh();
            return tm_now->tm_min;
        }
        
        int getsec()
        {
            refresh();
            return tm_now->tm_sec;
        }
        
        int getmsec()
        {
            refresh();
            return *(&tv.tv_usec) / 1000;
        }
        
        int getusec()
        {
            refresh();
            return *(&tv.tv_usec) % 1000;
        }
        
        std::string getstrtime(const std::string format)
        {
            refresh();
            char *t;
            strftime(t, format.size() * 10, format.data(), tm_now);
            return t;
        }
        
        void printdate(bool year = true)
        {
            if (year)
                std::cout << getyear() << "年";
            std::cout << getmonth() << "月" << getmday() << "日";
        }
        void printdate(bool year, char a)
        {
            if (year)
                std::cout << getyear() << a;
            std::cout << getmonth() << a << getmday();
        }
        
        void printtime()
        {
            std::cout << std::setw(2) << std::setfill('0') << gethour() << ":" << std::setw(2) << std::setfill('0') << getmin() << ":" << std::setw(2) << std::setfill('0') << getsec();
        }
        void printtime(bool sec, bool form = true/*是否采用24小时制（否则采用12小时制）*/, unsigned short a = 0/*分隔符（0="%h:%m:%s", 1="%h时%m分%s秒"）*/)
        {
            int h = gethour();
            if (!form && h > 12)
                h -= 12;
            std::cout << std::setw(2) << std::setfill('0') << h;
            if (a == 1)
                std::cout << "时" << std::setw(2) << std::setfill('0') << getmin() << "分";
            else
                std::cout << ":" << std::setw(2) << std::setfill('0') << getmin();
            if (sec)
            {
                if (a == 1)
                    std::cout << std::setw(2) << std::setfill('0') << getsec() << "秒";
                else
                    std::cout << ":" << std::setw(2) << std::setfill('0') << getsec();
            }
        }
        
        // 计时器
        class
        {
            private:
            struct timeval _tv;
            unsigned long long res = 0;
            unsigned long long start_time = 0, last_pause_time = 0, pausing_time = 0;
            bool is_start = 0, is_paused = 0;
            
            public:
            
            // 开始
            bool start()
            {
                if (is_start)
                    return 0;
                is_start = 1;
                gettimeofday(&_tv, NULL);
                start_time = time(0) + _tv.tv_usec;
                return 1;
            }
            // 暂停
            bool pause()
            {
                if (!is_start || is_paused)
                    return 0;
                is_paused = 1;
                gettimeofday(&_tv, NULL);
                last_pause_time = time(0) + _tv.tv_usec;
                return 1;
            }
            // 继续
            bool resume()
            {
                if (!is_paused)
                    return 0;
                is_paused = 0;
                gettimeofday(&_tv, NULL);
                pausing_time = time(0) + _tv.tv_usec - last_pause_time;
                return 1;
            }
            // 停止
            bool stop()
            {
                if (!is_start)
                    return 0;
                is_start = 0, is_paused = 0;
                gettimeofday(&_tv, NULL);
                res = time(0) + _tv.tv_usec - pausing_time - start_time;
                pausing_time = 0, start_time = 0;
                return 1;
            }
            // 获取计时结果
            unsigned long long duration()
            {
                if (is_start)
                {
                    gettimeofday(&_tv, NULL);
                    return time(0) + _tv.tv_usec - pausing_time - start_time;
                }
                return res;
            }
        } timer;
    } clock;
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#endif