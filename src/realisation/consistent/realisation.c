//
// Created by gallaann on 01.04.2022.
//

#include "../realisation.h"

int work(size_t amount){
    scanf ("%li",&amount);

    FILE* file = fopen("../input_file.txt", "r");

    Storage storage = storage_constructor(amount);
    fill_storage(&storage,file);
    for (size_t i = 0; i < amount; ++i){
        storage.length[i] = length(storage.points[i]);
    }
    print_storage(&storage);
    free_storage(&storage);

    fclose(file);

    return 1;
}
