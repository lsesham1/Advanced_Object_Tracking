#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Angler.hpp"
#include "../Printer.hpp"
#include "../Reducer.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

TEST_CASE("Angle between two points is calculated correctly") {
    Angler angler;
    cv::Point2f pointA(20.0f, 40.0f);
    cv::Point2f pointB(40.0f, 70.0f);

    float expectedAngle = 56.31f; // Assuming this is the expected angle in degrees
    float result = angler.getAngle(pointA, pointB);

    REQUIRE(result == Approx(expectedAngle).epsilon(0.01));
}

TEST_CASE("Angle does not exceed expected range") {
    Angler angler;
    cv::Point2f pointA(20.0f, 40.0f);
    cv::Point2f pointB(40.0f, 70.0f);

    float result = angler.getAngle(pointA, pointB);

    REQUIRE(result >= 0.0f);
    REQUIRE(result <= 180.0f);
}

TEST_CASE("Direction determination is correct") {
    Angler angler;
    cv::Point2f pointA(20.0f, 40.0f);
    cv::Point2f pointB(40.0f, 70.0f);

    int direction = angler.leftRightDeterminer(pointA, pointB);
    REQUIRE(direction == 0); // Assuming 0 means a specific direction (e.g., right)
}

TEST_CASE("Reducer handles a zeroed image correctly") {
    cv::Mat zero_img = cv::Mat::zeros(480, 640, CV_8UC4);
    Reducer reducer;

    std::pair<cv::Mat, cv::Mat> ret = reducer.reduceNoise(zero_img);

    REQUIRE(cv::countNonZero(ret.first) == 0);
    REQUIRE(cv::countNonZero(ret.second) == 0);
}
