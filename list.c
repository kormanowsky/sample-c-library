#include "list.h"

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


/**
 * Освобождает список
 */
void list_free(struct list *head, void (*free_data)(void*)) {
    struct list *prev_head;

    while (head != NULL) {
        if (free_data != NULL) {
            free_data(head->data);
        }

        prev_head = head;
        head = head->next;
        free(prev_head);
    }
}