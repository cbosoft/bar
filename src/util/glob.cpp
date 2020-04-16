#include <glob.h> // glob(), globfree()
#include <string.h> // memset()
#include <stdexcept>
#include <sstream>
#include <list>
#include <string>

// https://stackoverflow.com/questions/8401777/simple-glob-in-c-on-unix-system

std::list<std::string> glob(const std::string& pattern) {

  // glob struct resides on the stack
  glob_t glob_result;
  memset(&glob_result, 0, sizeof(glob_result));

  // do the glob operation
  int return_value = glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
  if(return_value != 0) {
    globfree(&glob_result);
    std::stringstream ss;
    ss << "glob() failed with return_value " << return_value << std::endl;
    throw std::runtime_error(ss.str());
  }

  // collect all the filenames into a std::list<std::string>
  std::list<std::string> filenames;
  for(size_t i = 0; i < glob_result.gl_pathc; ++i) {
    filenames.push_back(std::string(glob_result.gl_pathv[i]));
  }

  // cleanup
  globfree(&glob_result);

  // done
  return filenames;
}

