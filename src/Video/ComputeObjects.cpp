#include "ComputeObjects.h"

namespace Video
{

ComputeObjects:ComputeObjects(VideoCapture cap):m_cap(cap)
{
}

ComputeObjects::~ComputeObjects()
{
}

void ComputeObjects::startCompute()
{
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame,greyFrame,fgimg,background,diffimg,tresh;
    BackgroundSubtractorMOG2 bg(300,36);
    vector <vector<Point>> contours;

    vector<Point> ptsDetected;
    int radius = 50;
    int frameCount = 0;
    int objectCount = 0;
//  int radiusCarre = radius*radius;
//    vector<int> labels;
//    Mat1b gray;

    for(;;)
    {
        cap >> frame; // get a new frame from camera
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

//        Size originaleSize = diffimg.size();
//        Size size(100,100);//the dst image size,e.g.100x100
//        resize(diffimg,diffimg,size);//resize image

        int count = countNonZero(diffimg);

        if(count > 0)
        {
            findNonZero(diffimg,ptsDetected);

            if(objectCount == 0)
            {
                VideoObject vo(frameCount);
                m_listeObjects.push_back(vo);
            }
            objectCount = 1;
            Rect box = boundingRect(ptsDetected);
            Point3D newPoint;
            newPoint.x = box.tl.x + box.width()/2;
            newPoint.y = box.tl.y + box.height()/2;
            newPoint.z = box.area();
            m_listeObjects[0].m_listeCoordonnees.push_back(newPoint);

//            //Cette partie de programme est utile pour le multi objects (NON IMPLEMENTE)
//            int n_labels = partition(ptsDetected,labels,[radiusCarre](const Point& lhs, const Point& rhs){
//                return ((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y)) < radiusCarre;
//            });

//            vector<vector<Point>> contours(n_labels);
//            for(int i=0; i<ptsDetected.size(); ++i)
//            {
//                contours[labels[i]].push_back(ptsDetected[i]);
//            }

//            for(int i=0; i<contours.size(); ++i)
//            {
//                Rect box = boundingRect(contours[i]);
//                rectangle(frame,box,Scalar(0,0,255));
//            }
        }
        frameCount++;
        if(waitKey(30) >= 0) break;
    }

//    for(VideoObject vo : m_listeObjects)
//    {
//        Point3D vitesse;
//        vitesse.x = 0;
//        vitesse.y = 0;
//        vitesse.z = 0;
//        vo.m_listeVecteurVitesse[0] = vitesse;
//        for(int i=1; i < vo.m_listeVecteurVitesse.size();i++)
//        {
//            vo.m_listeVecteurVitesse[i].push_back(vo.
//        }
//    }
}


} // namespace Video

