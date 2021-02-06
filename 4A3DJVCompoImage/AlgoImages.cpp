#include <cmath>
#include "AlgoImages.h"
#include <filesystem>
#include <cmath>
namespace fs = std::filesystem;
using namespace cv;



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
/*
std::vector<Image> AlgoImages::selectUsedImages(std::vector<Image>& images, Settings* settings)
{
	if (settings->getIsOverlapImage())
		selectionFromOverlap(images, settings);
	else if (settings->getIsStepImage())
		selectionFromStep(images, settings);
	else if (settings->getIsDistanceImage())
		selectionFromDistance(images, settings);

	return std::vector<Image>();
}*/

bool AlgoImages::selectionFromOverlap(Image& maskFinal, Image& targetMask, int maxOverlapPercent)
{
	int overlap = 0;
	int nbPixTarget = 0;
	for (int x = 0; x < maskFinal.getWidth(); x++)
	{
		for (int y = 0; y < maskFinal.getHeight(); y++)
		{
			uint8_t* pix1 = maskFinal.getPixel(x, y);
			uint8_t* pix2 = targetMask.getPixel(x, y);
			if (pix2[0] == 255)
			{
				nbPixTarget++;
				if (pix1[0] == 255)
				{
					overlap++;
				}
			}
		}
	}

	return ((overlap * 100) / nbPixTarget <= maxOverlapPercent);
}

/*std::vector<Image> AlgoImages::selectionFromStep(std::vector<Image>& images, Settings* settings)
{
	return std::vector<Image>();
}*/
bool selectionFromDistance(Image& maskFinal, Image& targetMask, int minDistance)
{

	return false;
}
bool AlgoImages::validateImages(Settings* settings, std::vector<Image>& images)
{

	if (checkVideoInPath(settings->getVideoDirectory(), settings->getVideoName()))
	{
		getVideoFrame(settings->getOutputDirectory(), settings->getVideoDirectory() + "\\" + settings->getVideoName(),
			settings->getVideoFrameFrequency());
		images = getAllImagesInPath(settings->getOutputDirectory());
		return true;

	}
	if (settings->getVideoDirectory() != "" || settings->getVideoName() != "") {
		std::cout << "could not read video" << std::endl;
		settings->setVideoDirectory("");
		settings->setVideoName("");
		return false;
	}
	if (settings->getImageDirectory() == "" || settings->getOutputDirectory() == "")
	{
		std::cout << "please inform image directory and output directory first" << std::endl;
		return false;
	}
	images = getAllImagesInPath(settings->getImageDirectory());
	if (images.empty())
	{
		std::cout << "no images found in directory";
		return false;
	}

	if (!checkSizeImages(images))
	{
		std::cout << "images are not the same size" << std::endl;
		return false;
	}
	return true;
}



