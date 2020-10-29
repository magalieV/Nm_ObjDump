/*
** EPITECH PROJECT, 2019
** Nm
** File description:
** get_info_type
*/

#include "lib_header.h"
#include "nm.h"

t_value value_type[] = {
    {SHN_COMMON, 'C'},
    {SHN_UNDEF, 'U'},
    {SHN_ABS, 'A'},
    {0, '\0'}
};

static char type_of_weak_stb_little(Elf32_Sym *symbol)
{
    if (ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT &&
        symbol->st_shndx == SHN_UNDEF)
        return ('v');
    if (ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT)
        return ('V');
    if (symbol->st_shndx == SHN_UNDEF)
        return ('w');
    return ('W');
}

static char type_of_weak_stb_big(Elf64_Sym *symbol)
{
    if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT &&
        symbol->st_shndx == SHN_UNDEF)
        return ('v');
    if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
        return ('V');
    if (symbol->st_shndx == SHN_UNDEF)
        return ('w');
    return ('W');
}

char get_type_sym_little(Elf32_Sym *symbol)
{
    switch (ELF32_ST_BIND(symbol->st_info)) {
        case STB_WEAK:
            return (type_of_weak_stb_little(symbol));
        case STB_GNU_UNIQUE:
            return ('u');
        default :
            break;
    }
    for (int i = 0; value_type[i].c != '\0'; i++)
        if (symbol->st_shndx == value_type[i].value)
            return (value_type[i].c);
    return ('\0');
}

char get_type_sym_big(Elf64_Sym *symbol)
{
    switch (ELF64_ST_BIND(symbol->st_info)) {
        case STB_WEAK:
            return (type_of_weak_stb_big(symbol));
        case STB_GNU_UNIQUE:
            return ('u');
        default :
            break;
    }
    for (int i = 0; value_type[i].c != '\0'; i++)
        if (symbol->st_shndx == value_type[i].value)
            return (value_type[i].c);
    return ('\0');
}