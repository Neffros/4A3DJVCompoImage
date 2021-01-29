#pragma once
#include <iostream>

enum Extension {
	PNG, JPG, BMP, TGA
};
class Image {
	private:
		uint8_t* data = NULL;
		size_t size = 0;
		int width;
		int height;
		int channels;
		std::string directory;
		std::string name;
	public:
		Image(const char* filename);
		Image(int w, int h, int channels);
		Image(const Image& img);
		~Image();

		bool read(const char* filename);
		bool write(const char* filename);

		Extension getExtension(const char* filename);



};