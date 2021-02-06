#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"


//Empty image to write on for results
Image::Image()
{
	data = NULL;
	size = 0;
	width = 0;
	height = 0;
	channels = 0;
}

//Image::Image(const int width, const int height, const int channels)
//{
//	uint8_t* data = NULL;
//	size_t size = 0;
//	this->width = width;
//	this->height = height;
//	this->channels = channels;
//}

uint8_t* Image::getData() const { return data; }
Image::Image(const char* filename) {
	if (read(filename)) {
		printf("Read %s\n", filename);
		size = width * height * STBI_rgb_alpha;
	}
	else {
		printf("Failed to read %s\n", filename);
		stbi_image_free(data);
	}
}


Image::Image(const int w, const int h, const int channels) : width(w), height(h), channels(channels) {
	size = w * h * channels;
	data = new uint8_t[size];
}


Image::Image(const Image& img) : Image(img.width, img.height, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename) {
	data = stbi_load(filename, &width, &height, &channels, 0);
	//std::cout << filename << " nb channel:" << channels << std::endl;
	return data != NULL;
}

bool Image::write(const char* directory, const char* filename) {
	Extension ext = getExtension(filename);
	const int nb = strlen(directory) + strlen(filename);
	char res[200];
	strcpy_s(res, directory);
	strcat_s(res, filename);

	int ok;
	switch (ext) {
	case PNG:
		ok = stbi_write_png(res, width, height, channels, data, width * channels);
		break;
	case BMP:
		ok = stbi_write_bmp(res, width, height, channels, data);
		break;
	case JPG:
		ok = stbi_write_jpg(res, width, height, channels, data, 100);
		break;
	case TGA:
		ok = stbi_write_tga(res, width, height, channels, data);
		break;
	}
	return ok != 0;
}

int Image::getWidth() const
{
	return this->width;
}

int Image::getHeight() const
{
	return this->height;
}

int Image::getChannels() const
{
	return this->channels;
}

Extension Image::getExtension(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if (strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if (strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if (strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}

uint8_t* Image::getPixel(int x, int y) const
{
	return &data[(y * width + x) * channels];
}

void Image::setPixel(int x, int y, uint8_t* val)
{
	memcpy(data + (y * width + x) * channels, val, channels);
}




Image& Image::grayscale()
{
	if (channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				uint8_t* pix = getPixel(x, y);
				uint8_t gray = (pix[0] + pix[1] + pix[2]) / 3;
				pix[0] = pix[1] = pix[2] = gray;
				setPixel(x, y, pix);
			}
		}
	}
	return *this;
}

Image& Image::operator=(Image& const image)
{
	width = image.getWidth();
	height = image.getHeight();
	channels = image.getChannels();
	size = width * height * channels;
	memcpy(data, image.data, size);
	return *this;
}