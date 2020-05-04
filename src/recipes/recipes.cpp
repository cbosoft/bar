#include "recipes.hpp"

Recipes::Recipes(std::list<Recipe> recipes)
  :
    recipes(recipes)
{
}

Recipes::~Recipes()
{
  for (auto & thread : this->threads) {
    thread.join();
  }
}
