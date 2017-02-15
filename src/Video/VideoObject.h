#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Video
{
    struct Point3D{
        int x;
        int y;
        int z;
    };

    class VideoObject
    {
    public:
        VideoObject(int firstFrame);
        ~VideoObject();
    public:

        vector<Point3D> m_listeCoordonnees;
        vector<Point3D> m_listeVecteurVitesse;
        int m_firstFrame;

    }; // class VideoObject

} // namespace Video

#endif // VIDEOOBJECT_H

