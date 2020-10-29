/*
** EPITECH PROJECT, 2019
** Objdump
** File description:
** main
*/

#include "dump.h"
#include "lib_header.h"

void display_start_adress_little(t_elf *my_elf)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)my_elf->data;

    printf("start address 0x%08x\n\n", elf->e_entry);
}

void display_start_adress_big(t_elf *my_elf)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)my_elf->data;

    printf("start address 0x%016lx\n\n", elf->e_entry);
}

void display_info(t_elf *my_elf)
{
    t_linked_list *list = NULL;

    list = get_section(my_elf);
    display_file_format_and_sys(my_elf);
    if (my_elf->type_bits == BITS32)
        display_start_adress_little(my_elf);
    else
        display_start_adress_big(my_elf);
    print_list(list);
    free_all_list();
    use_section(NULL, FREE_SEC);
}

int main(int ac, char *argv[])
{
    t_elf e;
    int o = 0, value = 0, index = 1;

    o = recover_file_from_args(argv, &index, ac, &e.file_name);
    if (o <= -1)
        value = 84;
    while (o != -4) {
        e.flags = 0;
        if (o > -1 && !(e.data = read_this(o, e.file_name, PROGS))) {
            fprintf(stderr, "MMap failed\n");
            value = 84;
        } else if (o == -1 || is_file_correct(o, &e, PROGS) == false) {
            value = 84;
        } else
            o > -1 ? display_info(&e) : 0;
        if (o > -1 && e.file_name != NULL)
            free(e.file_name);
        o = recover_file_from_args(argv, &index, ac, &e.file_name);
    }
    return (value);
}