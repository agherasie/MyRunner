/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** ring.c
*/

#include "my_runner.h"

void update_rings(game *g, player *p)
{
    animate_object(g, g->ring, g->ring_anim, &g->ring_frame);
    sfSprite_setTextureRect(g->ring->spr, g->ring->rect);
    for (int i = 0; g->r[i].is_null == sfFalse; i++) {
        if (g->r[i].is_collected == sfFalse) {
            if (g->paused == sfFalse && p->goal_reached == sfFalse) {
                g->r[i].pos.x -= g->camera_speed.x;
                g->r[i].pos.y -= g->camera_speed.y;
            }
            sfSprite_setPosition(g->ring->spr, g->r[i].pos);
            sfRenderWindow_drawSprite(g->window, g->ring->spr, NULL);
        }
    }
}
