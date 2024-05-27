#include "Angler.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <vector>
#include <iostream>

float Angler::getAngle(cv::Point2f pointA, cv::Point2f pointB) {
    // Code adapted from: https://stackoverflow.com/questions/15888180/calculating-the-angle-between-points

    // Calculate the lengths of vectors to each of the points
    float len1 = sqrt(pointA.x * pointA.x + pointA.y * pointA.y);
    float len2 = sqrt(pointB.x * pointB.x + pointB.y * pointB.y);
    
    // Get the dot product of the two points
    float dot = pointA.x * pointB.x + pointA.y * pointB.y;
    
    // Calculate the cosine from the dot product and vector lengths
    float angle = dot / (len1 * len2);

    // Ensure cosine value is within the valid range of -1 to 1
    if (angle > 1.0) {
        return 0.0;
    } else if (angle < -1.0) {
        return M_PI;
    } else {
        // Convert angle from radians to degrees
        return acos(angle) * 180 / M_PI;
    }
}

float Angler::angleToGSR(float angle, int turn_dir) {
    // Constants for the GSR calculation
    const float ANGLE_TO_GSR_CONSTANT = -0.002237538;
    float GSR = angle * ANGLE_TO_GSR_CONSTANT;

    // Convert turning direction to GSR sign
    if (turn_dir == 1) {
        GSR = fabsf(GSR);
    }

    // Limit the GSR to maximum and minimum values
    if (GSR > 0.290888) {
        return 0.290888;
    } else if (GSR < -0.290888) {
        return -0.290888;
    } else {
        return GSR;
    }
}

float Angler::constantCalculator(float angle, float GSR) {
    // Calculate constant from angle and GSR
    if (angle == 0.0f) {
        return 0;
    }

    return GSR / angle;
}

int Angler::leftRightDeterminer(cv::Point2f pointA, cv::Point2f pointB) {
    // Determine turning direction based on the relative positions of points
    int turn_dir;

    if (pointA.x <= pointB.x) {
        turn_dir = 0;  // Right turn
    } else {
        turn_dir = 1;  // Left turn
    }

    return turn_dir;
}
