#include "MenuManager.h"

MenuManager& MenuManager::getInstance()
{
    static MenuManager instance;
    return instance;
}

std::string MenuManager::getImageDirectory()
{
    return this->imageDirectory;
}

std::string MenuManager::getOutputDirectory()
{
    return this->outputDirectory;
}

std::string MenuManager::getOutputName()
{
    return outputName;
}

bool MenuManager::getIsFading()
{
    return this->isFading;
}

bool MenuManager::getIsStepImage()
{
    return this->isStepImage;
}

bool MenuManager::getIsDistanceImage()
{
    return this->isDistanceImage;
}

int MenuManager::getOverlap()
{
    return this->overlap;
}

int MenuManager::getStepDistance()
{
    return this->stepDistance;
}

int MenuManager::getMinDistance()
{
    return minDistance;
}

void MenuManager::setImageDirectory(std::string directory)
{
    this->imageDirectory = directory;
}

void MenuManager::setOutputDirectory(std::string directory)
{
    this->outputDirectory = directory;
}

void MenuManager::setOutputName(std::string name)
{
    this->outputName = name;
}

void MenuManager::setIsFading(bool isFading)
{
    this->isFading = isFading;
}

void MenuManager::setIsStepImage(bool isStepImage)
{
    this->isStepImage = isStepImage;
}

void MenuManager::setIsDistanceImage(bool isDistanceImage)
{

    this->isDistanceImage = isDistanceImage;
}

void MenuManager::setOverlap(int val)
{
    this->overlap = val;

}

void MenuManager::setStepDistance(int val)
{
    this->stepDistance = val;

}

void MenuManager::setMinDistance(int val)
{
    this->minDistance = val;

}

void MenuManager::showMainMenu()
{
    int choice = 0;
    std::string strInput = "";
    std::cout << "Main Menu" << std::endl;
    std::cout << "1 = image directory\t*mandatory" << std::endl;
    std::cout << "2 = output directory\t*mandatory" << std::endl;
    std::cout << "3 = output file name" << std::endl;
    std::cout << "4 = options menu" << std::endl;
    std::cout << "5 = start process" << std::endl;
    std::cout << "-1 = quit program" << std::endl;
    std::cin >> choice;

    switch (choice)
    {
        default:
            std::cout << "Wrong input" << std::endl;;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showMainMenu();
            break;
        case 1:
            this->imageDirectory = BrowseFolder("E:\\dev\\4A3DJVCompoImage");
            std::cout << "Chosen path: " << this->imageDirectory << std::endl;
            break;
        case 2:
            this->outputDirectory = BrowseFolder("E:\\dev\\4A3DJVCompoImage");
            std::cout << "Chosen path: " << this->outputDirectory << std::endl;
            break;
        case 3:
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Enter chosen name." << std::endl;
            std::cin >> strInput;
            this->outputName = strInput;
            break;
        case 4:
            showOptionMenu();
            break;
        case 5:
            if (this->imageDirectory == "" || this->outputDirectory == "")
            {
                std::cout << "please inform image directory and output directory first" << std::endl;
                break;
            }
            //call image processing here
            break;
        case 0:
            std::cout << "Wrong input" << std::endl;;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showMainMenu();
            break;
        case -1:
        {
            std::exit(0);
            break;
        }
    }


    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Enter chosen name.";
    showMainMenu();

}

void MenuManager::showOptionMenu()
{
    int choice = 0;
    std::string strInput = "";
    std::cout << "Options Menu" << std::endl;
    std::cout << "1 = enable/disable fading" << std::endl;
    std::cout << "2 = enable/disable stepping" << std::endl;
    std::cout << "3 = set step value" << std::endl;
    std::cout << "4 = enable/disable distance" << std::endl;
    std::cout << "5 = set minimal distance value" << std::endl;
    std::cout << "-1 = return to Main Menu" << std::endl;
    std::cin >> choice;
    switch (choice)
    {
        default:
            std::cout << "Wrong input" << std::endl;;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showOptionMenu();
            break;
        case 1:
            this->isFading = !this->isFading;
            this->isFading ? 
                std::cout << "fading is now enabled" << std::endl :
                std::cout << "fading is now disabled" << std::endl;
            break;
        case 2:
            this->isStepImage = !this->isStepImage;
            this->isStepImage ?
                std::cout << "stepping is now enabled" << std::endl :
                std::cout << "stepping is now disabled" << std::endl;
            break;
        case 3:
            std::cout << "enter step distance" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cin >> this->stepDistance;
            break;
        case 4:
            this->isDistanceImage = !this->isDistanceImage;
            this->isDistanceImage ?
                std::cout << "distance image is now enabled" << std::endl :
                std::cout << "distance image is now disabled" << std::endl;
            break;
        case 5:
            std::cout << "enter minimal distance" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cin >> this->minDistance;
            break;
        case 0:
            std::cout << "Wrong input" << std::endl;;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showOptionMenu();
            break;
        case -1:
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showMainMenu();
            break;

    }

    showOptionMenu();
}

std::string MenuManager::BrowseFolder(std::string saved_path)
{
    TCHAR path[MAX_PATH];

    const char* path_param = saved_path.c_str();

    BROWSEINFO bi = { 0 };
    bi.lpszTitle = ("Browse for folder...");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (LPARAM)path_param;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0)
    {
        //get the name of the folder and put it in path
        SHGetPathFromIDList(pidl, path);

        //free memory used
        IMalloc* imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }

        return path;
    }

    return "";
}

int MenuManager::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
    {
        std::string tmp = (const char*)lpData;
        std::cout << "path: " << tmp << std::endl;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}
