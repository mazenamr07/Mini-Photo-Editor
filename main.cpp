#include "Image_Class.h"
#include <vector>

using namespace std;

void menu() {
    vector<unsigned char> pixels;
    Image img("img/frieren.jpg");
    Image square(250, 250);
    Image imgBro(720, 1080);
    Image imgRT90(img.height, img.width);
    Image imgRT270(img.height, img.width);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                imgBro(720 - i - 1, 1080 - j - 1, k) = img(i, j, k);
                imgRT90(j, 720 - i - 1 ,k) = img(i, j, k);
                imgRT270(1080 - j - 1, i ,k) = img(i, j, k);
            }
        }
    }

    square(125, 35, 0) = img(0, 0, 0);
    square(125, 35, 1) = img(0, 0, 1);
    square(125, 35, 2) = img(0, 0, 2);


    square.saveImage("saved img/cSquare.png");
    imgBro.saveImage("saved img/Mafggbombo.png");
    imgRT90.saveImage("saved img/RTfrieren.jpg");
    imgRT270.saveImage("saved img/RT270frieren.jpg");
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

int main() {
    Image img("img/photographer.jpg"), img2(img.width, img.height);
    EdgeDetect(img, img2);
    int i = img2.saveImage("saved img/gray123.jpg");
    cout << i;

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