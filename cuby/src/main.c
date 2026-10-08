#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mux.h"

void mini_geny_init(void) {
    printf("[*] Inicializando o ecossistema Cuby via mini-geny (cgems)...\n");
    printf("[+] Gerenciador de micro pacotes nativos ativado.\n");
}

int load_cgem(const char *gem_name) {
    char filepath[128];
    snprintf(filepath, sizeof(filepath), "cgems/%s.cg", gem_name);
    
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("[-] Erro: cgem '%s' nao encontrada em cgems/\n", gem_name);
        return 0;
    }

    CGem gem = {0};
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "name:", 5) == 0) {
            sscanf(line + 5, "%s", gem.name);
        } else if (strncmp(line, "version:", 8) == 0) {
            sscanf(line + 8, "%s", gem.version);
        } else if (strncmp(line, "desc:", 5) == 0) {
            line[strcspn(line, "\r\n")] = 0;
            strncpy(gem.description, line + 5, sizeof(gem.description) - 1);
        }
    }
    fclose(file);

    printf("\n[+] cgem carregada com sucesso pela mini-geny!\n");
    printf("    -> Nome:      %s\n", gem.name);
    printf("    -> Versao:    %s\n", gem.version);
    printf("    -> Descricao: %s\n", gem.description);
    return 1;
}

int main(int argc, char *argv[]) {
    mini_geny_init();

    if (argc > 1) {
        load_cgem(argv[1]);
    } else {
        printf("\nUso: %s <nome_da_cgem>\n", argv[0]);
        printf("Exemplo: %s rede_segura\n", argv[0]);
    }

    return 0;
}
