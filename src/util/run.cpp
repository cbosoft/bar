#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#define SHELL "/bin/bash"

int run(std::string command, std::string &output, std::string &error)
{
  // I know I know, this is all a bit too plain "C"-ish. But hey, it works.

  const char *args[4] = {
    SHELL, "-c", NULL, NULL
  };

  args[2] = command.c_str();
  std::cerr << args[2] << std::endl;

  int sp_in[2], sp_out[2], sp_err[2];
  pipe(sp_in);
  pipe(sp_out);
  pipe(sp_err);

  int child_pid = fork();

  if (child_pid) {

    // in main process, close the input end of sp_in, and the output ends of
    // sp_out and sp_err.
    close(sp_in[0]);
    close(sp_out[1]);
    close(sp_err[1]);

  }
  else {

    // in child
    close(sp_in[1]);
    close(sp_out[0]);
    close(sp_err[0]);

    dup2(sp_in[0], STDIN_FILENO);
    dup2(sp_out[1], STDOUT_FILENO);
    dup2(sp_err[1], STDERR_FILENO);
    execvp(SHELL, (char* const*)args);
  }

  int status = 0;
  waitpid(child_pid, &status, 0);

  char buffer[100] = {0};
  while (read(sp_out[0], &buffer, 99)) {
    output += std::string(buffer);
  }

  while (read(sp_err[0], &buffer, 99)) {
    error += std::string(buffer);
  }

  return WEXITSTATUS(status);
}
