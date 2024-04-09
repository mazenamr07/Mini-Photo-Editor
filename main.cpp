// FCAI – Structured Programming – 2024 – Assignment 3 – Part 1
// Program Name: CS112_A3_Part1_Section28_20230308_20230498_20230516.cpp
// Program Description: Mini Photo Editor to apply various filters and adjustments on images:
//                      1- Gray Scale,      2- Black & White,    3- Inverted Colors,       4- Merging Images
//                      5- Flipping Images, 6- Rotating Images,  7- Adjusting Brightness,  8- Cropping Images
//                      9- Adding Frames,  10- Edge Detection,  11- Resizing Images,      12- Blurring Images
// Last Modification Date: 27/3/2024

// Author 1: Mazen Amr Mohammed Morsy - ID: 20230308 - Section: 28 - Email: 11410120230308@stud.cu.edu.eg
// Author 2: Youssef Saad Eldeen Ahmed - ID: 20230498 - Section: 28 - Email: Yoyosaad85@gmail.com
// Author 3: Youssef Haysam Sadek - ID: 20230516 - Section: 28 - Email: Youssefhaysam@gmail.com
// Teaching Assistant: Eman Essam

// Who did what:
//      Mazen Amr: Worked on the menu and code for:
//                      1- Gray Scale, 4- Merging Images, 7- Brightness, 10- Edge Detection
//      Youssef Saad: Worked on the code for:
//                      2- Black & White, 5- Flipping Images, 8- Cropping Images, 11- Resizing Images
//      Youssef Haysam: Worked on the code for:
//                      3- Inverted Colors, 6- Rotating Images, 9- Adding Frames, 12- Blurring Images

// Notes: Since Resizing function is still in-progress,
//              the Merge function can't merge images with different dimensions

#include <sstream>
#include <vector>
#include <cmath>
#include "Image_Class.h"

using namespace std;

// Function to check choice validity
bool choiceCheck(const string& choice);

// Function to check image extension validity
bool exCheck(const string& ex);

// Function to change image extension
void exChange(Image img, int counter, const string& ex, string& filename, Image& jpgImg);

// Function to apply Gray scale filter
void GrayScale(Image img, Image& grayImg);

// Function to apply Black & White filter
void BlackWhite(Image grayImg, Image& bwImg);

// Function to merge two images
void Merge(Image img1, Image img2, float opacity, Image& mergedImg);

// Function to adjust an image brightness
void Brightness(Image img, float bright, Image& brightImg);

// Function to apply Edge Detection filter
void EdgeDetect(Image blurGrayImg, Image& edgeImg);

// Function to apply Inverted Colors filter
void InvertColor(Image myimage, Image& img);

// Functions to Rotate an image
void imageRotate90(Image img, Image& rtImg);
void imageRotate180(Image img, Image& rtImg);
void imageRotate270(Image img, Image& rtImg);

// Functions to Flip an image
void HorizontalFlip(Image img, Image& flipImg);
void VerticalFlip(Image img, Image& flipImg);

// Function to blur an image
void imageBlur(Image myImage, Image& blurImage, int slider = 1);

