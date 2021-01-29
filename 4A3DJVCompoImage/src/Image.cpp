#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"



Image::Image(const char* filename) {
	if (read(filename)) {
		printf("Read %s\n", filename);
		size = width * height * channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : width(w), height(h), channels(channels) {
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
