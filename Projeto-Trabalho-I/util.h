#if !defined(__util_h__)
#define __util_h__

#define NOT_FOUND (-1)

typedef unsigned int chave_t;
typedef unsigned int valor_t;

// realiza o hash de uma string
chave_t hash_str(const char *str);

#endif // __util_h__
