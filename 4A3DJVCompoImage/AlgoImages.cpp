#include <cmath>
#include "AlgoImages.h"
#include <filesystem>
#include <cmath>
namespace fs = std::filesystem;
using namespace cv;

namespace AlgoImg
{
	std::vector<Image> AlgoImages::getAllImagesInPath(std::string path)
	{
		std::vector<Image> images;
		int i = 0;

		for (const auto& entry : fs::directory_iterator(path))
		{
			std::string ext = entry.path().extension().string();

			if (ext != ".png" && ext != ".jpeg" && ext != ".BMP" && ext != ".TGA" && ext != ".jpg")
			{
				std::cout << entry.path().string().c_str() << " is not a compatible image" << std::endl;;
				continue;
			}
			Image im(entry.path().string().c_str());
			images.push_back(im);
			i++;
		}
		return images;
	}

	bool AlgoImages::checkVideoInPath(std::string path, std::string videoName) {
		if (path == "" || videoName == "") return false;
		int i = 0;
		for (const auto& entry : fs::directory_iterator(path))
		{
			std::cout << path + "\\" + videoName << std::endl;
			if (path + "\\" + videoName == entry.path().string().c_str()) {
				return true;
			}

			i++;
		}

		return false;
	}

	std::vector<std::pair<int, int>> AlgoImages::getConnexeNeighborsPixel(Image& image, int x, int y)
	{
		// eight-connexity neighbors x and y coordinates
		int eight[16] = { -1,1,0,1,1,1,-1,0,1,0,-1,-1,0,-1,1,-1 };
		std::vector<std::pair<int, int>> neigbhors;
		for (int i = 0; i < 16; i++)
		{
			int x_offset = x + eight[i];
			int y_offset = y + eight[i + 1];
			if (x_offset >= 0 && y_offset >= 0)
			{
				if (x_offset < image.getWidth() && y_offset < image.getHeight())
				{
					uint8_t* p = image.getPixel(x_offset, y_offset);
					if (p[0] == 255)
					{
						neigbhors.push_back(std::make_pair(x_offset, y_offset));
					}
				}
			}
		}
		return neigbhors;
	}

	int AlgoImages::getConnexeComposanteSize(Image& image, int x, int y)
	{
		std::deque<std::pair<int, int>> q;
		q.push_back(std::make_pair(x, y));
		Image copy(image);
		uint8_t pixBlack[3] = { 0 , 0 ,0 };
		copy.setPixel(x, y, pixBlack);
		std::vector<std::pair<int, int>> res;
		while (!q.empty())
		{
			std::pair<int, int> current = q.back();
			res.push_back(current);
			q.pop_back(); // remove it because back() does not do it
			std::vector<std::pair<int, int>>  neigbhors = getConnexeNeighborsPixel(copy, current.first, current.second);
			for (int i = 0; i < neigbhors.size(); i++)
			{
				copy.setPixel(neigbhors[i].first, neigbhors[i].second, pixBlack);
				q.push_front(neigbhors[i]);
			}

		}
		return res.size();
	}

	Image AlgoImages::removeConnexeComposante(Image& image, int x, int y)
	{
		std::deque<std::pair<int, int>> q;
		q.push_back(std::make_pair(x, y));
		Image copy(image);
		uint8_t pixBlack[3] = { 0 , 0 ,0 };

		copy.setPixel(x, y, pixBlack);
		std::vector<std::pair<int, int>> res;
		while (!q.empty())
		{
			std::pair<int, int> current = q.back();
			res.push_back(current);
			q.pop_back(); // remove it because back() does not do it
			std::vector<std::pair<int, int>>  neigbhors = getConnexeNeighborsPixel(copy, current.first, current.second);
			for (int i = 0; i < neigbhors.size(); i++)
			{
				copy.setPixel(neigbhors[i].first, neigbhors[i].second, pixBlack);
				q.push_front(neigbhors[i]);
			}

		}
		return copy;


	}

