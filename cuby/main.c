#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Função para exibir o uso correto da CLI do ecossistema Cuby / mini-geny
void print_help() {
    printf("Uso do Mini-Geny (Ecossistema Cuby):\n");
    printf("  cuby -dir -name <diretorio> -<sigla>\n\n");
    printf("Siglas disponíveis:\n");
    printf("  -cip, -hip, -sip  (Blocos base)\n");
    printf("  -sc, -hc, -cs     (Intermediários: C/Assembly/Header)\n");
    printf("  -ch, -sh, -hs     (Intermediários avançados)\n");
}

// Função para copiar o conteúdo de um arquivo para outro
int copiar_arquivo(const char *origem, const char *destino) {
    FILE *src = fopen(origem, "rb");
    if (!src) return -1;

    FILE *dst = fopen(destino, "wb");
    if (!dst) {
        fclose(src);
        return -1;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);
    return 0;
}

// Função que processa o diretório e auto-organiza os intermediários dentro de gen/
int compactar_diretorio(const char *dir_name, const char *sigla) {
    char pasta_gen[256] = "gen";
    char pasta_destino[512];
    
    // Cria fisicamente a pasta centralizadora 'gen/'
    struct stat st = {0};
    if (stat(pasta_gen, &st) == -1) {
        mkdir(pasta_gen, 0755);
    }

    // Define o caminho completo da subpasta isolada com underline dentro de gen/ (ex: gen/_sc)
    snprintf(pasta_destino, sizeof(pasta_destino), "%s/_%s", pasta_gen, sigla);

    // Cria fisicamente a pasta de destino isolada
    if (stat(pasta_destino, &st) == -1) {
        mkdir(pasta_destino, 0755);
    }

    printf("[Mini-Geny] Lendo diretório alvo: '%s'\n", dir_name);
    printf("[Mini-Geny] Auto-organizando na pasta intermediária: '%s/'\n", pasta_destino);

    // Abre o diretório de origem
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("[Erro] Não foi possível abrir o diretório de origem");
        return 1;
    }

    struct dirent *entry;
    int contador = 0;

    // Varre todos os arquivos e entradas dentro do diretório de origem
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char caminho_origem[512];
        char caminho_destino[512];

        snprintf(caminho_origem, sizeof(caminho_origem), "%s/%s", dir_name, entry->d_name);
        snprintf(caminho_destino, sizeof(caminho_destino), "%s/%s", pasta_destino, entry->d_name);

        struct stat file_st;
        if (stat(caminho_origem, &file_st) == 0 && S_ISREG(file_st.st_mode)) {
            printf("  -> Processando e isolando: %s\n", entry->d_name);
            
            if (copiar_arquivo(caminho_origem, caminho_destino) == 0) {
                // Remove o arquivo original após a cópia bem-sucedida para limpar a origem
                unlink(caminho_origem);
                contador++;
            } else {
                printf("     [Aviso] Falha ao copiar o arquivo %s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    printf("[Sucesso] Total de %d arquivos auto-organizados em '%s/'!\n", contador, pasta_destino);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "-dir") == 0) {
        if (strcmp(argv[2], "-name") == 0) {
            const char *dir_alvo = argv[3];
            const char *sigla_param = argv[4];

            if (sigla_param[0] == '-') {
                sigla_param++;
            }

            compactar_diretorio(dir_alvo, sigla_param);
        } else {
            printf("Erro: Argumento '-name' esperado após '-dir'.\n");
            print_help();
            return 1;
        }
    } else {
        printf("Comando desconhecido.\n");
        print_help();
        return 1;
    }

    return 0;
}
