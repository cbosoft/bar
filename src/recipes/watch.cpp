#include "recipes.hpp"

void Recipes::monitor()
{
  for (auto recipe : recipes) {
    threads.push_back(std::thread(&Recipe::monitor, recipe));
  }
}
