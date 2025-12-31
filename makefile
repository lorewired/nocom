# Compilador
CXX      := g++

# Flags de compilacao
# -I.    : Resolve includes que comecam com "src/..." (usado no main)
# -Isrc  : Resolve includes que comecam com "utils/..." (usado dentro do src)
CXXFLAGS := -std=c++17 -w -g -I. -Isrc

# Nome do executavel final
TARGET   := dungeon_gen.exe

# Lista de arquivos fonte (.cpp e .cxx)
SRCS     := cmd/main.cpp \
            src/procedural-generation/proc-gen.cxx \
            src/procedural-generation/proc-gen-entities.cxx

# Converte a lista de fontes para objetos (.o)
OBJS     := $(SRCS:.cpp=.o)
OBJS     := $(OBJS:.cxx=.o)

# Regra padrao
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJS)
	@echo [LINK] Criando executavel...
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo [SUCESSO] Executavel criado: $(TARGET)

# Compilar arquivos .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar arquivos .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos temporarios (Comando ajustado para Linux/WSL)
clean:
	# Use 'rm -f' para forçar a remocao sem pedir confirmacao e ignorar erros se o arquivo nao existir
	rm -f cmd/*.o src/procedural-generation/*.o $(TARGET)
	@echo [LIMPEZA] Arquivos temporarios e executavel removidos.