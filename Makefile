CC := gcc
CFLAGS := -Wall -Wextra  -pedantic -MMD -MP -g3
LDFLAGS := -lm -fsanitize=address

# Libs
CFLAGS += $(shell pkg-config --cflags sdl2)
LDFLAGS += $(shell pkg-config --libs sdl2)
CFLAGS += $(shell pkg-config --cflags SDL2_image)
LDFLAGS += $(shell pkg-config --libs SDL2_image)
CFLAGS += $(shell pkg-config --cflags SDL2_ttf)
LDFLAGS += $(shell pkg-config --libs SDL2_ttf)
CFLAGS += $(shell pkg-config --cflags SDL2_mixer)
LDFLAGS += $(shell pkg-config --libs SDL2_mixer)
CFLAGS += $(shell pkg-config --cflags jansson)
LDFLAGS += $(shell pkg-config --libs jansson)

# Directories
SRCDIR := src
BUILDDIR := build
TARGET := bin/game

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/engine/*.c) $(wildcard $(SRCDIR)/engine/structures/*.c) $(wildcard $(SRCDIR)/scenes/**/*.c) $(wildcard $(SRCDIR)/entities/**/*.c) $(wildcard $(SRCDIR)/weapons/**/*.c) 
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TEST_SRCS =  $(filter-out src/main.c, $(SRCS)) $(wildcard $(SRCDIR)/tests/*.c)
TEST_OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(TEST_SRCS))
TEST_DEPS = $(TEST_OBJS:.o=.d)

# Default target
.PHONY: all
all: $(TARGET)
	@mkdir -p bin/scenes
	@find src/scenes/ -name '*.json' -exec cp {} bin/scenes/ \;
	@cp src/assets/dialogs.json bin/

.PHONY: run
run: all
	./$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(TEST_DEPS)

.PHONY: test
test: $(TEST_OBJS)
	@echo $(TEST_OBJS)
	@mkdir -p bin/scenes
	@find src/scenes/ -name '*.json' -exec cp {} bin/scenes/ \;
	@cp src/assets/dialogs.json bin/
	@mkdir -p $(@D)
# $(CC) $(CFLAGS) $^ -o $(BUILDDIR)/run_tests $(LDFLAGS)
	$(CC) $(TEST_OBJS) -o bin/run_tests $(LDFLAGS)
	./bin/run_tests

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	rm -rf bin/*

