// FCAI – Structured Programming – 2024 – Assignment 3 – Part 2B
// Program Name: CS112_A3_Part1_Section28_20230308_20230498_20230516.cpp
// Program Description: Mini Photo Editor to apply various filters and adjustments on images:
//                      1- Gray Scale                       11- Resizing Images
//                      2- Black & White                    12- Blurring Images
//                      3- Inverted Colors                  13- Natural Sunlight Filter
//                      4- Merging Images                   14- Oil Paint Filter
//                      5- Flipping Images                  15- TV Noise Filter
//                      6- Rotating Images                  16-
//                      7- Adjusting Brightness             17- Infrared Light Filter
//                      8- Cropping Images                  18- Skewing Images by Degrees
//                      9- Adding Frames to Images          19-
//                      10- Edge Detection Filter           20-

// Last Modification Date: 13/4/2024

// Author 1: Mazen Amr Mohammed Morsy - ID: 20230308 - Section: 28 - Email: 11410120230308@stud.cu.edu.eg
// Author 2: Youssef Saad Eldeen Ahmed - ID: 20230498 - Section: 28 - Email: Yoyosaad85@gmail.com
// Author 3: Youssef Haysam Sadek - ID: 20230516 - Section: 28 - Email: Youssefhaysam@gmail.com
// Teaching Assistant: Eman Essam

// Who did what:
//      Mazen Amr: Worked on the menu and code for:
//                      1- Gray Scale, 4- Merging Images, 7- Adjusting Brightness, 10- Edge Detection Filter,
//                      13- Natural Sunlight Filter, 15- TV Noise Filter, 17- Infrared Light Filter
//
//      Youssef Saad: Worked on the code for:
//                      2- Black & White, 5- Flipping Images, 8- Cropping Images, 11- Resizing Images
//
//      Youssef Haysam: Worked on the code for:
//                      3- Inverted Colors, 6- Rotating Images, 9- Adding Frames to Images, 12- Blurring Images,
//                      18- Skewing Images by Degrees

#include "Image_Class.h"
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// Initializing random number generator
random_device rd;
mt19937 gen(rd());

// Function to check choice validity
bool choiceCheck(const string& choice);

// Function to generate random numbers
int randomInRange(int min, int max);

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

// Function to Blur an image
void imageBlur(Image myImage, Image& blurImage, int slider = 1);

// Function to apply Natural Sunlight filter
void NaturalSunlight(Image img, Image& sunImg);

// Function to apply TV Noise filter
void imageNoise(Image img, Image& noiseImg);

// Function to apply Infrared Light filter
void InfraredLight(Image img, Image& infraredImg);

