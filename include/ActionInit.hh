

#ifndef CPROJECT_ACTIONINIT_HH
#define CPROJECT_ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGen.hh"
#include "EventAct.hh"
#include "RunAct.hh"
#include "StepAct.hh"
class ActionInit : public G4VUserActionInitialization{
private:
public:
    ActionInit();
    virtual ~ActionInit();
    virtual void Build() const;
};


#endif //CPROJECT_ACTIONINIT_HH
