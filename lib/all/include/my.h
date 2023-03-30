/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** Contains prototypes for mylib functions
*/

#ifndef MY_H_

    #define MY_H_

    #include <stdlib.h>

///////////////////////////
///  Epitech Functions  ///
///////////////////////////

void my_swap(int *a, int *b);

char *my_strupcase(char *str);

int is_needle(char *str, char const *to_find);

char *my_strlowcase(char *str);

char *my_strcapitalize(char *str);

int my_str_isupper(char *str);

int my_str_isprintable(char *str);

int my_str_isnum(char *str);

int my_str_islower(char *str);

int my_str_isalpha(char const *str);

void my_sort_int_array(int *arr, int size);

int my_showstr(char const *str);

int my_showmem(char const *str, int size);

char *my_revstr(char *str);

int my_isneg(int n);

int my_is_prime(int n);

int my_find_prime_sup(int n);

int my_compute_square_root(int n);

int my_compute_power_rec(int n, int p);

void my_sort_str_array(char **arr, int size);

int my_show_word_array(char const **arr);

char *concat_params(int ac, char **av);

int is_sep(char c, char *sep);

int nb_words(char const *str, int len, char *sep);

int *get_word_indexes(char const *str, int len, int nbword, char *sep);

int get_word_len(char const *str, int index, char *sep);

char **my_str_to_word_array(char const *str, char *sep);

void my_put_float(float f, int dec);

int my_showstr(char const *str);

int process_int_base(int val, int num, const char *base);

int nb_in_base(char nb, const char *base);

int my_str_isalphanum(char *str);


//////////////////
///  My Lib C  ///
//////////////////

char *my_strchr(char *s, int c);

char *my_strrchr(char *s, int c);

char *my_strstr(char *str, char const *to_find);

char *my_strncpy(char *dest, char const *str, int n);

int my_strncmp(char const *s1, char const *s2, int n);

char *my_strncat(char *dest, char const *str, int n);

char *my_strcpy(char *dest, char const *str);

int my_strcmp(char const *s1, char const *s2);

char *my_strcat(char *dest, char const *str);

char *my_strdup(char const *str);

long int random_wl(int bytes, int fd);

void *my_memset(void *p, size_t n, char byte);

void *my_calloc(size_t len, size_t datasize, char byte);

char *my_strndup(char *str, int len);

void *my_memmove(void *dest, const void *src, size_t n);

void *my_memcpy(void *restrict dest, const void *restrict src, size_t n);

int my_printf(const char *f, ...);

int my_putchar(char c);

int my_strlen(char *str);

double my_pow(double val, double exp);

#endif
