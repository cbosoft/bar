# Build and Run

A simple program to monitor files for changes, and run commands on changes. This
is very much influenced by the amazing [entr](http://eradman.com/entrproject/),
however there were a few changes I wanted to make, and I fancied a simple
project.

## Features

  - Initial command

    For builds like LaTeX documents, you might want a different initial command,
    one that has a more intensive build process, and then subsequent builds can
    be lightweight build commands (lacking the bibtex and makeindex calls in the
    latex example).

  - Configuration based setup

    Instead of having a script for each setup of entr, a config file defines the
    "recipes" (combinations of dependent files, and build commands). These
    config file live in the directory with the files you want to check, so all
    you need to do is change to the relevent directory and run "bar"!

  - Notifications by default

    entr has the ability to run a shell command, so this can do *anything*,
    including send out a notification. I ended up writing a *lot* of boilerplate
    in scripts using entr, so I wanted to remove that necessity in bar.

  - Expanded "change" definition

    entr reckons a change has occurred when a files is modified, however
    sometimes I want to force a change, so saving or touch-ing the file should
    be recognised as a change too. Although, this seems to have changed
    recently, good stuff!
