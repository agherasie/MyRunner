/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** text.c
*/

#include "my_runner.h"

void draw_text(game *g, char *str, float x, float y)
{
    sfText_setPosition(g->score_text, (sfVector2f) {20 * x, 20 * y});
    sfText_setString(g->score_text, str);
    sfRenderWindow_drawText(g->window, g->score_text, NULL);
}

void d_txt_var(game *g, char *str, sfVector2i pos, int value)
{
    draw_text(g, str, pos.x, pos.y);
    sfText_setFillColor(g->score_text, sfWhite);
    draw_text(g, my_itoa(value), pos.x + my_strlen(str) + 1, pos.y);
    sfText_setFillColor(g->score_text, sfYellow);
}

void draw_spr_at_pos(game *g, sfSprite *spr, float x, float y)
{
    sfSprite_setPosition(spr, (sfVector2f) {x, y});
    sfRenderWindow_drawSprite(g->window, spr, NULL);
}
