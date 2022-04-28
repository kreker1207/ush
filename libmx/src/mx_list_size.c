#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
    int count = 0;
    t_list *temp_node = list;

    while (temp_node != NULL) {
        count++;
        temp_node = temp_node->next;
    }
    
    return count;
}

