#ifndef CENTER_H
#define CENTER_H

#include <string>
#include <iomanip>

using namespace std;

template<typename charT, typename traits = char_traits<charT> >
class Center {
    std::basic_string<charT, traits> str_;
public:
    explicit Center(std::basic_string<charT, traits> str);
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(basic_ostream<a, b>& s, const Center<a, b>& c);
};

template<typename charT, typename traits = char_traits<charT> >
Center<charT, traits> centered(basic_string<charT, traits> str);

template<typename charT, typename traits>
basic_ostream<charT, traits>& operator<<(basic_ostream<charT, traits>& s, const Center<charT, traits>& c);

#include "Center.cpp"

#endif //CENTER_H
