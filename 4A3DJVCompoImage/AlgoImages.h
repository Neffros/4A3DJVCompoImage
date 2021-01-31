#pragma once
#include "src/Image.h"

namespace AlgoImg
{
	class AlgoImages
	{
	private:
		std::vector<Image> images;
		template <typename T>
		static std::vector<T> sortVec(std::vector<T>& vec);
	public:
		static std::vector<Image> getAllImagesInPath(std::string path);
		static void writeImage(Image& image, std::string filename);
		static void getBackground(std::vector<Image> images, Image& res);
		static bool checkSizeImages(std::vector<Image> images);
		static void getImageMask(Image targetImage, Image background, Image& mask, float maxDiff);
		static void chooseImages();
		static void makeFinalImage(std::vector<Image> masks, Image background, Image& res);
	};
}
