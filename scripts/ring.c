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

ring *create_rings(int ring_count, char **map)
{
    ring *r = malloc(sizeof(enemy) * (ring_count + 1));
    r[ring_count] = (ring) {(sfVector2f) {-100, 0}, sfFalse, sfTrue};
    for (int i = 0; i < ring_count; i++) {
        int random_value = i * 50 + 225;
        float y_pos = 0;
        int free_spot = 0;
        int map_pos_x = random_value / 100;
        if (random_value % 100 > 50)
            map_pos_x++;
        free_spot = find_free_spot(map, map_pos_x);
        if (map[free_spot][map_pos_x] == 100
        || map[free_spot][map_pos_x] == 102)
            if (random_value % 100 == 25) {
                free_spot -= 2;
                random_value -= 25;
                y_pos += 50;
            } else {
                free_spot --;
                random_value += 25;
            }
        y_pos += free_spot * 100;
        r[i].pos = (sfVector2f) {random_value, y_pos};
        r[i].is_collected = sfFalse;
        r[i].is_null = sfFalse;
        if (map[free_spot][map_pos_x] == 5 || map[5][map_pos_x] == 6)
            r[i].is_collected = sfTrue;
        if (map[free_spot][map_pos_x] == 104)
            r[i].is_collected = sfTrue;
    }
    return r;
}
