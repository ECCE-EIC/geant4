// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VisCommandsCamera.hh,v 1.2 1999/01/09 16:30:55 allison Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// /vis~/camera/ commands
// John Allison  7th September 1997

#ifndef G4VISCOMMANDSCAMERA_HH
#define G4VISCOMMANDSCAMERA_HH

#include "globals.hh"
#include "G4VisManager.hh"
#include "G4ViewParameters.hh"

////////////////////////////////////////////////////  /vis~/camera/...  ////
//vis \hline
//vis /vis~/camera/ &&
//vis ...menu of camera commands. \\%
class G4VisCommandCamera {
public:
  G4String GetCommandName () const {return "/vis~/camera/";}
  G4String GetGuidance () const {
    return "...menu of camera commands.";
  }
};

/////////////////////////////////////  /vis~/camera/reset  ////
//camera \hline
//camera /vis~/camera/reset &&
//camera Resets dolly, pan and zoom.  Regains ``Standard View''. \\%
class G4VisCommandCameraReset {
public:
  G4String GetCommandName () const {return "/vis~/camera/reset";}
  G4String GetGuidance () const {
    return "Resets dolly, pan and zoom.  Regains \"Standard View\".";
  }
  void SetValue ();
};

#endif
