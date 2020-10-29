/*
** EPITECH PROJECT, 2019
** Objdump
** File description:
** header
*/

#ifndef __DUMP_HEADER__
#define __DUMP_HEADER__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "lib_header.h"
#include <stdbool.h>
#define PROGS "my_objdump"

void display_file_format_and_sys(t_elf *my_elf);
void print_list(t_linked_list *list);
void print_flags(unsigned int flags);

t_linked_list *get_section(t_elf *my_elf);
string get_little_name(int size, elf_lh elf);
string get_big_name(int size, elf_bh elf);
void use_section(t_section *section, enum use_sect action);

#endif //__DUMP_HEADER__