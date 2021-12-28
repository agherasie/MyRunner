/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** destroy.c
*/

#include "my_runner.h"

void destroy_entities(game *g)
{
    free(g->r);
    for (int i = 0; g->e[i].enemytype != -1; i++) {
        sfSprite_destroy(g->e[i].obj->spr);
        sfTexture_destroy(g->e[i].obj->text);
    }
    free(g->e);
}

void destroy_sprites(game *g, player *p)
{
    sfSprite_destroy(g->ring->spr);
    sfSprite_destroy(g->tile->spr);
    sfSprite_destroy(p->obj->spr);
    sfSprite_destroy(g->parallax0->spr);
    sfSprite_destroy(g->parallax1->spr);
    sfSprite_destroy(g->parallax2->spr);
    sfSprite_destroy(g->parallax3->spr);
    sfSprite_destroy(g->title_sonic->spr);
    sfTexture_destroy(g->parallax0->text);
    sfTexture_destroy(g->parallax1->text);
    sfTexture_destroy(g->parallax2->text);
    sfTexture_destroy(g->parallax3->text);
    sfTexture_destroy(g->title_sonic->text);
    sfTexture_destroy(g->ring->text);
    sfTexture_destroy(g->tile->text);
    sfTexture_destroy(p->obj->text);
}

void destroy_all(game *g, player *p)
{
    destroy_entities(g);
    destroy_sprites(g, p);
    sfText_destroy(g->score_text);
    sfFont_destroy(g->hud_font);
    sfClock_destroy(g->clock);
    for (int i = 0; g->map[i] != NULL; i++)
        free(g->map[i]);
    free(g->map);
    sfMusic_destroy(g->bg_music);
    sfMusic_destroy(g->title_music);
    sfMusic_destroy(g->finish_music);
    sfMusic_destroy(g->select_sound);
    for (int i = 0; i < 10; i++)
        sfMusic_destroy(p->sound[i]);
    sfRenderWindow_destroy(g->window);
}
