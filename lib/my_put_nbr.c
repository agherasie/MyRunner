/*
** EPITECH PROJECT, 2021
** my_put_nbr.c
** File description:
** fffffff
*/

void my_putchar(char c);

long checks(long *nb)
{
    if (*nb < 0) {
        my_putchar('-');
        *nb *= -1;
        return *nb;
    }
    if (*nb == 0) {
        my_putchar('0');
        return *nb;
    }
}

long print_zero(long c, long c2)
{
    while (c - c2 > 0) {
        my_putchar(48);
        c--;
    }
}

int my_put_nbr(long nb)
{
    long new_nb = 0;
    long c = 0;
    long c2 = 0;

    nb = checks(&nb);
    while (nb != 0) {
        new_nb = new_nb * 10;
        new_nb = new_nb + (nb % 10);
        nb = nb / 10;
        c++;
    }
    while (new_nb != 0) {
        my_putchar((new_nb % 10) + 48);
        new_nb /= 10;
        c2++;
    }
    print_zero(c, c2);
    return (new_nb);
}
