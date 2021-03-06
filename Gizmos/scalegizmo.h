#ifndef SCALEGIZMO_H
#define SCALEGIZMO_H

#include "Gizmos/IGizmo.h"

class ScaleGizmo : public IGizmo
{
public:
    ScaleGizmo();
     void draw(bool,bool,bool,bool=false);
     void show();
     void hide();
     void scale(float,float,float);
     Ogre::Vector3 getScale();
     void setPosition(Ogre::Vector3);
     void setOrientation(Ogre::Quaternion);
private:

    Ogre::SceneNode* MainScaleNode;
    Ogre::ManualObject* lineXScale;
    Ogre::SceneNode* NodelineXScale;
    Ogre::ManualObject* lineYScale;
    Ogre::SceneNode* NodelineYScale;
    Ogre::ManualObject* lineZScale;
    Ogre::SceneNode* NodelineZScale;
    Ogre::Entity * ScaleXent;
    Ogre::Entity * ScaleYent;
    Ogre::Entity * ScaleZent;
    Ogre::SceneNode* NodescaleXQuadr;
    Ogre::SceneNode* NodescaleYQuadr;
    Ogre::SceneNode* NodescaleZQuadr;
};

#endif // SCALEGIZMO_H
