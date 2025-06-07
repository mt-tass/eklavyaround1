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
    //Part1://to get a grid of characters that will denote maze and processed further for solution
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

    vector<vector<char>> grid_data(targetHeight,vector<char>(targetWidth));

    for (int i = 0; i < targetHeight; ++i) {
        for (int j = 0; j < targetWidth; ++j) {
            int original_y = static_cast<int>(i*stepY+ stepY /2.0);
            int original_x = static_cast<int>(j*stepX +stepX/ 2.0);
            original_y = min(original_y, originalHeight - 1);

            original_x = min(original_x, originalWidth - 1);

            cv::Vec3b pix = image.at<cv::Vec3b>(original_y, original_x);
            
            char pixel = getPixelType(pix);

            grid_data[i][j] = pixel;
        }
    }
    //part2:processing the grid_data
    string binary = "";
    //creating the binary string
    for (int row = 1 ; row<=13 ; row++){
        if(row%2 != 0){
            for(int col = 1 ; col<=13;col++){
                if(grid_data[row][col]=='W'){
                    binary.push_back('0');
                }
                if(grid_data[row][col]=='K'){
                    binary.push_back('1');
                }
            }
        }
        else{
            for(int col = 13 ; col>=1;col--){
                if(grid_data[row][col]=='W'){
                    binary.push_back('0');
                }
                if(grid_data[row][col]=='K'){
                    binary.push_back('1');
                }
            }
        }
    }
    cout << "Binary String : " << binary << endl;
    string ascii_pass = "";
    //slicing the string into 8char parts to convert to ascii
    for (int i = 0; i < binary.length(); i += 8) {
        string byte_str = binary.substr(i, 8);
        
        if (byte_str.length() == 8) {
            int char_code = stoi(byte_str, nullptr, 2);
            ascii_pass.push_back(static_cast<char>(char_code));
        }
    }
    //printing the password
    cout << "Password : " << ascii_pass << endl;
    return 0;
}