/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** tile_interpretor.c
*/

#include "my_runner.h"

void spring_placement(char **map, int y, int x, int maxy)
{
    if (y > 2 && y < maxy - 1 && map[y + 1][x] == 3
    && is_solid(map[y + 1][x]) == 0
    && is_solid(map[y][x + 1]) == 0 && is_solid(map[y - 1][x + 1]) == 0)
        if (is_solid(map[y - 3][x + 1]) == 0)
            map[y][x] = 102;
        else
            map[y][x] = 100;
    if (y < maxy - 1 && map[y + 1][x] == 3 && map[y][x - 1] == 2
    && is_solid(map[y][x + 1]) == 1 && is_solid(map[y][x + 2]) == 1)
        map[y][x] = 104;
    if (map[y][x] == 0 && y == maxy - 1)
        map[y][x] = 6;
}

void decoration_tiles(char **map, int y, int x, int maxy)
{
    if (map[y][x] == 0 && map[y + 1][x] == 3)
        if (range(0, 100) > 95)
            map[y][x] = either_or(either_or(9, 10), 10);
    int h = range(1, 3);
    if (y - h <= 0)
        return;
    if (map[y][x] == 3 && map[y - 1][x] == 0 && map[y - h][x] == 0
    && range(0, 100) > 95) {
        map[y - h - 1][x] = 7;
        for (h; h > 0; h--)
            map[y - h][x] = 8;
    }
}

void tile_interpretor(char **map, int y, int x)
{
    int maxy = 0;
    for (maxy; map[maxy] != NULL; maxy++);
    if (map[y][x] == 2 && map[y - 1][x] == 0)
        map[y][x] = 3;
    if (x > 3 && y < maxy - 1 && map[y + 1][x] == 3 && map[y][x] == 0
    && map[y][x - 1] == 2 && map[y][x + 1] == 2)
        map[y][x] = either_or(100, 5);
    spring_placement(map, y, x, maxy);
    decoration_tiles(map, y, x, maxy);
}