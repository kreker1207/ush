#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
    if (*list == NULL || list == NULL) {
        *list = mx_create_node(data);
        return;
    }

    t_list *temp_node = mx_create_node(data);
    temp_node->next = *list;
    *list = temp_node;
}

