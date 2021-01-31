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

Image::Image(const char* filename) {
	if (read(filename)) {
		printf("Read %s\n", filename);
		size = width * height * channels;
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
	return data != NULL;
}

bool Image::write(const char* filename) {
	Extension ext = getExtension(filename);
	int ok;
	switch (ext) {
	case PNG:
		ok = stbi_write_png(filename, width, height, channels, data, width * channels);
		break;
	case BMP:
		ok = stbi_write_bmp(filename, width, height, channels, data);
		break;
	case JPG:
		ok = stbi_write_jpg(filename, width, height, channels, data, 100);
		break;
	case TGA:
		ok = stbi_write_tga(filename, width, height, channels, data);
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
				pix[0] =pix[1] =pix[2] = gray;
				setPixel(x, y, pix);
			}
		}
	}
	return *this;
}

