/*
** EPITECH PROJECT, 2021
** RUNNER
** File description:
** main.c
*/

#include "my_runner.h"

int launch_game()
{
    game g = create_game();
    player p = create_player(&g);
    sfRenderWindow_setMouseCursorVisible(g.window, sfTrue);
    sfRenderWindow_setFramerateLimit(g.window, FPS);
    update(&g, &p);
    return EXIT_SUCCESS;
}

void print_file(char *filepath, int buffsize)
{
    int fp = open(filepath, O_RDONLY);
    char buff[buffsize];
    if (fp != -1) {
        read(fp, buff, buffsize);
        my_putstr(buff);
        close(fp);
    }
    return;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        srand(time(NULL));
        return launch_game();
    } else if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0)
            print_file("readme", 1000);
        if (my_strcmp(av[1], "-c") == 0)
            print_file("credits", 2100);
    }
}
