CURRENT_DIR = $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
DIRS = mod1 tool1
include $(addsuffix /Makefile,$(addprefix $(CURRENT_DIR)/,$(DIRS)))
