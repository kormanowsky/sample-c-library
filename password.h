#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdio.h>
#include <stdlib.h>

typedef char *password_t;
typedef password_t (*password_generate_t)(int);
typedef void (*password_free_t)(password_t);
typedef void (*password_print_t)(password_t);

password_t password_generate(int length); 

void password_print(password_t pwd);

void password_free(password_t password);

#endif 