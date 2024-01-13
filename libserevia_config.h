// <libserevia_config.h> -*- C++ -*-

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

#ifndef _LIBSEREVIA_CONFIG
#define _LIBSEREVIA_CONFIG 1

#ifdef _GLIBCXX_USE_LONG_LONG
#define _LIBSEREVIA_LONG_LONG long long
#else
#define _LIBSEREVIA_LONG_LONG long
#endif

#define repeat(n) for (int _LIBSEREVIA_REPEAT_INDEX = 0; _LIBSEREVIA_REPEAT_INDEX < n; _LIBSEREVIA_REPEAT_INDEX++)

#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))

#endif