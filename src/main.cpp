#include <iostream>
#include <opencv2/opencv.hpp>


#include "Audio/openal.h"
#include "Audio/wave.h"
#include "Audio/source.h"

#include "Video/ComputeObjects.h"

using namespace cv;
using namespace std;
using namespace Video;

int main(int argc, char *argv[])
{
    cout << "Hello world!" << endl;

    //Chargement de la video et precalcul
    char* video = argv[1];
    VideoCapture PreCap(video);
    if(!PreCap.isOpened())  // check if we succeeded
        return -1;

    ComputeObjects co(PreCap);
    co.startCompute();

    int nombreObject = co.m_listeObjects.size();


    //Reouverture du fichier video pour recuperation des carateristiques
    VideoCapture cap(video);

    //Initialisation audio
    ALfloat listenerPos[] = {(ALfloat)(cap.get(CV_CAP_PROP_FRAME_WIDTH)/2.0),(ALfloat)(cap.get(CV_CAP_PROP_FRAME_HEIGHT)/2.0), 0.0};
    cout << "listenerPos : " << (ALfloat)(cap.get(CV_CAP_PROP_FRAME_WIDTH)/2.0) << " " <<(ALfloat)(cap.get(CV_CAP_PROP_FRAME_HEIGHT)/2.0) << " " << 0.0 << endl;

    Audio::OpenAL::getInstance()->initialize(listenerPos);

    //Loading of the WAVE file
    Audio::Wave wave("TheySeeMeRolling-Short-mono.wav");
    wave.load();
    wave.createBuffer();

    Audio::Source source(wave.getIdBuffer());
    source.setRolloffFactor(1); // degré d'atténuation
    source.setMaxDistance(2000.0); // distance maximal ou la source est audible
    source.setReferenceDistance(400); // distance à partir de laquelle le rolloff_factor et la max distance influt vraiment

    //Lets go video-audio !
    Mat frame;
    int frameCount;
    bool reponse,stop;
    namedWindow("Film");
    while(!stop)
    {
        reponse = false;
        stop = false;
        frameCount = 0;
        for(;;)
        {
            cap >> frame; // get a new frame from camera
            if(frame.empty()) break;
            for(int i =0 ; i < nombreObject ;i++)
            {
                std::cout << "Object : " <<i;
                std::cout << " First frame : " << co.m_listeObjects[i].m_firstFrame;
                std::cout << " Last frame : " << co.m_listeObjects[i].m_lastFrame  << endl;
                int frameFromBeginObject = frameCount - co.m_listeObjects[i].m_firstFrame;
                int frameFromEndObject = frameCount - co.m_listeObjects[i].m_lastFrame;
                if(frameFromBeginObject == 0)
                {
                    //Apparition de l'objet

                    source.play();
                    ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                               (ALfloat)(co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z/160000)};
                    ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                    source.setPosition(positionObjet);
                    //source.setVelocity(velociteObjet);
                }
                else if(frameFromEndObject == 0)
                {
                    //Disparition de l'objet
                    ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                               (ALfloat)(co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z/160000.0)};
                    ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                    source.setPosition(positionObjet);
                    //source.setVelocity(velociteObjet);
                    source.pause();
                }
                else if(frameFromBeginObject > 0 && frameFromEndObject < 0)
                {
                    std::cout << "Position frame " <<frameCount << " : ";
                    std::cout << co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y<< " " ;
                    std::cout << co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x<< " " ;
                    std::cout << co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z/160000.0<< endl;


                    ALfloat positionObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].y,
                                               (ALfloat)(co.m_listeObjects[i].m_listeCoordonnees[frameFromBeginObject].z/160000.0)};
                    ALfloat velociteObjet[] = {(ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].x,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].y,
                                               (ALfloat)co.m_listeObjects[i].m_listeVecteurVitesse[frameFromBeginObject].z};

                    source.setPosition(positionObjet);
                    //source.setVelocity(velociteObjet);
                }
            }
            frameCount++;
            imshow("Film", frame);
            if(waitKey(30) >= 0) break;
        }
        source.stop();

        //Boucle de rejeu
        while(!reponse)
        {
            char rep;
            cout << "Encore ? (y or N)" << endl;
            cin >> rep;
            if(rep  == 'y')
            {
                reponse=true;
                cap.set(CV_CAP_PROP_POS_AVI_RATIO,0);
            }
            else if(rep  == 'N')
            {
                reponse=true;
                stop=true;
            }
        }
    }
    delete Audio::OpenAL::getInstance();
    return 0;
}
