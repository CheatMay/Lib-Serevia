// <localr.h> -*- C++ -*-

/*
Localr was under the MIT license.
Copyright(c) 2022 FurryR.
*/
#ifndef _LOCALR_H_
#define _LOCALR_H_
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
// localr������洢�˶����ַ�ת���Ļ���ʵ�֡�
namespace localr {
template <typename InternT, typename ExternT>
// codecvt ���ࡣ�˻��಻����ʵ�֡�
struct codecvt {
  // �������͡�
  typedef InternT in_type;
  // ������͡�
  typedef ExternT out_type;
  codecvt(){};
  // ת��src��out_type��
  static out_type in(const in_type& src);

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~codecvt();
};
template <>
// codecvt �ػ��ࡣ�����ɿ��ַ���խ�ַ���ת����
struct codecvt<wchar_t, char> {
  // �������͡�
  typedef wchar_t in_type;
  // ������͡�
  typedef std::string out_type;
  // ת��src��out_type��
  static out_type in(const in_type& src) {
    static const std::vector<std::pair<unsigned int, unsigned char>> range = {
        {0x80, 0x00},       // u0000 - u007f
        {0x800, 0xc0},      // u0080 - u07ff
        {0x10000, 0xe0},    // u0800 - uffff
        {0x200000, 0xf0},   // u10000 - u1ffff
        {0x400000, 0xf8},   // u200000 - u3ffffff
        {0x80000000, 0xfc}  // u4000000 - u7fffffff
    };
    if (src == 0) return "";
    for (size_t i = 0; i < range.size(); i++) {
      if (src < range[i].first) {
        wchar_t cp = src;
        std::string ret(i + 1, '\0');
        for (size_t j = i; j > 0; j--) {
          ret[j] = (cp & 0x3f) | 0x80;
          cp >>= 6;
        }
        ret[0] = cp | range[i].second;
        return ret;
      }
    }
    throw std::invalid_argument("codecvt::in");
  }
  codecvt(){};

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~codecvt();
};
template <>
// codecvt �ػ��ࡣ������խ�ַ������ַ���ת����
struct codecvt<char, wchar_t> {
  // �������͡�
  typedef std::string in_type;
  // ������͡�
  typedef wchar_t out_type;
  // ת��src��out_type��
  static out_type in(const in_type& src) {
    if (src.empty()) return 0;
    unsigned char b = src[0];
    wchar_t dst;
    if (b < 0x80) {
      if (src.length() == 1) return wchar_t(src[0]);
      throw std::invalid_argument("codecvt::in");
    } else if (b < 0xc0 || b > 0xfd)
      throw std::invalid_argument("codecvt::in");
    else if (b < 0xe0)
      dst = b & 0x1f;
    else if (b < 0xf0)
      dst = b & 0x0f;
    else if (b < 0xf8)
      dst = b & 0x07;
    else if (b < 0xfc)
      dst = b & 0x03;
    else
      dst = b & 0x01;
    for (size_t i = 1; i < src.length(); i++) {
      b = src[i];
      if (b < 0x80 || b > 0xbf) throw std::invalid_argument("codecvt::in");
      dst = (dst << 6) + (src[i] & 0x3f);
    }
    return dst;
  }
  codecvt(){};

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~codecvt();
};
template <typename Codecvt>
// string_convert ���ࡣ�˻���������ת����ͨ�ð档
struct string_convert {
  // ʹ�õ�codecvt���͡�
  typedef Codecvt codecvt_type;
  // ת������src����Codecvt::out_type��ɵ����С�
  static std::vector<typename codecvt_type::out_type> in(
      const std::vector<typename codecvt_type::in_type>& src) {
    std::vector<typename Codecvt::out_type> dst;
    for (size_t i = 0; i < src.size(); i++)
      dst.push_back(codecvt_type::in(src[i]));
    return dst;
  };
  string_convert(){};

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~string_convert(){};
};
template <>
// string_convert �ػ��ࡣ�����ɿ��ַ����е�խ�ַ����е�ת����
struct string_convert<codecvt<wchar_t, char>> {
  // ʹ�õ�codecvt���͡�
  typedef codecvt<wchar_t, char> codecvt_type;
  // ת��src��std::string��
  static std::string in(const std::wstring& src) {
    std::string dst;
    for (size_t i = 0; i < src.length(); i++)
      dst += codecvt<wchar_t, char>::in(src[i]);
    return dst;
  }
  string_convert(){};

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~string_convert(){};
};
template <>
// string_convert �ػ��ࡣ������խ�ַ����е����ַ����е�ת����
struct string_convert<codecvt<char, wchar_t>> {
  // ʹ�õ�codecvt���͡�
  typedef codecvt<char, wchar_t> codecvt_type;
  // ת��src��std::wstring��
  static std::wstring in(const std::string& src) {
    std::vector<std::string> t;
    std::wstring dst;
    for (size_t i = 0; i < src.length();) {
      unsigned char b = src[i];
      if (b < 0x80)
        t.push_back({src[i]}), i++;
      else if (b < 0xc0 || b > 0xfd)
        throw std::invalid_argument("string_convert::in");  // src is invalid
      else if (b < 0xe0)
        t.push_back(src.substr(i, 2)), i += 2;
      else if (b < 0xf0)
        t.push_back(src.substr(i, 3)), i += 3;
      else if (b < 0xf8)
        t.push_back(src.substr(i, 4)), i += 4;
      else if (b < 0xfc)
        t.push_back(src.substr(i, 5)), i += 5;
      else
        t.push_back(src.substr(i, 6)), i += 6;
    }
    for (size_t i = 0; i < t.size(); i++) {
      try {
        dst += codecvt<char, wchar_t>::in(t[i]);
      } catch (const std::invalid_argument&) {
        throw std::invalid_argument("string_convert::in");  // src is invalid
      }
    }
    return dst;
  }
  string_convert(){};

 private:
  // ���������������ɽ�������Ϊ����ʹ�á�
  ~string_convert(){};
};
}  // namespace localr
#endif