#include <iostream>
#include <opencv2/opencv.hpp>

#include "ComputeObjects.h"

using namespace cv;
using namespace std;
using namespace Video;


int main()
{
    cout << "Video world!" << endl;

    Mat frame,fgimg,background,diffimg;
    vector<Point> ptsDetected;
    BackgroundSubtractorMOG2 bg(300,36);
    vector <vector<Point>> contours;
    VideoCapture cap("../misc/Videos/TheySeeMe2.avi");
    namedWindow("Film");
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        if(frame.empty()) break;
        bg.operator ()(frame,fgimg);
        //On recupere le background
        bg.getBackgroundImage(background);

        cvtColor(background,background,COLOR_RGB2GRAY);
        fgimg = frame;
        cvtColor(fgimg,fgimg,COLOR_RGB2GRAY);

        //On blur l'image pour la detection
        GaussianBlur(fgimg,fgimg,Size(15,15),0);
        GaussianBlur(background,background,Size(15,15),0);

        absdiff(background,fgimg,diffimg);
        threshold(diffimg,diffimg,35,255,THRESH_BINARY);

        findContours(diffimg,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        drawContours(diffimg,contours,-1,255,1);

        int count = countNonZero(diffimg);

        if(count > 0)
        {
            findNonZero(diffimg,ptsDetected);
            cvtColor(diffimg,diffimg,COLOR_GRAY2RGB);
            Rect box = boundingRect(ptsDetected);
            rectangle(diffimg,box,Scalar(0,0,255));
        }

        imshow("Film", diffimg);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
