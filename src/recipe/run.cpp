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
  int rc = run(command, out, err);

  if (rc) {
    notify("Build failed!", Formatter() << "process returned with erorr (" << rc << "):\n" << out << "\n" << err, "critical", 60000);
  }
  else {
    notify("Build complete.", Formatter() << out << "\n" << err, "normal");
  }
}
