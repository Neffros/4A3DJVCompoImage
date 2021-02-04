#pragma once
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "AlgoImages.h"
#include "src/Image.h"
#include "Settings.h"



class MenuManager
{
	private:
		Settings* settings = Settings::getInstance();
		//display menus
		void showOptionMenu();
		void showImageMenu();
		void showVideoMenu();
		void showFadingSettings();
		void showOverlapSettings();
		void showDistanceSettings();
		void showStepSettings();

		//select directory methods
		std::string BrowseFolder(std::string saved_path);
		static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	public:
		//single instance of menuManager
		static MenuManager& getInstance();
		void showMainMenu();


	
};