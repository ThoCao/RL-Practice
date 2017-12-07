#include "Window.h"



Window::Window()
{
}

Window::Window(int W, int H,int U){
	this->mHeight = H;
	this->mWidth = W;
	this->mUnit = U;
	this->mImage = cv::Mat::zeros({ mWidth*U,mHeight*U },CV_8UC3);
	/* Draw monte here */
	cv::Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.width = U;
	rect.height = U;
	cv::rectangle(mImage, rect, { 0,0,255}, -1);
	rect.x = mWidth*U - U;
	rect.y = mHeight*U - U;
	cv::rectangle(mImage, rect, { 0,255,0}, -1);
	/* Init color space */
	this->mColor.assign(W*H, 0);
}


Window::~Window()
{

}

void Window::MoveToNewPos(int & pos){
	mImage.copyTo(mMontoMoveImage);

	RandomMove(pos, mOldPos);
	cv::circle(mMontoMoveImage, mOldPos, 15, { 100,100,255 }, -1);

	/* draw */
	
	cv::Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.width = mUnit;
	rect.height = mUnit;
	cv::rectangle(mImage, rect, { 0,0,255}, -1);
	rect.x = mWidth*mUnit - mUnit;
	rect.y = mHeight*mUnit - mUnit;
	cv::rectangle(mImage, rect, { 0,255,0}, -1);
	
}

void Window::setInitialPos(cv::Point & pos){
	this->mOldPos = pos;

	oldPx = pos.x / mUnit;
	oldPy = pos.y / mUnit;
}

void Window::Drawing(){
	
	
	std::string name = "Iterations: " + std::to_string(mNumEcho);
	cv::putText(mMontoMoveImage, name, { 0,130 }, 1, 2, { 0,255,0 }, 1);
	std::string name2 = "Epoche: " + std::to_string(mEpoche);
	cv::putText(mMontoMoveImage, name2, { 0,80 }, 1, 2, { 0,255,0 }, 1);
	std::string name3 = "Lose: " + std::to_string(mLose) + "  Win: " + std::to_string(mWin);
	cv::putText(mMontoMoveImage, name3, { 0,170 }, 1, 2, { 0,255,0 }, 1);

	if(!mMontoMoveImage.empty()) cv::imshow("monto", mMontoMoveImage);
}

void Window::setEcho(int num){
	this->mNumEcho = num;
}

void Window::RandomMove(int pos, cv::Point & newPos){

	this->mNumEcho += 1;
	int nx = 0;
	int ny = 0;

	switch (pos)
	{
	case 0:
		nx = 0 ;
		ny = -1;
		break;
	case 1:
		nx = 1;
		ny = 0;
		break;
	case 2:
		nx = 0;
		ny = 1;
		break;
	case 3:
		nx = -1;
		ny = 0;
		break;
	default:
		break;
	}

	oldPx += nx;
	oldPy += ny;

	if (oldPx < 0) oldPx = 0;
	if (oldPx > mWidth) oldPx =  mWidth -1;

	if (oldPy < 0) oldPy = 0;
	if (oldPy > mHeight) oldPy = mHeight -1;


	int scale = 10;
	if (oldPx == mWidth && oldPy == mHeight) {

		cv::putText(mImage, "YOU WIN!", { mImage.rows / 2,mImage.cols / 2 }, 1, 3, {0,255,0},3);

		this->mNumEcho = 0;
		this->mEpoche += 1;
		
		oldPx = rand() % mWidth + 1;
		oldPy = rand() % mHeight + 1;

		this->mWin +=1;
	}
	else if (oldPx == 0 && oldPy == 0 || mNumEcho > 100 ) {

		cv::putText(mImage, "YOU LOSE!", { mImage.rows / 2,mImage.cols / 2 }, 1, 3, {0,0,255},3);

		this->mNumEcho = 0;
		this->mEpoche += 1;

		oldPx = rand() % mWidth + 1;
		oldPy = rand() % mHeight + 1;

		this->mLose += 1;
	}

	newPos.x = oldPx*mUnit;
	newPos.y = oldPy*mUnit;
	
	/* Update Color */

	int idx = oldPx*oldPy;
	if (idx > mColor.size()) return;

	this->mColor[idx] += 5;
	double color = this->mColor[idx];

	cv::Rect rect;
	rect.x = newPos.x;
	rect.y = newPos.y;
	rect.width = mUnit;
	rect.height = mUnit;
	cv::rectangle(mImage, rect, { 0,0,color}, -1);
}
