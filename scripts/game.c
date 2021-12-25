/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** game.c
*/

#include "my_runner.h"

void destroy_all(game *g, player *p)
{
    sfSprite_destroy(g->tile->spr);
    sfTexture_destroy(g->tile->text);
    sfClock_destroy(g->clock);
    sfSprite_destroy(p->obj->spr);
    sfTexture_destroy(p->obj->text);
    for (int i = 0; g->map[i] != NULL; i++)
        free(g->map[i]);
    free(g->map);
    sfMusic_destroy(g->bg_music);
    sfMusic_destroy(p->jump_sound);
    sfSprite_destroy(g->parallax0->spr);
    sfSprite_destroy(g->parallax1->spr);
    sfTexture_destroy(g->parallax0->text);
    sfTexture_destroy(g->parallax1->text);
    sfRenderWindow_destroy(g->window);
}

void pause_game(game *g)
{
    if (g->event.key.code == sfKeyP) {
        if (g->paused == sfTrue)
            g->paused = sfFalse;
        else
            g->paused = sfTrue;
    }
}

void keyboard_events(game *g, player *p)
{
    while (sfRenderWindow_pollEvent(g->window, &g->event)) {
        if (g->event.type == sfEvtClosed)
            sfRenderWindow_close(g->window);
        if (g->event.type == sfEvtKeyPressed) {
            pause_game(g);
        }
        player_keyboard_events(g, p);
    }
}

void update(game *g, player *p)
{
    while (sfRenderWindow_isOpen(g->window)) {
        g->time = sfClock_getElapsedTime(g->clock);
        if (g->time.microseconds > 1000) {
            sfClock_restart(g->clock);
            if (p->goal_reached == sfFalse)
                g->camera_pan_x += g->camera_pan_speed;
            sfRenderWindow_display(g->window);
            sfRenderWindow_clear(g->window, sfWhite);
            keyboard_events(g, p);
            update_background(g, p);
            g->goalsign->pos.x = (g->width - 2) * 100 - g->camera_pan_x;
            g->goalsign->pos.y = 3 * 100;
            sfSprite_setPosition(g->goalsign->spr, g->goalsign->pos);
            sfRenderWindow_drawSprite(g->window, g->goalsign->spr, NULL);
            update_enemies(g, p);
            update_player(p, g);
        }
    }
    destroy_all(g, p);
    return;
}