// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VisCommandsSceneAdd.hh,v 1.2 1999/01/09 16:31:02 allison Exp $
// GEANT4 tag $Name: geant4-00-01 $

// /vis/scene commands - John Allison  9th August 1998

#ifndef G4VISCOMMANDSSCENEADD_HH
#define G4VISCOMMANDSSCENEADD_HH

#include "G4VisCommandsScene.hh"

class G4VisCommandSceneAddVolume: public G4VVisCommandScene {
public:
  // Uses compiler defaults for copy constructor and assignment.
  G4VisCommandSceneAddVolume ();
  ~G4VisCommandSceneAddVolume ();
  G4String GetCurrentValue (G4UIcommand* command);
  void SetNewValue (G4UIcommand* command, G4String newValue);
private:
  G4UIcommand* fpCommand;
};

class G4VisCommandSceneAddGhosts: public G4VVisCommandScene {
public:
  // Uses compiler defaults for copy constructor and assignment.
  G4VisCommandSceneAddGhosts ();
  ~G4VisCommandSceneAddGhosts ();
  G4String GetCurrentValue (G4UIcommand* command);
  void SetNewValue (G4UIcommand* command, G4String newValue);
private:
  G4UIcmdWithAString* fpCommand;
};

#endif
