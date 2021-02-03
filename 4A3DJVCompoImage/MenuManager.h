#pragma once
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "AlgoImages.h"
#include "src/Image.h"

enum FadingState {
	Opaque, TransparentToOpaque, OpaqueToTransparent
};

class MenuManager
{
	private:
		std::string imageDirectory;
		std::string outputDirectory;
		std::string outputName = "output.PNG";
		std::string videoDirectory;
		std::string videoName;
		bool isVideo;
		bool isStepImage;
		bool isOverlapImage;
		bool isDistanceImage;
		
		FadingState fade = Opaque;
		int overlap;
		int stepDistance;
		int minDistance;
		//display menus
		void showOptionMenu();
		void showImageMenu();
		void showVideoMenu();
		void showFadingSettings();
		void showOverlapSettings();
		void showDistanceSettings();
		void showStepSettings();

		std::string BrowseFolder(std::string saved_path);
		static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
		void startImageProcess();
	public:
		//single instance of menuManager
		static MenuManager& getInstance();
		//getters
		std::string getImageDirectory() const;
		std::string getOutputDirectory() const;
		std::string getOutputName() const;
		FadingState getFade() const;
		bool getIsStepImage() const;
		bool getIsDistanceImage() const;
		int getOverlap() const;
		int getStepDistance() const;
		int getMinDistance() const;
		//setters
		void setImageDirectory(std::string directory);
		void setOutputDirectory(std::string directory);
		void setOutputName(std::string name);
		void setFade(FadingState fade);
		void setIsStepImage(bool isStepImage);
		void setIsDistanceImage(bool isDistanceImage);
		void setOverlap(int val);
		void setStepDistance(int val);
		void setMinDistance(int val);
	
		void showMainMenu();


	
};