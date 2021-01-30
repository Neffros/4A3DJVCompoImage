#pragma once
#include <iostream>
#include <vector>
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
	public:
		Image(const char* filename);
		Image(int w, int h, int channels);
		Image(const Image& img);
		~Image();

		bool read(const char* filename);
		bool write(const char* filename);

		Extension getExtension(const char* filename);
		int getPixel(int x, int y, int chan) const;
		void setPixel(int x, int y, int chan, uint8_t val);

		Image& grayscale_v1();
		Image& grayscale_v2();


};