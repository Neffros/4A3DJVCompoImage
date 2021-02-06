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
		std::string videoDirectory;
		std::string videoName;
		int videoFrameFrequency = 5;
		float maxMaskDiff = 50.0f;
		//bool isStepImage;
		bool isOverlapImage = false;
		bool isDistanceImage = false;

		FadingState fade = Opaque;
		int overlap;
		//int stepDistance;
		int minDistance;
		

	protected:
		Settings();
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
		float getMaxMaskDiff() const;
		int getVideoFrameFrequency() const;
		FadingState getFade() const;
		bool getIsStepImage() const;
		bool getIsOverlapImage() const;
		bool getIsDistanceImage() const;
		int getOverlap() const;
		//int getStepDistance() const;
		int getMinDistance() const;
		//setters
		void setImageDirectory(std::string directory);
		void setOutputDirectory(std::string directory);
		void setOutputName(std::string name);
		void setVideoDirectory(std::string directory);
		void setVideoName(std::string name);
		void setMaxMaskDiff(float val);
		void setVideoFrameFrequency(int frame);
		void setFade(FadingState fade);
		void setIsStepImage(bool isStepImage);
		void setIsOverlapImage(bool isOverlapImage);
		void setIsDistanceImage(bool isDistanceImage);
		void setOverlap(int val);
		//void setStepDistance(int val);
		void setMinDistance(int val);

};