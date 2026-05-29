NAME = enchanter
VER_MAJOR = 0
VER_MINOR = 0
VER_CUTOFF_COMMIT = fee7068e379deafd8b33d76be17acb4f8846db29

RAYLIB_VER = 6.0

TARGET = linux_amd64
VALID_TARGETS := webassembly linux_amd64

BINARY = bin/$(NAME)
RLDIR = lib/raylib-$(RAYLIB_VER)_$(TARGET)
RLBIN = $(RLDIR)/lib/libraylib.a

CC = g++
LFLAGS = $(RLDIR)/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -I$(RLDIR)/include -std=c++20

OBJECTS = obj/main.o

# Make sure the build target is valid
ifeq (,$(findstring $(TARGET) , $(VALID_TARGETS) ))
$(error Invalid build target, valid targets are: $(VALID_TARGETS))
endif

#########################################
# Calculated compiler/linker flags
#########################################

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

#########################################
# Phony rules
#########################################

.PHONY: main clean pristine get-version get-revision

main: $(BINARY) $(RLDIR)

clean:
	rm -rf bin obj

pristine: clean
	rm -rf lib emsdk

get-version:
	@echo $(VER_MAJOR).$(VER_MINOR).$(VER_PATCH)

get-revision:
	git rev-parse HEAD

#########################################
# Actual rules
#########################################

# Web build
bin/$(NAME).html: $(OBJECTS) | bin/$(NAME).js
	$(CC) -o $@ $^ $(LFLAGS)

bin/$(NAME).js: $(OBJECTS) | bin/$(NAME).wasm
	$(CC) -o $@ $^ $(LFLAGS)

bin/$(NAME).wasm: $(OBJECTS) $(RLBIN) | bin
	$(CC) -o $@ $^ $(LFLAGS)

# Linux build
bin/$(NAME): $(OBJECTS) $(RLBIN) | bin
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

