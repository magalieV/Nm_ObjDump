/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** malloc
*/

#ifndef __NM_HEADER__
#define __NM_HEADER__

#define DEFAULT_FILE "a.out"

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "nm.h"
#include <unistd.h>
#define PROG "my_nm"

enum use_symb {SET_SYMBOL, FREE_SYMBOL};

typedef struct s_map {
    unsigned int info;
    unsigned int type;
    unsigned int flag;
    char c;
} t_map;

t_linked_list *get_symbol(t_elf *my_elf);
char get_type_symbol_big(Elf64_Sym *symbol, Elf64_Shdr *shdr);
char get_type_symbol_little(Elf32_Sym *symbol, Elf32_Shdr *shdr);
char get_type_sym_big(Elf64_Sym *sym);
char get_type_sym_little(Elf32_Sym *sym);
char get_type_big(Elf64_Sym *sym, Elf64_Shdr *shdr);
char get_type_little(Elf32_Sym *sym, Elf32_Shdr *shdr);
t_linked_list *sort_list(void);

#endif //__NM_HEADER__
