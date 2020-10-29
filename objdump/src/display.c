/*
** EPITECH PROJECT, 2019
** Objdump
** File description:
** Display
*/

#include "dump.h"

static void file_little_info(string *format, string *sys, t_elf *my_elf)
{
    elf_lh elf = (elf_lh)my_elf->data;

    if (elf->e_ident[EI_DATA] == 2) {
        *format = strdup("big");
        *sys = strdup("UNKNOWN!");
        return;
    } else if (elf->e_machine == 0x03) {
        *format = strdup("i386");
        *sys = strdup("i386");
        return;
    }
    *format = strdup("little");
    *sys = strdup("UNKNOWN!");
}

static void file_big_info(string *format, string *sys, t_elf *my_elf)
{
    elf_bh elf = (elf_bh)my_elf->data;

    if (elf->e_ident[EI_DATA] == 2) {
        *format = strdup("big");
        *sys = strdup("UNKNOWN!");
        return;
    } else if (elf->e_machine == 0x3e) {
        *format = strdup("x86-64");
        *sys = strdup("i386:x86-64");
        return;
    }
    *format = strdup("little");
    *sys = strdup("UNKNOWN!");
}

void display_file_format_and_sys(t_elf *my_elf)
{
    string format = NULL;
    string sys = NULL;

    if (my_elf->type_bits == BITS32) {
        file_little_info(&format, &sys, my_elf);
        printf("\n%s:     file format elf32-%s\n", my_elf->file_name, format);
    } else {
        file_big_info(&format, &sys, my_elf);
        printf("\n%s:     file format elf64-%s\n", my_elf->file_name, format);
    }
    printf("architecture: %s, flags 0x%08x:\n", sys, my_elf->flags);
    print_flags(my_elf->flags);
    free(format);
    free(sys);
}