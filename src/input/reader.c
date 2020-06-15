#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dante_viewver.h"

static void close_file(FILE **file)
{
    if (!file || !*file)
        return;
    fclose(*file);
}

static char *read_line(FILE *file, int *end)
{
    size_t n = 0;
    char *line = NULL;
    ssize_t read_size = getline(&line, &n, file);
    size_t last_index = read_size - 1;

    if (read_size < 1 || !line) {
        free(line);
        if (end)
            *end = 1;
        return (NULL);
    } else if (line[last_index] == '\n')
        line[last_index] = 0;
    if (end)
        *end = 0;
    return (line);
}

static void read_data(map_t *map, FILE *file)
{
    int end = 0;
    char *line = read_line(file, &end);
    size_t width = 0;

    *map = (map_t) {NULL, 0, 0};
    for (; !end; line = read_line(file, &end)) {
        map->data = realloc(map->data, sizeof(char *) * (++map->height + 1));
        if (map->data) {
            map->data[map->height] = NULL;
            map->data[map->height - 1] = line;
            width = strlen(line);
            map->width = (width > map->width) ? width : map->width;
        } else
            map->height = 0;
    }
}

map_t *read_file(const char *file_name)
{
    FILE *file __attribute__ ((__cleanup__ (close_file)));
    map_t *result;

    file = fopen(file_name, "r");
    if (!file)
        return (NULL);
    result = malloc(sizeof(map_t));
    if (!result)
        return (NULL);
    read_data(result, file);
    return (result);
}