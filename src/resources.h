#ifndef RESOURCES_H
#define RESOURCES_H

#include "engine/include/hashtable.h"
#include "engine/include/assets.h"
#include <string.h>

HashTable* init_resources();
extern unsigned char src_assets_black_png[];
extern int src_assets_black_png_len;

extern unsigned char src_assets_random_block_png[];
extern int src_assets_random_block_png_len;

extern unsigned char src_assets_door_png[];
extern int src_assets_door_png_len;

extern unsigned char src_assets_wall_jpg[];
extern int src_assets_wall_jpg_len;

extern unsigned char src_assets_block_circles_png[];
extern int src_assets_block_circles_png_len;

extern unsigned char src_assets_background_png[];
extern int src_assets_background_png_len;

#endif // RESOURCES_H