void menu(Image& img, const string& fileName, const string& oldName) {
    while (true) {
        string choice_1;
        cout << "\nWhich Filter would you like to apply?" << endl;
        printf("%-25s %-25s\n", "1- Gray Scale",         "11- Resize Image");
        printf("%-25s %-25s\n", "2- Black & White",      "12- Blur Image");
        printf("%-25s %-25s\n", "3- Invert Colors",      "13- Natural Sunlight Filter");
        printf("%-25s %-25s\n", "4- Merge Two Images",   "14- Oil Paint Filter");
        printf("%-25s %-25s\n", "5- Flip Image",         "15- TV Noise Filter");
        printf("%-25s %-25s\n", "6- Rotate Image",       "");
        printf("%-25s %-25s\n", "7- Adjust Brightness",  "");
        printf("%-25s %-25s\n", "8- Crop Image",         "");
        printf("%-25s %-25s\n", "9- Add Frame to Image", "");
        printf("%-25s %-25s\n", "10- Edge Detection",    "");
        cout << "0- Save, Exit Program\n" << ">>";
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
                img.saveImage(oldName);
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

            std::remove(fileName.c_str());
            cout << "All done... Bye bye!";
            exit(0);
        }

        // Gray Scale
        else if (choice_1 == "1") {
            Image grayImg(img.width, img.height);
            GrayScale(img, grayImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(grayImg, fileName, oldName);
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
            menu(bwImg, fileName, oldName);
        }

        // Inverted Colors
        else if (choice_1 == "3") {
            Image invertedImg(img.width, img.height);
            InvertColor(img, invertedImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(invertedImg, fileName, oldName);
        }

        // Merge Two Images // Needs work
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
            menu(mergedImg, fileName, oldName);
        }

        // Flip Image
        else if (choice_1 == "5") {
            string choiceFlip;
            cout << "Choose how to flip the image:\n"
                    "1- Horizontal Flip\n"
                    "2- Vertical Flip\n"
                    "0- Return" << endl << ">>";

            getline(cin, choiceFlip);
            while (choiceFlip != "1" and choiceFlip != "2" and choiceFlip != "0") {
                cout << "Please select a valid option:\n" << ">>";
                getline(cin, choiceFlip);
            }

            if (choiceFlip == "1") {
                Image flipImg(img.width, img.height);
                HorizontalFlip(img, flipImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(flipImg, fileName, oldName);
            }
            else if (choiceFlip == "2") {
                Image flipImg(img.width, img.height);
                VerticalFlip(img, flipImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(flipImg, fileName, oldName);
            }
            else {
                continue;
            }
        }

        // Rotate Image
        else if (choice_1 == "6") {
            string choiceDegree;
            cout << "Choose how to rotate the image:\n"
                    "1- 90 Degrees to the right\n"
                    "2- 90 Degrees to the left\n"
                    "3- 180 Degrees\n"
                    "0- Return" << endl << ">>";

            getline(cin, choiceDegree);
            while (choiceDegree != "1" and choiceDegree != "2" and choiceDegree != "3" and choiceDegree != "0") {
                cout << "Please select a valid option:\n" << ">>";
                getline(cin, choiceDegree);
            }

            if (choiceDegree == "1") {
                Image rtImg(img.height, img.width);
                imageRotate90(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName, oldName);
            }
            else if (choiceDegree == "2") {
                Image rtImg(img.height, img.width);
                imageRotate270(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName, oldName);
            }
            else if (choiceDegree == "3") {
                Image rtImg(img.width, img.height);
                imageRotate180(img, rtImg);

                cout << "Filter " << choice_1 << " was applied." << endl;
                menu(rtImg, fileName, oldName);
            }
            else {
                continue;
            }
        }

        // Adjust Brightness // Needs work
        else if (choice_1 == "7") {
            string level;
            cout << "Please enter level of brightness: (0 is darkest, 1 is normal, 2 is brightest)"
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
            menu(brightImg, fileName, oldName);
        }

        // Crop Image // Needs work
        else if (choice_1 == "8") {

        }

        // Add Frame // Needs work
        else if (choice_1 == "9") {

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
            menu(edgeImg, fileName, oldName);
        }

        // Resize Image // Needs work
        else if (choice_1 == "11") {

        }

        // Blur Image
        else if (choice_1 == "12") {
            Image blurImg(img.width, img.height);
            imageBlur(img, blurImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(blurImg, fileName, oldName);
        }

        // Natural Sunlight Filter // Needs work in function
        else if (choice_1 == "13") {
            Image sunImg(img.width, img.height);
            NaturalSunlight(img, sunImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(sunImg, fileName, oldName);
        }

        // Oil Paint Filter // Needs work
        else if (choice_1 == "14") {

        }

        // TV Noise Filter // Needs work in function
        else if (choice_1 == "15") {
            Image noiseImg(img.width, img.height);
            imageNoise(img, noiseImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(noiseImg, fileName, oldName);
        }

        // Infrared Light Filter // Needs work in function
        else if (choice_1 == "17") {
            Image infraredImg(img.width, img.height);
            InfraredLight(img, infraredImg);

            cout << "Filter " << choice_1 << " was applied." << endl;
            menu(infraredImg, fileName, oldName);
        }

        // Skew Image // Needs work
        else if (choice_1 == "18") {

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

    while (true) {
        bool extensionValid = true;
        bool nameValid = true;

        if (dotPos == string::npos or !exCheck(ex)) {
            extensionValid = false;
            goto SKIP;
        }
        try {
            Image img(imgName);
        }
        catch (const invalid_argument& e) {
            nameValid = false;
        }

        SKIP:
        if (extensionValid and nameValid) {
            break;
        }
        else if (!nameValid) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            cout << "Error: enter file name again:"
                 << endl << ">>";

            getline(cin, imgName);
            dotPos = imgName.find('.');
            ex = imgName.substr(dotPos + 1);
        } else {
            cout << "Error: unsupported file extension, enter file name again:"
                 << endl << ">>";

            getline(cin, imgName);
            dotPos = imgName.find('.');
            ex = imgName.substr(dotPos + 1);
        }
    }

    Image img(imgName);
    string oldName = imgName;

    cout << imgName << endl << oldName << endl;

    // Converting image to JPG
    if (size(ex) > 3) {
        imgName[dotPos + 1] = 'j';
        imgName[dotPos + 2] = 'p';
        imgName[dotPos + 3] = 'g';
        imgName[dotPos + 4] = '\0';
    }
    else {
        imgName[dotPos + 1] = 'j';
        imgName[dotPos + 2] = 'p';
        imgName[dotPos + 3] = 'g';
    }
    img.saveImage(imgName);

    cout << imgName;

    Image exImg(imgName);
    menu(exImg, imgName, oldName);
    return 0;
}

int pixelart() {
    Image img("img/doctor/night3.jpg");

    for (int i = 2; i < img.width; i += 5) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int color = img(i, j, k);
                img(i - 1, j, k) = color;
                img(i - 2, j, k) = color;
                img(i + 2, j, k) = color;
                img(i + 1, j, k) = color;
            }
        }
    }
}

int wmain() {
    clock_t start = clock();

    Image img("img/doctor/night3.jpg");
//    Image img("saved img/luggy.jpg");
    Image blue(img.width, img.height);
    Image red(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0;

                for (int x = -1; x <= 1; x++) { // -1 0 1
                    for (int y = -1; y <= 1; y++) { // -1 0 1
                        int new_i = i + x;
                        int new_j = j + y;

                        if (new_i >= 0 && new_i < img.width && new_j >= 0 && new_j < img.height) {

                            if (x == 0 and y == 0) {
                                sum += img(new_i, new_j, k) * 5;
                            }
                            else if (x != 0 and y != 0) {
                                sum += img(new_i, new_j, k) * 0;
                            }
                            else {
                                sum += img(new_i, new_j, k) * -1;
                            }
                        }
                    }
                }

                blue(i, j, k) = sum / 9;
            }
        }
    }

    cout << blue.saveImage("saved img/luggy.jpg") << endl;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

int gmain() {
    clock_t start = clock();

    Image img("img/doctor/night3.jpg");
    Image blue(img.width, img.height);
    Image red(img.width, img.height);

    int degree = img.height/36;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            unsigned int grayAvg = 0;
            for (int k = 0; k < 3; k++) {
                grayAvg += img(i, j, k);
            }
            grayAvg /= 3;

            if (i < img.width - degree) {
                blue(i + degree, j, 0) = 0;
                blue(i + degree, j, 1) = grayAvg;
                blue(i + degree, j, 2) = grayAvg;
            }
            if (i > degree) {
                red(i - degree, j, 0) = 255;
                red(i - degree, j, 1) = grayAvg;
                red(i - degree, j, 2) = grayAvg;
            }
        }
    }

    Merge(img, blue, 0.35, img);
    Merge(img, red, 0.12, img);

    cout << img.saveImage("saved img/luggy.jpg") << endl;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

int dmain() {
    clock_t start = clock();

    Image img("img/doctor/toy1.jpg");
    Image res(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int color = img(i, j, k);
                int rColor = color;

                // Blue Filter
                if (k == 0) {color /= 2;} else if (k == 1) {color /= 2;} else {color *= 1.5;}

                if (color > 255) {color = 255;} else if (color < 0) {color = 0;}
                img(i, j, k) = color;

                if (i < img.width - 100) {
                    res(i + 100, j, k) = img(i, j, k);
                }
                res(i, j, k) = (1 - 0.3) * img(i, j, k) + 0.3 * res(i, j, k);

                // Red Filter
                if (k == 2) {rColor /= 2;} else if (k == 1) {rColor /= 2;} else {rColor *= 2;}

                if (rColor > 255) {rColor = 255;} else if (rColor < 0) {rColor = 0;}
                img(i, j, k) = rColor;

                if (i > img.width + 100) {
                    res(i - 100, j, k) = img(i, j, k);
                }
                res(i, j, k) = (1 - 0.3) * img(i, j, k) + 0.3 * res(i, j, k);

            }
        }
    }

    cout << res.saveImage("saved img/luggy.jpg") << endl;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

