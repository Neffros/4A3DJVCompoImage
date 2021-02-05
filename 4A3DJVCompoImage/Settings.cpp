#include "Settings.h"

Settings* Settings::instance = 0;

Settings *Settings::getInstance()
{
	if (instance == nullptr)
		instance = new Settings();
	return instance;
}

Settings::Settings()
{}

std::string Settings::getImageDirectory() const
{
	return this->imageDirectory;
}

std::string Settings::getOutputDirectory() const
{
	return this->outputDirectory;
}

std::string Settings::getOutputName() const
{
	return outputName;
}

std::string Settings::getVideoDirectory() const
{
	return this->videoDirectory;
}

std::string Settings::getVideoName() const
{
	return this->videoName;
}

int Settings::getVideoFrameFrequency() const
{
	return this->videoFrameFrequency;
}
FadingState Settings::getFade() const
{
	return this->fade;
}

bool Settings::getIsStepImage() const
{
	return this->isStepImage;
}

bool Settings::getIsOverlapImage() const
{
	return this->isOverlapImage;
}

bool Settings::getIsDistanceImage() const
{
	return this->isDistanceImage;
}

float Settings::getMaxMaskDiff() const
{
	return this->maxMaskDiff;
}

int Settings::getOverlap() const
{
	return this->overlap;
}

int Settings::getStepDistance() const
{
	return this->stepDistance;
}

int Settings::getMinDistance() const
{
	return minDistance;
}

void Settings::setImageDirectory(std::string directory)
{
	this->imageDirectory = directory;
}

void Settings::setOutputDirectory(std::string directory)
{
	this->outputDirectory = directory;
}

void Settings::setOutputName(std::string name)
{
	this->outputName = name;
}
void Settings::setMaxMaskDiff(float val)
{
	this->maxMaskDiff = val;
}
void Settings::setVideoDirectory(std::string directory)
{
	this->videoDirectory = directory;
}

void Settings::setVideoName(std::string name)
{
	this->videoName = name;
}

void Settings::setVideoFrameFrequency(int frame)
{
	this->videoFrameFrequency = frame;
}

void Settings::setFade(FadingState fadingState)
{
	this->fade = fadingState;
}

void Settings::setIsStepImage(bool isStepImage)
{
	this->isStepImage = isStepImage;
}

void Settings::setIsOverlapImage(bool isOverlapImage)
{
	this->isOverlapImage = isOverlapImage;
}

void Settings::setIsDistanceImage(bool isDistanceImage)
{

	this->isDistanceImage = isDistanceImage;
}

void Settings::setOverlap(int val)
{
	this->overlap = val;

}

void Settings::setStepDistance(int val)
{
	this->stepDistance = val;

}

void Settings::setMinDistance(int val)
{
	this->minDistance = val;
}