#include <unistd.h>
#include <curses.h>

#include "dante_viewver.h"

int main(int argc, char **argv)
{
    map_t *map __attribute__ ((__cleanup__ (free_map))) = NULL;

    if (argc != 2) {
        write(2, "viewver <labyrinth file>\n", 25);
        return (1);
    }
    map = read_file(argv[1]);
    if (!map)
        return (1);
    return (start(map));
}