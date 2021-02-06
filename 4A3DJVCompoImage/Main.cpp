#include "MenuManager.h"
#include "src/Image.h"
#include "opencv2/opencv.hpp"
#include "Settings.h"

int main(int argc, const char* argv[])
{
    MenuManager* menuManager = MenuManager::getInstance();

    menuManager->showMainMenu();

    return 0;
}
