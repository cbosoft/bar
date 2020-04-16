#pragma once

#include <list>
#include <string>

class Recipe {

  private:

    std::list<std::string> dependencies;

    std::string initial_build;
    std::string subsequent_build;

    void run_initial();
    void run_subsequent();
    void run_build(std::string command);

  public:

    Recipe(std::list<std::string> dependency_patterns, std::string initial, std::string subsequent);
    ~Recipe();

    static Recipe from_file(std::string path);

    void monitor();
};
