#include "reconstruction.h"


namespace logicmelt{

    std::vector<int> find_lightband(cv::Mat input){
        
        std::vector<int> rowIndexes;

        int rows = input.rows;
        int cols = input.cols;
        int count = 0;
        float percentage;

        for(int i = 0; i < rows; ++i){
            count = 0;
            for(int j = 0; j < cols; ++j){
                size_t index = i*cols + j;
                if(input.data[index] >= WHITE_THRESHOLD){
                    count++;
                }
            }
            
            percentage = 100 * ((float)count / cols);
            if((percentage) >= WHITE_PERCENTAGE){
                int index = i;
                rowIndexes.push_back(index);
            }
        }
        
        std::cout << "Reached end of lightband search. Indexes found: " << rowIndexes.size() << std::endl;
        return rowIndexes;
    }

    int find_lightband_first_row(cv::Mat input, int wt, float wp){
        
        int rowIndex = -1;

        int rows = input.rows;
        int cols = input.cols;
        int count = 0;
        float percentage;
    
        for(int i = 0; i < rows; ++i){
            count = 0;
            for(int j = 0; j < cols; ++j){
                size_t index = i*cols + j;
                if(input.data[index] >= wt){
                    count++;
                }
            }

            percentage = 100 * ((float)count / cols);
            if((percentage) >= wp){

                rowIndex = i;

                break;
            }
        }
        
        return rowIndex;
    }

    cv::Mat find_and_draw_lightband(cv::Mat input){

        cv::Mat drawnImage = input.clone();
        
        std::vector<int> light_indexes = find_lightband(drawnImage);

        std::cout << "Found lightband! First row is: " << light_indexes.at(0) << std::endl;

        cv::Rect light_BBox = cv::Rect(5, light_indexes.at(0), drawnImage.cols - 5, ((int)light_indexes.size()));

        cv::rectangle(drawnImage, light_BBox, cv::Scalar(0,0,0), 3);

        return drawnImage;

    }

    cv::Mat reconstruct_from_lightband(std::vector<cv::Mat> images, int wt, float wp, int ph, int po){
      
        std::vector<cv::Mat> subimages;
        cv::Mat resultImg;
        
        int nImgs = images.size();

        int width = images.at(0).cols;

        
        for(int n = 0; n < nImgs; n++){
            
            int first = find_lightband_first_row(images.at(n), wt, wp);

            if(first != -1){ 
                cv::Range rows(first - ph - po, first - po);
                cv::Range cols(1, 1920);
                cv::Mat sub = images.at(n)(rows, cols);
                subimages.push_back(sub);
            }else{
                std::cout << "Lightband not found in image " << n << "! Ignoring it..." << std::endl;
            }
                    
        }

        cv::vconcat(subimages, resultImg);

        return resultImg;

    }

}