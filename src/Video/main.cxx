#include <iostream>
#include <opencv2/opencv.hpp>

#include "ComputeObjects.h"

using namespace cv;
using namespace std;
using namespace Video;


int main()
{
    cout << "Video world!" << endl;
    VideoCapture cap("../misc/TheySeeMe2.avi");
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    ComputeObjects co(cap);
    co.startCompute();

    int size = co.m_listeObjects[0].m_listeCoordonnees.size();
    cout << size << endl;
//    for(int i =0;i<size;++i)
//    {
//        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].x<< " " ;
//        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].y<< " " ;
//        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].z<< endl;
//    }


//    namedWindow("Film");
//    namedWindow("Background");
//    for(;;)
//    {
//        cap >> frame; // get a new frame from camera

//        imshow("Film", frame);
//        imshow("Background", diffimg);
//        if(waitKey(30) >= 0) break;
//    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
