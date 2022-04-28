#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (*list == NULL || list == NULL) {
        *list = mx_create_node(data);
        return;
    }

    t_list *temp_node = *list;

    while (temp_node->next != NULL) {
        temp_node = temp_node->next;
    }

    temp_node->next = mx_create_node(data);
}

