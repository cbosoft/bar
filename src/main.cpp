#include <iostream>
#include "recipe/recipe.hpp"
#include "util/notify.hpp"
#include "util/exception.hpp"

#define EITHER(A,B) ( (strcmp(argv[i], A) == 0) or (strcmp(argv[i], B) == 0) )

void show_help_and_exit()
{
  std::cerr
   << "  " BOLD "BAR" RESET "\n"
   << "\n"
   << "  " BOLD "Usage:" RESET "\n"
   << "    bar [--recipe <recipe>]\n"
   << "    bar --initial <val> --subsequent <val> --pattern <val> [--pattern <val> ...]\n"
   << "\n"
   ;
  exit(0);
}


int main(int argc, const char **argv)
{

  std::string initial = ":";
  std::string subsequent = ":";
  std::list<std::string> patterns;

  argc--; argv++;
  if (argc) {
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
      else if (EITHER("-h", "--help")) {
        show_help_and_exit();
      }
      else if (EITHER("-r", "--recipe")) {

        Recipe::from_file(std::string(argv[++i])).monitor();
        return 0;

      }
      else {
        throw ArgumentError(Formatter() << "Unknown argument " << argv[i] << ".");
      }

    }

    if (!patterns.size()) {
      throw ArgumentError(Formatter() << "No files or patterns specified.");
    }

    Recipe(patterns, initial, subsequent).monitor();
  }
  else {
    Recipe::from_file(".bar_recipe").monitor();
  }

}
