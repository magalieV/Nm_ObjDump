/*
** EPITECH PROJECT, 2019
** Objdump
** File description:
** display_info
*/

#include "dump.h"
#include <ctype.h>

t_flags flags_to_string [] = {
    {HAS_RELOC, "HAS_RELOC"},
    {EXEC_P, "EXEC_P"},
    {HAS_LINENO, "HAS_LINENO"},
    {HAS_DEBUG, "HAS_DEBUG"},
    {HAS_SYMS, "HAS_SYMS"},
    {HAS_LOCALS, "HAS_LOCALS"},
    {DYNAMIC, "DYNAMIC"},
    {WP_TEXT, "WP_TEXT"},
    {D_PAGED, "D_PAGED"},
    {BFD_NO_FLAGS, "BDF_NO_FLAGS"},
    {0, NULL},
};

static void print_a(t_section *section, unsigned int index_start,
    unsigned int index, string *str)
{
    string tmp = malloc(3);
    unsigned int i = 0;
    string data = malloc(17);

    data[0] = '\0';
    for (i = index_start; i < index; i++) {
        if (isprint(section->data[i]))
            sprintf(tmp, "%c", section->data[i]);
        else
            sprintf(tmp, ".");
        data = my_strncat(data, tmp, 2);
    }
    printf(" %-35s  %-16s", *str, data);
    printf("\n");
    free(*str);
    free(tmp);
    free(data);
    *str = malloc(36);
    *str[0] = '\0';
}

void print_flags(unsigned int flags)
{
    bool display_comma = false;

    for (int i = 0; flags_to_string[i].string_flag; i++) {
        if ((flags_to_string[i].value & flags) && display_comma)
            printf(", %s", flags_to_string[i].string_flag);
        else if (flags_to_string[i].value & flags) {
            printf("%s", flags_to_string[i].string_flag);
            display_comma = true;
        }
    }
    printf("\n");
}

static bool is_bad_section(t_section *section)
{
    string to_not_display[] = {".bss", ".strtab", ".shstrtab",
                                ".symtab", NULL};

    if (section->size == 0)
        return (false);
    for (int i = 0; to_not_display[i]; i++) {
        if (strcmp(to_not_display[i], section->name) == 0)
            return (false);
    }
    return (true);
}

static void print_value(t_linked_list *node)
{
    unsigned int idx = 0, start = 0;
    t_section *sec = (t_section *)node->data;
    string data = malloc(36);
    string tmp = malloc(3);

    if (!is_bad_section(sec))
        return free(data), free(tmp);
    printf("Contents of section %s:\n", sec->name);
    data[0] = '\0';
    while (idx < sec->size) {
        (idx % 16 == 0) ? printf(" %04x", (unsigned)(sec->addr + idx)) : 0;
        sprintf(tmp, "%02x", sec->data[idx++]);
        data = my_strncat(data, tmp, 2);
        if (idx % 4 == 0 && idx % 16 > 0 && idx < sec->size)
            1 ? sprintf(tmp, " "), data = my_strncat(data, tmp, 2) : 0;
        if (idx % 16 == 0 || idx >= sec->size)
            print_a(sec, start, idx, &data);
        start = (idx % 16 == 0 || idx >= sec->size) ? idx : start;
    }
    1 ? free(tmp), free(data) : 0;
}

void print_list(t_linked_list *list)
{
    while (1) {
        print_value(list);
        if (list->next == NULL)
            break;
        list = list->next;
    }
}