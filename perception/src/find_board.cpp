// Copyright (c) 2019 BluHaptics Inc., All Rights Reserved.
#include "find_board.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void FindBoard::getCorners(cv::Mat img)
{
    // convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // blur
    int kernel_size = 5;
    cv::Mat blur_gray;
    cv::GaussianBlur(gray, blur_gray, {kernel_size, kernel_size}, 0);

    // edge detection
    int low_threshold = 50;
    int high_threshold = 150;
    cv::Mat edges;
    cv::Canny(blur_gray, edges, low_threshold, high_threshold);

    // line detection
    double rho = 1;              // distance resolution in pixels of the Hough grid
    double theta = CV_PI / 180;  // angular resolution in radians of the Hough grid
    int threshold = 50;          // minimum number of votes (intersections in Hough grid cell)
    double min_line_length = 50; // minimum number of pixels making up a line
    double max_line_gap = 20;    // maximum gap in pixels between connectable line segments

    // Run Hough on edge detected image
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, rho, theta, threshold, min_line_length, max_line_gap);
    for (size_t i = 0; i < lines.size(); i++)
    {
        cv::line(img, cv::Point(lines[i][0], lines[i][1]),
                 cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0, 0, 255), 1, 8);
    }

    if (lines.size() > 1)
    {
        for (size_t i = 0; i < lines.size(); i++)
        {
            for (size_t j = 0; j < lines.size(); j++)
            {
                auto point = intersection(lines.at(i), lines.at(j));

                cv::circle(img, cv::Point(point[0], point[1]), 5, cv::Scalar(0, 255, 0), cv::FILLED);
            }
        }
    }

    cv::imwrite("/test_output/lines.jpeg", img);
}

cv::Vec2i FindBoard::intersection(cv::Vec4i line_1, cv::Vec4i line_2)
{
    int a_x = line_1[0];
    int a_y = line_1[1];
    int b_x = line_1[2];
    int b_y = line_1[3];
    int c_x = line_2[0];
    int c_y = line_2[1];
    int d_x = line_2[2];
    int d_y = line_2[3];

    // stuff for line 1
    int a1 = b_y - a_y;
    int b1 = a_x - b_x;
    int c1 = a1 * a_x + b1 * a_y;

    // stuff for line 2
    int a2 = d_y - c_y;
    int b2 = c_x - d_x;
    int c2 = a2 * c_x + b2 * c_y;

    int determinant = a1 * b2 - a2 * b1;

    std::cout << "determinant " << determinant << std::endl;

    if (determinant == 0)
    {
        // Return(infinity, infinity) if they never intersect
        // By "never intersect", I mean that the lines are parallel to each other
        return {0, 0};
    }
    else
    {
        int x = (b2 * c1 - b1 * c2) / determinant;
        int y = (a1 * c2 - a2 * c1) / determinant;

        // slopes
        float m1;
        float m2;
        if ((b_x - a_x) != 0)
            m1 = (float)(b_y - a_y) / (float)(b_x - a_x);
        else
            m1 = std::numeric_limits<float>::max();

        if ((c_x - d_x) != 0)
            m2 = (float)(c_y - d_y) / (float)(c_x - d_x);
        else
            m2 = std::numeric_limits<float>::max();

        float theta = atan(std::abs((m2 - m1) / (1 + m1 * m2)));
        std::cout << "intersection " << x << " " << y << " theta " << theta * 180 / 3.1415926535 << std::endl;
        return {x, y};
    }
}