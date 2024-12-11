#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вариативность

// Первый вариант
struct with_var_1 {
    char some_value[20];
    int type; 
    union {
        char c;
        int i;
    } data;
};

// Второй вариант
struct with_var_2_base {
    char some_value[20];
    int type;
};

struct with_var_2_c {
    struct with_var_2_base base;
    char c;
};

struct with_var_2_i {
    struct with_var_2_base base;
    int i;
};

// Связные списки 

struct list {
    void *data;
    struct list *next;
};

/**
 * Добавляяет элемент в начало списка
 * Список до: 
 * [item1]-->[item2]-->NULL
 * ^ head
 * Список после: 
 * [new_item]-->[item1]-->[item2]-->NULL
 * ^ возвращаемое значение
 */
struct list *list_add(struct list *head, void *new_item) {
    // Выделение памяти под новый экзепляр struct list
    struct list *new_head = (struct list *) malloc(sizeof(struct list));

    if (new_head == NULL) {
        // Ошибка выделения памяти
        return NULL;
    }

    new_head->data = new_item;
    new_head->next = head;

    return new_head;
}

/**
 * Печатает элементы списка
 */
void list_print(struct list *head) {
    while(head != NULL) {
        printf("%p %p %d\n", head, head->data, *(int *) head->data);
        head = head->next;
    }
}

/**
 * Обходит список и применяет к каждому элементу функцию callback
 */
void list_traverse(struct list *head, void (*callback)(void *)) {
    while(head != NULL) {
        callback(head->data);
        head = head->next;
    }
}

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


    // Побайтовое копирование
    // Есть строка (или какие-то данные)
    char c = 'E';
    struct list l1;
    l1.data = &c;
    struct list l2;

    memmove(&l2, &l1, sizeof(struct list));

    printf("RESULT: %c", *(char*)l2.data);

    return 0;
}