# rshell

Welcome to Rshell. This is a basic command prompt!

As of right now, it is under construction. But here are some basic things that you need to know:

1. The command prompt prints your username, followed by the name of the hostname os the machine.

2. The command prompt can only take in one command at a time, so you cannot use connectors such as || or && or ;

3. Comments can be placed anywhere in the command such as "ls -a#this is the ls command ".

## Features (ls)

* accepts -a as a parameter (lists hidden files)
* accepts -l as a parameter (lists lots of info about the files and directories, as well as a cumulative block count of the things printed)
* accepts any number of files/directories to print
* parameters and flags are dynamic

## Bugs (ls)
* compared to the GNU ls, I sort things differently. I sort everything alphabetically including the preceding periods. GNU ls sorts everything based on the first letter, ignoring preceding periods
* ls -l contains a bug if you make a dot file or directory.
* lS -R does not work
* does not contain the colors 

Sorry for the inconveniences. It is a work in progress.  
