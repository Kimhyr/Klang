# This Makefile was taken from
# [https://gist.github.com/mauriciopoppe/de8908f67923091982c8c8136a063ea6].

CC=clang++

# Directories
SRCDIR=./Source
BLDDIR=./Build

# Extensions
SRCEXT=cpp
HDREXT=h

# Files
BIN=klang.exe
SRCS=$(shell find $(SRCDIR) -name '*.$(SRCEXT)' | sort -k 1nr | cut -f2-)
OBJS=$(SRCS:$(SRCDIR)/%.$(SRCEXT)=$(BLDDIR)/%.obj)
DEPS=$(OBJS:.obj=.d)

# Flags
FLGS=-O2 -std=c++20 -Wall -Wextra -g
INCS=
LIBS=

.PHONY:default
default:release

.PHONY:release
release:dirs
	@$(MAKE) all

.PHONY:dirs
dirs:
	@echo "Creating directories..."
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(BLDDIR)

.PHONY:r
r:default
	./$(BIN)

.PHONY:c
c:
	@echo "Deleting $(BIN) symlink..."
	@$(RM) $(BIN)
	@echo "Deleting directories..."
	@$(RM) -r $(BLDDIR)
	@$(RM) ./$(BIN)

.PHONY:all
all:$(BLDDIR)/$(BIN)
	@echo "Making symlink for $(BIN) -> $<..."
	@$(RM) $(BIN)
	@ln -s $(BLDDIR)/$(BIN) $(BIN)

$(BLDDIR)/$(BIN):$(OBJS)
	@echo "Linking $@..."
	$(CC) $(OBJS) -o $@ ${LIBS}

-include $(DEPS)

$(BLDDIR)/%.obj: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $< -> $@..."
	$(CC) $(FLGS) $(INCS) -MP -MMD -c $< -o $@

