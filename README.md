# Build and Run

A simple program to monitor files for changes, and run commands on changes. This
is very much influenced by the amazing [entr](http://eradman.com/entrproject/),
however there were a few changes I wanted to make, and I fancied a simple
project.

## Changes over entr

  - Initial command

    For builds like LaTeX documents, you might want a different initial command,
    one that has a more intensive build process.

  - Configuration based setup

    Instead of having a script for each setup of entr, a config file defines the
    "recipes" (combinations of dependent files, and build commands).

  - Expanded "change" notification

    entr reckons a change has occured when a files is modified, however
    sometimes I want to force a change, so saving or touch-ing the file should
    be recognised as a change too.
