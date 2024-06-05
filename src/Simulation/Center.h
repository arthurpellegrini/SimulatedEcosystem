//
// Created by arthu on 05/06/2024.
//

#ifndef CENTER_H
#define CENTER_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

template<typename charT, typename traits = char_traits<charT> >

class Center {
    std::basic_string<charT, traits> str_;
public:
    Center(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(basic_ostream<a, b>& s, const Center<a, b>& c);
};

template<typename charT, typename traits = char_traits<charT> >
Center<charT, traits> centered(basic_string<charT, traits> str) {
    return Center<charT, traits>(str);
}

// Center<string::value_type, string::traits_type> centered(const string& str) {
//     return Center<string::value_type, string::traits_type>(str);
// }

template<typename charT, typename traits>
basic_ostream<charT, traits>& operator<<(basic_ostream<charT, traits>& s, const Center<charT, traits>& c) {
    streamsize w = s.width();
    if (w > c.str_.length()) {
        streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}

#endif //CENTER_H
