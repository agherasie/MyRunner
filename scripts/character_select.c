/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** character_select.c
*/

#include "my_runner.h"

void switch_character(game *g, player *p, char character)
{
    switch (character) {
        case 's':
            sfSprite_setTexture(p->obj->spr, g->sonic_text, sfFalse);
            g->player_icon->rect.left = 50;
            break;
        case 't':
            sfSprite_setTexture(p->obj->spr, g->tails_text, sfFalse);
            g->player_icon->rect.left = 100;
            break;
        case 'k':
            sfSprite_setTexture(p->obj->spr, g->knux_text, sfFalse);
            g->player_icon->rect.left = 150;
            break;
    }
    *p = create_animations(*p, character);
    sfSprite_setTextureRect(g->player_icon->spr, g->player_icon->rect);
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
    g->level = 1;
}
