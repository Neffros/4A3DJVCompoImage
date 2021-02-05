#include "MenuManager.h"

MenuManager& MenuManager::getInstance()
{
	static MenuManager instance;
	return instance;
}

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

void MenuManager::showOptionMenu()
{
	int choice = 0;
	float val = 0.0f;
	std::cout << "Options Menu" << std::endl;
	std::cout << "1 = fading settings" << std::endl;
	std::cout << "2 = overlap settings" << std::endl;
	std::cout << "3 = step settings" << std::endl;
	std::cout << "4 = minimal distance settings" << std::endl;
	std::cout << "5 = set max mask difference" << std::endl;
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
			showStepSettings();
			break;
		case 4:
			showDistanceSettings();
			break;
		case 5:
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "set max mask difference value (float)" << std::endl;
			std::cin >> val;
			settings->setMaxMaskDiff(val);
		case -1:
			showMainMenu();
			break;
	}

	std::cin.ignore(INT_MAX, '\n');

	showOptionMenu();
}

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
		settings->setImageDirectory(BrowseFolder("E:\\dev\\4A3DJVCompoImage"));
		std::cout << "Chosen path: " << settings->getImageDirectory() << std::endl;
		break;
	case 2:
		settings->setOutputDirectory(BrowseFolder("E:\\dev\\4A3DJVCompoImage") + "\\");
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

void MenuManager::showVideoMenu()
{
	int choice = 0;
	std::string strInput = "";

	std::cout << "Video Menu" << std::endl;
	std::cout << "1 = video directory" << std::endl;
	std::cout << "2 = video name (with extension)" << std::endl;
	std::cout << "3 = output directory" << std::endl;
	std::cout << "4 = output filename (with extension)" << std::endl;
	std::cout << "5 = set picture frequency per frame" << std::endl;

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
		settings->setVideoDirectory(BrowseFolder("E:\\dev\\4A3DJVCompoImage"));
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
		settings->setOutputDirectory(BrowseFolder("E:\\dev\\4A3DJVCompoImage") + "\\");
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
		std::cin >> choice; //might break?
		settings->setMinDistance(choice);
		break;
	case -1:
		showMainMenu();
		break;

	}

	std::cin.ignore(INT_MAX, '\n');
	showDistanceSettings();
}

void MenuManager::showStepSettings()
{

	int choice = 0;

	std::cout << "Step distance Menu" << std::endl;
	std::cout << "1 = enable/disable minimal step\t*disabled by default" << std::endl;
	std::cout << "2 = set step distance" << std::endl;
	std::cout << "\n\n-1 = return to Options Menu" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	default:
		std::cout << "Wrong input" << std::endl;;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		showStepSettings();
		break;
	case 1:
		settings->setIsStepImage(!settings->getIsStepImage());
		break;
	case 2:
		std::cout << "Enter step distance" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> choice; //might break?
		settings->setStepDistance(choice);
		break;
	case -1:
		showMainMenu();
		break;

	}

	std::cin.ignore(INT_MAX, '\n');
	showStepSettings();
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