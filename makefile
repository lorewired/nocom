CC      := g++
CCFLAGS := -std=c++23 -w -g -I. -Isrc

SRCS    := cmd/main.cc \
           src/procedural_generation/ProceduralGeneration.cc \
           src/procedural_generation/ProceduralGenerationEntities.cc \
           src/entities/Humanoid.cc \
           src/entities/Human.cc \
           src/entities/Map.cc \
           src/core/Runtime.cc \
           src/core/Keyboard.cc \
           src/core/Window.cc \
           src/core/Terminal.cc \
           src/systems/events/Events.cc \


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