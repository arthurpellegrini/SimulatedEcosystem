#include "Center.h"

template<typename charT, typename traits>
Center<charT, traits>::Center(std::basic_string<charT, traits> str) : str_(str) {}

template<typename charT, typename traits>
Center<charT, traits> centered(basic_string<charT, traits> str) {
    return Center<charT, traits>(str);
}

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