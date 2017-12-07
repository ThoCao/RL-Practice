#pragma once
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"


class Window
{
public:
	Window();
	Window(int W, int H, int U);
	~Window();

public:
	void MoveToNewPos(int & pos);
	void setInitialPos(cv::Point & pos);
	void Drawing();
	void setEcho(int num);
private:
	void RandomMove(int pos, cv::Point & newPos);

private:
	int mWidth;
	int mHeight;
	int mUnit;

	int oldPx = 0;
	int oldPy = 0;

	cv::Point mOldPos;
	cv::Mat mImage;
	cv::Mat mMontoMoveImage;
	int mNumEcho = 0;
	int mEpoche = 0;
	std::vector<int> mColor;

	int mLose = 0;
	int mWin = 0;
};

