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

void scroll_parallax(game *g, object *parallax, int speed)
{
    if (g->frame % speed == 0)
        parallax->rect.left += g->camera_pan_speed;
    sfSprite_setTextureRect(parallax->spr, parallax->rect);
    sfRenderWindow_drawSprite(g->window, parallax->spr, NULL);
}

void update_background(game *g)
{
    g->frame++;
    scroll_parallax(g, g->parallax0, 3);
    scroll_parallax(g, g->parallax1, 2);
    sfVector2f tilepos = {0, 0};
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            if (g->map[i][j] >= 0 && g->map[i][j] <= 9) {
                tilepos.x = j * 100 - g->camera_pan_x;
                tilepos.y = i * 100;
                g->tile->rect.top = 0;
                g->tile->rect.left = 50 * g->map[i][j];
                sfSprite_setPosition(g->tile->spr, tilepos);
                sfSprite_setTextureRect(g->tile->spr, g->tile->rect);
                sfRenderWindow_drawSprite(g->window, g->tile->spr, NULL);
            }
        }
    }
}

void update(game *g, player *p)
{
    while (sfRenderWindow_isOpen(g->window)) {
        g->time = sfClock_getElapsedTime(g->clock);
        if (g->time.microseconds > 1000) {
            sfClock_restart(g->clock);
            g->camera_pan_x += g->camera_pan_speed;
            sfRenderWindow_display(g->window);
            sfRenderWindow_clear(g->window, sfWhite);
            keyboard_events(g, p);
            update_background(g);
            update_player(p, g);
        }
    }
    destroy_all(g, p);
    return;
}