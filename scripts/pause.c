/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** pause.c
*/

#include "my_runner.h"

void button_draw(game *g, int number, char *str)
{
    if (g->select == number) {
        sfText_setFillColor(g->score_text, sfYellow);
        sfText_setCharacterSize(g->score_text, sfText_getCharacterSize(g->score_text) + 5);
        draw_text(g, str, W_W / 2 / 20 - 9, 8 + 4 * number);
        sfText_setFillColor(g->score_text, sfWhite);
        sfText_setCharacterSize(g->score_text, sfText_getCharacterSize(g->score_text) - 5);
    } else
        draw_text(g, str, W_W / 2 / 20 - 9, 8 + 4 * number);
}

void buttons(game *g, player *p)
{
    if (g->select == 1)
        restart(g, p);
    if (g->select == 2) {
        sfRenderWindow_close(g->window);
        launch_game();
    }
    if (g->select == 3)
        sfRenderWindow_close(g->window);
    if (g->select == 4) {
        sfSprite_setTexture(p->obj->spr, g->knux_text, sfFalse);
        *p = create_knux_animations(*p);
    }
    g->paused = sfFalse;
    g->select = 0;
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
    if (key == sfKeyEnter)
        buttons(g, p);
    if (g->select < 0)
        g->select = 4;
    g->select %= 5;
}

void pause_menu(game *g)
{
    if (g->pause_frame > 250) {
        button_draw(g, 0, "continue playing");
        button_draw(g, 1, "restart level");
        button_draw(g, 2, "return to title");
        button_draw(g, 3, "exit game");
        button_draw(g, 5, "tails");
        button_draw(g, 4, "knuckles");
    }
    fade_transition(g);
}

void pause_game(game *g, player *p)
{
    if (g->event.key.code == sfKeyP && g->is_main_menu == sfFalse) {
        if (g->paused == sfTrue)
            g->paused = sfFalse;
        else {
            g->paused = sfTrue;
            g->pause_frame = 0;
        }
    }
    if (g->paused == sfTrue)
        select_button(g, p);
}
