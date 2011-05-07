#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QTreeWidgetItem>

//#include <OgreSceneNode.h>
//#include <OgreSceneManager.h>

MainWindow * MainWindow::instance = 0;
int MainWindow::objectsCount = 0;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ogreWindow = new OgreWidget();
    ogreWindow->setMouseTracking(true);
    QTabWidget *tab = new QTabWidget;
    QWidget *wi = new QWidget;
    tab->addTab(ogreWindow,"Scene");
    tab->addTab(wi,"Game");
    this->setCentralWidget(tab);
    initProjectExplorer();

    QObject::connect(ui->position_x, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->position_y, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->position_z, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->rotation_x, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->rotation_y, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->rotation_z, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->scale_x, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->scale_y, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );
    QObject::connect(ui->scale_z, SIGNAL(textChanged(const QString &)), this, SLOT(OnPositionChanged(const QString &)) );


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initProjectExplorer()
{
    QFileSystemModel *fileSystemModel = new QFileSystemModel();
    fileSystemModel->setRootPath(QDir::currentPath());

    QStringList filters;
    filters.append("*.jpg");
    filters.append("*.png");
    filters.append("*.mesh");
    filters.append("*.material");
    fileSystemModel->setNameFilters(filters);
    fileSystemModel->setNameFilterDisables(false);

    ui->prExplorerTree->setModel(fileSystemModel);
    ui->prExplorerTree->setColumnHidden(1, true);
    ui->prExplorerTree->setColumnHidden(2, true);
    ui->prExplorerTree->setColumnHidden(3, true);

    ui->prExplorerTree->setRootIndex(fileSystemModel->index(QDir::currentPath()));
    ui->prExplorerTree->show();  
}

 void MainWindow::UpdateComponents(Ogre::SceneNode* sceneNode,Ogre::Entity * entity)
 {
     ui->position_x->clearFocus(); ui->position_y->clearFocus(); ui->position_z->clearFocus();
     ui->rotation_x->clearFocus(); ui->rotation_y->clearFocus(); ui->rotation_z->clearFocus();
     ui->scale_x->clearFocus(); ui->scale_y->clearFocus(); ui->scale_z->clearFocus();
     ui->position_x->setText(QString::number( sceneNode->getPosition().x));
     ui->position_y->setText(QString::number(sceneNode->getPosition().y));
     ui->position_z->setText(QString::number(sceneNode->getPosition().z));
     ui->rotation_x->setText(QString::number(sceneNode->getOrientation().getYaw().valueDegrees()));
     ui->rotation_y->setText(QString::number(sceneNode->getOrientation().getPitch().valueDegrees()));
     ui->rotation_z->setText(QString::number(sceneNode->getOrientation().getRoll().valueDegrees()));
     ui->scale_x->setText(QString::number(sceneNode->getScale().x));
     ui->scale_y->setText(QString::number(sceneNode->getScale().y));
     ui->scale_z->setText(QString::number(sceneNode->getScale().z));
     ui->mesh_edit->setText(QString::fromStdString(entity->getMesh()->getName()));
     ui->texture_edit->setText(QString::fromStdString(entity->getSubEntity(0)->getMaterialName()));

 }  


void MainWindow::createRobot(Ogre::Vector3 pos)
{
    objectsCount++;

    Ogre::Entity * myEntity =
            ogreWindow->getSceneManager()->createEntity("robot" +
                           QString::number(objectsCount).toStdString(),
                                                            "robot.mesh");
    Ogre::SceneNode * mynode =
            ogreWindow->getSceneManager()->getRootSceneNode()->createChildSceneNode("robot" +
                                       QString::number(objectsCount).toStdString());

    mynode->attachObject( myEntity );
    myEntity->setMaterialName("RobotMaterial");
    mynode->setPosition(pos);
    mynode->scale(1.1, 1.1, 1.1);

    QStringList lst;
    lst << QString::fromStdString(mynode->getName());
    QTreeWidgetItem* pItem = new QTreeWidgetItem(lst, 0);

    ui->sceneNodesTree->addTopLevelItem(pItem);

}

void MainWindow::OnPositionChanged(const QString & str)
{
    if (ogreWindow->CurrentNode) {

if (ui->position_x->hasFocus() || ui->position_x->hasFocus()|| ui->position_y->hasFocus() || ui->position_z->hasFocus() || ui->rotation_x->hasFocus()||
        ui->rotation_y->hasFocus() || ui->rotation_z->hasFocus() || ui->scale_x->hasFocus() || ui->scale_y->hasFocus() || ui->scale_z->hasFocus()){

   float x=ui->position_x->text().toFloat();
   float y=ui->position_y->text().toFloat();
   float z=ui->position_z->text().toFloat();
   float scalex=ui->scale_x->text().toFloat();
   float scaley=ui->scale_y->text().toFloat();
   float scalez=ui->scale_z->text().toFloat();
   float rotatex=ui->rotation_x->text().toFloat();
   float rotatey=ui->rotation_y->text().toFloat();
   float rotatez=ui->rotation_z->text().toFloat();

   qDebug()<<"str= "<<str;
   ogreWindow->CurrentNode->setOrientation(ogreWindow->CurrentNode->getOrientation().w,0,ogreWindow->CurrentNode->getOrientation().y,ogreWindow->CurrentNode->getOrientation().z);
   ogreWindow->CurrentNode->pitch(Ogre::Degree(rotatex));
   ogreWindow->CurrentNode->setOrientation(ogreWindow->CurrentNode->getOrientation().w,ogreWindow->CurrentNode->getOrientation().x,0,ogreWindow->CurrentNode->getOrientation().z);
   ogreWindow->CurrentNode->yaw(Ogre::Degree(rotatey));
   ogreWindow->CurrentNode->setOrientation(ogreWindow->CurrentNode->getOrientation().w,ogreWindow->CurrentNode->getOrientation().x,ogreWindow->CurrentNode->getOrientation().y,0);
   ogreWindow->CurrentNode->roll(Ogre::Degree(rotatez));
   ogreWindow->CurrentNode->setScale(scalex,scaley,scalez);
   ogreWindow->CurrentNode->setPosition(x,y,z);
   }

   }

}
