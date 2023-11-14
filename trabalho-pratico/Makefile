#START COPYRIGHT NOTICE

#   Copyright 2023 Hélder Gomes, João Lobo, Rita Camacho
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

#END COPYRIGHT NOTICE

CC := gcc

EXEC := programa-principal
FLAGS := -Wall -Wextra -Werror=pedantic -Wfatal-errors

LIBS := $(shell pkg-config --libs glib-2.0)
FLAGS += $(shell pkg-config --cflags glib-2.0)

SRC := $(shell find src/ -name "*.c")
INCLUDES := $(shell find include/ -name "*.h")

DOCS_DIRECTORY := docs

BUILD_TYPE ?= release
ifeq ($(BUILD_TYPE), debug)
	FLAGS += -g -O0
	BUILD_DIR_PATH := build/debug
	FLAGS += -Iinclude/
else ifeq ($(BUILD_TYPE), release)
	FLAGS += -O3
	BUILD_DIR_PATH := build/release
	FLAGS += -Iinclude/
endif

OBJ := $(addprefix $(BUILD_DIR_PATH)/, $(SRC:.c=.o))

RED := \033[1;31m
WHITE := \033[0m
BLUE := \033[1;34m
GREEN := \033[1;32m
PINK := \033[1;35m
GRAY := \033[1;30m

.PHONY: all
all: build-release place-build-on-root

build-debug:
	@printf "$(RED)[BUILD]$(WHITE) Debug build started.\n"
	@$(MAKE) BUILD_TYPE=debug build

build-release:
	@printf "$(GREEN)[BUILD]$(WHITE) Release build started.\n"
	@$(MAKE) BUILD_TYPE=release build

build: $(BUILD_DIR_PATH)/$(EXEC)

$(BUILD_DIR_PATH)/$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(FLAGS) -lm $(LIBS)
	@printf "$(BLUE)[COMPILER]$(WHITE) $(BLUE)$(EXEC) $(WHITE)compiled.\n"

$(BUILD_DIR_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)[COMPILER]$(WHITE) Compiling $(BLUE)$<$(WHITE).\n"
	@$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean-docs
clean-docs:
	@rm -rf $(DOCS_DIRECTORY)
	@echo "$(GRAY)[CLEAN]$(WHITE) Documentation directory removed."

.PHONY: clean
clean: clean-docs
	@rm -rf build;
	@rm -f programa-principal;
	@printf "$(GRAY)[CLEAN]$(WHITE) Build directory removed.\n"

.PHONY: format
format:
	@clang-format --verbose -i $(SRC) $(INCLUDES)
	@printf "$(PINK)[FORMATTER]$(WHITE) Formatted all available files.\n"

.PHONY: docs
docs:
	@printf "$(PINK)[DOCS]$(WHITE) Generating documentation.\n"
	@doxygen $(Doxyfile)
	@printf "$(GREEN)[DOCS]$(WHITE) Documentation generated in $(GREEN)$(DOCDIR)/$(WHITE) directory.\n"

place-build-on-root: build-release
	@cp $(BUILD_DIR_PATH)/$(EXEC) programa-principal
	@printf "$(GREEN)[BUILD]$(WHITE) Success, $(GREEN)$(EXEC) $(WHITE)ready on root.\n"