void skew() {
    clock_t start = clock();

    Image img("img/colors.jpg");

    double angle, preAngle;
    cin >> preAngle;

    angle = preAngle * M_PI/180;
    int nWidth = img.width + tan(angle) * img.height;
    cout << tan(angle) * img.height << endl;

    Image res(nWidth, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {

//                int new_i = i + j * tan(angle);
                int new_i = (i + tan(angle) * img.height) - j * tan(angle);
                if (new_i < 0) {
                    new_i = 0;
                }
                res(new_i, j, k) = img(i, j, k);
            }
        }
    }
//    for (int i = img.width - 1; i >= 1; i--) {
//        for (int j = 0; j < img.height; j++) {
//            for (int k = 0; k < 3; k++) {
//

//                res(new_i, j, k) = img(i, j, k);
//            }
//        }
//    }
//    Image res2(res.width, res.height);
//    HorizontalFlip(res, res2);

    cout << res.saveImage("saved img/gogogaga.jpg") << endl;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

void resize() {
    double hRatio, wRatio;
    cin >> hRatio >> wRatio;

    Image img("img/mountain.jpg");
    Image size(img.width * wRatio, img.height * hRatio);

    double cWidth = 1.0 / wRatio;
    double cHeight = 1.0 / hRatio;

    for (int i = 0; i < size.width; i++) {
        for (int j = 0; j < size.height; j++) {
            for (int k = 0; k < 3; k++) {
                size(i, j, k) = img(i * cWidth, j * cHeight, k);
            }
        }
    }

    size.saveImage("saved img/test.jpg");
}

