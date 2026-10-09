#!/bin/bash

# Cuby v0.1 - Automated Build & Pack Engine
echo "[CUBY BUILD] Iniciando automação do núcleo ngen..."

# 1. Detectar arquivos de gema ou diretórios ativos
TARGET_DIR=""
FILE_NAME=""

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -dir)
            TARGET_DIR="$2"
            shift
            ;;
        -name)
            FILE_NAME="$2"
            shift
            ;;
    esac
    shift
done

# Define o caminho padrão caso não seja informado
if [ -z "$TARGET_DIR" ]; then
    TARGET_DIR="ngen"
fi

if [ -z "$FILE_NAME" ]; then
    FILE_NAME="cuby.cgen"
fi

FULL_PATH="$TARGET_DIR/$FILE_NAME"

# 2. Garantir que a estrutura de diretórios e arquivos exista
mkdir -p "$TARGET_DIR"

if [ ! -f "$FULL_PATH" ]; then
    echo "[CUBY BUILD] Aviso: $FULL_PATH não encontrado. Gerando gema padrão..."
    printf '#include <stdio.h>\nint main() {\n    printf("[CUBY v0.1] Núcleo autogerado com sucesso!\\n");\n    return 0;\n}\n' > "$FULL_PATH"
fi

# 3. Empacotamento Matricial (Flatten / Vetorização do ngen)
echo "[CUBY BUILD] Empacotando gemas para codigo_gerado.c..."
cp "$FULL_PATH" codigo_gerado.c

# 4. Compilação Universal via Clang
echo "[CUBY BUILD] Compilando pacote unificado..."
clang -Wall -Wextra codigo_gerado.c -o cuby_app

if [ $? -eq 0 ]; then
    echo "[CUBY BUILD] Sucesso! Executando o aplicativo gerado:"
    ./cuby_app
else
    echo "[CUBY BUILD ERROR] Falha na compilação."
    exit 1
fi
