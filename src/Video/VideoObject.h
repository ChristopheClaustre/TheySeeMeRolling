#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Video
{
    class VideoObject
    {
    public:
        VideoObject();
        VideoObject(int firstFrame);
        ~VideoObject();
    public:

        vector<Point3_<int>> m_listeCoordonnees;
        vector<Point3_<int>> m_listeVecteurVitesse;
        int m_firstFrame;
        int m_lastFrame;

    }; // class VideoObject

} // namespace Video

#endif // VIDEOOBJECT_H

