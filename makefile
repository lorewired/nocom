CC      := g++
CCFLAGS := -std=c++23 -w -g -I. -Isrc

SRCS    := cmd/main.cc \
           src/procedural-generation/proc-gen.cc \
           src/procedural-generation/proc-gen-entities.cc \
           src/entities/humanoid.cc \
           src/entities/human.cc \
           src/entities/map.cc \
           src/core/runtime.cc \
           src/core/keyboard.cc \
           src/core/window.cc \
           src/core/terminal.cc

OBJS    := $(SRCS:.cc=.o)

ifeq ($(OS),Windows_NT)
    TARGET  := dungeon_gen.exe
    RM      := del /Q /F
    FixPath = $(subst /,\,$1)
else
    TARGET  := dungeon_gen
    RM      := rm -f
    FixPath = $1
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo [LINK] Creating $(TARGET)...
	$(CC) $(CCFLAGS) -o $@ $^
	@echo [SUCCESS] Built $(TARGET)

%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(call FixPath,$(OBJS)) $(call FixPath,$(TARGET))
	@echo [CLEAN] Removed files.