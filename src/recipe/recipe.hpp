#pragma once

#include <list>
#include <string>

class Recipe {

  private:

    std::list<std::string> dependencies;

    std::string initial_build;
    std::string subsequent_build;
    std::string on_error;

    void run_initial();
    void run_subsequent();
    void run_build(std::string command);

  public:

    Recipe(std::list<std::string> dependency_patterns,
        std::string command,
        std::string initial,
        std::string on_error);
    ~Recipe();

    void monitor();
};
