/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** update.c
*/

#include "my_runner.h"

void update_goalsign(game *g, player *p)
{
    g->goalsign->pos.x = (g->width - 2) * 100 - g->camera_pan.x;
    g->goalsign->pos.y = find_free_spot(g->map, (g->width - 2)) * 100;
    g->goalsign->pos.y -= g->camera_pan.y;
    if (p->goal_reached == sfTrue) {
        switch_music(g, g->finish_music);
        animate_object(g, g->goalsign, g->goalanim, &g->goalframe);
    }
    sfSprite_setPosition(g->goalsign->spr, g->goalsign->pos);
    sfSprite_setTextureRect(g->goalsign->spr, g->goalsign->rect);
    sfRenderWindow_drawSprite(g->window, g->goalsign->spr, NULL);
}

void update_level(game *g, player *p)
{
    sfMusic_stop(g->title_music);
    if (g->level != 0 && p->goal_reached == sfFalse) {
        if (g->act == 3)
            switch_music(g, g->boss_music);
        else
            switch_music(g, g->bgm[g->level - 1]);
    }
    update_goalsign(g, p);
    update_rings(g, p);
    for (int i = 0; g->e[i].enemytype != -1; i++)
        update_enemies(g, p, &g->e[i]);
    update_player(p, g);
    if (g->paused == sfFalse) {
        if (p->goal_reached == sfFalse) {
            g->seconds++;
            g->camera_pan.x += g->camera_speed.x;
            g->camera_pan.y += g->camera_speed.y;
        }
        hud_display(g, p->goal_reached);
    }
}

void update_clock(game *g, player *p)
{
    sfClock_restart(g->clock);
    sfRenderWindow_display(g->window);
    sfRenderWindow_clear(g->window, sfWhite);
    while (sfRenderWindow_pollEvent(g->window, &g->event))
        keyboard_events(g, p);
    window_events(g, p);
    update_background(g, p);
    if (g->is_main_menu == sfFalse
    && (g->paused == sfFalse || g->pause_frame < 250))
        update_level(g, p);
    else if (g->is_main_menu == sfTrue)
        update_title_screen(g);
    g->frame++;
    if (g->paused == sfTrue)
        select_screen(g);
}
