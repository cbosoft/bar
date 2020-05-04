#include <iostream>

#include "recipe.hpp"
#include "../util/glob.hpp"


Recipe::Recipe(std::list<std::string> dependency_patterns,
    std::string command,
    std::string initial,
    std::string on_error)
{

  for (auto pattern : dependency_patterns) {
    auto result = glob(pattern);
    this->dependencies.merge(result);
  }

  this->initial_build = initial;
  this->subsequent_build = command;
  this->on_error = on_error;

}

Recipe::~Recipe()
{
  // do nothing
}
