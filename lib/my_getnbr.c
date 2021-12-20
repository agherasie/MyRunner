/*
** EPITECH PROJECT, 2021
** my_getnbr.c
** File description:
** alexandrugherasie
*/

int negative_check(char const *str)
{
    int count_minus = 0;
    int count_plus = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            count_minus++;
        } else if (str[i] == '+') {
            count_plus++;
        }
    }
    if (count_plus < count_minus) {
        return (-1);
    } else {
        return (1);
    }
}

int limit_check(long long nbr)
{
    if (nbr > 2147483647 || nbr < -2147483648) {
        return (0);
    } else {
        return nbr;
    }
}

int my_getnbr(char const *str)
{
    long long nbr = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            nbr *= 10;
            nbr += str[i] - 48;
        }
    }
    nbr *= negative_check(str);
    return (limit_check(nbr));
}