#include "MenuManager.h"

MenuManager& MenuManager::getInstance()
{
	static MenuManager instance;
	return instance;
}


std::string MenuManager::getImageDirectory() const
{
	return this->imageDirectory;
}

std::string MenuManager::getOutputDirectory() const
{
	return this->outputDirectory;
}

std::string MenuManager::getOutputName() const
{
	return outputName;
}

bool MenuManager::getIsFading() const
{
	return this->isFading;
}

bool MenuManager::getIsStepImage() const
{
	return this->isStepImage;
}

bool MenuManager::getIsDistanceImage() const
{
	return this->isDistanceImage;
}

int MenuManager::getOverlap() const
{
	return this->overlap;
}

int MenuManager::getStepDistance() const
{
	return this->stepDistance;
}

int MenuManager::getMinDistance() const
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
    int i = 0;
    std::vector<Image> images;
    std::string strInput = "";
    Image res;
    Image mask;
    std::cout << "Main Menu" << std::endl;
    std::cout << "1 = image directory\t*mandatory" << std::endl;
    std::cout << "2 = output directory\t*mandatory" << std::endl;
    std::cout << "3 = output file name" << std::endl;
    std::cout << "4 = options menu" << std::endl;
    std::cout << "5 = start process" << std::endl;
    std::cout << "6 = Choose video" << std::endl;
    std::cout << "7 = Choose videos name" << std::endl;
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
            {
                if (AlgoImg::AlgoImages::checkVideoInPath(this->videoDirectory, this->videoName)) {
                    AlgoImg::AlgoImages::getVideoFrame(this->outputDirectory, this->videoDirectory + "\\" + this->videoName, 5);
                    images = AlgoImg::AlgoImages::getAllImagesInPath(this->outputDirectory);
                }
                else {
                    if (this->videoDirectory != "" || this->videoName != "") {
                        std::cout << "could not read video" << std::endl;
                        this->videoDirectory = "";
                        this->videoName = "";
                        break;
                    } else if (this->imageDirectory == "" || this->outputDirectory == "")
                    {
                        std::cout << "please inform image directory and output directory first" << std::endl;
                        break;
                    }
                    images = AlgoImg::AlgoImages::getAllImagesInPath(imageDirectory);
                }


                if (!AlgoImg::AlgoImages::checkSizeImages(images))
                {
                    std::cout << "images are not the same size" << std::endl;
                    break;
                }
                //Image background("E:\\dev\\4A3DJVCompoImage\\output\\background.png");
                Image background(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
				AlgoImg::AlgoImages::getBackground(images, background);
				Image image_final(background);
				AlgoImg::AlgoImages::writeImage(background, this->outputDirectory + this->outputName); //TODO not putting in the selected folder
				for (int i = 0; i < images.size(); i++)
				{
					Image mask(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
					AlgoImg::AlgoImages::getImageMask(images[i], background, mask, 20.0f);
					AlgoImg::AlgoImages::writeImage(mask, "mask" + std::to_string(i) + ".png");
					Image cleaned_mask(mask);
					AlgoImg::AlgoImages::cleanNoiseOnBinaryMask(cleaned_mask, 200);
					AlgoImg::AlgoImages::writeImage(cleaned_mask, "cleaned_mask" + std::to_string(i) + ".png");
					AlgoImg::AlgoImages::binaryMerge(&cleaned_mask, &image_final, &images[i]);
				}
				AlgoImg::AlgoImages::writeImage(image_final, "image_final.png");
                break;
            }
        case 6: {
            this->videoDirectory = BrowseFolder("E:\\dev\\4A3DJVCompoImage");
            std::cout << "Chosen path: " << this->videoDirectory << std::endl;
            break;
        }
        case 7:
        {
            std::cout << "enter video name (with extension)" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cin >> this->videoName;
            break;
        }
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