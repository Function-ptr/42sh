/*
** EPITECH PROJECT, 2023
** autocomplete_path.c
** File description:
** autocomplete for paths
*/
/*
 _____               __      __
|  __ \              \ \    / /
| |__) |  __ _  ___   \ \  / /   ___   __ _   __ _  _ __
|  ___/  / _` |/ __|   \ \/ /   / _ \ / _` | / _` || '_ \
| |     | (_| |\__ \    \  /   |  __/| (_| || (_| || | | |
|_|      \__,_||___/     \/     \___| \__, | \__,_||_| |_|
                                       __/ |
                                      |___/
*/

#include "line_edition.h"
#include <dirent.h>

char *search_alias(char *input, aliases_t *aliases)
{
    if (input == NULL || aliases == NULL)
        return NULL;
    for (uint32_t i = 0; i < aliases->nb_aliases; i++) {
        if (strncmp(input, aliases->alias[i], strlen(input)) == 0)
            return strdup(aliases->alias[i] + strlen(input));
    }
    return NULL;
}

char *search_in_dir(char *input, char *dir_path)
{
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        return NULL;
    }
    struct dirent *entry;
    char *matched_name = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(input, entry->d_name, strlen(input)) == 0) {
            matched_name = strdup(entry->d_name);
            break;
        }
    }
    closedir(dir);
    char *new = matched_name ? strdup(matched_name + strlen(input)) : NULL;
    free(matched_name);
    return new;
}

char *autocomplete_from_path(char *input, envdata_t *env)
{
    if (input[0] == '.' || input[0] == '/')
        return NULL;
    char *resa = search_alias(input, env->aliases);
    if (resa)
        return resa;
    pathdir_t *dir_path = *(env->path_dirs);
    for (; dir_path;) {
        char *res = search_in_dir(input, dir_path->dir);
        if (res)
            return res;
        dir_path = dir_path->next;
    }
    return NULL;
}

/*
─▄▀▀▀▀▄─█──█────▄▀▀█─▄▀▀▀▀▄─█▀▀▄
─█────█─█──█────█────█────█─█──█
─█────█─█▀▀█────█─▄▄─█────█─█──█
─▀▄▄▄▄▀─█──█────▀▄▄█─▀▄▄▄▄▀─█▄▄▀

─────────▄██████▀▀▀▀▀▀▄
─────▄█████████▄───────▀▀▄▄
──▄█████████████───────────▀▀▄
▄██████████████─▄▀───▀▄─▀▄▄▄──▀▄
███████████████──▄▀─▀▄▄▄▄▄▄────█
█████████████████▀█──▄█▄▄▄──────█
███████████──█▀█──▀▄─█─█─█───────█
████████████████───▀█─▀██▄▄──────█
█████████████████──▄─▀█▄─────▄───█
█████████████████▀███▀▀─▀▄────█──█
████████████████──────────█──▄▀──█
████████████████▄▀▀▀▀▀▀▄──█──────█
████████████████▀▀▀▀▀▀▀▄──█──────█
▀████████████████▀▀▀▀▀▀──────────█
──███████████████▀▀─────█──────▄▀
──▀█████████████────────█────▄▀
────▀████████████▄───▄▄█▀─▄█▀
──────▀████████████▀▀▀──▄███
──────████████████████████─█
─────████████████████████──█
────████████████████████───█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████▄▄▄▄▄█

─────────────█─────█─█──█─█───█
─────────────█─────█─█──█─▀█─█▀
─────────────█─▄█▄─█─█▀▀█──▀█▀
─────────────██▀─▀██─█──█───█
*/
