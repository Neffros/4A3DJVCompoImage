#pragma once
#include "src/Image.h"
#include <opencv2/opencv.hpp>
#include <deque> 
#include "Settings.h"

using namespace cv;


class AlgoImages
{
private:
	//std::vector<Image> images;
	Settings* settings = Settings::getInstance();
	static bool validateImages(Settings* settings, std::vector<Image>& images);
public:
	static std::vector<Image> getAllImagesInPath(std::string path);
	static void writeImage(Image& image, std::string directory, std::string filename);
	static void getBackground(std::vector<Image> images, Image& res);
	static bool checkSizeImages(std::vector<Image> images);
	static void getImageMask(Image targetImage, Image background, Image& mask, float maxDiff);
	static void binaryMerge(Image* mask, Image* image1, Image* image2, float alpha);
	static void getVideoFrame(std::string outputPath, std::string filename, int step);
	static bool checkVideoInPath(std::string path, std::string videoName);
	static std::vector<Image> selectUsedImages(std::vector<Image>& images, Settings* settings);
	static std::vector<Image> selectionFromOverlap(std::vector<Image>& images, Settings* settings);
	static std::vector<Image> selectionFromStep(std::vector<Image>& images, Settings* settings);
	static std::vector<Image> selectionFromDistance(std::vector<Image>& images, Settings* settings);
	static void StartImageProcess();

	std::vector<Image> getImages() const;
	void setImages(std::vector<Image> images);
	/// <summary>
	/// Return eights white neigbhors of a white pixel. 
	/// </summary>
	static std::vector<std::pair<int, int>> getConnexeNeighborsPixel(Image& image, int x, int y);
	static int getConnexeComposanteSize(Image& image, int x, int y);		
	static Image removeConnexeComposante(Image& image, int x, int y);
	static void cleanNoiseOnBinaryMask(Image& image, int threshold);		

};
