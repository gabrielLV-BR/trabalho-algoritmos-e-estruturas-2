#include "./util.h"

chave_t hash_str(const char* str) {
    int acc = 1;

    for (; *str != '\0'; str++) { 
        // faz loucuras com os bytes pra tentar aleatorizar o hash
        acc += (*str) * 567889;
        acc ^= (*str) - 74198;
        acc ^= (*str) - 33213;
        acc ^= (*str) - 43222;
    }

    return acc;
}