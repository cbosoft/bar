#include <iostream>
#include <sstream>
#include <errno.h>
#include <string.h>

#include "notify.hpp"
#include "run.hpp"

void notify(std::string title, std::string body, std::string urgency, int timeout)
{

  std::cerr << urgency << "| " << title << ": " << body << std::endl;

  std::stringstream ss;
  ss << "notify-send -u " << urgency;

  if (timeout > 0) {
    ss << " -t " << timeout;
  }

  ss <<" \"" << title << "\" \"" << body << "\"";

  std::string err, out, cmd=ss.str();
  int rc = run(cmd, out, err);

  if (rc) {
    std::cerr << "notify failed! (" << rc << "/" << errno << "): " << strerror(errno) << std::endl;
  }
}
