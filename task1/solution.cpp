//to get a grid of characters that will denote maze and processed further for solution
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

char getPixelType(const cv::Vec3b &pixel) {
    //BGR order to get pixel value
    int b = pixel[0];
    int g = pixel[1];
    int r = pixel[2];

    // assigning pixel the character 
    if (r == 255 && g == 0 && b == 0) { // Red
        return 'R';
    } else if (r == 0 && g == 255 && b == 0) { //Green
        return 'G';
    } else if (r == 0 && g == 0 && b == 255) { //Blue
        return 'B';
    } else if (r == 0 && g == 0 && b == 0) { //Black
        return 'K';
    } else if (r == 255 && g == 255 && b == 255) { //White
        return 'W';
    } 
    else{
        return 'X';//undefined
    }

}

int main() {
    string imagePath = "maze.png";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cout << "error in image opening" << endl;
        return -1;
    }

    int originalWidth = 240;
    int originalHeight = 240;
    int targetWidth = 15;
    int targetHeight = 15;
    //cout << originalHeight << " " << originalWidth << endl;

    // Calculate step size for sampling
    // We aim to sample from the approximate center of each conceptual 14.4x14.4 block
    double stepX = 16.0; //240/15
    double stepY = 16.0 ;//240/15

    std::cout << "Grid Data (15*15):\n";
    std::cout << "[\n";
    for (int i = 0; i < targetHeight; ++i) {
        std::cout << "    [";
        for (int j = 0; j < targetWidth; ++j) {
            // center of chunk of same pixel  to get grid data
            int original_y = static_cast<int>(i * stepY + stepY / 2.0);
            int original_x = static_cast<int>(j * stepX + stepX / 2.0);

            // checking bounds
            original_y = min(original_y, originalHeight - 1);
            original_x = min(original_x, originalWidth - 1);

            cv::Vec3b pixel = image.at<cv::Vec3b>(original_y, original_x);
            std::cout << "'" << getPixelType(pixel) << "'";
            if (j < targetWidth - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i < targetHeight - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "]\n";

    return 0;
}