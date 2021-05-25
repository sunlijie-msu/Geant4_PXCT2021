#include "ExG4ActionInitialization.hh"
#include "ExG4PrimaryGeneratorAction.hh"
#include "ExG4RunAction.hh"
#include "ExG4EventAction.hh"

ExG4ActionInitialization::ExG4ActionInitialization():G4VUserActionInitialization()
{}


ExG4ActionInitialization::~ExG4ActionInitialization()
{}

void ExG4ActionInitialization::BuildForMaster() const
{
  SetUserAction(new ExG4RunAction);
}

void ExG4ActionInitialization::Build() const
{
  SetUserAction(new ExG4PrimaryGeneratorAction);
  SetUserAction(new ExG4RunAction);
  SetUserAction(new ExG4EventAction);
}
