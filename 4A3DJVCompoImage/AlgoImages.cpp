#include <cmath>
#include "AlgoImages.h"
#include <filesystem>
#include <cmath>
namespace fs = std::filesystem;
namespace AlgoImg
{
    std::vector<Image> AlgoImages::getAllImagesInPath(std::string path)
    {
        std::vector<Image> images;
        int i = 0;

        for (const auto& entry : fs::directory_iterator(path))
        {
            std::string ext = entry.path().extension().string();
            if (ext != ".PNG" && ext != ".jpeg" && ext != ".BMP" && ext != ".TGA")
            {
                std::cout << entry.path().string().c_str() << " is not a compatible image" << std::endl;;
                continue;
            }
            Image im(entry.path().string().c_str());
            images.push_back(im);
            i++;
        }
        return images;
    }

    void AlgoImages::writeImage(Image& image, std::string filename)
    {
        std::cout << "write ? " << image.write(filename.c_str());
    }

    template <typename T>
    std::vector<T> AlgoImages::sortVec(std::vector<T>& vec)
    {
        T tmp;
        std::vector<T> res = vec;
        for (int j = 0; j < res.size() - 1; j++)
        {
            for (int i = 0; i < res.size() - 1; i++)
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
    void AlgoImages::getImageMask(Image targetImage, Image background, Image& mask, float maxDiff)
    {
        for (int x = 0; x < targetImage.getWidth(); x++)
        {
            for (int y = 0; y < targetImage.getHeight(); y++)
            {
                uint8_t* pixBg = background.getPixel(x, y);
                uint8_t* pixCur = targetImage.getPixel(x, y);
                
                uint8_t avgBg = (pixBg[0] + pixBg[1] + pixBg[2]) / 3;
                uint8_t avgPix = (pixCur[0] + pixCur[1] + pixCur[2]) / 3;

                if (abs(avgBg - avgPix > maxDiff))
                {
                    uint8_t pixMask[3] = { 0 , 0 ,0 };
                    mask.setPixel(x, y, pixMask);
                    //auto maskExt = std::tuple_cat(mask, std::make_tuple(x, y));
                }

            }
        }
    }

    void AlgoImages::getBackground(std::vector<Image> images, Image& res)
    {
       // Image res(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
        std::vector<uint8_t> pixValsR;
        std::vector<uint8_t> pixValsG;
        std::vector<uint8_t> pixValsB;
        for (int x = 0; x < images[0].getWidth(); x++)
        {
            for (int y = 0; y < images[0].getHeight(); y++)
            {
                pixValsR.clear();
                pixValsG.clear();
                pixValsB.clear();
                for (int imgIndex = 0; imgIndex < images.size(); imgIndex++)
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

                /*uint8_t* pixRes = res.getPixel(x, y);
                    
                pixRes[0] = red;
                pixRes[1] = green;
                pixRes[2] = blue;*/

                uint8_t pixRes[3] = { red,green,blue };
                res.setPixel(x, y, pixRes);

            }
        }
    }


    //Checks if all the images are same size. call this before any process to see if images are ok to use
    bool AlgoImages::checkSizeImages(std::vector<Image> images)
    {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int maxX = 0;
        int maxY = 0;
        for (int i = 0; i < images.size(); i++)
        {
            int imgWidth = images[i].getWidth();
            int imgHeigth = images[i].getHeight();
            if (imgWidth < minX)
                minX = imgWidth;
            else if (imgWidth > maxX)
                maxX = imgWidth;

            if (imgHeigth < minY)
                minY = imgHeigth;
            else if (imgHeigth > maxY)
                maxY = imgHeigth;


        }
        std::cout << "X: " << minX << " - " << maxX << std::endl;
        std::cout << "Y: " << minY << " - " << maxY << std::endl;
        if (minX == maxX && minY == maxY)
            return true;
        return false;
    }

}