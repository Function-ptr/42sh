/*
** EPITECH PROJECT, 2023
** autocomplete_dir.c
** File description:
** autocompletion for directories
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

static char* update_completion(char* completion, const char* entryName,
    const char* prefix)
{
    if (completion == NULL || strcmp(entryName, completion) < 0) {
        free(completion);
        return strdup(entryName + strlen(prefix));
    }
    return completion;
}

char* auto_complete_dir(const char* path)
{
    char* dir_path, *prefix, *last_slash = strrchr(path, '/');
    if (last_slash == NULL) {
        dir_path = "."; prefix = strdup(path);
    } else {
        dir_path = strndup(path, last_slash - path);
        prefix = strdup(last_slash + 1);
    } DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        free(prefix); if (last_slash != NULL) free(dir_path);
        return NULL;
    } struct dirent* entry; char* completion = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0)
            completion = update_completion(completion, entry->d_name, prefix);
    } closedir(dir); free(prefix); if (last_slash != NULL) free(dir_path);
    return completion;
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
