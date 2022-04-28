#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
    if (list == NULL || cmp == NULL) {
        return list;
    }

    int size = 0;
    t_list *temp_count = list, *temp_node;

    while (temp_count != NULL) {
        size++;
        temp_count = temp_count->next;
    }

    for (int i = 0; i < size; i++) {

        temp_node = list;

        for (int j = 0; j < size - 1; j++) {
            if(cmp(temp_node->data, temp_node->next->data)) {
                void *temp_data = temp_node->data;
                temp_node->data = temp_node->next->data;
                temp_node->next->data = temp_data;
            }
            temp_node = temp_node->next;
        }
    }   
    return list;
}