void AlgoImages::StartImageProcess()
{


	std::vector<Image> images;
	Settings* settings = Settings::getInstance();
	//settings->setOutputDirectory("E:\\dev\\4A3DJVCompoImage\\output\\");
	//settings->setImageDirectory("E:\\dev\\4A3DJVCompoImage\\4A3DJVCompoImage\\sampleImages\\SCHOODING_IMG");
	bool isValid = validateImages(settings, images);
	if (!isValid)
		return;

	//Image background("E:\\dev\\4A3DJVCompoImage\\background.png");
	Image background(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
	getBackground(images, background);
	Image image_final(background);
	std::cout << "nb channels: " << image_final.getChannels();
	writeImage(background, settings->getOutputDirectory(), "background.png");
	float alpha = 1;
	float alphaIncrement = 0;
	if (settings->getFade() == Opaque)
		alphaIncrement = 0;
	else if (settings->getFade() == TransparentToOpaque)
	{
		alpha = 0.15f;
		alphaIncrement = 1.0f / float(images.size());//std::round(images.size() * (100 / 255)/100);
	}
	else if (settings->getFade() == OpaqueToTransparent)
	{
		alpha = 1.0f;
		alphaIncrement = -1.0f / float(images.size()); //-std::round(images.size() * 1000 / 255);
	}

	Image maskFinal(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
	getImageMask(background, background, maskFinal, settings->getMaxMaskDiff());
	std::pair<int, int> p1 = getMiddleMask(maskFinal);

	for (int i = 0; i < images.size(); i++)
	{
		Image mask(images[0].getWidth(), images[0].getHeight(), images[0].getChannels());
		getImageMask(images[i], background, mask, settings->getMaxMaskDiff());
		//writeImage(mask, settings->getOutputDirectory(), "mask" + std::to_string(i) + ".png");
		//cleanNoiseOnBinaryMask(mask, settings->getConnexeTreshold());
		writeImage(mask, settings->getOutputDirectory(), "maskClean" + std::to_string(i) + ".png");
		if (settings->getIsOverlapImage() && !selectionFromOverlap(maskFinal, mask, settings->getOverlap()))
		{
			std::cout << "this cannot continue" << std::endl;
			continue;
		}
		std::pair<int, int> p2 = getMiddleMask(mask);
		if (getDistanceBetweenPoint(p1, p2) < 250) continue;
		binaryMerge(&mask, &image_final, &images[i], alpha);//(255 - i*3) % 255);
		alpha += alphaIncrement;
		if (alpha + alphaIncrement > 1)
			alpha = 1;
		else if (alpha + alphaIncrement < 0.15f)
			alpha = 0.15f;
		getImageMask(image_final, background, maskFinal, settings->getMaxMaskDiff());
		p1 = p2;
		//writeImage(maskFinal, settings->getOutputDirectory(), "maskfinal" + std::to_string(i) + ".png");
		//Image cleaned_mask(mask);
		//cleanNoiseOnBinaryMask(cleaned_mask, 200);
		//writeImage(cleaned_mask, settings->getOutputDirectory(), "cleaned_mask" + std::to_string(i) + ".png");
		//std::cout << "alpha is: " << alpha << std::endl;

	}
	writeImage(image_final, settings->getOutputDirectory(), settings->getOutputName());
}


std::vector<std::pair<int, int>> AlgoImages::getConnexeNeighborsPixel(Image& image, int x, int y)
{




	// surroudings-connexity neighbors x and y coordinates
	std::vector<std::pair<int, int>> surroundings = { std::make_pair(-1,1),std::make_pair(0,1),std::make_pair(1,1),std::make_pair(-1,0),std::make_pair(1,0),std::make_pair(-1,-1),std::make_pair(0,-1),std::make_pair(1,-1) };
	std::vector<std::pair<int, int>> neighbors;
	int size = surroundings.size();

	for (int i = 0; i < size; i++)
	{
		int x_offset = x + surroundings.at(i).first;
		int y_offset = y + surroundings.at(i).second;
		if (x_offset >= 0 && y_offset >= 0)
		{
			if (x_offset < image.getWidth() && y_offset < image.getHeight())
			{
				uint8_t* p = image.getPixel(x_offset, y_offset);
				if (p[0] == 255)
				{
					//image.setPixel(x_offset, y_offset, pixBlack);
					neighbors.push_back(std::make_pair(x_offset, y_offset));
				}
			}
		}
	}
	return neighbors;
}

int AlgoImages::getConnexeComposanteSize(Image& image, int x, int y)
{
	std::deque<std::pair<int, int>> q;
	q.push_back(std::make_pair(x, y));
	Image copy(image);
	//std::cout << "NB CHANNELS" << image.getChannels() << std::endl;
	uint8_t pixBlack[3] = { 0 , 0 ,0 };
	copy.setPixel(x, y, pixBlack);

	int totalSize = 1;
	while (!q.empty())
	{
		totalSize++;
		std::pair<int, int> current = q.back();
		q.pop_back(); // remove it because back() does not do it
		std::vector<std::pair<int, int>>  neigbhors = getConnexeNeighborsPixel(copy, current.first, current.second);
		for (int i = 0; i < neigbhors.size(); i++)
		{
			copy.setPixel(neigbhors[i].first, neigbhors[i].second, pixBlack);
			q.push_back(neigbhors[i]);
		}
	}
	//writeImage(copy, "E:\\dev\\4A3DJVCompoImage\\output\\", std::to_string(x + y) + "mask_prout.png");
	return totalSize;
}

void AlgoImages::removeConnexeComposante(Image& mask, int x, int y)
{
	std::deque<std::pair<int, int>> q;
	q.push_back(std::make_pair(x, y));
	Image copy(mask);
	uint8_t pixBlack[3] = { 0 , 0 ,0 };

	copy.setPixel(x, y, pixBlack);
	while (!q.empty())
	{
		std::pair<int, int> current = q.back();
		q.pop_back(); // remove it because back() does not do it
		std::vector<std::pair<int, int>>  neigbhors = getConnexeNeighborsPixel(copy, current.first, current.second);
		for (int i = 0; i < neigbhors.size(); i++)
		{
			copy.setPixel(neigbhors[i].first, neigbhors[i].second, pixBlack);
			q.push_back(neigbhors[i]);
		}

	}
	mask = copy;
}


void AlgoImages::cleanNoiseOnBinaryMask(Image& mask, int threshold)
{
	/*
		Image copy(mask);
	int w = copy.getWidth();
	int h = copy.getHeight();

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (copy.getPixel(x, y)[0] == 255)
			{
				if(get)
			}
		}
	}*/

	Image copy(mask);
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
					removeConnexeComposante(mask, x, y);
				}
			}
		}
	}
}




