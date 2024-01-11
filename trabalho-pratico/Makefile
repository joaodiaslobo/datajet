CC := gcc

EXEC := programa-principal
FLAGS := -Wall -Wextra -Werror=pedantic -Wfatal-errors -Wno-unused-variable -Wno-unused-parameter

LIBS := $(shell pkg-config --libs glib-2.0)
FLAGS += $(shell pkg-config --cflags glib-2.0)

SRC := $(shell find src/ -name "*.c")
INCLUDES := $(shell find include/ -name "*.h")

DOCS_DIRECTORY := docs

# Defines flags depending on the build type
BUILD_TYPE ?= release
ifeq ($(BUILD_TYPE), debug)
	FLAGS += -g -O0
	BUILD_DIR_PATH := build/debug
	FLAGS += -Iinclude/
else ifeq ($(BUILD_TYPE), release)
	FLAGS += -O3 -flto -funroll-loops
	BUILD_DIR_PATH := build/release
	FLAGS += -Iinclude/
endif

OBJ := $(addprefix $(BUILD_DIR_PATH)/, $(SRC:.c=.o))

# Colors used for output
ifneq (,$(findstring xterm,${TERM}))
	RED := $(shell tput -Txterm setaf 1)
	WHITE := $(shell tput -Txterm setaf 7)
	BLUE := $(shell tput -Txterm setaf 6)
	GREEN := $(shell tput -Txterm setaf 2)
	PINK := $(shell tput -Txterm setaf 5)
	GRAY := $(shell tput -Txterm setaf 6)
else
	RED := ""
	WHITE := ""
	BLUE := ""
	GREEN := ""
	PINK := ""
	GRAY := ""
endif

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