void purple() {
    // don't forget to time things
    Image img("img/luffy.jpg");

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            int nRed = -(img(i, j, 0)/8) + img(i, j, 0);
            nRed *= 1.2;
            if (nRed > 255) {
                nRed = 255;
            } // -10
            else if (nRed < 0) {
                nRed = 0;
            }

            int nGreen = -(img(i, j, 1)/3) + img(i, j, 1);
            nGreen *= 1.2;
            if (nGreen > 255) {
                nGreen = 255;
            } // -50
            else if (nGreen < 0) {
                nGreen = 0;
            }

            int nBlue = -(img(i, j, 2)/10) + img(i, j, 2);
            nBlue *= 1.4;
            if (nBlue > 255) {
                nBlue = 255;
            } // -10
            else if (nBlue < 0) {
                nBlue = 0;
            }

            img(i, j, 0) = nRed;
            img(i, j, 1) = nGreen;
            img(i, j, 2) = nBlue;
        }
    }

    img.saveImage("saved img/test.jpg");
}

bool choiceCheck(const string& choice) {
    vector<string> choices = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                              "11", "12", "13", "14", "15", "17", "18"};

    for (const string& i : choices) {
        if (choice == i) {
            return true;
        }
    }
    return false;
}
int randomInRange(int min, int max) {
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
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
    } else if (ex == "tga") {
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

                for (int x = -slider; x <= slider; x++) { // -1 0 1
                    for (int y = -slider; y <= slider; y++) { // -1 0 1
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
void NaturalSunlight(Image img, Image& sunImg) {
    Image yellowImg(img.width, img.height);
    Image mergeImg(img.width, img.height);

    for (int i = 0; i < img.width; i++) { // Creating yellow image with same dimensions
        for (int j = 0; j < img.height; j++) {
            yellowImg(i, j, 0) = 255;
            yellowImg(i, j, 1) = 191;
            yellowImg(i, j, 2) = 0;
        }
    }
    Merge(img, yellowImg, 0.2, mergeImg); // Merging adds the yellow color effect
    Brightness(mergeImg, 1.1, sunImg); // Brightening the image for better results
}
void imageNoise(Image img, Image& noiseImg) {
    Image noise(img.width, img.height);
    for (int i = 0; i < img.width; i++) {
        int counter = 0, subC = 0;
        for (int j = 0; j < img.height; j++) {
//            int _pixel = randomInRange(0, 255);
//            int rChannel = randomInRange(0, 2);

            if (i % 10 == 0) { // counter > img.height/30
                for (int k = 0; k < 3; k++) {
                    noise(i, j, k) = randomInRange(0, 180);
                }
//                int newP = _pixel - 30;
//                if (newP < 0) {
//                    newP = 0;
//                }
//                noise(i, j, rChannel) = newP;

                if (subC > 5) {
                    subC = 0;
                    counter = 0;
                }
                subC++;
                continue;
            }

//            noise(i, j, rChannel) = _pixel + 30;
            for (int k = 0; k < 3; k++) {
                noise(i, j, k) = randomInRange(0, 255);
            }
            counter++;
        }
    }
    Merge(img, noise, 0.15, noiseImg); // 0.15

    noise.saveImage("saved img/noise.jpg");
}
void InfraredLight(Image img, Image& infraredImg) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            unsigned int grayAvg = 0;
            for (int k = 0; k < 3; k++) {
                grayAvg += img(i, j, k);
            }

            grayAvg /= 3;
            infraredImg(i, j, 0) = 255; // 0
            infraredImg(i, j, 1) = 255 - grayAvg; // grayAvg
            infraredImg(i, j, 2) = 255 - grayAvg; // grayAvg
        }
    }
}
