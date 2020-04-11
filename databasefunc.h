#ifndef DATABASEFUNC_H
#define DATABASEFUNC_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>


#define READ_FROM_KEYBOARD 1
#define READ_FROM_FILE 2
#define LEFT_UPPER_CORNER "\u2554"
#define RIGHT_UPPER_CORNER "\u2557\n"
#define LINE "\u2550"
#define SEP "\u2551"
#define UPPER_HANDLE "\u2566"
#define LOWER_HANDLE "\u2569"
#define HANDLE "\u256C"
#define LEFT_SEP "\u2560"
#define RIGHT_SEP "\u2563\n"
#define RIGHT_LOWER_CORNER "\u255D\n"
#define LEFT_LOWER_CORNER "\u255A"


struct Character {
    char name[30];
    char warrior_class[10];
    char saber[10];
    size_t level;
    size_t midichlorians;
};

void run_database(struct Character [100], size_t *);

void list_menu(int *); 

void choose_input(int *);

void check_and_read(struct Character [100], size_t *, FILE *, const int *);

void input_data(struct Character [100], size_t *);

void print_frame();

void print_table(const struct Character [100], const size_t *);

void print_frame_to_file(FILE *);

void print_table_to_file(const struct Character [100], const size_t *, FILE *);

void print_lower_frame();

void print_lf_to_file(FILE *file);

void print_data(const struct Character [100], const size_t *);

void remove_data(struct Character [100], size_t *);

void find_data(struct Character [100], const size_t *);

void alg_sort(struct Character [100], const size_t *, int);

void sort_data(struct Character [100], const size_t *);

#endif