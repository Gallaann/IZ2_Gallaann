//
// Created by gallaann on 02.04.2022.
//

#include <gtest/gtest.h>

extern "C" {
#include "storage.h"
}

TEST(points_tests,points_divider_test){
    two_points test1 = {0, 0, 0, 1};
    two_points test2 = divide_to_coordinates(1);
    EXPECT_EQ(test1.first_x, test2.first_x);
    EXPECT_EQ(test1.first_y, test2.first_y);
    EXPECT_EQ(test1.second_x, test2.second_x);
    EXPECT_EQ(test1.second_y, test2.second_y);
}

TEST(points_tests,points_length_test){
    two_points test = {0,0,0,1};
    EXPECT_EQ(1, length(test));

    test = {0,0,0,0};
    EXPECT_EQ(0, length(test));
}

TEST(storage_tests,storage_constructor_test){
    Storage test_storage = storage_constructor(1);

    EXPECT_EQ(1,test_storage.size);
    EXPECT_TRUE(test_storage.points);
    EXPECT_TRUE(test_storage.length);

    free_storage(&test_storage);
}

TEST(storage_tests, fill_storage_test){
    Storage storage = storage_constructor(1);
    char str_mimic1[] = "";
    FILE* NULL_file = fmemopen(str_mimic1, strlen(str_mimic1), "r");
    EXPECT_EQ(0, fill_storage(&storage, NULL_file));

    char str_mimic2[] = "1 ";
    FILE* test_file = fmemopen(str_mimic2, strlen(str_mimic2), "r");
    EXPECT_EQ(1, fill_storage(&storage, test_file));

    free_storage(&storage);
    fclose(NULL_file);
    fclose(test_file);
}

TEST(storage_tests,print_storage_test){
    Storage test_storage = storage_constructor(3);
    char str_mimic[] = "1 2 3\n";
    FILE* test_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    fill_storage(&test_storage,test_file);

    testing::internal::CaptureStdout();
    print_storage(&test_storage);
    std::string print_storage_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(print_storage_output,"\t0\t0\t0\t1\t\tlength: 0.000000\n\t0\t0\t0\t2\t\tlength: 0.000000\n\t0\t0\t0\t3\t\tlength: 0.000000\n");

    free_storage(&test_storage);
}

TEST(storage_tests,free_storage_test){
    Storage test_storage = storage_constructor(3);
    char str_mimic[] = "1 2 3\n";
    FILE* test_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    fill_storage(&test_storage,test_file);

    free_storage(&test_storage);
    EXPECT_TRUE(!test_storage.points);
    EXPECT_TRUE(!test_storage.length);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}