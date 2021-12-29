/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** pause.c
*/

#include "my_runner.h"

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

void buttons(game *g, player *p)
{
    if (g->select == 1)
        restart(g, p);
    if (g->select == 2) {
        sfRenderWindow_close(g->window);
        g->relaunch = sfTrue;
    }
    if (g->select == 3)
        sfRenderWindow_close(g->window);
    g->paused = sfFalse;
    g->select = 0;
}

void switch_character(game *g, player *p, char character)
{
    if (character == 's')
        sfSprite_setTexture(p->obj->spr, g->sonic_text, sfFalse);
    if (character == 't')
        sfSprite_setTexture(p->obj->spr, g->tails_text, sfFalse);
    if (character == 'k')
        sfSprite_setTexture(p->obj->spr, g->knux_text, sfFalse);
    *p = create_animations(*p, character);
}

void character_buttons(game *g, player *p)
{
    if (g->select == 0)
        switch_character(g, p, 's');
    if (g->select == 1)
        switch_character(g, p, 't');
    if (g->select == 2)
        switch_character(g, p, 'k');
    g->paused = sfFalse;
    g->select = 0;
    g->character_menu = sfFalse;
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

void pause_menu(game *g)
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
