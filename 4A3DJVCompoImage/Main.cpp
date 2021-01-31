#include "MenuManager.h"
#include "src/Image.h"
#include "opencv2/opencv.hpp"

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