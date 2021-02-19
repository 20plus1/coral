# Coral

A simple consistent compilation structure based on Makefiles.

This project is suitable for compiled languages, typically C programming language, and Unix-like OS, typically Linux.

## Philosophy of Coral

1. simplicity
2. consistency

## The idea behind

### modules and tools

The output of a typical C project on Linux is libraries(static or dynamic) and executables.

Correspondingly, two concepts are defined in Coral: modules and tools.

A module is a directory containing a Makefile file, some source files and some sub-directories; each sub-directory can potentially be a module by itself.
Modules can only contain modules.

A tool is a directory containing a Makefile file, some source files and some sub-directories; each sub-directory can potentially be a module by itself.
Tools can only contain modules.

Modules can not contain tools.

Compiling a module generates a main library and some sub-libraries; compiling a tool generates an executable and some sub-libraries.

For example, Directory A is a module containing a1.c and sub-directories AB & AC; AB contains ab1.c and ab2.c, AC contains ac1.c and ac2.c.

cd /PATH/TO/A && make or make -C /PATH/TO/A will generate
1. /PATH/TO/lib/libA.a, which archives a1.o, ab1.o, ab2.o, ac1.o and ac2.o.
2. /PATH/TO/lib/libAC.a, which archives ac1.o and ac2.o.
3. /PATH/TO/lib/libAB.a, which archives ab1.o and ab2.o.
4. /PATH/TO/objs/A/a1.o
5. /PATH/TO/objs/A/AB/ab1.o
5. /PATH/TO/objs/A/AB/ab2.o
5. /PATH/TO/objs/A/AC/ac1.o
5. /PATH/TO/objs/A/AC/ac2.o

### Single Makefile

### Single header directory

### Single output directory

### Do nothing to OS

## How to add a new libray

create a directory, put the following Makefile into the directory.
```
```

## How to add a new executable

create a directory, put the following Makefile into the directory.
```
```

