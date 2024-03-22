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

int main() {
    Image img(250,250);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            for (int k = 0; k < 3; k++) {
                img(i, j, k) = 255;
            }
        }
    }
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            img(i, j, 0) = 200;
            img(i, j, 1) = 63;
            img(i, j, 2) = 154;
        }
    }


    img.saveImage("saved img/cSquare.png");
    return 0;
}
