/*
** EPITECH PROJECT, 2019
** Nm
** File description:
** get_symbol
*/

#include "lib_header.h"
#include "nm.h"

static void read_symbol_table_little(t_elf *e, elf_ls sec, t_symbol *sym)
{
    Elf32_Sym *symb = NULL;
    string name = NULL;
    elf_ls test = NULL;
    elf_bh elf = (elf_bh)e->data;

    for (unsigned int p = 0; p < sec->sh_size / sec->sh_entsize; p++) {
        symb = &((Elf32_Sym *)((string)elf + sec->sh_offset))[p];
        1 ? sym[p].value = symb->st_value, sym[p].info = symb->st_info : 0;
        if (symb->st_name == SHN_UNDEF)
            sym[p].name = NULL;
        else {
            test = &(((elf_ls)((string)elf +
                ((elf_lh)e->data)->e_shoff))[sec->sh_link]);
            name = (string)((uintptr_t)(test->sh_offset));
            sym[p].name = (name + (uintptr_t)elf + symb->st_name);
        }
        sym[p].type = get_type_little(symb, ((elf_ls)((string)elf +
        ((elf_lh)e->data)->e_shoff)));
        add_element(&sym[p]);
    }
}

static void read_symbol_table_big(t_elf *e, elf_bs sec, t_symbol *sym)
{
    Elf64_Sym *symb = NULL;
    string name = NULL;
    elf_bs test = NULL;
    elf_bh elf = (elf_bh)e->data;

    for (unsigned int p = 0; p < sec->sh_size / sec->sh_entsize; p++) {
        symb = &((Elf64_Sym *)((string)elf + sec->sh_offset))[p];
        1 ? sym[p].value = symb->st_value, sym[p].info = symb->st_info : 0;
        if (symb->st_name == SHN_UNDEF)
            sym[p].name = NULL;
        else {
            test = &(((elf_bs)((string)elf +
                ((elf_bh)e->data)->e_shoff))[sec->sh_link]);
            name = (string)((uintptr_t)(test->sh_offset));
            sym[p].name = (name + (uintptr_t)elf + symb->st_name);
        }
        sym[p].type = get_type_big(symb, ((elf_bs)((string)elf +
        ((elf_bh)e->data)->e_shoff)));
        add_element(&sym[p]);
    }
}

void get_symbol_little(t_elf *e)
{
    elf_lh elf = (elf_lh)e->data;
    size_t number_section = elf->e_shnum - 1;
    elf_ls sec = NULL;
    t_symbol *sym = NULL;

    for (size_t i = 0; i < number_section; i++) {
        sec = &(((elf_ls)((string)elf + ((elf_lh)e->data)->e_shoff))[i + 1]);
        if (sec->sh_type == SHT_SYMTAB) {
            sym = malloc(sizeof(t_symbol) * (sec->sh_size / sec->sh_entsize));
            read_symbol_table_little(e, sec, sym);
        }
    }
}

void get_symbol_big(t_elf *e)
{
    elf_bh elf = (elf_bh)e->data;
    size_t number_section = elf->e_shnum - 1;
    elf_bs sec = NULL;
    t_symbol *sym = NULL;

    for (size_t i = 0; i < number_section; i++) {
        sec = &(((elf_bs)((string)elf + ((elf_bh)e->data)->e_shoff))[i + 1]);
        if (sec->sh_type == SHT_SYMTAB) {
            sym = malloc(sizeof(t_symbol) * (sec->sh_size / sec->sh_entsize));
            read_symbol_table_big(e, sec, sym);
        }
    }
}

t_linked_list *get_symbol(t_elf *my_elf)
{
    if (use_list(GET_LIST_HEAD, NULL) != NULL)
        free_all_list();
    if (my_elf->type_bits == BITS32)
        get_symbol_little(my_elf);
    else
        get_symbol_big(my_elf);
    sort_list();
    return (use_list(GET_LIST_HEAD, NULL));
}