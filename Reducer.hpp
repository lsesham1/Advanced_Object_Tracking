#ifndef REDUCER_HPP  // Use a more descriptive and unique macro name
#define REDUCER_HPP

#include <opencv2/core/mat.hpp>  // Include the specific OpenCV modules used
#include <opencv2/imgproc.hpp>   // More specific include based on usage

/**
 * The Reducer class is responsible for reducing noise in images.
 * It specifically focuses on filtering and morphological operations to clean up images
 * for better processing in later stages, such as object detection.
 */
class Reducer
{
public:
    /**
     * Reduces noise from the given image using color segmentation and morphological operations.
     * The function focuses on isolating specific color ranges and applying morphological transformations
     * to clean the segmentation results.
     *
     * @param img The image to process, assumed to be in BGR color space.
     * @return A pair of cv::Mat, where the first contains the processed mask for one color,
     *         and the second contains the processed mask for another color.
     */
    std::pair<cv::Mat, cv::Mat> reduceNoise(cv::Mat &img);
};

#endif // REDUCER_HPP
