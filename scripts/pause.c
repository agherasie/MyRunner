/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** pause.c
*/

#include "my_runner.h"

void buttons(game *g, player *p)
{
    if (g->select == 1)
        restart(g, p);
    if (g->select == 2) {
        sfRenderWindow_close(g->window);
        g->relaunch = sfTrue;
    }
    if (g->select == 3)
        sfRenderWindow_close(g->window);
    g->paused = sfFalse;
    g->select = 0;
}

void pause_game(game *g, player *p)
{
    if ((g->event.key.code == sfKeyP || g->event.key.code == sfKeyEscape)
    && g->is_main_menu == sfFalse) {
        if (g->paused == sfTrue)
            g->paused = sfFalse;
        else {
            g->paused = sfTrue;
            g->pause_frame = 0;
        }
    }
    if (g->paused == sfTrue)
        select_button(g, p);
}
