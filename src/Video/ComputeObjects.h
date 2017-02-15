#ifndef COMPUTEOBJECTS_H
#define COMPUTEOBJECTS_H

#include <opencv2/opencv.hpp>
#include "VideoObject.h"

using namespace cv;
using namespace std;

namespace Video
{

    class ComputeObjects
    {
    public:
        ComputeObjects(VideoCapture cap);
        ~ComputeObjects();

        void startCompute();
    public:

        VideoCapture m_cap;
        vector<VideoObject> m_listeObjects;

    }; // class ComputeObjects

} // namespace Video

#endif // COMPUTEOBJECTS_H


