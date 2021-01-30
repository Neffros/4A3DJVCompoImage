#pragma once
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "AlgoImages.h"
#include "src/Image.h"


class MenuManager
{
	private:
		std::string imageDirectory;
		std::string outputDirectory;
		std::string outputName = "output.PNG";
		bool isFading;
		bool isStepImage;
		bool isDistanceImage;
		int overlap;
		int stepDistance;
		int minDistance;
	public:
		//single instance of menuManager
		static MenuManager& getInstance();
		//getters
		std::string getImageDirectory() const;
		std::string getOutputDirectory() const;
		std::string getOutputName() const;
		bool getIsFading() const;
		bool getIsStepImage() const;
		bool getIsDistanceImage() const;
		int getOverlap() const;
		int getStepDistance() const;
		int getMinDistance() const;
		//setters
		void setImageDirectory(std::string directory);
		void setOutputDirectory(std::string directory);
		void setOutputName(std::string name);
		void setIsFading(bool isFading);
		void setIsStepImage(bool isStepImage);
		void setIsDistanceImage(bool isDistanceImage);
		void setOverlap(int val);
		void setStepDistance(int val);
		void setMinDistance(int val);
		//display menus
		void showMainMenu();
		void showOptionMenu();
		std::string BrowseFolder(std::string saved_path);
		static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};