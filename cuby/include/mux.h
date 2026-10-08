#ifndef MUX_H
#define MUX_H

#define MAX_LINE 256

typedef struct {
    char name[64];
    char version[16];
    char description[128];
} CGem;

void mini_geny_init(void);
int load_cgem(const char *gem_name);

#endif
