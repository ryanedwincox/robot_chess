#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "find_board.h"

using namespace cv;
int main()
{
    Mat img = imread("/test_images/empty_board.jpeg", IMREAD_COLOR);
    FindBoard::getCorners(img);

    return 0;
}