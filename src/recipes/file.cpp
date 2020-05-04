#include <iostream>
#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "recipes.hpp"

std::string strip_whitespace(std::string s)
{
  auto cdata = s.data();
  int len = s.size();

  std::stringstream ss;
  int i = 0;
  while ((cdata[i] == ' ') or (cdata[i] == '\t')) i++;
  for (; i < len; i++) {
    ss << cdata[i];
  }

  return ss.str();
}

Recipes Recipes::from_file(std::string path)
{

  std::fstream infile(path);
  if (infile.fail()) {
    throw IOError(Formatter() << "Failed to open recipe file: " << path, true);
  }

  std::string command, initial, on_error;
  std::list<std::string> patterns;
  std::list<Recipe> recipes;
  bool reading = false;

  for (std::string line; std::getline(infile, line); ) {
    std::stringstream ss(line);

    std::string key, value;
    std::getline(ss, key, ':');
    std::getline(ss, value, ':');

    value = strip_whitespace(value);

    if (key.compare("command") == 0) {
      command = value;
    }
    else if (key.compare("initial") == 0) {
      initial = value;
    }
    else if (key.compare("pattern") == 0) {
      patterns.push_back(value);
    }
    else if (key.compare("on_error") == 0) {
      on_error = value;
    }
    else if (line.compare("---") == 0) {
      if (reading) {
        recipes.push_back(Recipe(patterns, command, initial, on_error));
        command = "";
        initial = "";
        on_error = "";
        patterns = std::list<std::string>();
      }
    }
    else {
      std::cerr << "warning: unknown key found in config: " << key << "." << std::endl;
    }

    reading = true;
  }

  recipes.push_back(Recipe(patterns, command, initial, on_error));
  return Recipes(recipes);
}

