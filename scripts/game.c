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

void scroll_parallax(game *g, player *p, object *parallax, int speed)
{
    if (g->paused == sfFalse && p->goal_reached == sfFalse)
        if (g->frame % speed == 0)
            parallax->rect.left += g->camera_pan_speed;
    sfSprite_setTextureRect(parallax->spr, parallax->rect);
    sfRenderWindow_drawSprite(g->window, parallax->spr, NULL);
}

void update_background(game *g, player *p)
{
    g->frame++;
    scroll_parallax(g, p, g->parallax0, 3);
    scroll_parallax(g, p, g->parallax1, 2);
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

void animate_object(game *g, object *obj, animation anim, int *frame)
{
    obj->rect.height = 50;
    obj->rect.width = 50;
    if (g->frame % anim.speed == 0 && anim.length != 1)
        *frame += 1;
    if (anim.loop == sfFalse && *frame == anim.length)
        *frame = anim.length - 1;
    if (*frame > anim.length - 1)
        *frame = 0;
    obj->rect.top = 0;
    obj->rect.left = 50 * *frame;
}

void update_enemies(game *g, player *p)
{
    for (int i = 0; i < 1; i++) {
        g->e[i].obj->pos.x += g->camera_pan_x;
        animate_object(g, g->e[i].obj, g->e[i].anim, &g->e[i].frame);
        sfSprite_setTextureRect(g->e[i].obj->spr, g->e[i].obj->rect);
        g->e[i].obj->pos.x -= g->camera_pan_x + g->camera_pan_speed;
        sfSprite_setPosition(g->e[i].obj->spr, g->e[i].obj->pos);
        sfRenderWindow_drawSprite(g->window, g->e[i].obj->spr, NULL);
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