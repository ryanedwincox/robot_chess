// Copyright (c) 2019 BluHaptics Inc., All Rights Reserved.
#ifndef FIND_BOARD_H
#define FIND_BOARD_H

#include <opencv2/core.hpp>
#include <iostream>

class FindBoard
{
public:
    static void getCorners(cv::Mat image);
    static cv::Vec2i intersection(cv::Vec4i line_1, cv::Vec4i line_2);
};

#endif // FIND_BOARD_H