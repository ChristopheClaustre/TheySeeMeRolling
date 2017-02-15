#include <iostream>
#include <opencv2/opencv.hpp>


#include "Audio/openal.h"
#include "Audio/wave.h"
#include "Audio/source.h"

#include "Video/ComputeObjects.h"

using namespace cv;
using namespace std;
using namespace Video;

int main()
{
    cout << "Hello world!" << endl;

    //Chargement de la video et precalcul
    VideoCapture PreCap("../misc/TheySeeMe2.avi");
    if(!PreCap.isOpened())  // check if we succeeded
        return -1;

    ComputeObjects co(PreCap);
    co.startCompute();

    int nombreObject = co.m_listeObjects.size();


    //Reouverture du fichier video pour recuperation des carateristiques
    VideoCapture cap("../misc/TheySeeMe2.avi");

    //Initialisation audio
    ALfloat listenerPos[] = {cap.get(CV_CAP_PROP_FRAME_HEIGHT)/2, cap.get(CV_CAP_PROP_FRAME_WIDTH)/2, 0.0};
    Audio::OpenAL::getInstance()->initialize(listenerPos);

    //Loading of the WAVE file
    Audio::Wave wave("TheySeeMeRolling-Short.wav");
    wave.load();
    wave.createBuffer();

    Audio::Source source(wave.getIdBuffer());

    //Lets go video-audio !
    Mat frame;
    int frameCount =0;
    namedWindow("Film");
    for(;;)
    {
        cap >> frame; // get a new frame from camera


        for(int i =0 ; i < nombreObject ;i++)
        {
            int frameFromBeginObject = frameCount - co.m_listeObjects[i].m_firstFrame;
            int frameFromEndObject = frameCount - co.m_listeObjects[i].m_lastFrame;
            if(frameFromBeginObject == 0)
            {
                //Apparition de l'objet

                source.play();
                ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z};
                ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                source.setPosition(positionObjet);
                source.setVelocity(velociteObjet);
            }
            else if(frameFromEndObject == 0)
            {
                //Disparition de l'objet
                ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z};
                ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                source.setPosition(positionObjet);
                source.setVelocity(velociteObjet);
                source.stop();
            }
            else if(frameFromBeginObject > 0 && frameFromEndObject < 0)
            {
                ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z};
                ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                           (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                source.setPosition(positionObjet);
                source.setVelocity(velociteObjet);
            }
            frameCount++;
        }
        imshow("Film", frame);
        if(waitKey(30) >= 0) break;
    }

    return 0;
}
