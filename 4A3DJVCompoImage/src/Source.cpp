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

int main(int argc, const char* argv[])
{
   // std::string path;
  //  path = BrowseFolder("E:\\dev\\4A3DJVCompoImage");
   // std::cout << path << std::endl;
    
  /*  for (const auto& entry : fs::directory_iterator(path))
    {
      //  std::cout << entry.path() << std::endl;
      //  std::cout << entry.path().extension() << std::endl;
      /*  if (entry.path().extension() == ".PNG")
        {
            std::cout << "is image" << std::endl;;
        }
        else
            std::cout << "isn't an image" << std::endl;;*/
    /*    Image im(entry.path().string().c_str());
        Image grayv1 = im;
        grayv1.grayscale_v1();
        std::cout << "write ? " << grayv1.write("E:\\dev\\4A3DJVCompoImage\\output\\one.png");
       /* Image grayv2 = im;
        grayv2.grayscale_v2();
        grayv2.write("E:\\dev\\4A3DJVCompoImage\\output\\two.png");*/

  //  }
  //  Image("D:\\Dev\\traitement_image\\4A3DJVCompoImage\\readmeImages\\settings1.PNG");
    Image im("D:\\Dev\\traitement_image\\4A3DJVCompoImage\\readmeImages\\settings1.PNG");
    Image grayv1 = im;
    grayv1.grayscale();
    std::cout << "write ? " << grayv1.write("one.png");
    return 0;
}