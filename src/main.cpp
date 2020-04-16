#include <iostream>
#include "recipe/recipe.hpp"
#include "util/notify.hpp"
#include "util/exception.hpp"

#define EITHER(A,B) ( (strcmp(argv[i], A) == 0) or (strcmp(argv[i], B) == 0) )


int main(int argc, const char **argv)
{
  std::string initial = ":";
  std::string subsequent = ":";
  std::list<std::string> patterns;

  argc--; argv++;
  for (int i = 0; i < argc; i++) {

    if (EITHER("-p", "--pattern")) {
      std::string s(argv[++i]);
      patterns.push_back(s);
    }
    else if (EITHER("-i", "--initial")) {
      initial = std::string(argv[++i]);
    }
    else if (EITHER("-s", "--subsequent")) {
      subsequent = std::string(argv[++i]);
    }
    else {
      throw ArgumentError(Formatter() << "Unknown argument " << argv[i] << ".");
    }
  }

  if (!patterns.size()) {
    throw ArgumentError(Formatter() << "No files specified to watch.");
  }

  // TODO read recipe from file
  Recipe r(patterns, initial, subsequent);
  r.monitor();
}
