#include <iostream>

#include "util/colour.hpp"
#include "recipes/recipes.hpp"

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

  argc--; argv++;
  if (argc) {
    show_help_and_exit();
  }

  Recipes::from_file(".bar_recipe").monitor();
}
