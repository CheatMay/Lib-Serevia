// <formatfwd.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_FORMATFWD_H
#define _LIBSEREVIA_FORMATFWD_H 1

// This header is an internal header included by other library
// headers. Never include this file directly.
#ifndef _LIBSEREVIA_FORMAT_LOCALE_H
#error do not include this file directly
#endif

#include <bits/ios_base.h>
#include <bits/localefwd.h>
#include <ext/stdio_sync_filebuf.h>

namespace serevia _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    const std::locale _XESSTD_FORMAT_LOCALE =
    std::locale() == std::locale("C.UTF-8")
    ? std::locale() : std::locale::global(std::locale("C.UTF-8"));
    
#ifdef _XESSTD_FORMATSTREAM_DEPRECATE_STDIO
    const bool _XESSTD_FORMAT_SYNC =
    std::ios_base::sync_with_stdio()
    ? std::ios_base::sync_with_stdio(false) == std::ios_base::sync_with_stdio() : 0;
#else
    const bool _XESSTD_FORMAT_SYNC = true;
#endif
    
    __gnu_cxx::stdio_sync_filebuf<char> buf_cin_sync(stdin);
    __gnu_cxx::stdio_sync_filebuf<char> buf_cout_sync(stdout);
#ifdef _GLIBCXX_USE_WCHAR_T
    __gnu_cxx::stdio_sync_filebuf<wchar_t> buf_wcin_sync(stdin);
    __gnu_cxx::stdio_sync_filebuf<wchar_t> buf_wcout_sync(stdout);
#endif
    
_GLIBCXX_END_NAMESPACE_VERSION
}

#ifdef _XESSTD_FORMATSTREAM_DEPRECATE_STDIO
__attribute__((deprecated)) extern int fclose(FILE *);
__attribute__((deprecated)) extern void clearerr(FILE *);
__attribute__((deprecated)) extern int feof(FILE *);
__attribute__((deprecated)) extern int ferror(FILE *);
__attribute__((deprecated)) extern int fflush(FILE *);
__attribute__((deprecated)) extern int fgetpos(FILE *, fpos_t *);
__attribute__((deprecated)) extern FILE *fopen(const char *, const char *);
__attribute__((deprecated)) extern size_t fread(void *, size_t, size_t, FILE *);
__attribute__((deprecated)) extern FILE *freopen(const char *, const char *, FILE *);
__attribute__((deprecated)) extern int fseek(FILE *, long, int);
__attribute__((deprecated)) extern int fsetpos(FILE *, const fpos_t *);
__attribute__((deprecated)) extern long int ftell(FILE *);
__attribute__((deprecated)) extern size_t fwrite(const void *, size_t, size_t, FILE *);
__attribute__((deprecated)) extern int remove(const char *);
__attribute__((deprecated)) extern int rename(const char *, const char *);
__attribute__((deprecated)) extern void rewind(FILE *);
__attribute__((deprecated)) extern void setbuf(FILE *, char *);
__attribute__((deprecated)) extern int setvbuf(FILE *, char *, int, size_t);
__attribute__((deprecated)) extern FILE *tmpfile(void);
__attribute__((deprecated)) extern char *tmpnam(char *);
__attribute__((deprecated)) extern int fprintf(FILE *, const char *, ...);
__attribute__((deprecated)) extern int printf(const char *, ...);
__attribute__((deprecated)) extern int sprintf(char *, const char *, ...);
__attribute__((deprecated)) extern int vfprintf(FILE *, const char *, va_list);
__attribute__((deprecated)) extern int vprintf(const char *, va_list);
__attribute__((deprecated)) extern int vsprintf(char *, const char *, va_list);
__attribute__((deprecated)) extern int fscanf(FILE *, const char *, ...);
__attribute__((deprecated)) extern int scanf(const char *, ...);
__attribute__((deprecated)) extern int sscanf(const char *, const char *, ...);
__attribute__((deprecated)) extern int fgetc(FILE *);
__attribute__((deprecated)) extern char *fgets(char *, int, FILE *);
__attribute__((deprecated)) extern int fputc(int, FILE *);
__attribute__((deprecated)) extern int fputs(const char *, FILE *);
__attribute__((deprecated)) extern int getc(FILE *);
__attribute__((deprecated)) extern int getchar(void);
__attribute__((deprecated)) extern char *gets(char *);
__attribute__((deprecated)) extern int putc(int, FILE *);
__attribute__((deprecated)) extern int putchar(int);
__attribute__((deprecated)) extern int puts(const char *);
__attribute__((deprecated)) extern int ungetc(int, FILE *);
__attribute__((deprecated)) extern void perror(const char *);
__attribute__((deprecated)) extern int snprintf(char *, size_t, const char *, ...);
#endif

#endif