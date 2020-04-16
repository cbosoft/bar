#include <iostream>

#include "recipe.hpp"
#include "../util/glob.hpp"


Recipe::Recipe(std::list<std::string> dependency_patterns, std::string initial, std::string subsequent)
{

  for (auto pattern : dependency_patterns) {
    auto result = glob(pattern);
    this->dependencies.merge(result);
  }

  this->initial_build = initial;
  this->subsequent_build = subsequent;

}

Recipe::~Recipe()
{
  // do nothing
}
