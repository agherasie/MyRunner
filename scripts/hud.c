/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** hud.c
*/

#include "my_runner.h"

void clock_draw(game *g, int time, int o)
{
    sfText_setFillColor(g->score_text, sfYellow);
    draw_text(g, "time", 1 + o, 3 + o);
    sfText_setFillColor(g->score_text, sfWhite);
    draw_text(g, " :", 6 + o, 3 + o);
    draw_text(g, my_itoa(time / 60), 6 + o, 3 + o);
    time %= 60;
    if (time < 10) {
        draw_text(g, "0", 7.5f + o, 3 + o);
        draw_text(g, my_itoa(time), 8.5 + o, 3 + o);
    } else
        draw_text(g, my_itoa(time), 7.5f + o, 3 + o);
}

void score_update(game *g, int o)
{
    if (g->score < 0)
        g->score = 0;
    if (g->hiscore < g->score) {
        g->hiscore = g->score;
        set_score(&g->hiscore);
    }
    d_txt_var(g, "score", (sfVector2i) {1 + o, 1 + o}, g->score);
    if (g->score < g->hiscore)
        d_txt_var(g, "hiscore", (sfVector2i) {1 + o, 7 + o}, g->hiscore);
}

void hud_display(game *g, sfBool center)
{
    int o = 0;
    if (center == sfTrue)
        o = 10;
    sfText_setFillColor(g->score_text, sfYellow);
    score_update(g, o);
    if (g->frame % 30 >= 15 && g->rings == 0)
        sfText_setFillColor(g->score_text, sfRed);
    d_txt_var(g, "rings", (sfVector2i) {1 + o, 5 + o}, g->rings);
    sfText_setFillColor(g->score_text, sfWhite);
    clock_draw(g, g->seconds / FPS, o);
    draw_spr_at_pos(g, g->player_icon->spr, o * 20 + 10, o * 20 + W_H - 100);
    draw_text(g, my_itoa(g->lives), 4.5f + o, W_H / 20 - 3.5f + o);
}
