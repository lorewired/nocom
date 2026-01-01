CC      := g++

CCFLAGS := -std=c++23 -w -g -I. -Isrc

TARGET  := dungeon_gen.exe

SRCS    := cmd/main.cc \
           src/procedural-generation/proc-gen.cc \
           src/procedural-generation/proc-gen-entities.cc

OBJS    := $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo [LINK] creating executable...
	$(CC) $(CCFLAGS) -o $@ $^
	@echo [SUCESSO] executable created: $(TARGET)

%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	@echo [LIMPEZA] removed temporary files and executable.