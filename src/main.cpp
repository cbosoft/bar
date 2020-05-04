#include <iostream>

#include "util/colour.hpp"
#include "recipes/recipes.hpp"

#define EITHER(A,B) ( (strcmp(argv[i], A) == 0) or (strcmp(argv[i], B) == 0) )

void show_help_and_exit()
{
  std::cerr
   << BOLD "bar" RESET "\n"
   << "\n"
   << "Watches for file changes then runs specified commands.\n"
   << "\n"
   << BOLD "Usage:" RESET "\n"
   << "  bar\n"
   << "\n"
   << BOLD "Config File" RESET "\n"
   << "Files and commands are specified by config files. bar looks for a file named\n"
   << "\".bar_recipe\" in the current directory. The configuration file constists of\n"
   << "sets of key-value pairs, one pair per line, separated by colon ':'.\n"
   << "\n"
   << "Values:\n"
   << "  command  ::  The shell command that will run when file changes are detected. Required.\n"
   << "\n"
   << "  initial  ::  If present, the command that is run when bar starts up. Optional.\n"
   << "\n"
   << "  pattern  ::  A glob-pattern specifying the files to monitor. Can be specified\n"
   << "               any number of times, but at least once.\n"
   << "\n"
   << "There can be multiple recipes specified in the same file, separated by three\n"
   << "dashes: \"---\".\n"
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
