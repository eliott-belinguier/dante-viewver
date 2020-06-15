#include <stdlib.h>

#include "dante_viewver.h"

void free_map(map_t **map)
{
    if (!map || !*map)
        return;
    if ((*map)->data)
        for (size_t i = 0; (*map)->data[i]; i++)
            free((*map)->data[i]);
    free((*map)->data);
    free(*map);
}