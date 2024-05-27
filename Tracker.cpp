#include "Tracker.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Contours.hpp"
#include <tuple>
#include <iostream>

static const cv::Scalar RED_COLOR(0, 0, 255, 255);

std::vector<cv::Point2f> Tracker::findCentroids(const cv::Mat& mask) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    std::vector<cv::Point2f> centroids;
    for (auto& contour : contours) {
        auto moments = cv::moments(contour);
        if (moments.m00 != 0) { // Avoid division by zero
            centroids.emplace_back(moments.m10 / moments.m00, moments.m01 / moments.m00);
        }
    }
    return centroids;
}

std::tuple<cv::Mat, cv::Point2f, cv::Point2f> Tracker::trackObjects(cv::Mat blueMask, cv::Mat yellowMask) {
    Contours contours;
    cv::Mat yellowDrawing = contours.makeContours(yellowMask, cv::Scalar(0, 255, 255, 255));
    cv::Mat blueDrawing = contours.makeContours(blueMask, cv::Scalar(255, 0, 0, 255));
    cv::Mat debugDrawing = yellowDrawing | blueDrawing;

    auto blueCentroids = findCentroids(blueMask);
    auto yellowCentroids = findCentroids(yellowMask);

    // Debug: Draw centroids for visual verification
    for (const auto& c : blueCentroids) {
        cv::circle(debugDrawing, c, 4, RED_COLOR, -1);
    }
    for (const auto& c : yellowCentroids) {
        cv::circle(debugDrawing, c, 4, RED_COLOR, -1);
    }

    // Determine points to return
    cv::Point2f pointA(0.0f, 0.0f), pointB(0.0f, 0.0f);
    const auto& centroids = blueCentroids.size() >= yellowCentroids.size() ? blueCentroids : yellowCentroids;
    if (centroids.size() >= 2) {
        pointA = centroids[0];
        pointB = centroids[1]; // Assuming the first two are the ones needed
    }

    return std::make_tuple(debugDrawing, pointA, pointB);
}
