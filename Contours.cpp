#include "Contours.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * Processes an image to detect and draw contours based on the Canny edge detection.
 * 
 * @param img The image to be processed
 * @param color The color to draw the contours with.
 * @param thresh The threshold value for the Canny edge detector. Default is 100.
 * 
 * @return A cv::Mat object containing the drawn contours.
 */
cv::Mat Contours::makeContours(cv::Mat &img, cv::Scalar color, int thresh = 100) {
    cv::Mat output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // Apply Canny edge detection on the image.
    cv::Canny(img, output, thresh, thresh * 2);

    // Find contours in the image processed by Canny detector.
    cv::findContours(output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Create an image to draw contours on.
    cv::Mat drawing = cv::Mat::zeros(img.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(drawing, contours, static_cast<int>(i), color, 3);
    }

    return drawing;
}
