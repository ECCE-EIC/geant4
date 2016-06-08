// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4BREPSolidBox.hh,v 1.1 1999/01/07 16:07:24 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
#ifndef __G4BREPSolidBOX
#define __G4BREPSolidBOX
#include "G4BREPSolid.hh"
#include "G4RotationMatrix.hh"

class G4BREPSolidBox: public G4BREPSolid
{
public:

  G4BREPSolidBox(G4String,const G4Point3D&, const G4Point3D&, 
		 const G4Point3D&, const G4Point3D&, const G4Point3D&, 
		 const G4Point3D&, const G4Point3D&, const G4Point3D& );       

  EInside Inside(register const G4ThreeVector&) const;

private:

  G4RotationMatrix Rotation;

};

#endif
