#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <memory>
#include "Window.h"


using namespace std;
using namespace cv;


#define W 15
#define H 15
#define U 50

int main(void) {


	Window Monto(W, H, U);
	int px = rand() % W*U + 1;
	int py = rand() % H*U + 1;

	Monto.setInitialPos(Point(px,py));


	while (true){

		int mov = rand() % 4 ;
	
		Monto.MoveToNewPos(mov);

		Monto.Drawing();

		char key = cv::waitKey(100);
		if (key == 'q') break;

	}
	return 0;
}