/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** get_section
*/

#include "lib_header.h"
#include "dump.h"

static unsigned int set_big_flags(unsigned int flag, elf_bh e, elf_bs s)
{
    unsigned int flags = 0x01 * (e->e_type == ET_REL && (s->sh_type == SHT_RELA
        || s->sh_type == SHT_REL)) | 0x02 * (e->e_type == ET_EXEC) |
        0x10 * (s->sh_type == SHT_SYMTAB || s->sh_type == SHT_DYNSYM) |
        0x40 * (e->e_type == ET_DYN) | 0x100 * ((e->e_type == ET_EXEC
        || e->e_type == ET_DYN));

    return (flags > flag ? flags : flag);
}

static unsigned int set_little_flags(unsigned int flag, elf_lh e, elf_ls s)
{
    unsigned int flags = 0x01 * (e->e_type == ET_REL
        && (s->sh_type == SHT_RELA || s->sh_type == SHT_REL))
        | 0x02 * (e->e_type == ET_EXEC) | 0x10 * (s->sh_type == SHT_SYMTAB
        || s->sh_type == SHT_DYNSYM) | 0x40 * (e->e_type == ET_DYN)
        | 0x100 * ((e->e_type == ET_EXEC
        || e->e_type == ET_DYN));

    return (flags > flag ? flags : flag);
}

void get_section_little(t_elf *e)
{
    elf_lh elf = (elf_lh)e->data;
    size_t number_section = elf->e_shnum - 1;
    t_section *section = malloc(sizeof(t_section) * (number_section));
    elf_ls sec = NULL;

    use_section(section, SET_SEC);
    for (size_t i = 0; i < number_section; i++) {
        sec = &(((elf_ls)((string)elf + ((elf_lh)e->data)->e_shoff))[i + 1]);
        section[i].addr = sec->sh_addr;
        section[i].size = sec->sh_size;
        section[i].name = get_little_name(sec->sh_name, elf);
        section[i].number_sect = number_section;
        section[i].data = (u_char *) e->data + sec->sh_offset;
        e->flags = set_little_flags(e->flags, elf, sec);
        add_element(&section[i]);
    }
}

void get_section_big(t_elf *e)
{
    elf_bh elf = (elf_bh)e->data;
    size_t number_section = elf->e_shnum - 1;
    t_section *section = malloc(sizeof(t_section) * (number_section));
    elf_bs sec = NULL;

    use_section(section, SET_SEC);
    for (size_t i = 0; i < number_section; i++) {
        sec = &(((elf_bs)((string)elf + ((elf_bh)e->data)->e_shoff))[i + 1]);
        section[i].addr = sec->sh_addr;
        section[i].size = sec->sh_size;
        section[i].name = get_big_name(sec->sh_name, elf);
        section[i].number_sect = number_section;
        section[i].data = (u_char *) e->data + sec->sh_offset;
        e->flags = set_big_flags(e->flags, elf, sec);
        add_element(&section[i]);
    }
}

t_linked_list *get_section(t_elf *my_elf)
{
    if (use_list(GET_LIST_HEAD, NULL) != NULL)
        free_all_list();
    if (my_elf->type_bits == BITS32)
        get_section_little(my_elf);
    else
        get_section_big(my_elf);
    return (use_list(GET_LIST_HEAD, NULL));
}