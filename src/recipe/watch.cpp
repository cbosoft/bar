#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <sys/inotify.h>

#include "recipe.hpp"

#define EVENT_SIZE          ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN       ( 1024 * ( EVENT_SIZE + NAME_MAX + 1) )

// written with help from https://gist.github.com/pkrnjevic/6016356

void Recipe::monitor()
{
  int fd = inotify_init1(IN_NONBLOCK);

  // checking for error
  if (fd < 0) {
    perror("inotify_init");
  }

  fd_set watch_set;
  FD_ZERO(&watch_set);
  FD_SET(fd, &watch_set);

  for (auto dependency : this->dependencies) {
    const char *dependency_cstr = dependency.c_str();
    inotify_add_watch(fd, dependency_cstr, IN_MODIFY | IN_ATTRIB);
  }

  this->run_initial();
  char buffer[EVENT_BUF_LEN];
  int length;
  while (true) {

    length = read(fd, buffer, EVENT_BUF_LEN);
    while (length < 0) {
      length = read(fd, buffer, EVENT_BUF_LEN);
      usleep(100000);
    }

    // Loop through event buffer
    for (int i = 0; i < length;) {
      struct inotify_event *event = (struct inotify_event *) &buffer[i];
      
      if ((event->wd == -1) or (event->mask & IN_Q_OVERFLOW)) {
	      break;
    	}

      if ((event->mask & IN_MODIFY) or (event->mask & IN_ATTRIB)) {
        this->run_subsequent();
        break;
      }

      i += EVENT_SIZE + event->len;
    }
  }

}
