/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create_entities.c
*/

#include "my_runner.h"

enemy create_enemy(int type, float spawn_pos, int free_spot)
{
    enemy e;
    if (type == -1)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    if (type == 0)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    if (type == 1)
        e.obj = create_object(50, 2, "art/motorbug.png");
    e.pos = spawn_pos;
    e.obj->pos.y = free_spot * 100 - 10;
    e.obj->pos.x = e.pos;
    e.enemytype = type;
    e.direction = -1;
    e.frame = 0;
    create_animation(&e.anim[0], 4, 30, sfTrue);
    create_animation(&e.anim[1], 5, 10, sfFalse);
    create_animation(&e.anim[2], 5, 10, sfFalse);
    e.is_dead = sfFalse;
    return e;
}

int find_free_spot(char **map, int map_pos_x)
{
    for (int y = 1; map[y] != NULL; y++)
        if (is_solid(map[y][map_pos_x]) == 0
        && is_solid(map[y - 1][map_pos_x]) == 1)
            return y - 1;
}

enemy *create_enemies(int enemy_count, char **map)
{
    enemy_count -= 2;
    enemy *e = malloc(sizeof(enemy) * (enemy_count + 1));
    e[enemy_count] = create_enemy(-1, 0, 0);
    for (int i = 0; i < enemy_count; i++) {
        int random_value = range(i * 300 + 500, i * 300 + 500);
        int free_spot = 0;
        int map_pos_x = random_value / 100;
        if (random_value % 100 >= 50)
            map_pos_x++;
        free_spot = find_free_spot(map, map_pos_x);
        e[i] = create_enemy(either_or(0, 1), random_value, free_spot);
        if (map[free_spot][map_pos_x] == 5 || map[5][map_pos_x] == 6
        || map[free_spot][map_pos_x] >= 100) {
            e[i].is_dead = sfTrue;
            e[i].frame = e[i].anim->length;
        }
    }
    return e;
}

float ring_positioner(int *x_pos, int *map_pos_x, int *map_pos_y, char **map)
{
    float y_pos = 0;
    if (*x_pos % 100 > 50)
        *map_pos_x += 1;
    *map_pos_y = find_free_spot(map, *map_pos_x);
    if (map[*map_pos_y][*map_pos_x] == 100
    || map[*map_pos_y][*map_pos_x] == 102)
        if (*x_pos % 100 == 25) {
            *map_pos_y -= 2;
            *x_pos -= 25;
            y_pos += 50;
        } else {
            *map_pos_y--;
            *x_pos += 25;
        }
    y_pos += *map_pos_y * 100;
    return y_pos;
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
        y_pos = ring_positioner(&random_value, &map_pos_x, &free_spot, map);
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
