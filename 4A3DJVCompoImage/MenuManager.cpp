#include "MenuManager.h"

MenuManager* MenuManager::instance = nullptr;

MenuManager* MenuManager::getInstance()
{
	if (instance == nullptr)
		instance = new MenuManager();
	return instance;
}

MenuManager::MenuManager()
{

}
//Main menu with choices for configurations
void MenuManager::showMainMenu()
{
	int choice = 0;

	std::cout << "Main Menu" << std::endl;
	std::cout << "1 = image processing" << std::endl;
	std::cout << "2 = video processing" << std::endl;
	std::cout << "3 = algorithm settings" << std::endl;
	std::cout << "\n\n4 = start proccess" << std::endl;
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
		showImageMenu();
		break;
	case 2:
		showVideoMenu();
		break;
	case 3:
		showOptionMenu();
		break;
	case 4:
		AlgoImages::StartImageProcess();
		break;
	case -1:
		std::exit(0);
		break;

	}
	std::cin.ignore(INT_MAX, '\n');
	showMainMenu();

}
//Show options on the menu
void MenuManager::showOptionMenu()
{
	int choice = 0;
	float val = 0.0f;
	std::cout << "Options Menu" << std::endl;
	std::cout << "1 = fading settings" << std::endl;
	std::cout << "2 = overlap settings" << std::endl;
	std::cout << "3 = minimal distance settings" << std::endl;
	std::cout << "4 = mask settings" << std::endl;
	std::cout << "5 = grayscale output" << std::endl;
	
	std::cout << "\n\n-1 = return to Main Menu" << std::endl;
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
			showFadingSettings();
			break;
		case 2:
			showOverlapSettings();
			break;
		case 3:
			showDistanceSettings();
			break;
		case 4:
			showMaskMenu();
			break;
		case 5:
			settings->setIsGrayScale(!settings->getIsGrayScale());
			std::cout << "gray scale set to: " << settings->getIsGrayScale() << std::endl;
			break;
		case -1:
			showMainMenu();
			break;
	}

	std::cin.ignore(INT_MAX, '\n');

	showOptionMenu();
}
//Show images options on the menu
void MenuManager::showImageMenu()
{
	int choice = 0;
	std::string strInput = "";

	std::cout << "Image Menu" << std::endl;
	std::cout << "1 = image directory" << std::endl;
	std::cout << "2 = output directory" << std::endl;
	std::cout << "3 = output filename (with extension)" << std::endl;
	std::cout << "\n\n-1 = Return to main menu" << std::endl;

	std::cin >> choice;


	switch (choice)
	{
	default:
		std::cout << "Wrong input" << std::endl;;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		showImageMenu();
		break;
	case 1:
		settings->setImageDirectory(BrowseFolder(settings->getSavedDirectory()));
		settings->setSavedDirectory(settings->getImageDirectory());
		std::cout << "Chosen path: " << settings->getImageDirectory() << std::endl;
		break;
	case 2:
		settings->setOutputDirectory(BrowseFolder(settings->getSavedDirectory()) + "\\");
		settings->setSavedDirectory(settings->getOutputDirectory());
		std::cout << "Chosen path: " << settings->getOutputDirectory() << std::endl;
		break;
	case 3:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Enter chosen name." << std::endl;
		std::cin >> strInput;
		settings->setOutputName(strInput);
		break;
	case -1:
		showMainMenu();
		break;
	}

	std::cin.ignore(INT_MAX, '\n');
	showImageMenu();

}
//Show videos options on the menu
void MenuManager::showVideoMenu()
{
	int choice = 0;
	std::string strInput = "";

	std::cout << "Video Menu" << std::endl;
	std::cout << "1 = video directory" << std::endl;
	std::cout << "2 = video name (with extension)" << std::endl;
	std::cout << "3 = output directory" << std::endl;
	std::cout << "4 = output filename (with extension)" << std::endl;
	std::cout << "5 = set picture taken per frame" << std::endl;

	std::cout << "\n\n-1 = Return to main menu" << std::endl;

	std::cin >> choice;


	switch (choice)
	{
	default:
		std::cout << "Wrong input" << std::endl;;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		showVideoMenu();
		break;
	case 1:
		settings->setVideoDirectory(BrowseFolder(settings->getSavedDirectory()));
		settings->setSavedDirectory(settings->getVideoDirectory());

		std::cout << "Chosen path: " << settings->getVideoDirectory() << std::endl;
		break;
	case 2:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Enter Video name (with extension)." << std::endl;
		std::cin >> strInput;
		settings->setVideoName(strInput);
		break;
	case 3:
		settings->setOutputDirectory(BrowseFolder(settings->getSavedDirectory()) + "\\");
		settings->setSavedDirectory(settings->getOutputDirectory());
		std::cout << "Chosen path: " << settings->getOutputDirectory() << std::endl;
		break;
	case 4:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Enter chosen name. (with extension)" << std::endl;
		std::cin >> strInput;
		settings->setOutputName(strInput);
		break;
	case 5:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "set frame frequency per second" << std::endl;
		std::cin >> choice;
		settings->setVideoFrameFrequency(choice);
		break;
	case -1:
		showMainMenu();
		break;
	}

	std::cin.ignore(INT_MAX, '\n');
	showVideoMenu();
}

