/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** update.c
*/

#include "my_runner.h"

void update_goalsign(game *g, player *p)
{
    g->goalsign->pos.x = (g->width - 2) * 100 - g->camera_pan_x;
    g->goalsign->pos.y = 3 * 100;
    if (p->goal_reached == sfTrue) {
        sfMusic_stop(g->bg_music);
        if (sfMusic_getStatus(g->finish_music) != sfPlaying) {
            sfMusic_play(g->finish_music);
        }
        animate_object(g, g->goalsign, g->goalanim, &g->goalframe);
    }
    sfSprite_setPosition(g->goalsign->spr, g->goalsign->pos);
    sfSprite_setTextureRect(g->goalsign->spr, g->goalsign->rect);
    sfRenderWindow_drawSprite(g->window, g->goalsign->spr, NULL);
}

void update_level(game *g, player *p)
{
    sfMusic_stop(g->title_music);
    if (sfMusic_getStatus(g->bg_music) != sfPlaying)
        sfMusic_play(g->bg_music);
    update_goalsign(g, p);
    update_rings(g, p);
    update_enemies(g, p);
    update_player(p, g);
    if (g->paused == sfFalse) {
        if (p->goal_reached == sfFalse) {
            g->seconds++;
            g->camera_pan_x += g->camera_pan_speed;
        }
        hud_display(g, p->goal_reached);
    }
}

void update_clock(game *g, player *p)
{
    sfClock_restart(g->clock);
    sfRenderWindow_display(g->window);
    sfRenderWindow_clear(g->window, sfWhite);
    keyboard_events(g, p);
    update_background(g, p);
    if (g->is_main_menu == sfFalse && (g->paused == sfFalse || g->pause_frame < 250)) {
        update_level(g, p);
    } else if (g->is_main_menu == sfTrue)
        update_title_screen(g);
    g->frame++;
    if (g->paused == sfTrue)
        pause_menu(g);
}

void update(game *g, player *p)
{
    while (sfRenderWindow_isOpen(g->window))
        if (sfClock_getElapsedTime(g->clock).microseconds > 1000)
            update_clock(g, p);
    destroy_all(g, p);
    return;
}
