#include "recipe.hpp"
#include "../util/run.hpp"
#include "../util/notify.hpp"
#include "../util/exception.hpp"

void Recipe::run_initial()
{
  if (this->initial_build.size()) {
    this->run_build(this->initial_build);
  }
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
    std::stringstream ss;
    ss << command << " returned with error";

    if (this->on_error.size()) {
      run(this->on_error, out, err);
      ss << ": " << out;
    }

    ss << ".\n";
    notify("Build failed!", ss.str(), "critical", 60000);
  }
  else {
    notify("Build complete.", command, "normal");
  }
}
