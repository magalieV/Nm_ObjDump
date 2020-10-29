/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** Security file
*/

#include "lib_header.h"
#include <errno.h>

void *read_this(int op, cstring file_name, string name)
{
    struct stat my_stat;
    void *data = NULL;

    if (fstat(op, &my_stat) == -1) {
        fprintf(stderr, "%s: '%s' %s\n", name, file_name, strerror(errno));
        return (NULL);
    } else if (!S_ISREG(my_stat.st_mode)) {
        fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
            name, file_name);
        return (NULL);
    }
    data = mmap(NULL, my_stat.st_size, PROT_READ, MAP_SHARED, op, 0);
    if (data == MAP_FAILED)
        return (NULL);
    return (data);
}

int size_hight_elf(t_elf *my_elf, cstring name)
{
    elf_bh elf = (elf_bh) my_elf->data;
    elf_bs shdr = (elf_bs) (my_elf->data + elf->e_shoff);

    if (elf->e_ehsize + (elf->e_phnum * elf->e_phentsize) +
        (elf->e_shnum * elf->e_shentsize) > my_elf->size
        || (string)shdr > (my_elf->data + my_elf->size)
        || (string)(shdr + (elf->e_shnum)) > (my_elf->data + my_elf->size)) {
        fprintf(stderr, "%s: %s: File truncated\n",
            name, my_elf->file_name);
        return (-1);
    }
    return (0);
}

int size_little_elf(t_elf *my_elf, cstring name)
{
    elf_lh elf = (elf_lh) my_elf->data;
    elf_ls shdr = (elf_ls) (my_elf->data + elf->e_shoff);

    if (elf->e_ehsize + (elf->e_phnum * elf->e_phentsize) +
        (elf->e_shnum * elf->e_shentsize) > my_elf->size
        || (string)shdr > (my_elf->data + my_elf->size)
        || (string)(shdr + (elf->e_shnum)) > (my_elf->data + my_elf->size)) {
        fprintf(stderr, "%s: %s: File truncated\n",
                name, my_elf->file_name);
        return (-1);
    }
    return (0);
}

bool is_file_correct(int op, t_elf *e, cstring name)
{
    elf_bh elf = (elf_bh)e->data;
    elf_lh elf32 = (elf_lh)e->data;

    if (elf->e_ident[EI_DATA] == 1 || elf32->e_ident[EI_DATA] == 1)
        e->type_sys = LITTLE;
    else
        e->type_sys = BIG;
    e->type_bits = (elf->e_ident[EI_CLASS] == ELFCLASS32) ? BITS32 : BITS64;
    if ((e->type_bits == BITS64 && check_file_big(e, elf, op, name) == -1)
    || check_file_little(e, elf32, op, name) == -1)
        return (false);
    if (e->type_sys != BIG && e->type_bits == BITS32) {
        if (size_little_elf(e, name) == -1) {
            return (false);
        }
    } else if (e->type_sys != BIG && size_hight_elf(e, name) == -1)
        return (false);
    return (true);
}