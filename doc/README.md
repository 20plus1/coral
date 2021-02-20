# Coral

A simple consistent compilation framework based on Makefiles.

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
No source file contains the main function.

A tool is a directory containing a Makefile file, some source files and some sub-directories; each sub-directory can potentially be a module by itself.
Tools can only contain modules.
one of the source files in tool directory contains the main function.

Modules can not contain tools.

Compiling a module generates a main library and some sub-libraries, each sub-directory corresponds to a sub-library; compiling a tool generates an executable and some sub-libraries, each sub-directory corresponds to a sub-library.

### module and library

The name of the module directory is used as a part of the name of the library.

For example, if a module is located at _/PATH/TO/A/MODULE/net_, the name of the generated library will be libnet.a, e.g. _/PATH/TO/OUTPUT/LIBRARY/DIR/libnet.a_.

If the module contains some sub-modules, each sub-module will be used to generate corresponding library.

For example, if there are two sub-modules in _/PATH/TO/A/MODULE/net_: _/PATH/TO/A/MODULE/net/ipv4_ and _/PATH/TO/A/MODULE/net/ipv6_, then two libraries, _/PATH/TO/OUTPUT/LIBRARY/DIR/libipv4.a_ and _/PATH/TO/OUTPUT/LIBRARY/DIR/libipv6.a_, will be generated.

As you may already noticed, all the libraries, including root-library and sub-libraries, are all located in the same output directory, e.g. _/PATH/TO/OUTPUT/LIBRARY/DIR/_, as a result, the name of the module need to be unique across the whole project.

The parent module contains all the contents in all his children modules.
In the above example, _libnet.a_ contains all the object files (_.o_ file) in both _libipv4.a_ and _libipv6.a_.

In this repo, the default library output path is _/PROJECT_ROOT/_prod/lib/_.

### tool and executable

Each tool directory at least contains a source file. tool directory can contains multiple source files, there should be exact one source file containing the main function.

If the tool directory contains some sub-modules, each sub-module will generate a corresponding library which is located in the same project-scope library output directory, e.g. the above _/PATH/TO/OUTPUT/LIBRARY/DIR/_.

A tool usually depends on some modules not located inside its directory, then we need to explicitly specify the dependences in the Makefile of the tool, e.g. _/PATH/TO/A/TOOL/checknet/Makefile_.

The output of compiling a tool directory is an executable.

In this repo, the default tool output path is _/PROJECT_ROOT/_prod/bin/_.

### Single Complete Dependence Graph

There are two styles of using Makefile:
1. calling `make -C /ANOTHER/PATH` in recipts of rules.
2. not calling `make -C /ANOTHER/PATH` in recipts of rules.

Coral is style 2.

There is a Makefile in each tool or module directory, which is the root Makefile.
It's ok to execute `make` in any tool or module directory, and `make` will do the right thing.

Each time executing `make` command in a tool or module directory, `make` will read the root Makefile, as well as all the Makefiles included in the root Makefile; after reading all the Makefiles, `make` will construct a dependence graph and start to executing recipes according to the graph.

### Single root header directory

To make the coral simple, all the header files are placed in one root header directory.

How to structure the root header directory is up to you.

In the project, by default, the root header directory is _/PROJECT_ROOT/src/h/_, and there is no sub directory in the root header directory; all the header files are directly placed in the root header directory; the `-I/PROJECT_ROOT/src/h` is added to the command of compiling _.c_ to _.o_; as a result, all _.c_ files include header files in the way of `#include "header.h"`, instead of `#include "path/to/header.h"`.

### Do nothing to OS



## Examples

### Example 1
Directory _A_ is a module containing _a1.c_ and sub-directories _AB_ & _AC_; _AB_ contains _ab1.c_ and _ab2.c_, _AC_ contains _ac1.c_ and _ac2.c_.

`cd /PATH/TO/A && make` or `make -C /PATH/TO/A` will generate
1. _/PATH/TO/lib/libA.a_, which archives _a1.o_, _ab1.o_, _ab2.o_, _ac1.o_ and _ac2.o_.
2. _/PATH/TO/lib/libAC.a_, which archives _ac1.o_ and _ac2.o_.
3. _/PATH/TO/lib/libAB.a_, which archives _ab1.o_ and _ab2.o_.
4. _/PATH/TO/objs/A/a1.o_
5. _/PATH/TO/objs/A/AB/ab1.o_
5. _/PATH/TO/objs/A/AB/ab2.o_
5. _/PATH/TO/objs/A/AC/ac1.o_
5. _/PATH/TO/objs/A/AC/ac2.o_

## How to add a new libray

create a directory, put the following Makefile into the directory.
```
```

## How to add a new executable

create a directory, put the following Makefile into the directory.
```
```

