/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** Linked list create
*/

#include "lib_header.h"

int check_file_big(t_elf *my_elf, elf_bh elf, int op, cstring name)
{
    if (elf->e_ident[EI_CLASS] > 2 || elf->e_ident[EI_DATA] > 2) {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    if (elf->e_ident[EI_MAG0] != 0x7F || elf->e_ident[EI_MAG1] != 'E') {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    if (elf->e_ident[EI_MAG2] != 'L' || elf->e_ident[EI_MAG3] != 'F') {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    my_elf->size = lseek(op, 0, SEEK_END);
    return (0);
}

int check_file_little(t_elf *my_elf, elf_lh elf, int op, cstring name)
{
    if (elf->e_ident[EI_CLASS] > 2 || elf->e_ident[EI_DATA] > 2) {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    if (elf->e_ident[EI_MAG0] != 0x7F || elf->e_ident[EI_MAG1] != 'E') {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    if (elf->e_ident[EI_MAG2] != 'L' || elf->e_ident[EI_MAG3] != 'F') {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                name, my_elf->file_name);
        return (-1);
    }
    my_elf->size = lseek(op, 0, SEEK_END);
    return (0);
}

void free_all_list(void)
{
    t_linked_list *head = use_list(GET_LIST_HEAD, NULL);
    t_linked_list *tmp = NULL;

    if (!head)
        return;
    while (1) {
        tmp = head;
        if (!head->next)
            break;
        head = head->next;
        tmp->next = NULL;
        head->prev = NULL;
        free(tmp);
        use_list_size(DEC_LIST_SIZE);
    }
    head->prev = NULL;
    free(head);
    use_list_size(DEC_LIST_SIZE);
    use_list(SET_LIST_TAIL, NULL);
    use_list(SET_LIST_HEAD, NULL);
}