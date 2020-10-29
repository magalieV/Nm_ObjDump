/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** get_section_info
*/

#include "lib_header.h"
#include "dump.h"

void use_section(t_section *section, enum use_sect action)
{
    static t_section *sec = NULL;

    if (action == SET_SEC)
        sec = section;
    else if (sec != NULL)
        free(sec);
}

string get_little_name(int size, elf_lh elf)
{
    elf_ls shdr = NULL;
    string strtab = NULL;

    if (elf->e_shstrndx == SHN_UNDEF)
        return (NULL);
    strtab = (string)((string)elf + ((elf_lh)elf)->e_shoff);
    shdr = &((elf_ls)strtab)[elf->e_shstrndx];
    return (((string) elf + shdr->sh_offset) + size);
}

string get_big_name(int size, elf_bh elf)
{
    elf_bs shdr = NULL;
    string strtab = NULL;

    if (elf->e_shstrndx == SHN_UNDEF)
        return (NULL);
    strtab = (string)((string)elf + ((elf_bh)elf)->e_shoff);
    shdr = &((elf_bs)strtab)[elf->e_shstrndx];
    return (((string) elf + shdr->sh_offset) + size);
}