void MenuManager::showFadingSettings()
{
	int choice = 0;

	std::cout << "Fading Menu" << std::endl;
	std::cout << "1 = set to Opaque\t*default" << std::endl;
	std::cout << "2 = set each frame from transparant to opaque" << std::endl;
	std::cout << "3 = set each frame from opaque to transparant" << std::endl;
	std::cout << "\n\n-1 = return to Options Menu" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
		default:
			std::cout << "Wrong input" << std::endl;;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			showFadingSettings();
			break;
		case 1:
			settings->setFade(Opaque);
			break;
		case 2:
			settings->setFade(TransparentToOpaque);
			break;
		case 3:
			settings->setFade(OpaqueToTransparent);
			break;
		case -1:
			showOptionMenu();
			break;
	}
	std::cin.ignore(INT_MAX, '\n');
	showFadingSettings();
}

//Show overlap settings on the menu
void MenuManager::showOverlapSettings()
{
	int choice = 0;

	std::cout << "Overlap Menu" << std::endl;
	std::cout << "1 = enable/disable overlap\t*disabled by default" << std::endl;
	std::cout << "2 = set max overlap" << std::endl;
	std::cout << "\n\n-1 = return to Options Menu" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
		default:
			std::cout << "Wrong input" << std::endl;;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			showOverlapSettings();
			break;
		case 1:		
			settings->setIsOverlapImage(!settings->getIsOverlapImage());
			break;
		case 2:
			std::cout << "Enter maximum overlap (percentage value without writting %)" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cin >> choice; //might break?
			settings->setOverlap(choice);
			break;
		case -1:
			showMainMenu();
			break;

	}

	std::cin.ignore(INT_MAX, '\n');
	showOverlapSettings();
}

//Show distance settings on the menu
void MenuManager::showDistanceSettings()
{

	int choice = 0;

	std::cout << "Distance Menu" << std::endl;
	std::cout << "1 = enable/disable minimal distance\t*disabled by default" << std::endl;
	std::cout << "2 = set max overlap" << std::endl;
	std::cout << "\n\n-1 = return to Options Menu" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	default:
		std::cout << "Wrong input" << std::endl;;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		showDistanceSettings();
		break;
	case 1:
		settings->setIsDistanceImage(!settings->getIsDistanceImage());
		break;
	case 2:
		std::cout << "Enter minimum distance" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> choice; 
		settings->setMinDistance(choice);
		break;
	case -1:
		showMainMenu();
		break;

	}

	std::cin.ignore(INT_MAX, '\n');
	showDistanceSettings();
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
//Show masks settings on the menu
void MenuManager::showMaskMenu(){

	int choice = 0;
	float val = 0.0f;
	std::cout << "Options Menu" << std::endl;
	std::cout << "1 = set max mask difference" << std::endl;
	std::cout << "2 = enable Connexe" << std::endl;
	std::cout << "3 = set max connexe treshhold" << std::endl;
	std::cout << "4 = print each mask" << std::endl;
	std::cout << "5 = print each step of final mask" << std::endl;

	std::cout << "\n\n-1 = return to Options Menu" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	default:
		std::cout << "Wrong input" << std::endl;;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		showMaskMenu();
		break;
	case 1:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "set max mask difference value (float)" << std::endl;
		std::cin >> val;
		settings->setMaxMaskDiff(val);
		break;
	case 2:
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "set max connexe treshhold value " << std::endl;
		std::cin >> val;
		settings->setConnexeThreshold(val);
		break;
	case 3:
		settings->setIsGrayScale(!settings->getIsGrayScale());
		std::cout << "gray scale set to: " << settings->getIsGrayScale() << std::endl;
		break;
	case 4:
		settings->setDrawMask(!settings->getDrawMask());
		std::cout << "draw mask set to:" << settings->getDrawMask() << std::endl;
		break;
	case 5:
		settings->setDrawFinalMask(!settings->getDrawFinalMask());
		std::cout << "draw each step of final mask set to:" << settings->getDrawMask() << std::endl;
		break;
	case -1:
		showOptionMenu();
		break;
	}

	std::cin.ignore(INT_MAX, '\n');
	showMaskMenu();
}