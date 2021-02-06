#pragma once
#include <iostream>

enum FadingState {
	Opaque, TransparentToOpaque, OpaqueToTransparent
};

class Settings {

	private:
		static Settings* instance;
		std::string imageDirectory;
		std::string outputDirectory;
		std::string outputName = "output.PNG";
		std::string savedDirectory;
		std::string videoDirectory;
		std::string videoName;
		int videoFrameFrequency = 5;
		float maxMaskDiff = 50.0f;
		int connexeTreshold = 50;
		bool isOverlapImage = false;
		bool isDistanceImage = false;
		bool isGrayScale = false;
		bool drawMask = false;
		bool drawFinalMask = false;
		bool enableConnexe = false;
		FadingState fade = Opaque;
		int overlap;
		int minDistance;
		Settings();


	protected:
		~Settings(){}
	public:
		//singleton
		Settings(Settings& other) = delete;
		void operator=(const Settings&) = delete;
		static Settings *getInstance();

		//getters
		std::string getImageDirectory() const;
		std::string getOutputDirectory() const;
		std::string getOutputName() const;
		std::string getVideoDirectory() const;
		std::string getVideoName() const;
		std::string getSavedDirectory() const;
		float getMaxMaskDiff() const;
		FadingState getFade() const;
		bool getIsStepImage() const;
		bool getIsOverlapImage() const;
		bool getIsDistanceImage() const;
		bool getIsGrayScale() const;
		bool getEnableConnexe() const;
		void setEnableConnexe(bool b);
		int getVideoFrameFrequency() const;
		int getOverlap() const;
		int getMinDistance() const;
		int getConnexeTreshold() const;
		int getDrawMask() const;
		int getDrawFinalMask() const;
		//setters
		void setImageDirectory(std::string directory);
		void setOutputDirectory(std::string directory);
		void setOutputName(std::string name);
		void setVideoDirectory(std::string directory);
		void setVideoName(std::string name);
		void setSavedDirectory(std::string directory);
		void setMaxMaskDiff(float val);
		void setVideoFrameFrequency(int frame);
		void setFade(FadingState fade);
		void setIsStepImage(bool isStepImage);
		void setIsOverlapImage(bool isOverlapImage);
		void setIsDistanceImage(bool isDistanceImage);
		void setOverlap(int val);
		void setConnexeThreshold(int treshold);
		void setIsGrayScale(bool isGrayScale);
		void setDrawMask(bool b) ;
		void setDrawFinalMask(bool b);
		void setMinDistance(int val);

};