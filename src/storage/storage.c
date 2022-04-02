//
// Created by gallaann on 30.03.2022.
//

#include "storage.h"
#include "two_points.h"
#include "stdlib.h"
#include "string.h"

Storage storage_constructor(size_t amount_of_tuples){
    Storage storage;
    storage.size = amount_of_tuples;
    storage.points = (two_points*) malloc(amount_of_tuples * sizeof(two_points));
    storage.length = (double*) malloc(amount_of_tuples * sizeof(double ));

    return storage;
}

int fill_storage(Storage* storage, FILE* file){
    if (file == NULL){
        return 0;
    }

    char* raw = NULL;
    size_t input_size;
    getline(&raw, &input_size, file);
    int32_t tuple;

    for (size_t i = 0; i < storage->size; ++i){
        char* str = NULL;
        char *end;
        if (i == 0){
            str = strtok(raw, " \n");
        }else{
            str = strtok(NULL, " \n");
        }

        if (str==NULL){
            return 0;
        }

        tuple = strtol(str,&end,10);

        storage->points[i] = divide_to_coordinates(tuple);
    }

    return 1;
}

void print_storage(Storage* storage){
    for (size_t i = 0; i < storage->size; ++i){
        printf("\t%i", storage->points[i].first_x);
        printf("\t%i", storage->points[i].first_y);
        printf("\t%i", storage->points[i].second_x);
        printf("\t%i", storage->points[i].second_y);
        printf("\t\tlength: %lf\n", storage->length[i]);
    }
}

void free_storage(Storage* storage){
    free(storage->points);
    storage->points = NULL;
}
