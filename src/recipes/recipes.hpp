#pragma once

#include <list>
#include <string>
#include <thread>

#include "../recipe/recipe.hpp"

class Recipes {

  private:
    std::list<Recipe> recipes;
    std::list<std::thread> threads;

  public:

    Recipes(std::list<Recipe> recipes);
    ~Recipes();

    static Recipes from_file(std::string path);
    void monitor();
};
