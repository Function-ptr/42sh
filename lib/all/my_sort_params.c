/*
** EPITECH PROJECT, 2022
** my_sort_params.c
** File description:
** Print this programs parameters sorted
*/

int my_strcmp(char const *s1, char const *s2);

void my_sort_str_array(char **arr, int size)
{
    int i = 1;
    while (i < size) {
        int j = i;
        while (j > 0 && my_strcmp(arr[j - 1], arr[j]) > 0) {
            char *tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
            j--;
        }
        i++;
    }
}
