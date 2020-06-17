#include <curses.h>
#include <string.h>

#include "dante_viewver.h"

static void set_char(int y, int x, char c)
{
    if (y == (LINES / 2) && x == (COLS / 2)) {
        attron(COLOR_PAIR(SELF));
        mvaddch(y, x, c);
        attroff(COLOR_PAIR(SELF));
        return;
    }
    switch (c) {
        default:
            attron(COLOR_PAIR(WALL));
            mvaddch(y, x, c);
            attroff(COLOR_PAIR(WALL));
            break;
        case PATH_CHAR:
            attron(COLOR_PAIR(PATH));
            mvaddch(y, x, c);
            attroff(COLOR_PAIR(PATH));
            break;
        case SOLVE_CHAR:
            attron(COLOR_PAIR(SOLVE));
            mvaddch(y, x, c);
            attroff(COLOR_PAIR(SOLVE));
            break;
    }
}

static void display_line(const char *line, ssize_t tab_y, int y, size_t x)
{
    int middle_x = COLS / 2;
    ssize_t tab_x = x - ((size_t) middle_x);
    int i;

    for (i = 0; tab_y >= 0 && (tab_x < 0 || line[tab_x])
        && i < COLS; i++, tab_x++) {
        if (tab_x >= 0)
            set_char(y, i, line[tab_x]);
        else
            set_char(y, i, WALL_CHAR);
    }
    for (; i < COLS; i++)
        set_char(y, i, WALL_CHAR);
}

int display(map_t *map, size_t y, size_t x)
{
    int middle_y;
    ssize_t tab_y;
    int i = 0;

    if (y >= map->height || x >= map->width)
        return (0);
    middle_y = LINES / 2;
    tab_y = y - ((size_t) middle_y);
    for (; (tab_y < 0 || map->data[tab_y]) && i < LINES; i++, tab_y++)
        display_line(map->data[tab_y], tab_y, i, x);
    for (; i < LINES; i++)
        for (int j = 0; j < COLS; j++)
            set_char(i, j, WALL_CHAR);
    refresh();
    return (1);
}

void init_colors(void)
{
    start_color();
    init_color(DCOLOR_BLACK, 0, 0, 0);
    init_color(DCOLOR_WHITE, 1000, 1000, 1000);
    init_color(DCOLOR_GRAY, 220, 220, 220);
    init_color(DCOLOR_BLUE, 0, 0, 1000);
    init_color(DCOLOR_BROWN, 500, 0, 0);
    init_color(DCOLOR_RED, 1000, 0, 0);
    init_pair(WALL, WALL_COLOR_FG, WALL_COLOR_BG);
    init_pair(PATH, PATH_COLOR_FG, PATH_COLOR_BG);
    init_pair(SOLVE, SOLVE_COLOR_FG, SOLVE_COLOR_BG);
    init_pair(SELF, SELF_COLOR_FG, SELF_COLOR_BG);
}
