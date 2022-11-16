NAME=kplc
EXT=cpp
CC=clang++

SRC=./Source
OUT=./Output
OBJ=$(OUT)/Objects
BIN=$(OUT)/$(NAME).exe

DIRS=. Analyzer Utils
INCS=$(foreach D,$(DIRS),$(SRC)/$(D))
SRCS=$(foreach D,$(INCS),$(wildcard $(D)/*.$(EXT)))
OBJS=$(patsubst $(SRC)/%.$(EXT),$(OBJ)/%.obj,$(SRCS))

EFLGS=-std=c++20 -O3
WFLGS= -Wall -Wextra -pedantic
FLGS=$(EFLGS) $(WFLGS) $(foreach D,$(INCS),-I$(D))

all:$(BIN)

run:$(BIN)
	$(BIN)

test:$(BIN)
	$(BIN) /workspaces/KPLC/Tests/Basic.kpl

$(BIN):$(OBJS)
	$(CC) $^ -o $@

$(OBJ)/%.obj:$(SRC)/%.$(EXT)
	$(CC) -c $^ -o $@ $(FLGS)

clean:
	rm -rf $(OUT)/*
	mkdir $(OBJ)
	mkdir $(foreach D,$(DIRS),$(OBJ)/$(D))
#	powershell "Get-ChildItem '.\Output\*.*' -Recurse -Force | Remove-Item"

diffs:
	@git status
	@git diff --stat

.PHONY:all clean diff
