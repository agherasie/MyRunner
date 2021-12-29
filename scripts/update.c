/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** update.c
*/

#include "my_runner.h"

void animate_sonic_title(game *g)
{
    g->title_sonic_frame--;
    sfIntRect tr = g->title_sonic->rect;
    tr.height = 224;
    tr.width = 320;
    if (g->title_sonic_frame == 0) {
        tr.left += 320;
        g->title_sonic_frame = 10;
    }
    if (tr.left >= 320 * 3 && tr.top < 224 * 5) {
        tr.left = 0;
        tr.top += 224;
    }
    if (tr.left >= 320 * 3 && tr.top == 224 * 5) {
        tr.left = 320;
        tr.top = 224 * 5;
    }
    g->title_sonic->rect = tr;
    sfSprite_setTextureRect(g->title_sonic->spr, g->title_sonic->rect);
    sfRenderWindow_drawSprite(g->window, g->title_sonic->spr, NULL);
}

void update_title_screen(game *g)
{
    draw_text(g, "epitech 2021", W_W / 20 - 12, W_H / 20 - 3.5f);
    sfMusic_stop(g->bg_music);
    if (sfMusic_getStatus(g->title_music) != sfPlaying)
        sfMusic_play(g->title_music);
    animate_sonic_title(g);
    if (g->pause_frame > 250)
        g->is_main_menu = sfFalse;
}

void update_goalsign(game *g, player *p)
{
    g->goalsign->pos.x = (g->width - 2) * 100 - g->camera_pan_x;
    g->goalsign->pos.y = find_free_spot(g->map, (g->width - 2)) * 100;
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
    for (int i = 0; g->e[i].enemytype != -1; i++)
        update_enemies(g, p, &g->e[i]);
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
    while (sfRenderWindow_pollEvent(g->window, &g->event))
        keyboard_events(g, p);
    update_background(g, p);
    if (g->is_main_menu == sfFalse
    && (g->paused == sfFalse || g->pause_frame < 250))
        update_level(g, p);
    else if (g->is_main_menu == sfTrue)
        update_title_screen(g);
    g->frame++;
    if (g->paused == sfTrue)
        pause_menu(g);
}
