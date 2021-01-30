#include "MenuManager.h"
#include "src/Image.h"
#include <cmath>
namespace fs = std::filesystem;

static std::vector<Image> getAllImagesInPath(std::string path)
{
    std::vector<Image> images;
    int i = 0;
    for (const auto& entry : fs::directory_iterator(path))
    {
        Image im(entry.path().string().c_str());
        images.push_back(im);
        i++;
    }
    return images;
}

static void writeImage(Image image, std::string filename)
{
    std::cout << "write ? " << image.write(filename.c_str());
}

static Image getBackground(std::vector<Image> images)
{
    Image res = images[0];
    std::vector<uint8_t> pixValsR;
    std::vector<uint8_t> pixValsG;
    std::vector<uint8_t> pixValsB;
    for (int x = 0; x < images[0].getWidth(); x++)
    {
        for (int y = 0; y < images[0].getHeigth(); y++)
        {
            for (int imgIndex = 0; imgIndex < images.size(); imgIndex)
            {
                uint8_t* pix = images[imgIndex].getPixel(x, y);
                pixValsR.push_back(pix[0]);
                pixValsG.push_back(pix[1]);
                pixValsB.push_back(pix[2]);
            }
            pixValsR = sortVec(pixValsR);
            pixValsG = sortVec(pixValsG);
            pixValsB = sortVec(pixValsB);

            uint8_t red = pixValsR[ceil(pixValsR.size() / 2)];
            uint8_t green = pixValsG[ceil(pixValsG.size() / 2)];
            uint8_t blue = pixValsB[ceil(pixValsB.size() / 2)];
            
            uint8_t* pixRes = res.getPixel(x, y);

            pixRes[0] = red;
            pixRes[1] = green;
            pixRes[2] = blue;
            
            res.setPixel(x, y, pixRes);
        }
    }
    return res;
}

template <typename T>
std::vector<typename T> sortVec(std::vector<typename T> &vec)
{
    typename T tmp;
    std::vector<typename T> res = vec;
    for (int j = 0; j < N - 1; j++)
    {
        for (int i = 0; i < N - 1; i++)
        {

            if (res[i] > res[i + 1])
            {
                tmp = res[i + 1];
                res[j + 1] = res[j];
                res[j] = tmp;
            }
        }
    }

    return res;
}

//Checks if all the images are same size. call this before any process to see if images are ok to use
static bool checkSizeImages(std::vector<Image> images)
{
    int minX, minY = INT_MAX;
    int maxX, maxY = 0;
    for (int i = 0; i < images.size(); i++)
    {
        int imgWidth = images[i].getWidth();
        int imgHeigth = images[i].getHeigth();
        if (imgWidth < minX)
            minX = imgWidth;
        else if (imgWidth > maxX)
            maxX = imgWidth;

        if (imgHeigth < minY)
            minY = imgHeigth;
        else if (imgHeigth > maxY)
            maxY = imgHeigth;

        
    }
    if (minX == maxX && minY == maxY)
        return true;
    return false;
}
int main(int argc, const char* argv[])
{
    MenuManager menuManager;
    
    menuManager.getInstance();
        
    menuManager.showMainMenu();
    /*std::string path;
    path = BrowseFolder("E:\\dev\\4A3DJVCompoImage");

    int i = 0;
    for (const auto& entry : fs::directory_iterator(path))
    {
        Image im(entry.path().string().c_str());
        Image grayv1 = im;
        grayv1.grayscale();
        std::string filename = "one_" + std::to_string(i) + ".png";
        std::cout << "write ? " << grayv1.write(filename.c_str());
        i++;
    }*/
    return 0;
}