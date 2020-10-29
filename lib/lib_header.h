/*
** EPITECH PROJECT, 2019
** lib
** File description:
** libHeader
*/

#ifndef __LIB_HEADER__
#define __LIB_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FAIL -1
#define BFD_NO_FLAGS    0x00
#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_LINENO      0x04
#define HAS_DEBUG       0x08
#define HAS_SYMS        0x10
#define HAS_LOCALS      0x20
#define DYNAMIC         0x40
#define WP_TEXT         0x80
#define D_PAGED         0x100

#define DEFAULT_FILE "a.out"

typedef char * string;
typedef char const * cstring;
typedef Elf32_Ehdr * elf_lh;
typedef Elf64_Ehdr * elf_bh;
typedef Elf32_Shdr * elf_ls;
typedef Elf64_Shdr * elf_bs;

enum type_arch {
    BITS32,
    BITS64
};

enum type_system {
    LITTLE,
    BIG
};

typedef struct s_elf
{
    string file_name;
    string data;
    enum type_arch type_bits;
    enum type_system type_sys;
    off_t size;
    unsigned int flags;
} t_elf;

typedef struct s_linked_list {
    void *data;
    struct s_linked_list *next;
    struct s_linked_list *prev;
} t_linked_list;

typedef struct s_symbol {
    unsigned int value;
    char type;
    string name;
    int info;
} t_symbol;

typedef struct s_section {
    string name;
    size_t number_sect;
    uintptr_t addr;
    size_t size;
    unsigned char *data;
    enum type_arch type_bits;
} t_section;

typedef struct s_flags {
    unsigned int value;
    string string_flag;
} t_flags;

typedef struct s_value {
    unsigned int value;
    char c;
} t_value;

enum use_list_e {SET_LIST_HEAD, SET_LIST_TAIL, GET_LIST_HEAD, GET_LIST_TAIL};
enum use_list_size_e {INC_LIST_SIZE, DEC_LIST_SIZE, GET_LIST_SIZE};
enum use_sect {SET_SEC, FREE_SEC};

int recover_file_from_args(string argv[], int *next_index, int ac,
    char **file_name);
int my_return(cstring str, int value);
bool is_file_correct(int op, t_elf *my_elf, cstring name);

t_linked_list *use_list(enum use_list_e action, t_linked_list *list);
size_t use_list_size(enum use_list_size_e action);
void add_element(void *data);
void free_all_list(void);

//SECTION
void *read_this(int op, cstring file_name, string name);
string my_strncat(string dest, string src, int n);
int check_file_little(t_elf *my_elf, elf_lh elf, int op, cstring name);
int check_file_big(t_elf *my_elf, elf_bh elf, int op, cstring name);

#endif //__LIB_HEADER__
