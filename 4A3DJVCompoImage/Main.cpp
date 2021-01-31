#include "MenuManager.h"
#include "src/Image.h"
#include "opencv2/opencv.hpp"

int main(int argc, const char* argv[])
{
    MenuManager menuManager;

    menuManager.getInstance();

    menuManager.showMainMenu();

    return 0;
}
