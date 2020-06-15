#ifndef DANTE_VIEWVER_H_
#define DANTE_VIEWVER_H_

#define DCOLOR_BLACK 0
#define DCOLOR_WHITE 1
#define DCOLOR_GRAY 2
#define DCOLOR_BLUE 3
#define DCOLOR_BROWN 4
#define DCOLOR_RED 5


#define WALL 2
#define WALL_CHAR 'X'
#define WALL_COLOR_BG DCOLOR_BLACK
#define WALL_COLOR_FG DCOLOR_BLACK

#define PATH 3
#define PATH_CHAR '*'
#define PATH_COLOR_BG DCOLOR_GRAY
#define PATH_COLOR_FG DCOLOR_GRAY

#define SOLVE 4
#define SOLVE_CHAR 'o'
#define SOLVE_COLOR_BG DCOLOR_WHITE
#define SOLVE_COLOR_FG DCOLOR_WHITE

#define SELF 5
#define SELF_COLOR_BG DCOLOR_RED
#define SELF_COLOR_FG DCOLOR_RED

typedef struct map_s {
    char **data;
    size_t width;
    size_t height;
} map_t;

map_t *read_file(const char *file_name);
void free_map(map_t **map);
void init_colors(void);
int display(map_t *map, size_t y, size_t x);
int start(map_t *map);

#endif
