#include <stdio.h>

// Declaração das funções dos módulos fragmentados
void sys_read_module();
void sys_write_module();

int main() {
    printf("========================================\n");
    printf("[CUBY v0.1] Inicializando Ambiente SuperUser\n");
    printf("========================================\n");
    
    sys_read_module();
    sys_write_module();
    
    printf("========================================\n");
    printf("[CUBY] Todos os módulos carregados com sucesso!\n");
    return 0;
}
