CC := gcc
CFLAGS += -Wall -g -std=c99 -pedantic $(includes)

all_sources := $(wildcard $(src_folder)/*.c)
all_objects := $(patsubst $(src_folder)/%.c,%.o,$(all_sources))

all_executes := $(patsubst $(src_folder)/%.c,%,$(all_sources))

.PHONY: all clean help
all:

# automatic prerequisites (working for both lib and app) ########
autodependence := $(patsubst $(src_folder)/%.c,%.d,$(all_sources))
ifneq "$(MAKECMDGOALS)" "clean"
include $(autodependence)
endif
%.d: $(src_folder)/%.c
	set -e; rm -f $@; $(CC) -M $(CFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

%.o: $(src_folder)/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
