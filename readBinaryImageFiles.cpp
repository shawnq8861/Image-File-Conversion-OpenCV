/******************************************************************************
 *
 * Reads a raw image file from memory, converts it to RGB, and saves it
 * as a jpeg.
 *
 * Uses OpenCV library version 3.1, and depends on dll files for execution.
 *
 * TO DO:  create static build for single file execution (command line)
 *         get rid of hard coded paths
 *
 * Shawn Quinn
 * June 2, 2016
 *
 *****************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

using namespace std;
using namespace cv;

const uint32_t rows = 480;
const uint32_t columns = 640;
uint8_t buffer[rows * columns * 2];

int main(void)
{
    cout << "enter camera source, video0, video1, or video2: ";
    string camera;
    cin >> camera;
    FILE *inputFile = NULL;
    cout << "Trying to open file..." << endl;
    if (camera.compare("video0") == 0) {
        inputFile = fopen("D:/SavedImages/video0Data.bin", "rb");
    }
    else if (camera.compare("video1") == 0) {
        inputFile = fopen("D:/SavedImages/video1Data.bin", "rb");
    }
    else if (camera.compare("video2") == 0) {
        inputFile = fopen("D:/SavedImages/video2Data.bin", "rb");
    }
    else {
        cout << "invalid input..." << endl;
        return 1;
    }
    if (inputFile == NULL) {
        cout << "could not open file..." << endl;
        return 1;
    }
    // get the size of the file
    // set position to end of file
    fseek(inputFile, 0, SEEK_END);
    // tell position and assign to length
    long length = ftell(inputFile);
    cout << "file size = " << length << endl;
    // reset point to beginning of file
    rewind(inputFile);
    // read the data into the buffer
    cout << "reading file data into buffer..." << endl;
    fread(buffer, 1, length, inputFile);

    // create a matrix using the data buffer
    Mat inputImage = Mat(rows, columns, CV_8UC2, 2);
    inputImage.data = (uchar *)buffer;
    // convert raw pixels to grayscale YUY2
    cvtColor(inputImage, inputImage, CV_YUV2RGB_YUY2);
    namedWindow("fisheye camera image", WINDOW_NORMAL | WINDOW_KEEPRATIO);
    // display the image
    imshow("fisheye camera image", inputImage);

    cout << "press any key to exit..." << endl;
    waitKey();
    // release window resources
    destroyAllWindows();

    // save image to jpeg file
    string fileName;
    cout << "enter file name: ";
    cin >> fileName;
    string filePath("D:\\SavedImages\\");
    filePath.append(fileName);
    filePath.append(".jpg");
    cout << "saving image to file" << endl;
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);
    try {
        imwrite(filePath, inputImage, compression_params);
    }
    catch (Exception& ex) {
        fprintf(stderr, "Exception converting image to JPG format: %s\n", ex.what());
        return 1;
    }

    // close the file when done
    cout << "closing file..." << endl;
    fclose(inputFile);
    destroyAllWindows();

    return 0;
}
