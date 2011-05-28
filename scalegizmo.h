#ifndef SCALEGIZMO_H
#define SCALEGIZMO_H
#include "IGizmo.h"
#include "QtWidget.h"
class ScaleGizmo : public IGizmo
{
public:
    ScaleGizmo(OgreWidget*);
     void draw(bool,bool,bool,bool=false);
     void show();
     void hide();
     void setPosition(Ogre::Vector3);

private:

OgreWidget *ogreWidget;

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