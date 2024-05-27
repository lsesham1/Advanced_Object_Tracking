#ifndef ANGLER
#define ANGLER
#include <cmath>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Angler {
public:
    float getAngle(cv::Point2f pointA, cv::Point2f pointB);
    float angleToGSR(float angle, int turn_dir);
    float constantCalculator(float angle, float GSR);
    int leftRightDeterminer(cv::Point2f pointA, cv::Point2f pointB);
};

float Angler::getAngle(cv::Point2f pointA, cv::Point2f pointB) {
    // Use atan2 to find the angle relative to the horizontal axis
    float deltaY = pointB.y - pointA.y;
    float deltaX = pointB.x - pointA.x;
    float angle = std::atan2(deltaY, deltaX) * 180 / M_PI;
    return angle >= 0 ? angle : angle + 360;  // Normalize angle to [0, 360)
}

float Angler::angleToGSR(float angle, int turn_dir) {
    const float ANGLE_TO_GSR_CONSTANT = -0.002237538;
    float GSR = angle * ANGLE_TO_GSR_CONSTANT;

    // Adjust sign based on turn direction
    GSR = (turn_dir == 1) ? std::abs(GSR) : -std::abs(GSR);

    // Clamp the GSR value to a specific range
    return std::clamp(GSR, -0.290888f, 0.290888f);
}

float Angler::constantCalculator(float angle, float GSR) {
    // Avoid division by zero
    return angle != 0.0f ? GSR / angle : std::numeric_limits<float>::quiet_NaN();
}

int Angler::leftRightDeterminer(cv::Point2f pointA, cv::Point2f pointB) {
    // Use the cross product to determine direction
    return (pointB.x - pointA.x) * (pointB.y + pointA.y) > 0 ? 0 : 1;
}

#endif
