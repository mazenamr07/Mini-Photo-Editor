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

int main() {
    Image img("saved img/RT270frieren.jpg");

    Image grayImg(img.width, img.height);
    GrayScale(img, grayImg);

    int x = grayImg.saveImage("saved img/gray_frieren.jpg");
    cout << x;
    return 0;
}
