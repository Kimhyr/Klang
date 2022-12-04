NAME=kplc

# Directories
SRCD=./Source
OUTD=./Output
OBJD=$(OUTD)/Objects
DIRS=. Compiler/Analyzer Utility/Collections Utility/Eceptions Utility/System Utility/Text

# Files
SRCS=$(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.cpp))
OBJS=$(patsubst $(SRCD)/%.cpp,$(OBJD)/%.obj,$(SRCS))
BIN=$(OUTD)/$(NAME).exe

# Build command
CC=clang++
CFLGS=-std=c++20 -O3
WFLGS=-Wall -Wextra -Werror
LFLGS=
IFLGS=$(foreach D,$(DIRS),-I$(D))
FLGS=$(CFLGS) $(WFLGS) $(IFLGS)

all:$(BIN)

run:$(BIN)
	$(BIN)

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LFLGS)

$(OBJD)/%.obj:$(SRCD)/%.cpp
	$(CC) -c $^ -o $@ $(FLGS)

clean:$(OUTD)
	$(shell powershell "Get-ChildItem -Recurse $(OUTD) -File | Remove-Item")

dirs:
	$(foreach D,$(DIRS),$(shell powershell New-Item $(OBJD)/$(D) -ItemType Directory))

.PHONY:all run clean dirs
