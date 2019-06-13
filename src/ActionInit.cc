
#include "ActionInit.hh"

ActionInit::ActionInit()
{ }

ActionInit::~ActionInit()
{ }

void ActionInit::Build() const
{
    SetUserAction(new PrimaryGen());
    //SetUserAction(new RunGen());

    RunAct* runAct = new RunAct;
    SetUserAction(runAct);

    EventAct* eventAct = new EventAct(runAct);
    SetUserAction(eventAct);

    SetUserAction(new StepAct (eventAct));

}
