/*
** EPITECH PROJECT, 2021
** B-MAT-100-LYN-1-1-101pong-alexandru.gherasie
** File description:
** nbr_analysis.c
*/

int power_of_nbr(long number)
{
    long count = 1;
    for (number; number > 9; number /= 10)
        count *= 10;
    return count;
}

int number_of_digits(long number)
{
    int count = 0;
    for (number; number > 9; number /= 10)
        count++;
    return count;
}

int power_of_ten(int count)
{
    long number = 1;
    for (count; count > 0; count--)
        number *= 10;
    return number;
}

int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}