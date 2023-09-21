#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <chrono>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

//Define parameters for image reconstruction

//Pixel intensity threshold
#define WHITE_THRESHOLD 255
//Minimum percentage of pixels to consider a row to be a lightband 
#define WHITE_PERCENTAGE 70.0f
//Number of pixels to use for reconstruction.
//It should correspond to the amount of pixels the piece moves betweeen images.
#define PIXEL_ADD_HEIGHT 15
//Offset applied to the row number where lightband starts
#define PIXEL_OFFSET 10

namespace logicmelt{

    /** @brief Method for extracting lightband row indexes from a given image.
     * 
     * @param input Input image.
     * 
     * @return Vector with indexes of the rows that contain a lightband.
    */
    std::vector<int> find_lightband(cv::Mat input);

    /** @brief Method for extracting a lightband's first row index from a given image.
     * 
     * @param image Input image.
     * 
     * @return Index of the row where the lightband begins.
    */
    int find_lightband_first_row(cv::Mat image);
    
    /** @brief Method for drawing a rectangle around the lightband in an image.
     * 
     * @param input Input image.
     * 
     * @return Drawn image.
    */
    cv::Mat find_and_draw_lightband(cv::Mat input);

    /** @brief Method for reconstructing an image from a sequence that contains a lightband.
     * 
     * @param images Vector of images to reconstruct from. They must be ordered.
     * 
     * @return Reconstructed image.
    */
    cv::Mat reconstruct_from_lightband(std::vector<cv::Mat> images);

}