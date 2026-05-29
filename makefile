NAME = enchanter
VER_MAJOR = 0
VER_MINOR = 0
VER_CUTOFF_COMMIT = fee7068e379deafd8b33d76be17acb4f8846db29

RAYLIB_VER = 6.0
CPP_STD = c++20

TARGET = linux_amd64
VALID_TARGETS := webassembly linux_amd64

BINARY = bin/$(NAME)
RLDIR = lib/raylib-$(RAYLIB_VER)_$(TARGET)
RLBIN = $(RLDIR)/lib/libraylib.a

CC = g++
LFLAGS = $(RLDIR)/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -I$(RLDIR)/include -std=$(CPP_STD) \
	-W -Wall -Wextra -Werror \
	-pedantic -fexceptions

# Make sure the build target is valid
ifeq (,$(findstring $(TARGET) , $(VALID_TARGETS) ))
$(error Invalid build target, valid targets are: $(VALID_TARGETS))
endif

#########################################
# Calculated compiler/linker flags
#########################################

#Try to compile for our specific architecture
ifneq (,$(findstring mingw,$(CC)))
OS = Windows_NT
endif

ARCH = $(shell $(CC) -dumpmachine)

BITS =
ifeq ($(findstring x86_64,$(ARCH)),x86_64)
BITS = 64
else
ifeq ($(findstring i686,$(ARCH)),i686)
BITS = 32
endif
endif
ifeq ($(BITS),)
CCTARGET =
else
CCTARGET = -m$(BITS)
endif

CFLAGS += $(CCTARGET)

ifneq (,$(findstring $(TARGET),webassembly))
# Calculate flags for webassembly target
CC = em++
LFLAGS += -sUSE_GLFW=3
CFLAGS += -DPLATFORM_WEB
BINARY = bin/$(NAME).js

# Debug webassembly flags
ifdef DEBUG
CFLAGS += -O0 -DDEBUG
LFLAGS += --emrun
BINARY = bin/$(NAME).html
else
CFLAGS += -Os
endif

else
# Not targeting web

ifdef DEBUG
CFLAGS += -g$(DEBUG) -O0 -DDEBUG
else
CFLAGS += -O3
endif

endif

#Auto-calculate patch version based on current commit.
#If patch version can't be calculated, just use the OS name.
LATEST_COMMIT = $(shell git rev-parse HEAD)
ifeq ($(LATEST_COMMIT),)
ifeq ($(OS),Windows_NT)
VER_PATCH = windows
else
VER_PATCH = linux
endif
else
VER_PATCH = $(shell git rev-list --count $(VER_CUTOFF_COMMIT)..HEAD^)
endif

D0 = $(sort $(dir $(wildcard src/*/)))
D1 = $(sort $(dir $(wildcard $(D0)*/)))
DIRS := $(sort $(dir $(wildcard $(D1)*/)) $(D0) $(D1) )
SRCS := $(wildcard $(addsuffix *.cpp, $(DIRS)))
HEADERS := $(wildcard $(addsuffix *.hpp, $(DIRS))) $(wildcard src/*.hpp)
OBJS := $(patsubst src/%.cpp,obj/%.o,$(SRCS))
DEPENDS := $(patsubst src/%.cpp,obj/%.d,$(SRCS))

#########################################
# Phony rules and documentation
#########################################

.PHONY: main clean pristine get-version get-revision format try-format dox docs count-loc

main: $(BINARY) $(RLDIR)

clean:
	rm -rf bin obj

pristine: clean
	rm -rf lib emsdk

get-version:
	@echo $(VER_MAJOR).$(VER_MINOR).$(VER_PATCH)

get-revision:
	git rev-parse HEAD

lint: lint.log
	@cat $^

lint.log: $(HEADERS)
	@find z/ -type f \( -name '*.cpp' -or -name '*.hpp' \) -not -name '*Constructors.hpp' -not -name 'utf*.hpp' -not -name 'ascii.hpp' -not -name 'shared.hpp' | xargs -P8 -I{} clang-tidy {} -header-filter=.* -- -std=c++17 -m64 -W -Wall -Wextra -Wno-psabi -Werror -pedantic -fexceptions -fPIC -fdata-sections -ffunction-sections -O3 -Wno-unused-private-field > lint.log 2>/dev/null || { cat $@; [ "$$(cat $@)" = '' ] && echo 'ERROR: Is clang-tidy installed?' && rm $@ -f; exit 1; }

format:
	find . -type f \( -name '*.cpp' -or -name '*.hpp' \) -not -name 'catch_amalgamated.*' | xargs -P8 -I{} sh -c 'echo Formatting {}; clang-format -i {}'

try-format:
	@find . -type f \( -name '*.cpp' -or -name '*.hpp' \) -not -name 'catch_amalgamated.*' | xargs -P8 -I{} sh -c 'clang-format --dry-run -Werror -i {}'

dox: docs
docs: html
	@cat doxygen.log

html: $(HEADERS) Doxyfile $(wildcard Doxypages/*.dox) Doxypages/examples.dox $(wildcard examples/src/*.cpp) README.md
	$(RMDIR) html
	PROJECT_NUMBER=$(VER_MAJOR).$(VER_MINOR).$(VER_PATCH) doxygen

count-loc:
	@find src -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} +

#########################################
# Actual rules
#########################################

# Web build
bin/$(NAME).html: $(OBJS) | bin/$(NAME).js
	$(CC) -o $@ $^ $(LFLAGS)

bin/$(NAME).js: $(OBJS) | bin/$(NAME).wasm
	$(CC) -o $@ $^ $(LFLAGS)

bin/$(NAME).wasm: $(OBJS) $(RLBIN) | bin
	$(CC) -o $@ $^ $(LFLAGS)

# Linux build
bin/$(NAME): $(OBJS) $(RLBIN) | bin
	$(CC) -o $@ $^ $(LFLAGS)

# Objects
obj/main.o: src/main.cpp | obj $(RLDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.cpp src/%.hpp | obj
	$(CC) $(CFLAGS) -o $@ -c $<

# Raylib rules.
# The exact version of raylib will change depending on the target environment.

$(RLDIR): $(RLBIN)

lib/raylib-$(RAYLIB_VER)_linux_%/lib/libraylib.a: lib/raylib-$(RAYLIB_VER)_linux_%.tar.gz
	tar xzf $< -C lib/

lib/raylib-$(RAYLIB_VER)_%/lib/libraylib.a: lib/raylib-$(RAYLIB_VER)_%.zip
	unzip $< -d lib/

lib/raylib-$(RAYLIB_VER)_webassembly/lib/libraylib.a: lib/raylib-$(RAYLIB_VER)_webassembly.zip
	unzip $< -d lib/
	mv $(dir $@)/libraylib.web.a $@

lib/raylib-%.tar.gz: | lib
	wget https://github.com/raysan5/raylib/releases/download/$(RAYLIB_VER)/$(notdir $@) -O $@

lib/raylib-%.zip: | lib
	wget https://github.com/raysan5/raylib/releases/download/$(RAYLIB_VER)/$(notdir $@) -O $@

# Directory rules.
# These make sure the directories exist without rebuilding if their contents change.

bin: bin/.sentinel
obj: obj/.sentinel
lib: lib/.sentinel

%/.sentinel:
	mkdir -p $(dir $@)
	@touch $@

