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

void keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtClosed)
        sfRenderWindow_close(g->window);
    if (g->event.type == sfEvtKeyPressed) {
        pause_game(g, p);
        if (g->event.key.code == sfKeyEnter) {
            if (g->is_main_menu == sfTrue) {
                g->character_menu = sfTrue;
                g->paused = sfTrue;
            }
            if (p->goal_reached == sfTrue) {
                g->tally_speed = 2;
                p->cooldown = 9700;
            }
        }
        if (g->event.key.code == sfKeyR)
            toggle(&g->is_runner);
    }
}

void fade_transition(game *g)
{
    int alpha = 0;
    if (g->pause_frame < 255)
        alpha = g->pause_frame;
    if (g->pause_frame >= 255)
        alpha = 255 - g->pause_frame % 255;
    if (g->pause_frame >= 255*2)
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
    return;
}