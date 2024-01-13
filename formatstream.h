// <formatstream.h> -*- C++ -*-

// Copyright (C) 2023-2024  CheatMay & FurryR
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

/** @file formatstream.h
 *  This is a Serevia library header.
 *  Copyright (C) 2023 - 2024 CheatMay & FurryR
 */

#ifndef _XESSTD_FORMATSTREAM_H
#define _XESSTD_FORMATSTREAM_H 1

// Give up compatibility with C-style standard I/O or not.
// If not, undef this defination.
#define _XESSTD_FORMATSTREAM_DEPRECATE_STDIO 1

// Use everything based on wchar_t or not.
// If defined, std::locale::global() will be tried to set to
// std::locale("C.UTF-8");
// If not, undef this defination.
#define _XESSTD_FORMATSTREAM_SUGGEST_WCHAR_T 1

#include "format_locale.h"
#include "color.h"
#include <ext/stdio_filebuf.h>
#include <sstream>
#include <iomanip>
#include <thread> // For std::this_thread::sleep_for().

namespace xesstd _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
    
    // The following definition of bitmask type is enum, not int,
    // as permitted (but not required) in the standard, in order to provide
    // better type safety in formatstream calls.
    enum _Fs_Fmtflags
    {
        _F_italic = 1L << 0,
        _F_underline = 1L << 1,
        _F_enableblinking = 1L << 2,
        _F_showcursor = 1L << 3,
        _F_usershape = 1L << 4,
        _F_blinkingblock = 1L << 5,
        _F_steadyblock = 1L << 6,
        _F_blinkingunderline = 1L << 7,
        _F_steadyunderline = 1L << 8,
        _F_blinkingbar = 1L << 9,
        _F_steadybar = 1L << 10,
        _F_cursorshapefield = _F_usershape | _F_blinkingblock | _F_steadyblock
        | _F_blinkingunderline | _F_steadyunderline | _F_blinkingbar | _F_steadybar,
        _F_fs_fmtflags_end = 1L << 16,
        _F_fs_fmtflags_max = __INT_MAX__,
        _F_fs_fmtflags_min = ~__INT_MAX__
    };
    
    inline constexpr _Fs_Fmtflags
    operator &(_Fs_Fmtflags _a, _Fs_Fmtflags _b)
    { return _Fs_Fmtflags(static_cast<int>(_a) & static_cast<int>(_b)); }
    
    inline constexpr _Fs_Fmtflags
    operator |(_Fs_Fmtflags _a, _Fs_Fmtflags _b)
    { return _Fs_Fmtflags(static_cast<int>(_a) | static_cast<int>(_b)); }
    
    inline constexpr _Fs_Fmtflags
    operator ^(_Fs_Fmtflags _a, _Fs_Fmtflags _b)
    { return _Fs_Fmtflags(static_cast<int>(_a) ^ static_cast<int>(_b)); }
    
    inline constexpr _Fs_Fmtflags
    operator ~(_Fs_Fmtflags _a)
    { return _Fs_Fmtflags(~static_cast<int>(_a)); }
    
    inline const _Fs_Fmtflags &
    operator &=(_Fs_Fmtflags &_a, _Fs_Fmtflags _b)
    { return _a = _a & _b; }
    
    inline const _Fs_Fmtflags &
    operator |=(_Fs_Fmtflags &_a, _Fs_Fmtflags _b)
    { return _a = _a | _b; }
    
    inline const _Fs_Fmtflags &
    operator ^=(_Fs_Fmtflags &_a, _Fs_Fmtflags _b)
    { return _a = _a ^ _b; }
    
    class format_base // : public std::ios_base
    {
        public:
        /**
         * @brief Type format_base::ffmtflags
         * 
         * This is a bitmask type.
         * @c @a _Fs_Fmtflags is implementation-defined, but it is valid to
         * perform bitwise operations on these values and expect the Right
         * Thing to happen. Defined objects of type ffmtflags are:
         * - italic
         * - underline
         * - enableblinking
         * - showcursor
         * - usershape
         * - blinkingblock
         * - steadyblock
         * - blinkingunderline
         * - steadyunderline
         * - blinkingbar
         * - steadybar
         * - cursorshapefield
         */
        typedef _Fs_Fmtflags ffmtflags;
        
        // Set italic font.
        static constexpr const ffmtflags italic = _F_italic;
        
        // Set underline.
        static constexpr const ffmtflags underline = _F_underline;
        
        // Enable the cursor to blink.
        static constexpr const ffmtflags enableblinking = _F_enableblinking;
        
        // Show the cursor.
        static constexpr const ffmtflags showcursor = _F_showcursor;
        
        // Set the cursor's shape to user's default shape.
        static constexpr const ffmtflags usershape = _F_usershape;
        
        // Set the cursor's shape to blinking block.
        static constexpr const ffmtflags blinkingblock = _F_blinkingblock;
        
        // Set the cursor's shape to steady block.
        static constexpr const ffmtflags steadyblock = _F_steadyblock;
        
        // Set the cursor's shape to blinking underline.
        static constexpr const ffmtflags blinkingunderline = _F_blinkingunderline;
        
        // Set the cursor's shape to steady underline.
        static constexpr const ffmtflags steadyunderline = _F_steadyunderline;
        
        // Set the cursor's shape to blinking bar.
        static constexpr const ffmtflags blinkingbar = _F_blinkingbar;
        
        // Set the cursor's shape to steady bar.
        static constexpr const ffmtflags steadybar = _F_steadybar;
        
        // A mask of the shape of the cursor. Useful for the 2-arg form of @c setff.
        static constexpr const ffmtflags cursorshapefield = _F_cursorshapefield;
        
        /**
         * @brief Base constructor.
         * 
         * This is the only ctor, which initializes the base.
         */
        format_base():
        _autoflush(true),
        _font_color(white), _bg_color(black),
        _do_refresh_font_color(false), _do_refresh_bg_color(false),
        _ff(showcursor | enableblinking | usershape)
        { }
        
        // fmtflags state functions
        /**
         * @brief Access to format flags.
         * @return The format control flags for both input and output.
         */
        ffmtflags fflags() const
        { return _ff; }
        
        /**
         * @brief Setting new format flags all at once.
         * @param _new The new flags to set.
         * @return The previous format control flags.
         * 
         * This function overwrites all the format flags with @a _new.
         */
        ffmtflags fflags(ffmtflags _new)
        {
            ffmtflags _old = _ff;
            _ff = _new;
            return _old;
        }
        
        /**
         * @brief Setting new format flags.
         * @param __ff Additional flags to set.
         * @return The previous format control flags.
         * 
         * This function sets additional flags in format control. Flags that
         * were previously set remain set.
         */
        ffmtflags setff(ffmtflags __ff)
        {
            ffmtflags _old = _ff;
            _ff |= __ff;
            return _old;
        }
        
        /**
         * @brief Setting new format flags.
         * @param __ff Additional flags to set.
         * @param _mask The flags mask for @a __ff.
         * @return The previous format control flags.
         * 
         * This function clears @a mask in the format flags, then sets
         * @a ff @c & @a mask.
         */
        ffmtflags setff(ffmtflags __ff, ffmtflags _mask)
        {
            ffmtflags _old = _ff;
            _ff &= ~_mask;
            _ff |= (__ff & _mask);
            return _old;
        }
        
        /**
         * @brief Clearing format flags.
         * @param _mask The flags to unset.
         * 
         * This function clears @a _mask in the format flags.
         */
        void unsetff(ffmtflags _mask)
        { _ff &= ~_mask; }
        
        /**
         * 
         */
        bool autoflush() const
        { return _autoflush; }
        
        /**
         * 
         */
        bool autoflush(bool __autoflush)
        {
            bool _old = _autoflush;
            _autoflush = __autoflush;
            return _old;
        }
        
        /**
         * 
         */
        color fontcolor() const
        { return _font_color; }
        
        /**
         * 
         */
        color fontcolor(color _new)
        {
            color _old = _font_color;
            _font_color = _new;
            _do_refresh_font_color = true;
            return _old;
        }
        
        /**
         * 
         */
        color bgcolor() const
        { return _bg_color; }
        
        /**
         * 
         */
        color bgcolor(color _new)
        {
            color _old = _bg_color;
            _bg_color = _new;
            _do_refresh_bg_color = true;
            return _old;
        }
        
        protected:
        // Data members
        bool _autoflush;
        color _font_color;
        color _bg_color;
        ffmtflags _ff;
        bool _do_refresh_font_color;
        bool _do_refresh_bg_color;
    };
    
    template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
    class basic_format : public format_base, std::basic_ios<_CharT, _Traits>
    {
        public:
        using char_type         = _CharT;
        using string_type       = std::basic_string         <_CharT, _Traits>;
        using streambuf_type    = std::basic_streambuf      <_CharT, _Traits>;
        using ios_type          = std::basic_ios            <_CharT, _Traits>;
        using stringstream_type = std::basic_stringstream   <_CharT, _Traits>;
        
        template<typename _CharT2, typename _Traits2>
        friend class basic_formatstream;
        
        /**
         * @brief Base constructor.
         * 
         * This is the only ctor, which initializes the streambuf.
         */
        basic_format(streambuf_type *_streambuf)
        { this->init(_streambuf); }
        
        protected:
        /**
         * @brief Widens character.
         * @param _c The character to widen
         * @return The widened character
         */
        char_type widen(char _c) const
        { return this->ios_type::widen(_c); }
        
        /**
         * @brief Widens character string.
         * @param _s The character string to widen
         * @return The widened character string
         */
        string_type widen(std::string _s) const
        {
            string_type _ret;
            for (auto &&_i : _s)
                _ret += this->widen(_i);
            return _ret;
        }
        
        /**
         * @brief Narrows character.
         * @param _c The character to narrow
         * @return The narrowed character
         */
        char narrow(char_type _c) const
        { return this->ios_type::narrow(_c, '?'); }
        
        /**
         * @brief Narrows character string.
         * @param _c The character string to narrow
         * @return The narrowed character string
         */
        std::string narrow(string_type _s) const
        {
            std::string _ret;
            for (auto &&_i : _s)
                _ret += narrow(_i);
            return _ret;
        }
        
        // Data members
        stringstream_type _base_ss;
    };
    
    struct _At
    { size_t _M_x, _M_y; };
    
    struct _Athonrizontal
    { size_t _M_x; };
    
    struct _Atvertical
    { size_t _M_x; };
    
    /**
     * @brief Template class basic_formatstream.
     * @addtogroup io
     * 
     * @tparam _CharT Type of character stream.
     * @tparam _Traits Traits for character type,
     *                 defaults to char_traits<_CharT>.
     * 
     * This is a further formatted output stream,
     * (fake) derived class of basic_stringstream,
     * adds several manipulators and limits user's
     * permission to access base class manipulators.
     */
    template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
    class basic_formatstream : public basic_format<_CharT, _Traits>
    {
        public:
        
        // Standard types
        using char_type         = _CharT;
        using traits_type       = _Traits;
        using int_type          = typename traits_type::int_type;
        using pos_type          = typename traits_type::pos_type;
        using off_type          = typename traits_type::off_type;
        
        // Non-standard types
        using string_type       = std::basic_string         <_CharT, _Traits>;
        using streambuf_type    = std::basic_streambuf      <_CharT, _Traits>;
        using ostreambuf_iterator_type = std::ostreambuf_iterator<_CharT, _Traits>;
        using num_put_type      = std::num_put              <_CharT, ostreambuf_iterator_type>;
        using ios_type          = std::basic_ios            <_CharT, _Traits>;
        using ostream_type      = std::basic_ostream        <_CharT, _Traits>;
        using stringstream_type = std::basic_stringstream   <_CharT, _Traits>;
        using format_type       = basic_format              <_CharT, _Traits>;
        using formatstream_type = basic_formatstream        <_CharT, _Traits>;
        
        /**
         * @note If _FORMATSTREAM_DEPRECATE_STDIO is defined,
         * <code> std::ios_base::sync_with_stdio(false) </code>
         * is implemented in @file localefwd header to attempt
         * to make sure that xesstd::fout and xesstd::wfout
         * can be used together. If std::cout or std::wcout
         * is synchronized with stdio when doing output,
         * @c _state will be set false.
         * 
         * If not defined, under linux system, xesstd::wfout
         * cannot be used together with any other narrow
         * character streams, so as xesstd::fout with wide
         * character streams. Additionally, synchronization
         * with stdio will not effect basic_formatstream, so
         * if asynchronized, @c _state will be set false.
         */
        
        /**
         * @brief Base constructor.
         * 
         * This is the only ctor user can call directly
         * to create an object. It initialize the base
         * streambuf.
         */
        basic_formatstream(streambuf_type *__streambuf):
        basic_format<_CharT, _Traits>(__streambuf)
        { }
        
        /**
         * @brief Base destructor.
         * 
         * Recover streambuf flags.
         */
        ~basic_formatstream()
        {
            this->width(0);
            this->setff(format_base::blinkingbar, format_base::cursorshapefield);
            this->setff(format_base::showcursor);
            this->setff(format_base::enableblinking);
            _M_push();
            _insert_cmd("\x1b[0m");
        }
        
        // Initialization machinary for standard formatstream objects
        class init;
        
        /**
         * @brief Interface for self manipulators.
         * @param _pf A manipulator function
         * @return @c *this if successful
         * 
         * Manipulators such as xesstd::flush() use this
         * function exactly the same as ostream manipulators.
         */
        formatstream_type &operator <<(formatstream_type &(*_pf)(formatstream_type &))
        { return _pf(*this); }
        
        /**
         * @brief Interface for base class manipulators.
         * @param _pf A manipulator function
         * @return @c *this if successful
         */
        formatstream_type &operator <<(ostream_type &(*_pf)(ostream_type &))
        {
            ostream_type &(*_pf_flush)(ostream_type &) = std::flush;
            ostream_type &(*_pf_endl)(ostream_type &) = std::endl;
            ostream_type &(*_pf_ends)(ostream_type &) = std::ends;
            if (_pf == _pf_flush)
                flush();
            else if (_pf == _pf_endl)
                _unformatted_insert('\n').flush();
            else if (_pf == _pf_ends)
                _unformatted_insert('\0');
            return *this;
        }
        
        formatstream_type &operator <<(ios_type &(*_pf)(ios_type &))
        {
            _pf(*this);
            return *this;
        }
        
        formatstream_type &operator <<(std::ios_base &(*_pf)(std::ios_base &))
        {
            _pf(*this);
            return *this;
        }
        
        /**
         * @brief Interface for iomanip manipulators.
         * @param A manipulator function
         * @return @c *this if successful
         * 
         * For more infomation, see iomanip header.
         */
        formatstream_type &operator <<(decltype(std::setw(1)) _pf)
        {
            this->_base_ss << _pf;
            this->width(this->_base_ss.width());
            return *this;
        }
        
        formatstream_type &operator <<(decltype(std::setfill<char_type>(char_type())) _pf)
        {
            this->_base_ss << _pf;
            this->fill(this->_base_ss.fill());
            return *this;
        }
        
        formatstream_type &operator <<(decltype(std::setprecision(1)) _pf)
        {
            this->_base_ss << _pf;
            this->precision(this->_base_ss.precision());
            return *this;
        }
        
        formatstream_type &operator <<(decltype(std::setbase(10)) _pf)
        {
            this->_base_ss << _pf;
            this->setf(this->_base_ss.flags() & std::ios_base::basefield, std::ios_base::basefield);
            return *this;
        }
        
        formatstream_type &operator <<(decltype(std::setiosflags(std::ios_base::fmtflags())) _pf)
        {
            this->_base_ss.flags(this->flags());
            this->_base_ss << _pf;
            this->flags(this->_base_ss.flags());
            return *this;
        }
        
        formatstream_type &operator <<(decltype(std::resetiosflags(std::ios_base::fmtflags())) _pf)
        {
            this->_base_ss.flags(this->flags());
            this->_base_ss << _pf;
            this->flags(this->_base_ss.flags());
            return *this;
        }
        
        template<typename _Tp>
        formatstream_type &operator <<(std::_Put_money<_Tp> _pf)
        {
            this->_base_ss.width(this->width());
            this->_base_ss.fill(this->fill());
            this->_base_ss.precision(this->precision());
            this->_base_ss.flags(this->flags());
            this->_base_ss << _pf;
            _M_push();
            return *this;
        }
        
        template<typename _Tp>
        formatstream_type &operator <<(std::_Put_time<_Tp> _pf)
        {
            this->_base_ss.width(this->width());
            this->_base_ss.fill(this->fill());
            this->_base_ss.precision(this->precision());
            this->_base_ss.flags(this->flags());
            this->_base_ss << _pf;
            _M_push();
            return *this;
        }
        
        /**
         * @brief Integer arithmetic inserters.
         * @param _out A variable of builtin integer type
         * @return @c *this if successful
         */
        formatstream_type &operator <<(short _out)
        {
            const std::ios_base::fmtflags _fmt = this->flags() & std::ios_base::basefield;
            if (_fmt == std::ios_base::oct || _fmt == std::ios_base::hex)
                return _formatted_insert(static_cast<long>(static_cast<unsigned short>(_out)));
            return _formatted_insert(static_cast<long>(_out));
        }
        
        formatstream_type &operator <<(unsigned short _out)
        { return _formatted_insert(static_cast<unsigned long>(_out)); }
        
        formatstream_type &operator <<(int _out)
        {
            const std::ios_base::fmtflags _fmt = this->flags() & std::ios_base::basefield;
            if (_fmt == std::ios_base::oct || _fmt == std::ios_base::hex)
                return _formatted_insert(static_cast<long>(static_cast<unsigned int>(_out)));
            return _formatted_insert(static_cast<long>(_out));
        }
        
        formatstream_type &operator <<(unsigned int _out)
        { return _formatted_insert(static_cast<unsigned long>(_out)); }
        
        formatstream_type &operator <<(long _out)
        { return _formatted_insert(_out); }
        
        formatstream_type &operator <<(unsigned long _out)
        { return _formatted_insert(_out); }
        
#ifdef _GLIBCXX_USE_LONG_LONG
        formatstream_type &operator <<(long long _out)
        { return _formatted_insert(_out); }
        
        formatstream_type &operator <<(unsigned long long _out)
        { return _formatted_insert(_out); }
#endif
        
        formatstream_type &operator <<(bool _out)
        { return _formatted_insert(_out); }
        
        /**
         * @brief Floating point arithmetic inserters
         * @param _out A variable of builtin floating point type
         * @return @c *this if successful
         */
        formatstream_type &operator <<(float _out)
        { return _formatted_insert(static_cast<double>(_out)); }
        
        formatstream_type &operator <<(double _out)
        { return _formatted_insert(_out); }
        
        formatstream_type &operator <<(long double _out)
        { return _formatted_insert(_out); }
        
        /**
         * @brief Pointer arithmetic inserters.
         * @param _out A variable of (any) pointer type
         * @return @c *this if successful
         * 
         * This inserts the address of the pointer
         */
        formatstream_type &operator <<(const void *_out)
        { return _formatted_insert(_out); }

#if __cplusplus >= 201703L
        formatstream_type &operator <<(std::nullptr_t)
        { return *this << "nullptr"; }
#endif

#if __cplusplus > 202002L
        __attribute__((__always_inline__))
        formatstream_type &operator <<(const volatile void *_out)
        { return _formatted_insert(const_cast<const void *>(_out)); }
#endif
        
        /**
         * @brief Extracting from another streambuf.
         * @param _out  A pointer to a streambuf
         * 
         * This function behaves like one of the basic arithmetic extractors,
         * in that it also constructs a sentry object and has the same error
         * handling behavior.
         * 
         * If @p _out is NULL, the stream will set failbit in its error state.
         * 
         * Characters are extracted from @p _out and inserted into @c *this
         * until one of the following occurs:
         * 
         * - the input stream reaches end-of-file,
         * - insertion into the output sequence fails (in this case, the
         *   character that would have been inserted is not extracted), or
         * - an exception occurs while getting a character from @p _out, which
         *   sets failbit in the error state
         * 
         * If the function inserts no characters, failbit is set.
         */
        formatstream_type &operator <<(streambuf_type *_out)
        {
            std::ios_base::iostate _err = std::ios_base::goodbit;
            sentry _cerb(*this);
            if (_cerb && _out)
	        {
	            try
	            {
	                if (!__copy_streambufs(_out, this->rdbuf()))
		                _err |= std::ios_base::failbit;
	            }
	            catch (__cxxabiv1::__forced_unwind&)
	            {
	                this->_M_setstate(std::ios_base::badbit);		
	                __throw_exception_again;
	            }
	            catch (...)
	            { this->_M_setstate(std::ios_base::failbit); }
	        }
            else if (!_out)
	            _err |= std::ios_base::badbit;
            if (_err)
	            this->setstate(_err);
            flush();
            return *this;
        }
        
        /**
         * @brief Character inserters.
         * @param _out A character
         * @return @c *this if successful
         */
        formatstream_type &operator <<(char_type _out)
        { return _unformatted_insert(_out); }
        
        /**
         * @brief String inserters.
         * @param _out A character string
         * @return @c *this if successful
         */
        formatstream_type &operator <<(const char_type *_out)
        { return _unformatted_insert(_out); }
        
        formatstream_type &operator <<(string_type _out)
        { return _unformatted_insert(_out); }
        
        /**
         * @brief Function-like formatted inserter.
         * @param _fmt A format description
         * @param _first the first argument to be inserted
         * @param _args the rest argument to be inserted
         * @return @c *this if successful
         * 
         * This allows you to write constructs like
         * <code> xesstd::fout("...", a, b, c) </code> and
         * the number of argument is not regulated. If the
         * description is in wrong format or argument is
         * missing, @c std::invalid_argument will be throw.
         */
        formatstream_type &operator ()(string_type _fmt)
        {
            for (int i = 0; i < _fmt.size(); i++)
            {
                if (_fmt[i] == this->widen('{'))
                {
                    if (i != 0 && _fmt[i - 1] == this->widen('{'))
                        _unformatted_insert(this->widen('{'));
                    else
                        throw std::invalid_argument("basic_formatstream.operator(): unexpected '{'");
                }
                else if (_fmt[i] == this->widen('}'))
                {
                    if (i != 0 && _fmt[i - 1] == this->widen('}'))
                        _unformatted_insert(this->widen('}'));
                    else
                        throw std::invalid_argument("basic_formatstream.operator(): unexpected '}'");
                }
                else
                    _unformatted_insert(_fmt[i]);
            }
            return *this;
        }
        
        template<typename _First, typename... _Args>
        formatstream_type &operator ()(string_type _fmt,
            const _First &_first, const _Args &... _args)
        {
            for (int i = 0; i < _fmt.size(); i++)
            {
                if (_fmt[i] == this->widen('{'))
                {
                    if (i != 0 && _fmt[i - 1] == this->widen('{'))
                        _unformatted_insert(this->widen('{'));
                    else
                    {
                        while (i < _fmt.size() && _fmt[i] != this->widen('}'))
                            i++;
                        if (i == _fmt.size())
                            throw std::invalid_argument("basic_formatstream.operator(): expected '}'");
                        operator <<(_first);
                        operator ()(_fmt.substr(i + 1), _args...);
                        return *this;
                    }
                }
                else if (_fmt[i] == this->widen('}'))
                {
                    if (i != 0 && _fmt[i - 1] == this->widen('}'))
                        _unformatted_insert(this->widen('}'));
                    else
                        throw std::invalid_argument("basic_formatstream.operator(): unexpected '}'");
                }
                else
                    _unformatted_insert(_fmt[i]);
            }
            return *this;
        }
        
        /**
         * @brief Synchronizing the stream buffer.
         * @return @c *this
         *
         * If @c rdbuf() is a null pointer, changes nothing.
         *
         * Otherwise, calls @c rdbuf()->pubsync(), and if that returns -1,
         * sets badbit.
         */
        formatstream_type &flush()
        {
            if (streambuf_type *_buf = this->rdbuf())
        	{
        	    sentry _cerb(*this);
        	    if (_cerb)
        	    {
        	        std::ios_base::iostate _err = std::ios_base::goodbit;
        	        try
            		{
            		    if (this->rdbuf()->pubsync() == -1)
            		        _err |= std::ios_base::badbit;
            		}
            	    catch (__cxxabiv1::__forced_unwind &)
            		{
            		    this->_M_setstate(std::ios_base::badbit);
            		    __throw_exception_again;
            		}
            	    catch (...)
            		{ this->_M_setstate(std::ios_base::badbit); }
        	        if (_err)
        		        this->setstate(_err);
        	    }
        	}
            return *this;
        }
        
        // basic_formatstream console manipulators.
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        cls(basic_formatstream<_CharT2, _Traits2> &);
        
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        cll(basic_formatstream<_CharT2, _Traits2> &);
        
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        clear(basic_formatstream<_CharT2, _Traits2> &);
        
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        operator <<(basic_formatstream<_CharT2, _Traits2> &, _At);
        
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        operator <<(basic_formatstream<_CharT2, _Traits2> &, _Athonrizontal);
        
        template<typename _CharT2, typename _Traits2>
        friend
        basic_formatstream<_CharT2, _Traits2> &
        operator <<(basic_formatstream<_CharT2, _Traits2> &, _Atvertical);
        
        protected:
        // Default constructor.
        basic_formatstream() = delete;
        
        // Copy constructor.
        basic_formatstream(const basic_formatstream &) = delete;
        
        // Move constructor.
        basic_formatstream(basic_formatstream &&) = delete;
        
        // Assignment operator.
        basic_formatstream &operator =(const basic_formatstream &) = delete;
        
        // Safe prefix/suffix operations.
        class sentry;
        friend class sentry;
        
        /**
         * 
         */
        template<typename _ValueT>
        formatstream_type &_formatted_insert(_ValueT _out)
        {
            sentry _cerb(*this);
            if (_cerb)
            {
                std::ios_base::iostate _err = std::ios_base::goodbit;
                try
                {
                    const num_put_type &_np = __check_facet(this->_M_num_put);
                    if (_np.put(ostreambuf_iterator_type(this->rdbuf()), *this, this->fill(), _out).failed())
                        _err |= std::ios_base::badbit;
                }
                catch (__cxxabiv1::__forced_unwind &)
                {
                    this->_M_setstate(std::ios_base::badbit);
                    __throw_exception_again;
                }
                catch (...)
                { this->_M_setstate(std::ios_base::badbit); }
                if (_err)
                    this->setstate(_err);
            }
            return *this;
        }
        
        /**
         * 
         */
        template<typename _ValueT>
        formatstream_type &_unformatted_insert(_ValueT _out)
        {
            sentry _cerb(*this);
            if (_cerb)
            {
                if (std::is_same<std::string, _ValueT>::value
                    || std::is_same<const char *, _ValueT>::value
                    || std::is_same<char, _ValueT>::value)
                {
                    string_type _filted;
                    _filted += _out;
                    _filter(_filted);
                    _M_pad(_filted);
                }
                else
                {
                    this->_M_setstate(std::ios_base::failbit);
                    this->setstate(std::ios_base::failbit);
                }
            }
            return *this;
        }
        
        /**
         * 
         */
        template<typename _ValueT>
        formatstream_type &_insert_cmd(_ValueT _out)
        {
            sentry _cerb(*this);
            if (_cerb)
            {
                if (std::is_same<std::string, _ValueT>::value
                    || std::is_same<const char *, _ValueT>::value
                    || std::is_same<char, _ValueT>::value)
                {
                    string_type _tmp;
                    _tmp += this->widen(_out);
                    _M_do_put(_tmp);
                }
                else
                {
                    this->_M_setstate(std::ios_base::failbit);
                    this->setstate(std::ios_base::failbit);
                }
            }
            return *this;
        }
        
        /**
         * 
         */
        formatstream_type &_M_push()
        {
            const std::streamsize _curwidth = this->width(0);
            _M_pad(this->_base_ss.str());
            this->width(_curwidth);
            this->_base_ss.str(string_type());
            return *this;
        }
        
        private:
        std::streamsize _curbufsiz = 0;
        string_type _filter_tmp;
        bool _is_italic = false;
        bool _is_underlined = false;
        bool _cursor_visibility = true;
        bool _do_cursor_blinking = true;
        format_base::ffmtflags _cursor_shape = format_base::usershape;
        
        std::streamsize _M_pad(string_type _ws)
        {
            // Set font color
            if (this->_do_refresh_font_color)
            {
                this->_do_refresh_font_color = false;
                _M_do_put(this->widen("\x1b[38;2;"));
                _formatted_insert(static_cast<long>(this->_font_color.R));
                _M_do_put(this->widen(";"));
                _formatted_insert(static_cast<long>(this->_font_color.G));
                _M_do_put(this->widen(";"));
                _formatted_insert(static_cast<long>(this->_font_color.B));
                _M_do_put(this->widen("m"));
            }
            
            // Set background color
            if (this->_do_refresh_bg_color)
            {
                this->_do_refresh_bg_color = false;
                _M_do_put(this->widen("\x1b[48;2;"));
                _formatted_insert(static_cast<long>(this->_bg_color.R));
                _M_do_put(this->widen(";"));
                _formatted_insert(static_cast<long>(this->_bg_color.G));
                _M_do_put(this->widen(";"));
                _formatted_insert(static_cast<long>(this->_bg_color.B));
                _M_do_put(this->widen("m"));
            }
            
            // Set cursor's visibility
            if (_cursor_visibility)
            {
                if (!(this->fflags() & format_base::showcursor))
                {
                    _M_do_put(this->widen("\x1b[?25l"));
                    _cursor_visibility = false;
                }
            }
            else if (this->fflags() & format_base::showcursor)
            {
                _M_do_put(this->widen("\x1b[?25h"));
                _cursor_visibility = true;
            }
            
            // Set cursor's capibility of blinking
            if (_do_cursor_blinking)
            {
                if (!(this->fflags() & format_base::enableblinking))
                {
                    _M_do_put(this->widen("\x1b[?12l"));
                    _do_cursor_blinking = false;
                }
            }
            else if (this->fflags() & format_base::enableblinking)
            {
                _M_do_put(this->widen("\x1b[?12h"));
                _do_cursor_blinking = true;
            }
            
            // Set italic
            if (_is_italic)
            {
                if (!(this->fflags() & format_base::italic))
                {
                    _M_do_put(this->widen("\x1b[23m"));
                    _is_italic = false;
                }
            }
            else if (this->fflags() & format_base::italic)
            {
                _M_do_put(this->widen("\x1b[3m"));
                _is_italic = true;
            }
            
            // Set underline
            if (_is_underlined)
            {
                if (!(this->fflags() & format_base::underline))
                {
                    _M_do_put(this->widen("\x1b[24m"));
                    _is_underlined = false;
                }
            }
            else if (this->fflags() & format_base::underline)
            {
                _M_do_put(this->widen("\x1b[4m"));
                _is_underlined = true;
            }
            
            // Change cursor's shape
            format_base::ffmtflags _shape = this->fflags() & format_base::cursorshapefield;
            if (_shape != _cursor_shape)
            {
                switch (_shape)
                {
                    case format_base::usershape:
                    _M_do_put(this->widen("\x1b[0\x20\x71"));
                    break;
                    
                    case format_base::blinkingblock:
                    _M_do_put(this->widen("\x1b[1\x20\x71"));
                    break;
                    
                    case format_base::steadyblock:
                    _M_do_put(this->widen("\x1b[2\x20\x71"));
                    break;
                    
                    case format_base::blinkingunderline:
                    _M_do_put(this->widen("\x1b[3\x20\x71"));
                    break;
                    
                    case format_base::steadyunderline:
                    _M_do_put(this->widen("\x1b[4\x20\x71"));
                    break;
                    
                    case format_base::blinkingbar:
                    _M_do_put(this->widen("\x1b[5\x20\x71"));
                    break;
                    
                    case format_base::steadybar:
                    _M_do_put(this->widen("\x1b[6\x20\x71"));
                    break;
                    
                    default:
                    break;
                }
                _cursor_shape = _shape;
            }
            
            // Pad if necessary
            if (this->width())
            {
                size_t _l = xesstd::width(_ws);
                if (this->width() > _l)
                {
                    string_type _padding(this->width() - _l, ' ');
                    std::ios_base::fmtflags _adjust = this->_base_ss.flags() & std::ios::adjustfield;
                    if (_adjust == std::ios_base::internal)
                    {
                        // If it is a number ... or whatever?
                        // Seriously, doesn't "internal" mean output should be
                        // in the middle of the expected width?
                        if (true)
                        {
                            size_t _mod = 0;
                            if (_ws[0] == this->widen('+')
                                || _ws[0] == this->widen('-'))
                                _mod = 1;
                            else if (_ws[0] == this->widen('0')
                                && _l > 1 && (_ws[1] == this->widen('x')
                                    || _ws[1] == this->widen('X')))
                                _mod = 2;
                            if (_mod)
                                _ws.insert(_mod, _padding);
                        }
                    }
                    else if (_adjust == std::ios_base::left)
                        _ws += _padding;
                    else
                        _ws.insert(0, _padding);
                }
                this->width(0);
            }
            
            return _M_do_put(_ws);
        }
        
        std::streamsize _M_do_put(string_type _ws)
        {
            for (auto &&_i : _ws)
            {
                _curbufsiz++;
                if (_curbufsiz > 128)
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(12800));
                    _curbufsiz = 0;
                }
                _M_put(_i);
            }
            if (this->autoflush())
                this->flush();
            return _ws.size();
        }
        
        std::streamsize _M_put(char_type _wc)
        { return this->rdbuf()->sputc(_wc); }
        
        void _filter(string_type &_x)
        {
            string_type _n;
            _n += this->widen('\x1b');
            _n += this->widen('\\');
            for (size_t i = 0; i < _x.size(); )
            {
                if (_filter_tmp.empty())
                {
                    if (_x[i] == this->widen('\x1b'))
                    {
                        _filter_tmp += _x[i];
                        _x.erase(i, 1);
                    }
                    else
                        i++;
                }
                else
                {
                    _filter_tmp += _x[i];
                    _x.erase(i, 1);
                    if (_x[i] == this->widen('\x1b'))
                    {
                        _filter_tmp.clear();
                        _filter_tmp += _x[i];
                        _x.erase(i, 1);
                    }
                    if (_filter_tmp.find(this->widen('[')) == 1)
                    {
                        if (std::isalpha(_filter_tmp[_filter_tmp.size() - 1])
                            || _filter_tmp[_filter_tmp.size() - 1] == this->widen('@'))
                            _filter_tmp.clear();
                    }
                    else if (_filter_tmp.find(this->widen(']')) == 1)
                    {
                        if (_filter_tmp.find(_n) != -1)
                            _filter_tmp.clear();
                    }
                    else if (_filter_tmp.size() == 2)
                        _filter_tmp.clear();
                }
            }
        }
    };
    
    // basic_formatstream manipulators.
    // @{
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::italic).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    italic(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::italic);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::underline).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    underline(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::underline);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::showcursor).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    showcursor(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::showcursor);
        return _fs;
    }
    
    // Calls fs.unsetff(basic_formatstream<_CharT, _Traits>::showcursor).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    hidecursor(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.unsetff(basic_formatstream<_CharT, _Traits>::showcursor);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::enableblinking).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    enableblinking(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::showcursor);
        return _fs;
    }
    
    // Calls fs.unsetff(basic_formatstream<_CharT, _Traits>::enableblinking).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    unableblinking(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.unsetff(basic_formatstream<_CharT, _Traits>::enableblinking);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::usershape,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    usershape(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::usershape, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::blinkingblock,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    blinkingblock(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::blinkingblock, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::steadyblock,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    steadyblock(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::steadyblock, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::blinkingunderline,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    blinkingunderline(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::blinkingunderline, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::steadyunderline,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    steadyunderline(basic_formatstream<_CharT, _Traits> &_fs)
    { return _fs.setff(basic_formatstream<_CharT, _Traits>::steadyunderline, basic_formatstream<_CharT, _Traits>::cursorshapefield); }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::blinkingbar,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    blinkingbar(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::blinkingbar, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    
    // Calls fs.setff(basic_formatstream<_CharT, _Traits>::steadybar,
    // basic_formatstream<_CharT, _Traits>::cursorshapefield).
    template<typename _CharT, typename _Traits>
    inline basic_formatstream<_CharT, _Traits> &
    steadybar(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::steadybar, basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs;
    }
    // @}
    // @{
    struct _Setfontcolor
    { color _M_color; };
    
    inline _Setfontcolor setfontcolor(color _x)
    { return _Setfontcolor{_x}; }
    
    /**
     * 
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _Setfontcolor _pf)
    {
        _fs.fontcolor(_pf._M_color);
        return _fs;
    }
    
    struct _Setbgcolor
    { color _M_color; };
    
    inline _Setbgcolor setbgcolor(color _x)
    { return _Setbgcolor{_x}; }
    
    /**
     * 
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _Setbgcolor _pf)
    {
        _fs.bgcolor(_pf._M_color);
        return _fs;
    }
    
    /**
     * @brief Flushes the output stream.
     *
     * This manipulator simply calls the stream's @c flush() member function.
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    flush(basic_formatstream<_CharT, _Traits> &_fs)
    { return _fs.flush(); }
    
    struct _Endl
    { size_t _M_x; };
    
    inline _Endl endl(size_t _x)
    { return _Endl{_x}; }
    
    /**
     * @brief Insert a certain number of new lines and then
     * flush the output stream.
     * 
     * This manipulator inserts several @a '\n's and then calls @c flush().
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _Endl _pf)
    {
        _fs << std::basic_string<_CharT, _Traits>(_pf._M_x, '\n');
        return _fs.flush();
    }
    // @}
    
    // basic_formatstream console manipulators.
    // @{
    /**
     * @brief Clears the whole terminal display.
     * 
     * This is a console manipulator. It inserts a controllong sequence.
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    cls(basic_formatstream<_CharT, _Traits> &_fs)
    { return _fs._insert_cmd("\x1b[2J\x1b[1;1H").flush(); }
    
    /**
     * @brief Clears the whole line which the cursor is in currently.
     * 
     * This is a console manipulator. It inserts a controllong sequence.
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    cll(basic_formatstream<_CharT, _Traits> &_fs)
    { return _fs._insert_cmd("\x1b[2K\x1b[1G").flush(); }
    
    /**
     * @brief Resets all the console format flags.
     * 
     * This is a console manipulator. It inserts a controllong sequence.
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    clear(basic_formatstream<_CharT, _Traits> &_fs)
    {
        _fs.setff(basic_formatstream<_CharT, _Traits>::blinkingbar,
            basic_formatstream<_CharT, _Traits>::cursorshapefield);
        return _fs._insert_cmd("\x1b[0m").flush();
    }
    
    inline _At at(size_t _x, size_t _y)
    { return _At{_x, _y}; }
    
    /**
     * 
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _At _pf)
    {
        _fs._insert_cmd("\x1b[");
        _fs._formatted_insert(_pf._M_y);
        _fs._insert_cmd(';');
        _fs._formatted_insert(_pf._M_x);
        return _fs._insert_cmd('H');
    }
    
    inline _Athonrizontal athorizontal(size_t _x)
    { return _Athonrizontal{_x}; }
    
    /**
     * 
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _Athonrizontal _pf)
    {
        _fs._insert_cmd("\x1b[");
        _fs._formatted_insert(_pf._M_x);
        return _fs._insert_cmd('G');
    }
    
    inline _Atvertical atvertical(size_t _x)
    { return _Atvertical{_x}; }
    
    /**
     * 
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, _Atvertical _pf)
    {
        _fs._insert_cmd("\x1b[");
        _fs._formatted_insert(_pf._M_x);
        return _fs._insert_cmd('d');
    }
    // @}
    
    /**
     * @brief Performs setup work for output streams.
     *
     * Objects of this class are created before all of the standard
     * inserters are run. It is responsible for <em>exception-safe prefix and
     * suffix operations</em>.
     */
    template<typename _CharT, typename _Traits>
    class basic_formatstream<_CharT, _Traits>::sentry
    {
        public:
        /**
         * @brief The constructor performs preparatory work.
         * @param __fs The output stream to guard.
         *
         * If the stream state is good, then the sentry state becomes
         * true (@a okay).
         */
        explicit sentry(basic_formatstream<_CharT, _Traits> &__fs):
        _ok(false), _fs(__fs)
        {
            if (_fs.good() && std::ios_base::sync_with_stdio() == _XESSTD_FORMAT_SYNC)
                _ok = true;
            else if (_fs.bad())
                _fs.setstate(std::ios_base::failbit);
        };
        
        /**
         * @brief Possibly flushes the stream.
         * 
         * If the stream has @c std::ios_base::unitbuf flag, turn on
         * the stream's autoflush.
         */
        ~sentry()
        {
            if (!_fs.autoflush() && _fs._base_ss.flags() & std::ios_base::unitbuf)
                _fs.autoflush(true);
            // if (_fs.autoflush())
                // _fs.flush();
        }
        
        /**
         * @brief Quick status checking.
         * @return The sentry state.
         *
         * For ease of use, sentries may be converted to booleans. The
         * return value is that of the sentry state (true == okay).
         */
        explicit operator bool() const
        { return _ok; }
        
        private:
        // Data members
        bool _ok;
        basic_formatstream<_CharT, _Traits> &_fs;
    };
    
    /**
     * @brief Character inserter specialization.
     * @param _out A character of type char
     * @return @c *this if successful
     * 
     * This specialization is mainly to support narrow
     * character literal output.
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, char _out)
    { return _fs << _fs.widen(_out); }
    
    /**
     * @brief Character inserter specialization.
     * @param _out A character of type signed char
     * @return @c *this if successful
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, signed char _out)
    { return _fs << static_cast<char>(_out); }
    
    /**
     * @brief Character inserter specialization.
     * @param _out A character of type unsigned char
     * @return @c *this if successful
     */
    template<typename _CharT, typename _Traits>
    basic_formatstream<_CharT, _Traits> &
    operator <<(basic_formatstream<_CharT, _Traits> &_fs, unsigned char _out)
    { return _fs << static_cast<char>(_out); }
    
    /**
     * @brief String inserter specialization.
     * @param _out A character string of type char *
     * @return @c *this if successful
     * 
     * This specialization is mainly to support narrow
     * string literal output by basic_formatstream<wchar_t>.
     */
    template<typename _Traits>
    basic_formatstream<wchar_t, _Traits> &
    operator <<(basic_formatstream<wchar_t, _Traits> &_fs, const char *_out)
    { return _fs << localr::string_convert<localr::codecvt<char, wchar_t>>::in(_out); }
    
    /**
     * @brief String inserter specialization.
     * @param _out A character string of type std::string
     * @return @c *this if successful
     * 
     * This specialization is mainly to support narrow
     * string output by basic_formatstream<wchar_t>.
     */
    template<typename _Traits>
    basic_formatstream<wchar_t, _Traits> &
    operator <<(basic_formatstream<wchar_t, _Traits> &_fs, std::string _out)
    { return _fs << localr::string_convert<localr::codecvt<char, wchar_t>>::in(_out); }
    
    using formatstream = basic_formatstream<char>;
    __gnu_cxx::stdio_filebuf<char> formatstream_out_filebuf(stdout, std::ios_base::out);
    formatstream fout(&formatstream_out_filebuf);
    
#ifdef _GLIBCXX_USE_WCHAR_T
    using wformatstream = basic_formatstream<wchar_t>;
    __gnu_cxx::stdio_filebuf<wchar_t> wformatstream_out_filebuf(stdout, std::ios_base::out);
    wformatstream wfout(&wformatstream_out_filebuf);
#endif
    
    using std::endl;
    using std::ends;
    using std::setw;
    using std::setfill;
    using std::setprecision;
    using std::setbase;
    using std::setiosflags;
    using std::resetiosflags;
    using std::put_money;
    using std::put_time;
    using std::boolalpha;
    using std::noboolalpha;
    using std::showbase;
    using std::noshowbase;
    using std::showpoint;
    using std::noshowpoint;
    using std::showpos;
    using std::noshowpos;
    using std::skipws;
    using std::noskipws;
    using std::uppercase;
    using std::nouppercase;
    using std::unitbuf;
    using std::nounitbuf;
    using std::internal;
    using std::left;
    using std::right;
    using std::dec;
    using std::hex;
    using std::oct;
    using std::fixed;
    using std::scientific;
#if __cplusplus >= 201103L
    using std::hexfloat;
    using std::defaultfloat;
#endif
    
_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#endif