#ifndef CONTOURS
#define CONTOURS
#include <cstdint>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * The Contours class provides a method to detect and draw contours in an image
 * using the Canny edge detection algorithm.
 */
class Contours
{
public:
    /**
     * Detects and draws contours on the provided image using specified color and threshold.
     * 
     * @param img The image on which to detect and draw contours.
     * @param color The color to use for drawing the contours.
     * @param thresh The threshold value for the Canny edge detector. Default is 100.
     * @return A new image with contours drawn.
     */
    cv::Mat makeContours(cv::Mat &img, cv::Scalar color, int thresh = 100);
};

#endif
