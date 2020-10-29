/*
** EPITECH PROJECT, 2019
** Objdump
** File description:
** file
*/

#include "lib_header.h"
#include <errno.h>

int my_return(cstring str, int value)
{
    fprintf(stderr, "%s\n", str);
    return (value);
}

string copy_name_prog(cstring name)
{
    string prog_name = NULL;
    int size = 0;
    int index = 2;
    int idx = 0;

    for (size = 0; name[size]; size++);
    prog_name = malloc(sizeof(char) * (size + 1));
    for (idx = 0; idx < size; idx++) {
        prog_name[idx] = name[index];
        index++;
    }
    prog_name[idx] = '\0';
    return (prog_name);
}

static int open_file(cstring file_name, cstring name)
{
    int op = 0;
    string nme = copy_name_prog(name);

    op = open(file_name, O_RDONLY);
    if (op == -1) {
        if (errno == EACCES) {
            fprintf(stderr, "%s: '%s': Permission denied\n", nme, file_name);
        }
        fprintf(stderr, "%s: '%s': No such file\n", nme, file_name);
        free(nme);
        return (FAIL);
    }
    free(nme);
    return (op);
}

static int open_default_file(int *next_index, char **file_name, cstring name)
{
    *file_name = strdup(DEFAULT_FILE);
    *next_index += 1;
    return (open_file(DEFAULT_FILE, name));
}

int recover_file_from_args(char *argv[], int *next_index, int ac,
    char **file_name)
{
    if (ac == 1 && *next_index == 1)
        return (open_default_file(next_index, file_name, argv[0]));
    for (int idx = *next_index; idx < ac; idx++) {
        *next_index += 1;
        if (argv[idx][0] != '-') {
            *file_name = strdup(argv[idx]);
            return (open_file(*file_name, argv[0]));
        }
    }
    return (-4);
}