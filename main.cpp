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

// Function to apply Edge Detect filter
void EdgeDetect(Image grayedImg, Image& edgeImg);

// Function to apply Inverted Colors filter
void InvertColor(Image myimage, Image& img);

// Functions to Rotate an image
void imageRotate90(Image img, Image& rtImg);
void imageRotate180(Image img, Image& rtImg);
void imageRotate270(Image img, Image& rtImg);

// Functions to Flip an image

void menu() {
    cout << "Welcome to our mini photo editor.\n"
            "(to start put your images in the cMake folder)\n" << endl;

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

    string choice_1;
    cout << "\nWhich Filter would you like to apply?" << endl;
    cout << "1- Gray Scale\n"
            "2- Black & White\n"
            "3- Invert Colors\n"
            "4- Merge Two Images\n"
            "5- Flip Image\n"
            "6- Rotate Image\n"
            "7- Adjust Brightness\n"
            "0- Exit Program\n" << ">>";
    getline(cin, choice_1);

    // checking if input is valid
    while (!choiceCheck(choice_1)) {
        cout << "Please select a valid option:\n" << ">>";
        getline(cin, choice_1);
    }

    if (choice_1 == "0") { // Exiting Program
        cout << "Bye bye!";
        exit(0);
    }

    else if (choice_1 == "1") { // Gray Scale
        Image img(imgName), grayImg(img.width, img.height);
        GrayScale(img, grayImg);

        string choice_2;
        cout << "Save changes in a new images or same image:\n"
                "1- Adjust same image\n"
                "2- Save to a new image\n"
                ">>";

        getline(cin, choice_2);
        while (choice_2 != "1" and choice_2 != "2") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_2);
        }

        if (choice_2 == "1") {
            grayImg.saveImage(imgName);
        }
        else {
            string newName;
            cout << "Enter the name of new image:" << endl << ">>";
            getline(cin, newName);

            dotPos = newName.find('.');
            ex = newName.substr(dotPos + 1);

            //Checking if file extension is valid
            while (dotPos == string::npos or !exCheck(ex)) {
                cout << "Error: unsupported file extension, enter file name again:"
                     << endl << ">>";

                getline(cin, newName);
                dotPos = newName.find('.');
                ex = newName.substr(dotPos + 1);
            }

            grayImg.saveImage(newName);
        }
    }

    else if (choice_1 == "2") { // Black & White
        // First, we grayscale the image
        Image img(imgName), grayImg(img.width, img.height);
        GrayScale(img, grayImg);

        // Then, we apply the filter
        Image bwImg (img.width, img.height);
        BlackWhite(grayImg, bwImg);

        string choice_2;
        cout << "Save changes in a new images or same image:\n"
                "1- Adjust same image\n"
                "2- Save to a new image\n"
                ">>";

        getline(cin, choice_2);
        while (choice_2 != "1" and choice_2 != "2") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_2);
        }

        if (choice_2 == "1") {
            bwImg.saveImage(imgName);
        }
        else {
            string newName;
            cout << "Enter the name of new image:" << endl << ">>";
            getline(cin, newName);

            dotPos = newName.find('.');
            ex = newName.substr(dotPos + 1);

            //Checking if file extension is valid
            while (dotPos == string::npos or !exCheck(ex)) {
                cout << "Error: unsupported file extension, enter file name again:"
                     << endl << ">>";

                getline(cin, newName);
                dotPos = newName.find('.');
                ex = newName.substr(dotPos + 1);
            }

            bwImg.saveImage(newName);
        }
    }

    else if (choice_1 == "3") {

    }

    else if (choice_1 == "4") { // Merge Two Images
        string imgName_2;
        cout << "Enter the name of your second image:" << endl << ">>";
        getline(cin, imgName_2);

        dotPos = imgName_2.find('.');
        ex = imgName_2.substr(dotPos + 1);

        //Checking if file extension is valid
        while (dotPos == string::npos or !exCheck(ex)) {
            cout << "Error: unsupported file extension, enter file name again:"
                 << endl << ">>";

            getline(cin, imgName_2);
            dotPos = imgName_2.find('.');
            ex = imgName_2.substr(dotPos + 1);
        }

        Image img_1(imgName), img_2(imgName_2);

        if (img_1.width != img_2.width or img_1.height != img_2.height) {
            // should do resizing here
        }

        Image tempImg1, tempImg2;
        string filename1, filename2;
        exChange(img_1, 1, ".jpg", filename1, tempImg1);
        exChange(img_2, 2, ".jpg", filename2, tempImg2);

        Image merged(img_1.width, img_1.height);
        Merge(tempImg1, tempImg2, 0.5, merged);

        remove(filename1.c_str());
        remove(filename2.c_str());

        string choice_2;
        cout << "Save changes in a new images or first image:\n"
                "1- Adjust first image\n"
                "2- Save to a new image\n"
                ">>";

        getline(cin, choice_2);
        while (choice_2 != "1" and choice_2 != "2") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_2);
        }

        if (choice_2 == "1") {
            merged.saveImage(imgName);
        }
        else {
            string newName;
            cout << "Enter the name of new image:" << endl << ">>";
            getline(cin, newName);

            dotPos = newName.find('.');
            ex = newName.substr(dotPos + 1);

            //Checking if file extension is valid
            while (dotPos == string::npos or !exCheck(ex)) {
                cout << "Error: unsupported file extension, enter file name again:"
                     << endl << ">>";

                getline(cin, newName);
                dotPos = newName.find('.');
                ex = newName.substr(dotPos + 1);
            }

            merged.saveImage(newName);
        }
    }

    else if (choice_1 == "5") {

    }

    else if (choice_1 == "6") {

    }

    else if (choice_1 == "7") {

    }

}

int main() {
    menu();
    return 0;
}

void notes() {
    if ("Brightness notes to be added to menu") {

        // only works with .jpg bardo
        Image img("img/moon.jpg"), bright(img.width, img.height);
        Brightness(img, 2.5, bright); // 0 - 2 level
        int i = bright.saveImage("saved img/at.png");
        cout << i;
    }
    if ("Merge notes to be added to menu") {
        Image img("img/fire.png");
        Image img2("img/moon.jpg");

        Image tempImg1, tempImg2;
        string filename1, filename2;
        exChange(img, 1, ".jpg", filename1, tempImg1);
        exChange(img2, 2, ".bmp", filename2, tempImg2);

        Image mergedImg(img.width, img.height);
        Merge(tempImg1, tempImg2, 0.5, mergedImg);

        remove(filename1.c_str());
        remove(filename2.c_str());

        mergedImg.saveImage("saved img/merged.jpg");
    }
}

bool choiceCheck(const string& choice) {
    vector<string> choices = {"0", "1", "2", "3", "4", "5", "6", "7"};

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
    filename = "temp/tempPic";
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
            if (grayImg(i, j, 0) > 135) {
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
void EdgeDetect(Image grayedImg, Image& edgeImg) {
    for (int i = 0; i < grayedImg.width; i++) {
        for (int j = 0; j < grayedImg.height; j++) {
            if (grayedImg(i + 1, j, 0) - grayedImg(i, j, 0) > 10
                or grayedImg(i, j + 1, 0) - grayedImg(i, j, 0) > 10) {
                edgeImg(i, j, 0) = 0;
                edgeImg(i, j, 1) = 0;
                edgeImg(i, j, 2) = 0;
            }
            else {
                edgeImg(i, j, 0) = 255;
                edgeImg(i, j, 1) = 255;
                edgeImg(i, j, 2) = 255;
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
