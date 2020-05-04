#include <iostream>
#include <regex>

#include "replace.hpp"


std::string replace(std::string s, std::string pattern, std::string newvalue)
{
  std::regex r(pattern);
  auto beg = std::sregex_iterator(s.begin(), s.end(), r);
  auto end = std::sregex_iterator();

  std::cerr << s << " " << pattern << " " << newvalue << "\n";

  int i = 0, len = s.size();
  const char *cdata = s.data();
  std::stringstream ss;
  for (auto it = beg; it != end; it++) {

    auto match = (*it);
    for (; i < match.position(); i++)
      ss << cdata[i];

    i += match.length();
    ss << newvalue;

  }

  for (; i < len; i++)
    ss << cdata[i];

  return ss.str();
}
