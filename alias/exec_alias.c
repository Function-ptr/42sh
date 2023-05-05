/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include "alias.h"

void replace(char *str, char *src, char *dest) {
    int srcLen = strlen(src), destLen = strlen(dest), strLen = strlen(str),
    count = 0; char *pos = str;
    while ((pos = strstr(pos, src)) != NULL) {
        count++; pos += srcLen;
    }
    int newLen = strLen + count * (destLen - srcLen) + 1;
    if (newLen > strLen) {
        char *newStr = (char *)malloc(newLen * sizeof(char));
        char *destPos = newStr;
        char *srcPos = str;
        while ((pos = strstr(srcPos, src)) != NULL) {
            int copyLen = pos - srcPos;
            strncpy(destPos, srcPos, copyLen);
            destPos += copyLen;
            strncpy(destPos, dest, destLen);
            destPos += destLen;
            srcPos = pos + srcLen;
        }
        strcpy(destPos, srcPos); strcpy(str, newStr); free(newStr);
    }
}

void exec_alias(command_t *cmd, envdata_t *env)
{
    node_t *current = env->aliases;
    while (current != NULL) {
        replace(cmd->command, current->data_a, current->data_b);
        current = current->next;
    }
}
