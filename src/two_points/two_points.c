//
// Created by gallaann on 30.03.2022.
//

#include "two_points.h"

#define first_byte 24U //in reverse because later 0xff used like mask of 11111111
#define second_byte 16U
#define third_byte 8U
#define fourth_byte 0U

two_points divide_to_coordinates(int32_t tuple){
    two_points divided;

    divided.first_x = (tuple >> first_byte) & 0xff;
    divided.first_y = (tuple >> second_byte) & 0xff;
    divided.second_x = (tuple >> third_byte) & 0xff;
    divided.second_y = (tuple >> fourth_byte) & 0xff;
    
    return divided;
}

double length(two_points points){
    double first_point_sqr = (points.first_x - points.second_x) * (points.first_x - points.second_x);
    double second_point_sqr = (points.first_y - points.second_y) * (points.first_y - points.second_y);
    double result = sqrt(first_point_sqr + second_point_sqr);
    return result;
}
