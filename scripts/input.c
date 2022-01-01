/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** input.c
*/

#include "my_runner.h"

void press_enter(game *g, player *p)
{
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
}

void keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtClosed)
        sfRenderWindow_close(g->window);
    if (g->event.type == sfEvtLostFocus
    && g->is_main_menu == sfFalse && p->goal_reached == sfFalse)
        g->paused = sfTrue;
    if (g->event.type == sfEvtKeyPressed) {
        pause_game(g, p);
        press_enter(g, p);
        level_init(g);
        if (g->event.key.code == sfKeyR)
            toggle(&g->is_runner);
        if (g->event.key.code == sfKeyD)
            toggle(&g->debug);
        if (g->event.key.code == sfKeyE)
            for (int i = 0; g->e[i].enemytype != -1; i++)
                g->e[i].is_dead = sfTrue;
    }
    if (!(p->anim_state == HURTING && p->is_grounded == sfFalse)
    && g->paused == sfFalse)
        player_keyboard_events(g, p);
    else
        player_release_key(g, p);
}
