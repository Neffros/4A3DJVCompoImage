#pragma once
#include "src/Image.h"
#include <opencv2/opencv.hpp>
using namespace cv;

namespace AlgoImg
{
	class AlgoImages
	{
	private:
		std::vector<Image> images;
	public:
		static std::vector<Image> getAllImagesInPath(std::string path);
		static void writeImage(Image& image, std::string filename);
		static void getBackground(std::vector<Image> images, Image& res);
		static bool checkSizeImages(std::vector<Image> images);
		static void getImageMask(Image targetImage, Image background, Image& mask, float maxDiff);
		static void chooseImages();
		static void binaryMerge(Image* mask, Image* image1, Image* image2);
		static void getVideoFrame(std::string outputPath, std::string filename, int step);
		static bool checkVideoInPath(std::string path, std::string videoName);
	};
}
