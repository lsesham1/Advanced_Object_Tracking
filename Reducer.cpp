#include "Reducer.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>

std::pair<cv::Mat, cv::Mat> Reducer::reduceNoise(cv::Mat &img) {
    // Validate input image
    if (img.empty()) {
        throw std::runtime_error("Input image is empty");
    }

    // HSV thresholds for blue
    const int minHBlue = 51, maxHBlue = 145;
    const int minSBlue = 93, maxSBlue = 199;
    const int minVBlue = 42, maxVBlue = 214;

    // HSV thresholds for yellow
    const int minHYellow = 15, maxHYellow = 42;
    const int minSYellow = 75, maxSYellow = 210;
    const int minVYellow = 172, maxVYellow = 241;

    // Define ROI based on image dimensions
    cv::Mat splitImg = img(cv::Range(img.rows / 2, img.rows * 3 / 4), cv::Range(0, img.cols));

    // Convert to HSV and apply blur
    cv::Mat imgHSV, imgBlur;
    cvtColor(splitImg, imgHSV, cv::COLOR_BGR2HSV);
    blur(imgHSV, imgBlur, cv::Size(3, 3));

    // Generate masks
    cv::Mat blueMask, yellowMask;
    inRange(imgHSV, cv::Scalar(minHBlue, minSBlue, minVBlue), cv::Scalar(maxHBlue, maxSBlue, maxVBlue), blueMask);
    inRange(imgHSV, cv::Scalar(minHYellow, minSYellow, minVYellow), cv::Scalar(maxHYellow, maxSYellow, maxVYellow), yellowMask);

    // Noise reduction
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
    morphologyEx(yellowMask, yellowMask, cv::MORPH_CLOSE, kernel);
    morphologyEx(yellowMask, yellowMask, cv::MORPH_OPEN, kernel);
    morphologyEx(blueMask, blueMask, cv::MORPH_CLOSE, kernel);
    morphologyEx(blueMask, blueMask, cv::MORPH_OPEN, kernel);

    return {blueMask, yellowMask};
}
