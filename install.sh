#!/bin/bash

echo "[CUBY Installer] Instalando a Cuby globalmente no sistema..."

# Verifica se o usuário tem permissão de root ou está no Termux
if [ -d "/data/data/com.termux/files/usr/bin" ]; then
    # Ambiente Termux
    INSTALL_DIR="/data/data/com.termux/files/usr/bin"
else
    # Linux padrão (Ubuntu, Arch, Debian, etc.)
    INSTALL_DIR="/usr/local/bin"
fi

# Copia o script principal e dá permissão de execução
if [ -f "cuby" ]; then
    chmod +x cuby
    cp cuby "$INSTALL_DIR/cuby"
    echo "[CUBY Installer] Sucesso! O comando 'cuby' agora está disponível globalmente."
    echo "[CUBY Installer] Você pode rodar 'cuby' de qualquer pasta do seu terminal!"
else
    echo "[CUBY ERROR] O arquivo 'cuby' não foi encontrado na pasta atual."
fi
