// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenGLXmWindowHandlingCallbacks.hh,v 1.2 1999/01/09 16:23:07 allison Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
//

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#ifndef G4OPENGLXMWINDOWHANDLINGCALLBACKS_HH
#define G4OPENGLXMWINDOWHANDLINGCALLBACKS_HH

#include "G4OpenGLXmViewer.hh"

void expose_callback (Widget w, XtPointer clientData, XtPointer callData);
void resize_callback (Widget w, XtPointer clientData, XtPointer callData);

#endif

#endif
