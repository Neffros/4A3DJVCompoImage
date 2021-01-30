#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "Image.h"


namespace fs = std::filesystem; 



static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

    if (uMsg == BFFM_INITIALIZED)
    {
        std::string tmp = (const char*)lpData;
        std::cout << "path: " << tmp << std::endl;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}

std::string BrowseFolder(std::string saved_path)
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

void showOptionMenu()
{

}
void showMainMenu()
{
    int choice = 0;
    std::cout << "Menu" << std::endl;
    std::cout << "1 = image directory" << std::endl;
    std::cout << "2 = output directory" << std::endl;
    std::cout << "3 = output file name" << std::endl;
    std::cout << "4 = options menu" << std::endl;
    std::cin >> choice;
    switch (choice)
    {
        default:
            std::cout << "Wrong input";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showMainMenu();
            break;
        case 1:
            std::string path;
            //imageDirectory = BrowseFolder("E:\\dev\\4A3DJVCompoImage");
            break;
    }
}
/*
int main(int argc, const char* argv[])
{

    showMainMenu();
    std::string path;
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
    }
    return 0;
}
*/