	void AlgoImages::cleanNoiseOnBinaryMask(Image& image, int threshold)
	{
		Image copy(image);
		int w = copy.getWidth();
		int h = copy.getHeight();
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				if (copy.getPixel(x, y)[0] == 255)
				{
					if (getConnexeComposanteSize(copy, x, y) < threshold)
					{
						image = removeConnexeComposante(image, x, y);
					}
				}
			}
		}
	}

	void AlgoImages::setAlphaImage(Image& image, int alpha)
	{
		if (image.getChannels() != 4) throw("no alpha channel detected");
		for (int x = 0; x < image.getWidth(); x++)
		{
			for (int y = 0; y < image.getHeight(); y++)
			{
				uint8_t* pix1 = image.getPixel(x, y);
				pix1[3] = alpha;
				image.setPixel(x, y, pix1);
			}
		}
	}


	void AlgoImages::writeImage(Image& image, std::string directory, std::string filename)
	{
		std::cout << "write ? " << image.write(directory.c_str(), filename.c_str());
	}


	void AlgoImages::getImageMask(Image targetImage, Image background, Image& mask, float maxDiff)
	{
		uint8_t pixBlack[3] = { 0 , 0 ,0 };
		uint8_t pixWhite[3] = { 255, 255 ,255 };

		for (int x = 0; x < targetImage.getWidth(); x++)
		{
			for (int y = 0; y < targetImage.getHeight(); y++)
			{
				uint8_t* pixBg = background.getPixel(x, y);
				uint8_t* pixCur = targetImage.getPixel(x, y);

				uint8_t avgBg = (pixBg[0] + pixBg[1] + pixBg[2]) / 3;
				uint8_t avgPix = (pixCur[0] + pixCur[1] + pixCur[2]) / 3;

				if (abs(avgBg - avgPix) > maxDiff)
				{
					mask.setPixel(x, y, pixWhite);
				}
				else
				{
					mask.setPixel(x, y, pixBlack);
				}

			}
		}
	}

	void AlgoImages::binaryMerge(Image* mask, Image* image1, Image* image2)
	{

		for (int x = 0; x < image1->getWidth(); x++)
		{
			for (int y = 0; y < image1->getHeight(); y++)
			{
				uint8_t* pix1 = image1->getPixel(x, y);
				uint8_t* pix2 = image2->getPixel(x, y);
				uint8_t* pixM = mask->getPixel(x, y);
				if (pixM[0] != 0)
				{
					image1->setPixel(x, y, pix2);
				}

			}
		}
	}

	void AlgoImages::getBackground(std::vector<Image> images, Image& res)
	{
		std::vector<uint8_t> pixValsR;
		std::vector<uint8_t> pixValsG;
		std::vector<uint8_t> pixValsB;
		for (int x = 0; x < images[0].getWidth(); x++)
		{
			for (int y = 0; y < images[0].getHeight(); y++)
			{
				pixValsR.clear();
				pixValsG.clear();
				pixValsB.clear();
				for (int imgIndex = 0; imgIndex < images.size(); imgIndex++)
				{
					uint8_t* pix = images[imgIndex].getPixel(x, y);
					pixValsR.push_back(pix[0]);
					pixValsG.push_back(pix[1]);
					pixValsB.push_back(pix[2]);
				}
				std::sort(pixValsR.begin(), pixValsR.end());
				std::sort(pixValsG.begin(), pixValsG.end());
				std::sort(pixValsB.begin(), pixValsB.end());

				uint8_t red = pixValsR[ceil(pixValsR.size() / 2)];
				uint8_t green = pixValsG[ceil(pixValsG.size() / 2)];
				uint8_t blue = pixValsB[ceil(pixValsB.size() / 2)];

				uint8_t pixRes[3] = { red,green,blue };
				res.setPixel(x, y, pixRes);

			}
		}
	}


	//Checks if all the images are same size. call this before any process to see if images are ok to use
	bool AlgoImages::checkSizeImages(std::vector<Image> images)
	{
		int minX = INT_MAX;
		int minY = INT_MAX;
		int maxX = 0;
		int maxY = 0;
		for (int i = 0; i < images.size(); i++)
		{
			int imgWidth = images[i].getWidth();
			int imgHeigth = images[i].getHeight();
			if (imgWidth < minX)
				minX = imgWidth;
			else if (imgWidth > maxX)
				maxX = imgWidth;

			if (imgHeigth < minY)
				minY = imgHeigth;
			else if (imgHeigth > maxY)
				maxY = imgHeigth;
		}
		std::cout << "X: " << minX << " - " << maxX << std::endl;
		std::cout << "Y: " << minY << " - " << maxY << std::endl;
		if (minX == maxX && minY == maxY)
			return true;
		return false;
	}

	void AlgoImages::getVideoFrame(std::string outputPath, std::string videoDirectory, int step) {
		VideoCapture vid(videoDirectory);
		int c = 0;
		int nbImg = 0;
		// Check if camera opened successfully
		if (!vid.isOpened()) {
			std::cout << "Error opening video stream or file" << std::endl;
			return;
		}

		Mat frame;
		while (1) {

			// Capture frame-by-frame
			vid >> frame;

			// If the frame is empty, break immediately
			if (frame.empty())
				break;

			c++;
			if (c % step == 0) {
				imwrite(outputPath + "\\img" + std::to_string(nbImg) + ".jpg", frame);
				c = 0;
				nbImg++;
			}
		}
	}

}
