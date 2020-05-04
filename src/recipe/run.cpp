#include "recipe.hpp"
#include "../util/run.hpp"
#include "../util/notify.hpp"
#include "../util/exception.hpp"

void Recipe::run_initial()
{
  this->run_build(this->initial_build);
}

void Recipe::run_subsequent()
{
  this->run_build(this->subsequent_build);
}

void Recipe::run_build(std::string command)
{
  std::string out, err;
  
  notify("Build started...", command, "normal");

  int rc = run(command, out, err);
  std::cerr << out << "\n" << err << std::endl;

  if (rc) {
    notify("Build failed!", Formatter() << command << " returned with erorr (" << rc << ").\n", "critical", 60000);
  }
  else {
    notify("Build complete.", command, "normal");
  }
}
