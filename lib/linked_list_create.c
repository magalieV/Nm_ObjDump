/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** Linked list create
*/

#include "lib_header.h"

string my_strncat(string dest, string src, int n)
{
    int size_dest = 0;
    int size_src = 0;

    for (size_dest = 0; dest[size_dest]; size_dest++);
    for (size_src = 0; src[size_src]; size_src++);
    for (int i = 0; src[i]; i++) {
        if (i >= n)
            break;
        dest[size_dest] = src[i];
        size_dest++;
    }
    dest[size_dest] = '\0';
    return (dest);
}

t_linked_list *use_list(enum use_list_e action, t_linked_list *list)
{
    static t_linked_list *head = NULL;
    static t_linked_list *tail = NULL;

    if (action == SET_LIST_HEAD)
        head = list;
    else if (action == SET_LIST_TAIL)
        tail = list;
    if (action == GET_LIST_HEAD)
        return (head);
    else if (action == GET_LIST_TAIL)
        return (tail);
    return (NULL);
}

size_t use_list_size(enum use_list_size_e action)
{
    static size_t size = 0;

    if (action == INC_LIST_SIZE)
        size += 1;
    else if (action == DEC_LIST_SIZE)
        size -= 1;
    return (size);
}

void add_element(void *data)
{
    t_linked_list *el = malloc(sizeof(t_linked_list));
    t_linked_list *tail = use_list(GET_LIST_TAIL, NULL);

    if (!el)
        return;
    el->data = data;
    el->next = NULL;
    el->prev = NULL;
    if (tail == NULL) {
        use_list(SET_LIST_HEAD, el);
    } else {
        tail->next = el;
        el->prev = tail;
    }
    use_list(SET_LIST_TAIL, el);
    use_list_size(INC_LIST_SIZE);
}