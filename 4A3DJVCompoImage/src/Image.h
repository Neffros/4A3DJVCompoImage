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
		Image();
		Image(const int width, const int height, const int channels);
		Image(const char* filename);
		Image(const Image& img);
		~Image();

		bool read(const char* filename);
		bool write(const char* directory, const char* filename);

		int getWidth() const;
		int getHeight() const;
		int getChannels() const;
		uint8_t* getData() const;
		Extension getExtension(const char* filename);
		uint8_t* getPixel(int x, int y) const;
		void setPixel(int x, int y, uint8_t* val);
		
		Image& grayscale();

		Image& operator=(Image& const image);

};