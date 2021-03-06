#include <limits.h>
#include <unistd.h>
#include <sys/inotify.h>

#include "recipe.hpp"

#define EVENT_SIZE          ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN       ( 1024 * ( EVENT_SIZE + NAME_MAX + 1) )

// written with help from https://gist.github.com/pkrnjevic/6016356

std::string Recipe::read_and_get_path(char *buffer, int bufflen)
{
  for (auto kv : this->fd2path) {
    if (read(kv.first, buffer, bufflen) > 0) return kv.second;
  }
  return "";
}

void Recipe::monitor()
{

  std::string changed = "";
  for (auto dependency : this->dependencies) {
    int fd = inotify_init1(IN_NONBLOCK);
    const char *dependency_cstr = dependency.c_str();
    fd_set watch_set;
    FD_ZERO(&watch_set);
    FD_SET(fd, &watch_set);
    inotify_add_watch(fd, dependency_cstr, IN_MODIFY | IN_ATTRIB);
    this->fd2path[fd] = dependency;
  }
  changed = this->fd2path.begin()->second;

  this->run_initial(changed);
  char buffer[EVENT_BUF_LEN];

  while (true) {

    changed = this->read_and_get_path(buffer, EVENT_BUF_LEN);
    while (not changed.size()) {
      changed = this->read_and_get_path(buffer, EVENT_BUF_LEN);
      usleep(100000);
    }

    struct inotify_event *event = (struct inotify_event *) &buffer[0];

    if ((event->mask & IN_MODIFY) or (event->mask & IN_ATTRIB)) {
      this->run_subsequent(changed);
    }

  }

}
