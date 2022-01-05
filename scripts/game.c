/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** game.c
*/

#include "my_runner.h"

void toggle(sfBool *boolean)
{
    if (*boolean == sfTrue)
        *boolean = sfFalse;
    else
        *boolean = sfTrue;
}

void level_init(game *g)
{
    if (g->event.key.code == sfKeyNum1)
        g->level = 1;
    if (g->event.key.code == sfKeyNum2)
        g->level = 2;
    if (g->event.key.code == sfKeyNum3)
        g->level = 3;
    if (g->event.key.code == sfKeyB)
        g->act = 3;
}

void fade_transition(game *g)
{
    int alpha = 0;
    if (g->pause_frame < 255)
        alpha = g->pause_frame;
    if (g->pause_frame >= 255)
        alpha = 255 - g->pause_frame % 255;
    if (g->pause_frame >= 255 * 2)
        alpha = 0;
    g->pause_frame += 20;
    sfRectangleShape *screen = sfRectangleShape_create();
    sfRectangleShape_setFillColor(screen, (sfColor) {0, 0, 0, alpha});
    sfRectangleShape_setSize(screen, (sfVector2f) {W_W, W_H});
    sfRenderWindow_drawRectangleShape(g->window, screen, NULL);
    sfRectangleShape_destroy(screen);
}

void update(game *g, player *p)
{
    while (sfRenderWindow_isOpen(g->window))
        if (sfClock_getElapsedTime(g->clock).microseconds > 1000)
            update_clock(g, p);
    destroy_all(g, p);
    if (g->relaunch == sfTrue)
        launch_game();
    return;
}
