/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** title.c
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
    switch_music(g, g->title_music);
    animate_sonic_title(g);
    if (g->pause_frame > 250)
        g->is_main_menu = sfFalse;
}
