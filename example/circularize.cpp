#include "circularize.h"
#include <iostream>

int main(int argc, char *argv[])
{
	using namespace std;
	using namespace numcpp;

	auto image = imread("Lena.bmp");
	if (image.empty())
	{
		cout << "Cannot read image file!" << endl;
		return -1;
	}

	const int DIAMETER = 1024;
	array_t<uint8_t> result_image;

	Circularize circularize;

	// Run CPU version
	cout << "Running CPU version..." << endl;
	circularize(result_image, image, DIAMETER);
	cout << "Finished!" << endl;
	imshow(result_image);

	// Run GPU version
	cout << "Running GPU version..." << endl;
	device_array_t<uint8_t> image_d(image), result_image_d;
	circularize(result_image_d, image_d, DIAMETER);
	
	array_t<uint8_t> result_image_h(DIAMETER, DIAMETER);
	device_to_host(result_image_h, result_image_d);
	cout << "Finished!" << endl;
	imshow(result_image_h); 

	return 0;
}