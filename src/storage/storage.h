//
// Created by gallaann on 30.03.2022.
//

#include "two_points.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct {
    size_t size;
    two_points* points;
    double* length;
} Storage;

Storage storage_constructor(size_t amount_of_tuples);
int fill_storage(Storage* storage, FILE* file);
void print_storage(Storage* storage);
void free_storage(Storage* storage);