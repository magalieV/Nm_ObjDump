/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** Linked list create
*/

#include "lib_header.h"
#include "nm.h"

t_map type[] = {
    {STT_FUNC, SHT_NULL, 0, 'U'},
    {STT_OBJECT, SHT_PROGBITS, 50, 'R'},
    {STT_NOTYPE, SHT_PROGBITS, 50, 'R'},
    {STT_NOTYPE, SHT_PROGBITS, 2, 'R'},
    {STT_OBJECT, SHT_PROGBITS, 2, 'R'},
    {STT_OBJECT, SHT_NOTE, 2, 'R'},
    {SHF_WRITE, SHT_PROGBITS, 18, 'R'},
    {STT_OBJECT, SHT_INIT_ARRAY, 3, 'T'},
    {STT_NOTYPE, SHT_INIT_ARRAY, 3, 'T'},
    {STT_FUNC, SHT_PROGBITS, 6, 'T'},
    {STT_NOTYPE, SHT_PROGBITS, 6, 'T'},
    {STT_NOTYPE, SHT_FINI_ARRAY, 3, 'T'},
    {STT_OBJECT, SHT_FINI_ARRAY, 3, 'T'},
    {STT_OBJECT, SHT_DYNAMIC, 3, 'D'},
    {STT_TLS, SHT_PROGBITS, 1027, 'D'},
    {STT_NOTYPE, SHT_PROGBITS, 3, 'D'},
    {STT_OBJECT, SHT_PROGBITS, 3, 'D'},
    {STT_NOTYPE, SHT_PROGBITS, 0, 'N'},
    {STT_OBJECT, SHT_PROGBITS, 0, 'N'},
    {STT_TLS, SHT_NOBITS, 1027, 'B'},
    {STT_OBJECT, SHT_NOBITS, 3, 'B'},
    {STT_NOTYPE, SHT_NOBITS, 3, 'B'},
    {STT_LOOS, SHT_PROGBITS, 6, 'I'},
    {0, 0, 0, '\0'}
};

static char get_shdr_little(Elf32_Sym *symbol, Elf32_Shdr *shdr)
{
    for (int i = 0; type[i].c != '\0'; i++) {
        if (ELF32_ST_TYPE(symbol->st_info) == type[i].info &&
            shdr[symbol->st_shndx].sh_flags == type[i].flag
            && shdr[symbol->st_shndx].sh_type == type[i].type)
            return (type[i].c);
    }
    return ('\0');
}

static char get_shdr_big(Elf64_Sym *symbol, Elf64_Shdr *shdr)
{
    for (int i = 0; type[i].c != '\0'; i++) {
        if (ELF64_ST_TYPE(symbol->st_info) == type[i].info &&
            shdr[symbol->st_shndx].sh_flags == type[i].flag
            && shdr[symbol->st_shndx].sh_type == type[i].type)
            return (type[i].c);
    }
    return ('\0');
}

char get_type_little(Elf32_Sym *symbol, Elf32_Shdr *shdr)
{
    char c = '\0';

    c = get_type_sym_little(symbol);
    if (c == '\0')
        c = get_shdr_little(symbol, shdr);
    if (c == '\0')
        return ('?');
    if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
        return ((char)(c + 32));
    return c;
}

char get_type_big(Elf64_Sym *symbol, Elf64_Shdr *shdr)
{
    char c = '\0';

    c = get_type_sym_big(symbol);
    if (c == '\0')
        c = get_shdr_big(symbol, shdr);
    if (c == '\0')
        return ('?');
    if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
        return ((char)(c + 32));
    return c;
}