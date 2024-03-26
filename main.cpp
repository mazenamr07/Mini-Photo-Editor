#include <sstream>
#include <vector>
#include "Image_Class.h"

using namespace std;

bool choiceCheck(const string& choice) {
    vector<string> choices = {"0", "1", "2", "3", "4", "5"};

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

void InvertColor(Image myimage, Image& img){
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

void menu() {
    cout << "Welcome to our mini photo editor.\n"
            "(to start put your images in the cMake folder)\n" << endl;

    string imgName, ex;
    cout << "Enter the name of your image:" << endl << ">>";
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
    cout << "1- GrayScale\n"
            "2- Merge Two Images\n"
            "3- Adjust Brightness\n"
            "4- Invert Color\n"
            "5- **** ****\n"
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

    else if (choice_1 == "1") { // GrayScale
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
            string newName, newEx;
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

    else if (choice_1 == "2") { // Merge Two Images

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