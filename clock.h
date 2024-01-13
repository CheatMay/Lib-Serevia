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
        int tm_sec;   // �룬������Χ��0��59����������61
        int tm_min;   // �֣���Χ��0��59
        int tm_hour;  // Сʱ����Χ��0��23
        int tm_mday;  // һ���еĵڼ��죬��Χ��1��31
        int tm_mon;   // �£���Χ��0��11
        int tm_year;  // �� 1900 ���������
        int tm_wday;  // һ���еĵڼ��죬��Χ��0��6��������������
        int tm_yday;  // һ���еĵڼ��죬��Χ��0��365����1��1������
        int tm_isdst; // ����ʱ
        
        strftime() getstrtime()
        %a ���ڼ��ļ�д
        %A ���ڼ���ȫ��
        %b �·ֵļ�д
        %B �·ݵ�ȫ��
        %c ��׼�����ڵ�ʱ�䴮
        %C ��ݵĺ���λ����
        %d ʮ���Ʊ�ʾ��ÿ�µĵڼ���
        %D ��/��/��
        %e �����ַ����У�ʮ���Ʊ�ʾ��ÿ�µĵڼ���
        %F ��-��-��
        %g ��ݵĺ���λ���֣�ʹ�û����ܵ���
        %G ��֣�ʹ�û����ܵ���
        %h ��д���·���
        %H 24Сʱ�Ƶ�Сʱ
        %I 12Сʱ�Ƶ�Сʱ
        %j ʮ���Ʊ�ʾ��ÿ��ĵڼ���
        %m ʮ���Ʊ�ʾ���·�
        %M ʮʱ�Ʊ�ʾ�ķ�����
        %n ���з�
        %p ���ص�AM��PM�ĵȼ���ʾ
        %r 12Сʱ��ʱ��
        %R ��ʾСʱ�ͷ��ӣ�hh:mm
        %S ʮ���Ƶ�����
        %t ˮƽ�Ʊ��
        %T ��ʾʱ���룺hh:mm:ss
        %u ÿ�ܵĵڼ��죬����һΪ��һ�� ��ֵ��0��6������һΪ0��
        %U ����ĵڼ��ܣ�����������Ϊ��һ�죨ֵ��0��53��
        %V ÿ��ĵڼ��ܣ�ʹ�û����ܵ���
        %w ʮ���Ʊ�ʾ�����ڼ���ֵ��0��6��������Ϊ0��
        %W ÿ��ĵڼ��ܣ�������һ��Ϊ��һ�죨ֵ��0��53��
        %x ��׼�����ڴ�
        %X ��׼��ʱ�䴮
        %y �������͵�ʮ������ݣ�ֵ��0��99��
        %Y �����Ͳ��ֵ�ʮ�����
        %z
        %Z ʱ�����ƣ�������ܵõ�ʱ�������򷵻ؿ��ַ���
        %% �ٷֺ�
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
            
            // ΢��
            gettimeofday(&tv, NULL);
            
            switch (tm_now->tm_wday)
            {
                case 0:
                wday = "��";
                case 1:
                wday = "һ";
                case 2:
                wday = "��";
                case 3:
                wday = "��";
                case 4:
                wday = "��";
                case 5:
                wday = "��";
                case 6:
                wday = "��";
                default:
                break;
            }
            
            if (tm_now->tm_hour <= 12)
                dtm = "����";
            else
                dtm = "����";
            
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
                std::cout << getyear() << "��";
            std::cout << getmonth() << "��" << getmday() << "��";
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
        void printtime(bool sec, bool form = true/*�Ƿ����24Сʱ�ƣ��������12Сʱ�ƣ�*/, unsigned short a = 0/*�ָ�����0="%h:%m:%s", 1="%hʱ%m��%s��"��*/)
        {
            int h = gethour();
            if (!form && h > 12)
                h -= 12;
            std::cout << std::setw(2) << std::setfill('0') << h;
            if (a == 1)
                std::cout << "ʱ" << std::setw(2) << std::setfill('0') << getmin() << "��";
            else
                std::cout << ":" << std::setw(2) << std::setfill('0') << getmin();
            if (sec)
            {
                if (a == 1)
                    std::cout << std::setw(2) << std::setfill('0') << getsec() << "��";
                else
                    std::cout << ":" << std::setw(2) << std::setfill('0') << getsec();
            }
        }
        
        // ��ʱ��
        class
        {
            private:
            struct timeval _tv;
            unsigned long long res = 0;
            unsigned long long start_time = 0, last_pause_time = 0, pausing_time = 0;
            bool is_start = 0, is_paused = 0;
            
            public:
            
            // ��ʼ
            bool start()
            {
                if (is_start)
                    return 0;
                is_start = 1;
                gettimeofday(&_tv, NULL);
                start_time = time(0) + _tv.tv_usec;
                return 1;
            }
            // ��ͣ
            bool pause()
            {
                if (!is_start || is_paused)
                    return 0;
                is_paused = 1;
                gettimeofday(&_tv, NULL);
                last_pause_time = time(0) + _tv.tv_usec;
                return 1;
            }
            // ����
            bool resume()
            {
                if (!is_paused)
                    return 0;
                is_paused = 0;
                gettimeofday(&_tv, NULL);
                pausing_time = time(0) + _tv.tv_usec - last_pause_time;
                return 1;
            }
            // ֹͣ
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
            // ��ȡ��ʱ���
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