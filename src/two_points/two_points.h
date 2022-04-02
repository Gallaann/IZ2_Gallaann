//
// Created by gallaann on 30.03.2022.
//

#ifndef IZ2_GALLAANN_TWO_POINTS_H
#define IZ2_GALLAANN_TWO_POINTS_H

#include "stdlib.h"
#include "math.h"

typedef struct {
    char first_x; //char values are stored in 1 byte in memory
    char first_y; //and char type is integer type in C
    char second_x;
    char second_y;
} two_points; // int32_t = 4 bytes in memory

two_points divide_to_coordinates(int32_t tuple);
double length(two_points points);

#endif //IZ2_GALLAANN_TWO_POINTS_H
