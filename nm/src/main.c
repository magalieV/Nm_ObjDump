/*
** EPITECH PROJECT, 2019
** Nm
** File description:
** main
*/

#include "lib_header.h"
#include "nm.h"

static int count_number_file(int ac, char *argv[])
{
    int nb_file = 0;

    if (ac == 1)
        return (1);
    for (int idx = 1; idx < ac; idx++) {
        if (argv[idx][0] != '-')
            nb_file++;
    }
    return (nb_file);
}

static void print_symbol(t_elf *elf, t_symbol *symbol)
{
    bool is_print = false;

    if (symbol->type != 'w' && symbol->type != 'U' &&
        symbol->type != 'v' && elf->type_bits == BITS64) {
        printf("%016x %c %s\n", symbol->value, symbol->type, symbol->name);
        is_print = true;
    } else if (symbol->type != 'w' && symbol->type != 'U' &&
        symbol->type != 'v' && elf->type_bits == BITS32) {
        printf("%08x %c %s\n", symbol->value, symbol->type, symbol->name);
        is_print = true;
    }
    if (!is_print && elf->type_bits == BITS64)
        printf("%16s %c %s\n", "", symbol->type, symbol->name);
    else if (!is_print)
        printf("%8s %c %s\n", "", symbol->type, symbol->name);
}

static void print_nm(t_linked_list *list, t_elf *elf)
{
    t_symbol *symbol = NULL;

    while (1) {
        symbol = (t_symbol *)(list->data);
        if (symbol->name != NULL && symbol->info != 4) {
            print_symbol(elf, symbol);
        }
        if (list->next == NULL)
            break;
        list = list->next;
    }
    free_all_list();
}

static void print_file(t_elf *elf, int nb_files)
{
    t_linked_list *list = NULL;

    if (nb_files > 1)
        printf("\n%s:\n", elf->file_name);
    list = get_symbol(elf);
    if (list)
        print_nm(list, elf);
    else
        printf("%s: %s: no symbols\n", "./my_nm", elf->file_name);
}

int main(int ac, char *argv[])
{
    t_elf e;
    int o = 0, value = 0, index = 1, nb_files = 0;

    nb_files = count_number_file(ac, argv);
    o = recover_file_from_args(argv, &index, ac, &e.file_name);
    value = (o <= -1) ? 84 : 0;
    while (o != -4) {
        e.flags = 0;
        if (o > -1 && !(e.data = read_this(o, e.file_name, PROG))) {
            fprintf(stderr, "MMap failed\n");
            value = 84;
        } else if (o == -1 || is_file_correct(o, &e, PROG) == false) {
            value = 84;
        } else
            o > -1 ? print_file(&e, nb_files) : 0;
        if (o > -1 && e.file_name != NULL)
            free(e.file_name);
        o = recover_file_from_args(argv, &index, ac, &e.file_name);
    }
    return (value);
}