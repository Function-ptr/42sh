/*
** EPITECH PROJECT, 2022
** my_sort_int_array.c
** File description:
** Sort an array of int in ascending order
*/

void my_sort_int_array(int *arr, int size)
{
    int i = 1;
    while (i < size) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
            j--;
        }
        i++;
    }
}
