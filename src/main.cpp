#include "reconstruction.h"

using namespace cv;

void usage(){
    std::cout << "Not enough arguments were given! Please specify path to images and path where results must be stored." << std::endl;
    std::cout << "Usage example:" << std::endl;
    std::cout << "./build/src/image_reconstruction {path to input images} {path to results folder} {number of images}" << std::endl;
}

int main(int argc, char** argv){

    /*
    std::string location = "/home/gabrielmonteagudo/LogicMelt/Maier/Imaxes_Probas/";
    std::string destination = "/home/gabrielmonteagudo/LogicMelt/Maier/Imaxes_Brillos/";
    std::string destRec = "/home/gabrielmonteagudo/LogicMelt/Maier/Imaxes_Reconstruidas/imaxe_reconstruida.png";    
    int nImgs = 50;
    */
    
    if(argc < 4){
        usage();
        return -1;
    }

    std::string resultName = "reconstructed_image.png";
    std::string location = argv[1];
    std::string destRec = argv[2] + resultName;
    std::string nStr = argv[3];
    int nImgs = std::stoi(nStr, nullptr, 10);;

    auto start_read = std::chrono::steady_clock::now();

    std::vector<Mat> images;
    std::cout << "Reading images..." << std::endl;
    for(int i = 0; i < nImgs; i++){
        std::string actual = location + "img" + std::to_string(i);
        cv::Mat tempMat = imread(actual, IMREAD_GRAYSCALE);
        if(tempMat.data != NULL){
            images.push_back(tempMat);
        }

    }
    
    if((int)images.size() == 0){
        std::cout << "No images were read! Make sure you specified a correct path to input images." << std::endl;
        return -1;
    }

    auto end_read = std::chrono::steady_clock::now();

    // Commented code is to draw rectangles around lightbands
    // (to check whether they are being detected correctly)

    /*
    std::cout << "Finding and drawing lightbands..." << std::endl;
    for(int i = 0; i < nImgs; i++){
        
        std::string actualDest = destination + "img" + std::to_string(i) + ".png";
        
        cv::Mat drawnImg;
        images.at(i).convertTo(drawnImg, CV_8U);

        drawnImg = logicmelt::find_and_draw_lightband(drawnImg);

        imwrite(actualDest, drawnImg);

    }
    */

    auto start_reconstruction = std::chrono::steady_clock::now();
    std::cout << "Reconstructing..." << std::endl;

    cv::Mat reconstructed = logicmelt::reconstruct_from_lightband(images);

    auto end_reconstruction = std::chrono::steady_clock::now();
    std::cout << "Reconstruction finished!" << std::endl;
    
    std::chrono::duration<double> time_elapsed = end_reconstruction - start_reconstruction;
    std::chrono::duration<double> time_read = end_read - start_read;
    
    std::cout << "Time elapsed for reading images: " << time_read.count() << std::endl;
    std::cout << "Time elapsed for reconstruction: " << time_elapsed.count() << std::endl;

    imwrite(destRec, reconstructed);

    return 0;
}
