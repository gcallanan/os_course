# Tree Structure Demonstration

## Introduction

Commands demonstrating the linux tree structure and symbolic links

This file was written by Gareth Callanan and is intended for use in the operating systems course. Everything here has been tested on a system running the "Ubuntu 20.04.6 LTS" Operating System. Ubuntu is distribution of the Linux OS. All these commands are intended to be run from the terminal.

It is required that the "tree" package be installed on your system. Install by running the command: `sudo apt-get install tree`

## Commands 

Lets start by making some recursive folder structure. Run the following commands:
1. `mkdir treeDir1`
2. `cd treeDir1`
3. `mkdir treeDir2`
4. `cd treeDir2/`
5. `ln -s ../../treeDir1/ treeDir3`

Here we create a folder treeDir1 and a sub-folder treeDir2 within treeDir1. Within treeDir2 we create a **symbolic link** called treeDir3 that we link back to treeDir1. If you run `ls -latr` from treeDir2, you should see: 

    ... treeDir3 -> ../../treeDir1/

This shows how treeDir3 actually links to treeDir1. If you enter treeDir3 (`cd treeDir3`), which directory do you expect to end up in? If you view the directoy (`ls -latr`) do you see treeDir2? What does this tell you about the directory we are in?

To view the folder tree structure, run the ``tree` command from the terminal. If you run this from the directory containing treeDir1, do you see something like this?

    └── treeDir1"
        └── treeDir2"
            └── treeDir3 -> ../../treeDir1/"
    
View tree structure of entire user directory: `cd` and `tree -L 3` (-L limits us to only 3 layers of directories, this makes the output more manegable).