#include <iostream>
#include <opencv2/opencv.hpp>

#include "ComputeObjects.h"

using namespace cv;
using namespace std;
using namespace Video;


int main()
{
    cout << "Video world!" << endl;
    VideoCapture PreCap("../misc/TheySeeMe2.avi");
    if(!PreCap.isOpened())  // check if we succeeded
        return -1;

    ComputeObjects co(PreCap);
    co.startCompute();

    int size = co.m_listeObjects[0].m_listeCoordonnees.size();
    cout << size << endl;
    for(int i =0;i<size;++i)
    {
        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].x<< " " ;
        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].y<< " " ;
        std::cout << co.m_listeObjects[0].m_listeCoordonnees[i].z<< endl;
        std::cout << "Vitesse : ";
        std::cout << co.m_listeObjects[0].m_listeVecteurVitesse[i].x<< " " ;
        std::cout << co.m_listeObjects[0].m_listeVecteurVitesse[i].y<< " " ;
        std::cout << co.m_listeObjects[0].m_listeVecteurVitesse[i].z<< endl;
    }


    VideoCapture cap("../misc/TheySeeMe2.avi");
    Mat frame;
    namedWindow("Film");
    for(;;)
    {
        cap >> frame; // get a new frame from camera

        imshow("Film", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
