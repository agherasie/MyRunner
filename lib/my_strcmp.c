/*
** EPITECH PROJECT, 2021
** alexandrugherasie
** File description:
** my_strcmp.c
*/

int cmp_len(char *s1, char *s2)
{
    int len1 = 0;
    int len2 = 0;

    for (s1; *s1 != '\0'; s1++)
        len1++;
    for (s2; *s2 != '\0'; s2++)
        len2++;
    return (len1 - len2);
}

int my_strcmp(char *s1, char *s2)
{
    cmp_len(s1, s2);
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] < s2[i])
            return (-1);
        if (s1[i] > s2[i])
            return (1);
    }
    return cmp_len(s1, s2);
}