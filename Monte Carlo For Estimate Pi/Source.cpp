#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define W 800
#define H 800

int main(void) {

	Mat image = Mat::zeros({ W,W }, CV_8UC3);

	float Radius = W;
	int dotIn = 0;
	int dotOut = 0;

	int counter = 0;
	while (true)
	{
		int x = rand()%W + 1;
		int y = rand()%H + 1;

		float norm = cv::norm(Point(x, y) - Point(W/2, W/2));
		norm = roundf(norm);

		if (norm > W/2) {

			circle(image, { x,y }, 3, { 100,100,255 }, -1);
			dotOut += 1;
		}
		else {

			circle(image, {x,y}, 3, { 255,100, }, -1);
			dotIn += 1;
		}

		if (dotIn + dotOut > 0) {
			cout << "Pi: " << (float)dotIn*4 / (dotIn + dotOut) << endl;
		}
		imshow("Monte Carlo ", image);
		char key = waitKey(10);

		if (key == 'q') {
			break;
		}

		counter++;
		if (counter == 1000000) break;
	}



	system("pause");

	return 0;
}