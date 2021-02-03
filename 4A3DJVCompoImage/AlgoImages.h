#pragma once
#include "src/Image.h"
#include <opencv2/opencv.hpp>
#include <deque> 

using namespace cv;

namespace AlgoImg
{
	class AlgoImages
	{
	private:
		std::vector<Image> images;
	public:
		static std::vector<Image> getAllImagesInPath(std::string path);
		static void writeImage(Image& image, std::string directory, std::string filename);
		static void getBackground(std::vector<Image> images, Image& res);
		static bool checkSizeImages(std::vector<Image> images);
		static void getImageMask(Image targetImage, Image background, Image& mask, float maxDiff);
		static void binaryMerge(Image* mask, Image* image1, Image* image2);
		static void getVideoFrame(std::string outputPath, std::string filename, int step);
		static bool checkVideoInPath(std::string path, std::string videoName);
		/// <summary>
		/// Return eights white neigbhors of a white pixel. 
		/// </summary>
		static std::vector<std::pair<int, int>> getConnexeNeighborsPixel(Image& image, int x, int y);
		static int getConnexeComposanteSize(Image& image, int x, int y);		
		static Image removeConnexeComposante(Image& image, int x, int y);
		static void cleanNoiseOnBinaryMask(Image& image, int threshold);		

	};
}
