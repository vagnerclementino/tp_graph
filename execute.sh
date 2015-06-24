#!/bin/bash
EXE_NAME="tp_graph"
readonly EXE_NAME
BIN_DIR="./bin"
INPUTS_DIR="./inputs"
readonly INPUTS_DIR
OUTPUTS_DIR="./outputs"
readonly OUTPUTS_DIR
echo "Executando o Trabalho Prático 2 PAA: SybilFinder"
$BIN_DIR/$EXE_NAME $INPUTS_DIR/inGA.txt $INPUTS_DIR/sybilGA.txt $INPUTS_DIR/inGB.txt $INPUTS_DIR/sybilGB.txt
