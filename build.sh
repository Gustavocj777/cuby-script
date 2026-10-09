#!/bin/bash

echo "[CUBY BUILD] Iniciando automação do núcleo ngen (Modo Modular)..."

TARGET_DIR=""
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -dir)
            TARGET_DIR="$2"
            shift
            ;;
    esac
    shift
done

if [ -z "$TARGET_DIR" ]; then
    TARGET_DIR="ngen"
fi

if [ ! -d "$TARGET_DIR" ]; then
    echo "[CUBY ERROR] Diretório $TARGET_DIR não encontrado."
    exit 1
fi

# Empacotamento Matricial: Junta TODOS os arquivos .c do diretório em codigo_gerado.c
echo "[CUBY BUILD] Empacotando e fundindo todos os módulos .c de $TARGET_DIR..."
cat "$TARGET_DIR"/*.c > codigo_gerado.c

# Compilação Universal via Clang do pacote fundido
echo "[CUBY BUILD] Compilando pacote unificado..."
clang -Wall -Wextra codigo_gerado.c -o cuby_app

if [ $? -eq 0 ]; then
    echo "[CUBY BUILD] Sucesso! Executando o aplicativo gerado:"
    ./cuby_app
else
    echo "[CUBY BUILD ERROR] Falha na compilação."
    exit 1
fi
