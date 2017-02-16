#include "ComputeObjects.h"

namespace Video
{

ComputeObjects::ComputeObjects(VideoCapture cap):m_cap(cap)
{
}

ComputeObjects::~ComputeObjects()
{
}

int ComputeObjects::startCompute()
{
    if(!m_cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame,fgimg,background,diffimg;
    BackgroundSubtractorMOG2 bg(300,36);
    vector <vector<Point>> contours;

    vector<Point> ptsDetected;

    int frameCount = 0;
    int objectCount = 0;
//    int radius = 50;
//    int radiusCarre = radius*radius;
//    vector<int> labels;
//    Mat1b gray;

    cout << "Computing...";
    for(;;)
    {
        m_cap >> frame; // get a new frame from camera
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

            if(objectCount == 0)
            {
                VideoObject vo(frameCount);
                m_listeObjects.push_back(vo);
            }
            objectCount = 1;
            Rect box = boundingRect(ptsDetected);
            Point3_<int> newPoint(box.x + box.width/2,box.y + box.height/2,box.area());
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
        else
        {
            if(objectCount == 1)
            {
                m_listeObjects[0].m_lastFrame = frameCount;
                objectCount = 0;
            }
        }


        frameCount++;
        cout << "." << flush;
    }
    m_cap.release();

    for(vector<VideoObject>::iterator it = m_listeObjects.begin();it < m_listeObjects.end(); ++it)
    {
        Point3_<int> vitesse(0,0,0);
        it->m_listeVecteurVitesse.push_back(vitesse);
        for(int i=1; i < it->m_listeCoordonnees.size();i++)
        {
            it->m_listeVecteurVitesse.push_back(it->m_listeCoordonnees[i]-it->m_listeCoordonnees[i-1]);
        }
    }
    return 0;
}

} // namespace Video

