#        _  _  _ __   _ ______  ______
# |      |  |  | | \  | |_____] |     \
# |_____ |__|__| |  \_| |_____] |_____/
#

CC ?= gcc
# TODO: can't use -pedantic-errors yet due to LOG macros
# 
CFLAGS = -Iinclude -std=c99 -Wall -Wfatal-errors
DEBUG ?= 0

APP_VERSION := $(shell git describe --always --tags)
TARGET ?= unix
RONN = ronn
MANPAGE = lwnbd.3

include .env
include src/Makefile

ifeq ($(TARGET),unix)
include ports/unix/Makefile
endif

ifeq ($(TARGET),iop)
include ports/playstation2/iop.mk
endif

ifeq ($(TARGET),ee)
include ports/playstation2/ee.mk
endif

ifeq ($(LWNBD_DEBUG),0)
else ifeq ($(DEBUG),1)
	LWNBD_DEBUG = 1
endif

ifeq ($(LWNBD_DEBUG),1)
	CFLAGS += -DLWNBD_DEBUG
endif

$(BIN): banner $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS) $(LIBS)

$(MANPAGE): README.md
	$(RONN) -r --pipe $< > $@

banner:
	@echo "       _  _  _ __   _ ______  ______"
	@echo "|      |  |  | | \\  | |_____] |     \\"
	@echo "|_____ |__|__| |  \\_| |_____] |_____/"
	@echo
	@echo -e "library version $(APP_VERSION) - BSD 2-Clause License\n"

clean:
	rm -f $(BIN) $(MANPAGE) $(OBJ) *~ core 

nbdcleanup:
	sudo lsof -t /dev/nbd* | sudo xargs -r kill -9

# hackish but let you check/format same way both CI and your own env.
# and manage .clang-format-ignore file properly.
cfla = $(WORKSPACE)/tools/clang-format-lint-action
check:
	@python3 $(cfla)/run-clang-format.py --clang-format-executable $(cfla)/clang-format/clang-format14 -r .

format:
	@python3 $(cfla)/run-clang-format.py --clang-format-executable $(cfla)/clang-format/clang-format14 -r . -i true

.PHONY: all clean test