void menu(Image& img, string fileName) {
    while (true) {
        string choice_1;
        cout << "\nWhich Filter would you like to apply?" << endl;
        cout << "1- Gray Scale\n"
                "2- Black & White\n"
                "3- Invert Colors\n"
                "4- Merge Two Images\n"
                "5- Flip Image\n"
                "6- Rotate Image\n"
                "7- Adjust Brightness\n"
                "8- Crop Image\n"
                "9- Add Frame to Image\n"
                "10- Edge Detection\n"
                "11- Resize Image\n"
                "12- Blur Image\n"
                "0- Save, Exit Program\n" << ">>";
        getline(cin, choice_1);

        // checking if input is valid
        while (!choiceCheck(choice_1)) {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_1);
        }

        if (choice_1 == "0") { // Exiting Program
            string saveChoice;
            cout << "Choose a saving method:\n"
                    "1- Save to same file\n"
                    "2- Save to a new file\n"
                    ">>";
            getline(cin, saveChoice);

            while (saveChoice != "1" and saveChoice != "2") {
                cout << "Please select a valid option:" << endl << ">>";
                getline(cin, saveChoice);
            }

            if (saveChoice == "1") {
                img.saveImage(fileName);
            }
            else {
                string newName, newEx;
                cout << "Enter the name of the new image: (e.g. image.png)" << endl << ">>";
                getline(cin, newName);

                size_t dotPos = newName.find('.');
                newEx = newName.substr(dotPos + 1);

                //Checking if file extension is valid
                while (dotPos == string::npos or !exCheck(newEx)) {
                    cout << "Error: unsupported file extension, enter file name again:"
                         << endl << ">>";

                    getline(cin, newName);
                    dotPos = newName.find('.');
                    newEx = newName.substr(dotPos + 1);
                }
                img.saveImage(newName);
            }

            cout << "All done... Bye bye!";
            exit(0);
        }

        // Gray Scale
        else if (choice_1 == "1") {
            Image grayImg(img.width, img.height);
            GrayScale(img, grayImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(grayImg, fileName);
        }

        // Black & White
        else if (choice_1 == "2") {
            // First, we grayscale the image
            Image grayImg(img.width, img.height);
            GrayScale(img, grayImg);

            // Then, we apply the filter
            Image bwImg (img.width, img.height);
            BlackWhite(grayImg, bwImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(bwImg, fileName);
        }

        // Inverted Colors
        else if (choice_1 == "3") {
            Image invertedImg(img.width, img.height);
            InvertColor(img, invertedImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(invertedImg, fileName);
        }

        // Merge Two Images
        else if (choice_1 == "4") {
            string imgName_2, ex;
            cout << "Enter the name of your second image:" << endl << ">>";
            getline(cin, imgName_2);

            size_t dotPos = imgName_2.find('.');
            ex = imgName_2.substr(dotPos + 1);

            //Checking if file extension is valid
            while (dotPos == string::npos or !exCheck(ex)) {
                cout << "Error: unsupported file extension, enter file name again:"
                     << endl << ">>";

                getline(cin, imgName_2);
                dotPos = imgName_2.find('.');
                ex = imgName_2.substr(dotPos + 1);
            }

            Image img_2(imgName_2);

            if (img.width != img_2.width or img.height != img_2.height) {
                // should do resizing here
            }

            Image tempImg1, tempImg2;
            string filename1, filename2;
            exChange(img, 1, ".jpg", filename1, tempImg1);
            exChange(img_2, 2, ".jpg", filename2, tempImg2);

            Image mergedImg(tempImg1.width, tempImg1.height);
            Merge(tempImg1, tempImg2, 0.5, mergedImg);

            remove(filename1.c_str());
            remove(filename2.c_str());

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(mergedImg, fileName);
        }

        // Flip Image
        else if (choice_1 == "5") {
            string choiceFlip;
            cout << "Choose how to flip the image:\n"
                    "1- Horizontal Flip\n"
                    "2- Vertical Flip" << endl << ">>";

            getline(cin, choiceFlip);
            while (choiceFlip != "1" and choiceFlip != "2") {
                cout << "Please select a valid option:\n" << ">>";
                getline(cin, choiceFlip);
            }

            if (choiceFlip == "1") {
                Image flipImg(img.width, img.height);
                HorizontalFlip(img, flipImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(flipImg, fileName);
            }
            else {
                Image flipImg(img.width, img.height);
                VerticalFlip(img, flipImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(flipImg, fileName);
            }
        }

        // Rotate Image
        else if (choice_1 == "6") {
            string choiceDegree;
            cout << "Choose how to rotate the image:\n"
                    "1- 90 Degrees to the right\n"
                    "2- 90 Degrees to the left\n"
                    "3- 180 Degrees" << endl << ">>";

            getline(cin, choiceDegree);
            while (choiceDegree != "1" and choiceDegree != "2" and choiceDegree != "3") {
                cout << "Please select a valid option:\n" << ">>";
                getline(cin, choiceDegree);
            }

            if (choiceDegree == "1") {
                Image rtImg(img.height, img.width);
                imageRotate90(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName);
            }
            else if (choiceDegree == "2") {
                Image rtImg(img.height, img.width);
                imageRotate270(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName);
            }
            else {
                Image rtImg(img.width, img.height);
                imageRotate180(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName);
            }
        }

        // Adjust Brightness
        else if (choice_1 == "7") {
            string level;
            cout << "Please enter level of brightness: (0 is darkest, 1 is normal, 3 is brightest)"
                 << endl << ">>";

            getline(cin, level);
            float fLevel = stof(level);
            while (fLevel < 0 or fLevel > 3) {
                cout << "Level must be between 0 - 2, enter again:\n" << ">>";
                getline(cin, level);
                fLevel = stof(level);
            }

            Image brightImg(img.width, img.height);
            Brightness(img, fLevel, brightImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(brightImg, fileName);
        }

        // Edge Detection
        else if (choice_1 == "10") {
            Image grayImg(img.width, img.height);
            Image blurImg(img.width, img.height);
            Image edgeImg(img.width, img.height);

            GrayScale(img, grayImg);
            imageBlur(grayImg, blurImg);
            EdgeDetect(blurImg, edgeImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(edgeImg, fileName);
        }

        // Blur Image
        else if (choice_1 == "12") {
            Image blurImg(img.width, img.height);
            imageBlur(img, blurImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(blurImg, fileName);
        }
    }
}

int main() {
    cout << "Welcome to our mini photo editor.\n"
            "(to start put your images in the project folder)\n" << endl;

    string imgName, ex;
    cout << "Enter the name of your image: (e.g. image.png)" << endl << ">>";
    getline(cin, imgName);

    size_t dotPos = imgName.find('.');
    ex = imgName.substr(dotPos + 1);

    //Checking if file extension is valid
    while (dotPos == string::npos or !exCheck(ex)) {
        cout << "Error: unsupported file extension, enter file name again:"
             << endl << ">>";

        getline(cin, imgName);
        dotPos = imgName.find('.');
        ex = imgName.substr(dotPos + 1);
    }

    // Converting image to JPG
    imgName[dotPos + 1] = 'j';
    imgName[dotPos + 2] = 'p';
    imgName[dotPos + 3] = 'g';

    Image img(imgName);
    menu(img, imgName);
    return 0;
}

int smain() {
    Image img1("img/photographer.jpg");
    Image gray(img1.width, img1.height);
    Image blur(img1.width, img1.height);
    Image edge(img1.width, img1.height);

    GrayScale(img1, gray);
    imageBlur(gray, blur);
    EdgeDetect(blur, edge);

    img1.saveImage("saved img/img_test.jpg");
    gray.saveImage("saved img/gray_test.jpg");
    blur.saveImage("saved img/blur_test.jpg");
    edge.saveImage("saved img/edge_test.jpg");
}

bool choiceCheck(const string& choice) {
    vector<string> choices = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

    for (const string& i : choices) {
        if (choice == i) {
            return true;
        }
    }
    return false;
}
bool exCheck(const string& ex) {
    if (ex == "png") {
        return true;
    } else if (ex == "jpg") {
        return true;
    } else if (ex == "jpeg") {
        return true;
    } else if (ex == "bmp") {
        return true;
    }
    return false;
}
void exChange(Image img, int counter, const string& ex, string& filename, Image& jpgImg) {
    filename = "tempPic";
    filename += to_string(counter);
    filename += ex;
    img.saveImage(filename);

    jpgImg.loadNewImage(filename);
}
void GrayScale(Image img, Image& grayImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            unsigned int grayAvg = 0;
            for (int k = 0; k < 3; k++) {
                grayAvg += img(i, j, k);
            }

            grayAvg /= 3;
            for (int k = 0; k < 3; k++) {
                grayImg(i, j, k) = grayAvg;
            }
        }
    }
}
void BlackWhite(Image grayImg, Image& bwImg) {
    for (int i = 0; i < grayImg.width; i++) {
        for (int j = 0; j < grayImg.height; j++) {

            int color;
            if (grayImg(i, j, 0) > 130) {
                color = 255;
            }
            else {
                color = 0;
            }
            for (int k = 0; k < 3; k++) {
                bwImg(i, j, k) = color;
            }
        }
    }
}
void Merge(Image img1, Image img2, float opacity, Image& mergedImg) {
    for (int i = 0; i < img1.width; i++) {
        for (int j = 0; j < img1.height; j++) {

            double color;
            for (int k = 0; k < 3; k++) {
                color = (1 - opacity) * img1(i, j, k) + opacity * img2(i, j, k);
                mergedImg(i, j, k) = color;
            }
        }
    }
}
void Brightness(Image img, float bright, Image& brightImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int bb = img(i, j, k) * bright;
                if (bb > 255) {
                    bb = 255;
                }
                brightImg(i, j, k) = bb;
            }
        }
    }
}
void EdgeDetect(Image blurGrayImg, Image& edgeImg) {
    for (int i = 0; i < blurGrayImg.width; i++) {
        for (int j = 0; j < blurGrayImg.height; j++) {
            for (int k = 0; k < 3; k++) {
                int horizontalSum = 0;
                int verticalSum = 0;

                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        int ix = i + x;
                        int jy = j + y;
                        bool pixelExists = ix >= 0 && ix < blurGrayImg.width && jy >= 0 && jy < blurGrayImg.height;

                        if (pixelExists) {
                            // Horizontal Kernel
                            if (y == 0) {
                                horizontalSum += blurGrayImg(ix, jy, 0) * x * 2;
                            }
                            else {
                                horizontalSum += blurGrayImg(ix, jy, 0) * x;
                            }
                            // Vertical Kernel
                            if (x == 0) {
                                verticalSum += blurGrayImg(ix, jy, 0) * y * -2;
                            }
                            else {
                                verticalSum += blurGrayImg(ix, jy, 0) * y * -1;
                            }
                        }
                    }
                }
                int magnitude = sqrt( pow(horizontalSum, 2) + pow(verticalSum, 2) );
                if (magnitude > 30) {
                    edgeImg(i, j, k) = 0;
                }
                else {
                    edgeImg(i, j, k) = 255;
                }
            }
        }
    }
}
void InvertColor(Image myimage, Image& img) {
    for (int i=0;i<myimage.width;i++)
    {
        for (int j=0;j<myimage.height;j++)
        {
            for (int k=0;k<myimage.channels;k++)
            {
                img(i,j,k)=255-myimage(i,j,k);
            }
        }
    }
}
void imageRotate90(Image img, Image& rtImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rtImg( img.height - 1 - j, i, k) = img(i, j, k);
            }
        }
    }
}
void imageRotate180(Image img, Image& rtImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rtImg( img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
            }
        }
    }
}
void imageRotate270(Image img, Image& rtImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rtImg( j, img.width - 1 - i, k) = img(i, j, k);
            }
        }
    }
}
void HorizontalFlip(Image img, Image& flipImg) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                flipImg(i, j, k) = img(img.width - 1 - i, j, k);
            }
        }
    }
}
void VerticalFlip(Image img, Image& flipImg) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                flipImg(i, j, k) = img(i, img.height - 1 - j, k);
            }
        }
    }
}
void imageBlur(Image myImage, Image& blurImage, int slider) {
    for (int i = 0; i < myImage.width; i++) {
        for (int j = 0; j < myImage.height; j++) {
            for (int k = 0; k < myImage.channels; k++) {
                int sum = 0;
                int count = 0;

                for (int x = -slider; x <= slider; x++) {
                    for (int y = -slider; y <= slider; y++) {
                        int new_i = i + x;
                        int new_j = j + y;

                        if (new_i >= 0 && new_i < myImage.width && new_j >= 0 && new_j < myImage.height) {
                            sum += myImage(new_i, new_j, k);
                            count++;
                        }
                    }
                }

                blurImage(i, j, k) = sum / count;
            }
        }
    }
}