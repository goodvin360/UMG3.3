

#ifndef CPROJECT_LOADER_H
#define CPROJECT_LOADER_H

//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "DetGeometry.hh"
#include "ActionInit.hh"
#include "PrimaryGen.hh"


#include <iostream>

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


class DetGeometry;
class G4Loader{
private:

//#ifdef G4MULTITHREADED
//    G4MTRunManager* runManager;
//#else
    G4RunManager* runManager;
//#endif
    DetGeometry *detGeom;
#ifdef G4VIS_USE
    G4VisManager* visManager;
#endif
public:
    G4Loader(int argc, char** argv);
    ~G4Loader();

};



#endif //CPROJECT_LOADER_H
