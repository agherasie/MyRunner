/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** buttons.c
*/

#include "my_runner.h"

void select_screen(game *g)
{
    if (g->pause_frame > 250) {
        if (g->character_menu == sfTrue) {
            button_draw(g, 0, "sonic", 0);
            button_draw(g, 1, "tails", 0);
            button_draw(g, 2, "knuckles", 0);
        } else {
            button_draw(g, 0, "continue playing", 0);
            button_draw(g, 1, "restart level", 0);
            button_draw(g, 2, "return to title", 0);
            button_draw(g, 3, "exit game", 2);
        }
    }
    fade_transition(g);
}

void button_draw(game *g, int number, char *str, float offset)
{
    if (g->select == number) {
        unsigned int chr_size = sfText_getCharacterSize(g->score_text);
        sfText_setFillColor(g->score_text, sfYellow);
        sfText_setCharacterSize(g->score_text, chr_size + 5);
        draw_text(g, str, W_W / 2 / 20 - 9, 8 + 4 * number + offset);
        sfText_setFillColor(g->score_text, sfWhite);
        sfText_setCharacterSize(g->score_text, chr_size);
    } else
        draw_text(g, str, W_W / 2 / 20 - 9, 8 + 4 * number + offset);
}

void select_button(game *g, player *p)
{
    sfKeyCode key = g->event.key.code;
    if (key == sfKeyUp || key == sfKeyDown || key == sfKeyEnter) {
        sfMusic_stop(g->select_sound);
        sfMusic_play(g->select_sound);
    }
    if (key == sfKeyUp)
        g->select--;
    if (key == sfKeyDown)
        g->select++;
    if (key == sfKeyEnter) {
        if (g->character_menu == sfTrue)
            character_buttons(g, p);
        else
            buttons(g, p);
    }
    int button_number = 5;
    if (g->character_menu == sfTrue)
        button_number = 4;
    g->select %= button_number - 1;
    if (g->select < 0)
        g->select = button_number - 2;
}