void AlgoImages::writeImage(Image& image, std::string directory, std::string filename)
{
	std::cout << "write ? " << image.write(directory.c_str(), filename.c_str()) << " at filename: " << filename << std::endl;
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

void AlgoImages::binaryMerge(Image* mask, Image* finalImage, Image* currentImage, float alpha)
{
	for (int y = 0; y < finalImage->getHeight(); y++)
	{
		for (int x = 0; x < finalImage->getWidth(); x++)
		{
			uint8_t* pix1 = finalImage->getPixel(x, y);
			uint8_t* pix2 = currentImage->getPixel(x, y);
			uint8_t* pixM = mask->getPixel(x, y);
			if (pixM[0] != 0)
			{
				//pix2[3] = alpha;
				if (alpha != 1)
				{
					pix2[0] = int((alpha * pix2[0] + pix1[0]) / 2);
					pix2[1] = int((alpha * pix2[1] + pix1[1]) / 2);
					pix2[2] = int((alpha * pix2[2] + pix1[2]) / 2);
				}
				/*std::cout << "red:" << unsigned(pix2[0]) << std::endl;
				std::cout << "green:" << unsigned(pix2[1]) << std::endl;
				std::cout << "blue:" << unsigned(pix2[2]) << std::endl;
				std::cout << "alpha:" << unsigned(pix2[3]) << std::endl;
				std::cout << std::endl;*/

				// trouver la bonne m�thode blend ici
				//pix1[0] = pix2[0];
				//pix1[1] = pix2[1];
				//pix1[2] = pix2[2];
				//pix1[3] = 0.2f;


				finalImage->setPixel(x, y, pix2);

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
			imwrite(outputPath + "\\img" + std::to_string(nbImg) + ".png", frame);
			c = 0;
			nbImg++;
		}
	}
}

float AlgoImages::getDistanceBetweenPoint(std::pair<int, int> p1, std::pair<int, int> p2)
{
	return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.first, 2) * 1.0);
}

std::pair<int, int> AlgoImages::getMiddleMask(Image& mask)
{
	int w = mask.getWidth();
	int h = mask.getHeight();
	int X = 0;
	int Y = 0;
	int denominator = 0;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (mask.getPixel(x, y)[0] == 255)
			{
				X += x;
				Y += y;
				denominator++;
			}
		}
	}
	if (denominator == 0)
	{
		denominator = 1;
		X /= denominator;
		Y /= denominator;
	}
	else {
		X /= denominator;
		Y /= denominator;
	}
	return std::make_pair(X, Y);
}