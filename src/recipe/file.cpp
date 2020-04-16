#include <iostream>
#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "recipe.hpp"

Recipe Recipe::from_file(std::string path)
{

  std::fstream infile(path);
  if (infile.fail()) {
    throw IOError(Formatter() << "Failed to open recipe file: " << path, true);
  }

  std::string initial, subsequent;
  std::list<std::string> patterns;

  for (std::string line; std::getline(infile, line); ) {
    std::stringstream ss(line);

    std::string key, value;
    std::getline(ss, key, ':');
    std::getline(ss, value, ':');

    if (key.compare("initial") == 0) {
      initial = value;
    }
    else if (key.compare("subsequent") == 0) {
      subsequent = value;
    }
    else if (key.compare("pattern") == 0) {
      patterns.push_back(value);
    }
    else {
      throw RecipeSyntaxError(Formatter() << "Unknown key " << key << ".");
    }

  }

  if (not patterns.size()) {
    throw RecipeSyntaxError(Formatter() << "No patterns specified in recipe.");
  }

  Recipe recipe(patterns, initial, subsequent);
  return recipe;
}
