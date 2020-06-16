#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "dante_viewver.h"

static int solve(map_t *map, ssize_t row, ssize_t col)
{
    int result;

    if (row < 0 || col < 0 || !map->data[row] || !map->data[row][col]
        || map->data[row][col] != '*')
        return (0);
    map->data[row][col] = 'o';
    display(map, row, col);
    usleep(130000);
    if (getch() == 27)
        return (1);
    if (!map->data[row + 1] && !map->data[row][col + 1])
        return (1);
    result = solve(map, row, col + 1) || solve(map, row + 1, col)
             || solve(map, row, col - 1) || solve(map, row - 1, col);
    if (!result) {
        map->data[row][col] = '*';
        display(map, row, col);
        usleep(130000);
    }
    return (result);
}

int start(map_t *map)
{
    WINDOW *window = initscr();
    int input;

    keypad(window, TRUE);
    curs_set(0);
    nodelay(window, true);
    init_colors();
    timeout(0);
    if (solve(map, 0, 0) == -1) {
        endwin();
        return (2);
    }
    do {
        input = getch();
    } while (input != 27);
    endwin();
    return (0);
}