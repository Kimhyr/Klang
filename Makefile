NAME=kc

# Directories
SRCD=./Source
BLDD=./Build
OBJD=$(BLDD)/Objects
DIRS=. Analyzer Utilities

# Files
SRCS=$(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.CPP))
OBJS=$(patsubst $(SRCD)/%.CPP,$(OBJD)/%.OBJ,$(SRCS))
BIN=$(BLDD)/$(NAME).EXE

# Build
CC=clang++
CFLGS=-std=c++20 -O3
WFLGS=-Wall -Wextra
FLGS=$(CFLGS) $(WFLGS) $(IFLGS)

all:$(BIN)

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LFLGS)

$(OBJD)/%.OBJ:$(SRCD)/%.CPP
	$(CC) -c $^ -o $@ $(FLGS)

r:$(BIN)
	clear
	$(BIN)

c:$(BLDD)
	rm -rf $(OBJS) $(BIN)

f:
	clang-format -i $(SRCS) $(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.H))

.PHONY:all r c f
