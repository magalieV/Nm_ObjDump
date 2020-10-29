/*
** EPITECH PROJECT, 2019
** Nm
** File description:
** compare
*/

#include "lib_header.h"
#include "nm.h"
#include <string.h>
#include <ctype.h>

t_linked_list *swap_list(t_linked_list *first, t_linked_list *second)
{
    t_linked_list *next = first->next;
    t_linked_list *prev = first->prev;

    if (first->next != NULL)
        first->next->prev = second;
    first->next = second->next;
    if (second->next != NULL)
        second->next->prev = first;
    else
        use_list(SET_LIST_TAIL, first);
    second->next = next;
    if (first->prev != NULL)
        first->prev->next = second;
    else
        use_list(SET_LIST_HEAD, second);
    first->prev = second->prev;
    if (second->prev != NULL)
        second->prev->next = first;
    second->prev = prev;
    return (use_list(GET_LIST_HEAD, NULL));
}

static int go_to_next_letter(cstring str, int index)
{
    while (str[index]) {
        if (str[index] >= 'A' && str[index] <= 'Z')
            return (index);
        else if (str[index] >= 'a' && str[index] <= 'z')
            return (index);
        if (str[index] >= '0' && str[index] <= '0')
            return (index);
        index++;
    }
    return (index);
}

int compare_str(cstring first, cstring second)
{
    int index = 0;
    int idx = 0;

    while (first[index] && second[idx]) {
        index = go_to_next_letter(first, index);
        idx = go_to_next_letter(second, idx);
        if (toupper(first[index]) != toupper(second[idx]))
            return (toupper(first[index]) - toupper(second[idx]));
        if (first[index])
            index++;
        if (second[idx])
            idx++;
    }
    index = go_to_next_letter(first, index);
    idx = go_to_next_letter(second, idx);
    return (toupper(first[index]) - toupper(second[idx]));
}

static int compare_that(void *first_data, void *second_data)
{
    int cmp = 0;
    t_symbol *sym_one = (t_symbol *)first_data;
    t_symbol *sym_two = (t_symbol *)second_data;

    if ((sym_one->name == NULL && sym_two->name == NULL)
    || sym_two->name == NULL)
        return (0);
    if (sym_one->name == NULL)
        return (1);
    cmp = compare_str(sym_one->name, sym_two->name);
    if (cmp == 0 && sym_one->name != NULL && sym_two->name != NULL)
        cmp = sym_one->name[0] - sym_two->name[0];
    return (cmp);
}

t_linked_list *sort_list(void)
{
    t_linked_list *head = use_list(GET_LIST_HEAD, NULL);
    int cmp = 0;

    while (head) {
        if (head->next == NULL)
            break;
        cmp = compare_that(head->data, head->next->data);
        if (cmp > 0) {
            head = swap_list(head, head->next);
        } else
            head = head->next;
    }
    return (use_list(GET_LIST_HEAD, NULL));
}