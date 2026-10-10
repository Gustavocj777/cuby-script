#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("[MGEN] A inicializar o motor de gemas de automacao...\n");

    // 1. Cria a gema .mgen com a assinatura unitaria 'U'
    FILE *f = fopen("projeto.mgen", "wb");
    if (f) {
        char assinatura = 'U';
        fwrite(&assinatura, sizeof(char), 1, f);
        
        char *conteudo_gema = 
            "// Gema NGEN de Automacao - Cuby\n"
            "TARGET=cuby_core\n"
            "SRC=Cubyfile\n";
        
        fwrite(conteudo_gema, sizeof(char), strlen(conteudo_gema), f);
        fclose(f);
        printf("[MGEN] Ficheiro 'projeto.mgen' criado com sucesso com a assinatura 'U'.\n");
    }

    // 2. Leitura e validacao da gema gerada
    FILE *f_read = fopen("projeto.mgen", "rb");
    if (!f_read) {
        printf("[MGEN] Erro ao abrir a gema.\n");
        return 1;
    }

    char sig;
    fread(&sig, sizeof(char), 1, f_read);
    fclose(f_read);

    if (sig != 'U') {
        printf("[MGEN] Erro: Gema invalida (assinatura incorreta).\n");
        return 1;
    }

    printf("[MGEN] Gema validada com sucesso! Caractere unitario 'U' detetado.\n");
    printf("[MGEN] A processar e traduzir o Cubyfile para C puro...\n");

    // 3. Parser simples: Lê o Cubyfile e traduz 'gen main' para 'int main' e 'Retur' para 'return'
    FILE *fin = fopen("Cubyfile", "r");
    FILE *fout = fopen("cuby_transpile.c", "w");
    
    if (!fin || !fout) {
        printf("[MGEN] Erro ao abrir o Cubyfile para traducao.\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), fin)) {
        // Substituições básicas da DSL do Cuby para C nativo
        // Ex: gen main -> int main
        char *p;
        if ((p = strstr(linha, "gen main"))) {
            fprintf(fout, "int main(void) ");
            // Copia o resto da linha a partir de onde termina "gen main" se houver chaves
            char *resto = p + strlen("gen main");
            fprintf(fout, "%s", resto);
        } else if ((p = strstr(linha, "Retur"))) {
            // Substitui 'Retur' por 'return' mantendo o resto da instrução
            fprintf(fout, "    return %s", p + strlen("Retur"));
        } else {
            // Mantém linhas normais (comentários ou outras estruturas)
            fprintf(fout, "%s", linha);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("[MGEN] Traducao concluida com sucesso para 'cuby_transpile.c'.\n");

    // 4. Compilação do código transpilado pelo motor
    int ret = system("clang cuby_transpile.c -o cuby_core");
    if (ret == 0) {
        printf("[MGEN] Compilacao concluida com sucesso pelo nucleo do Cuby! Executavel gerado: 'cuby_core'\n");
    } else {
        printf("[MGEN] Erro durante a compilacao do codigo traduzido.\n");
    }

    return 0;
}
