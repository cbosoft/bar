#include "recipe.hpp"
#include "../util/run.hpp"
#include "../util/notify.hpp"
#include "../util/exception.hpp"
#include "../util/replace.hpp"


void Recipe::run_initial(std::string changed)
{
  if (this->initial_build.size()) {
    this->run_build(this->initial_build, changed);
  }
}

void Recipe::run_subsequent(std::string changed)
{
  this->run_build(this->subsequent_build, changed);
}

void Recipe::run_build(std::string command, std::string changed)
{
  std::string out, err;

  if (changed.size()) {
    command = replace(command, "<FILE>", changed);
    std::string noext = replace(changed, "(\\.\\w+)$", "");
    command = replace(command, "<FILE_NOEXT>", noext);
  }

  notify("Build started...", command, "normal");

  int rc = run(command, out, err);

  if (rc) {
    std::stringstream ss;
    ss << command << " returned with error";

    if (this->on_error.size()) {
      run(this->on_error, out, err);
      ss << ": " << out;
    }
    else {
      std::cerr << out << "\n" << err << std::endl;
    }

    ss << ".\n";
    notify("Build failed!", ss.str(), "critical", 60000);
  }
  else {
    notify("Build complete.", command, "normal");
  }
}
