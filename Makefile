CC=g++
CFLAGS= -g -c -Wall -D__USE_FIXED_PROTOTYPES__ -lm -O3
#
# Compiler flags:
# -c -- Compile or assemble the source files, but do not link.
# -g -- Enable debugging
# -Wall -- Turn on all warnings 
# -D__USE_FIXED_PROTOTYPES__ -- Force the compiler to use the correct headers
# -ansi -- Don't use GNU extensions. Stick to ANSI C.
PROGRAM_NAME=tp_paradigmas
CRIADOR=Vagner Clementino
PAA_LIB_PATH=../lib
SRC_FOLDER=./src
BIN_DIR=./bin
IN_DIR=./inputs
OUT_DIR=./intputs
OBJS=$(SRC_FOLDER)/main.o \
	$(SRC_FOLDER)/Brain.o \
	$(SRC_FOLDER)/TPInstance.o \
	$(SRC_FOLDER)/TPParadigmas.o \
	$(SRC_FOLDER)/FBSolution.o \
	$(SRC_FOLDER)/FBAlgorithm.o \
	$(SRC_FOLDER)/TPSolution.o \
	$(SRC_FOLDER)/GreedyAlgorithm.o \
	$(SRC_FOLDER)/PDAlgorithm.o \
	$(PAA_LIB_PATH)/FileManager.o \
	$(PAA_LIB_PATH)/PAAException.o \
	$(PAA_LIB_PATH)/TrabalhoPratico.o \

#INPUTFILE= $(pwd)entradas/input.txt
INPUTFILE=$(-i ../inputs/input.txt)
OUTPUTFILE=$(-o ../outputs/output.txt) 

all: app_structure msg_user linking $(BIN_DIR)/$(PROGRAM_NAME)
	@echo "Compilado com sucesso..."
	@rm -f $(OBJS) *.gch	
#@./$(BIN_DIR)/$(PROGRAM_NAME) $(INPUTFILE) $(OUTPUTFILE) -p all

app_structure:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(IN_DIR)
	@mkdir -p $(OUT_DIR)
	
msg_user:
	@echo "Compilando o programa " \
	 	  "$(PROGRAM_NAME) criado por $(CRIADOR)."
	
linking: $(OBJS)
	@$(CC) -o $(BIN_DIR)/$(PROGRAM_NAME) $(OBJS)
	@echo "Linking executado com sucesso."

main.o: $(SRC_FOLDER)/main.cpp
	@$(CC) $(CFLAGS) main.cpp

FileManager.o: $(PAA_LIB_PATH)/FileManager.h $(PAA_LIB_PATH)/FileManager.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/FileManager.cpp

PAAException.o: $(PAA_LIB_PATH)/PAAException.h $(PAA_LIB_PATH)/PAAException.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/PAAException.cpp

TrabalhoPratico.o: TrabalhoPratico.h TrabalhoPratico.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TrabalhoPratico.cpp

Brain.o: Brain.h Brain.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/Brain.cpp

TPInstance.o: TPInstance.h TPInstance.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TPInstance.cpp

TPParadigmas.o: TPParadigmas.h TPParadigmas.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TPParadigmas.cpp
	
FBSolution.o: FBSolution.h FBSolution.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/FBSolution.cpp
	
FBAlgorithm.o: FBAlgorithm.h FBAlgorithm.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/FBAlgorithm.cpp
	
TPSolution.o: TPSolution.h TPSolution.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TPSolution.cpp
	
TPSolution.o: GreedyAlgorithm.h GreedyAlgorithm.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/GreedyAlgorithm.cpp
	
TPSolution.o: PDAlgorithm.h PDAlgorithm.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/PDAlgorithm.cpp
clean:
	@echo "Removendo arquivos temporários e o executável..."
	@rm -f $(OBJS) *.gch $(PROGRAM_NAME)
	@echo "Arquivos removidos com sucesso."