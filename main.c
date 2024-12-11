#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "list.h"
#include "password.h"

int main() {
    // Пустой список 
    struct list *list_empty = NULL;

    // Добавим в список элементы массива
    struct list *list_with_numbers = NULL;

    int numbers[] = {1, 2, 3, 4, 5};

    for(int i = 0; i < 5; ++i) {
        list_with_numbers = list_add(
            list_with_numbers, numbers + i
        );
    }

    list_print(list_with_numbers);

    // Освободим список 
    list_free(list_with_numbers, NULL);

    // Побайтовое копирование
    // Есть строка (или какие-то данные)
    char c = 'E';
    struct list l1;
    l1.data = &c;
    struct list l2;

    memmove(&l2, &l1, sizeof(struct list));

    printf("RESULT: %c\n", *(char*)l2.data);

    // Используем функции из динамической библиотеки
    void *password_library = dlopen("libexample_password.dylib", RTLD_LAZY);

    if (password_library == NULL) {
        perror("dlopen");
        return 1;
    }

    password_generate_t password_generate = (password_generate_t) dlsym(password_library, "password_generate");

    if (password_generate == NULL) {
        perror("dlsym(password_generate)");
        dlclose(password_library);
        return 1;
    }

    password_free_t password_free = (password_free_t) dlsym(password_library, "password_free");

    if (password_free == NULL) {
        perror("dlsym(password_free)");
        dlclose(password_library);
        return 1;
    }

    password_print_t password_print = (password_print_t) dlsym(password_library, "password_print");

    if (password_free == NULL) {
        perror("dlsym(password_print)");
        dlclose(password_library);
        return 1;
    }

    struct list *list_with_passwords = NULL;

    for(int i = 1; i <= 5; ++i) {
        password_t pwd = password_generate(10 * i);
        list_with_passwords = list_add(list_with_passwords, pwd);
    }

    list_traverse(list_with_passwords, (void(*)(void*)) password_print);

    list_free(list_with_passwords, (void(*)(void*)) password_free);

    dlclose(password_library);

    return 0;
}