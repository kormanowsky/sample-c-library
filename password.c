#include "password.h"

password_t password_generate(int length) {
    password_t pwd = (password_t) calloc(sizeof (char), length + 1);

    if (pwd != NULL) {
        for(int i = 0; i < length; ++i) {
            pwd[i] = 'a' + (rand() % (('z' - 'a') + 1));
        }
    }

    return pwd;
}

void password_print(password_t password) {
    printf("%s\n", password);
}

void password_free(password_t password) {
    free(password);
}
