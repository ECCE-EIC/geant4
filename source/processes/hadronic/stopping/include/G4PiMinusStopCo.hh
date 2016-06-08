// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4PiMinusStopCo.hh,v 1.1 1999/01/07 16:13:39 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//      For information related to this code contact:
//      CERN, IT Division, ASD group
//
//      File name:     G4PiMinusStopCo.hh 
//
//      Author:        Maria Grazia Pia (pia@genova.infn.it)
// 
//      Creation date: 18 May 1998
//
//      Modifications: 
// -------------------------------------------------------------------

#ifndef G4PIMINUSSTOPCO_HH
#define G4PIMINUSSTOPCO_HH 

#include <rw/tpordvec.h>
#include <rw/tvordvec.h>
#include <rw/cstring.h>

#include "G4PiMinusStopMaterial.hh"
#include "globals.hh"
#include "G4LorentzVector.hh"

class G4PiMinusStopCo : public G4PiMinusStopMaterial
{  

private:

  // Hide assignment operator as private 
  G4PiMinusStopCo& operator=(const G4PiMinusStopCo &right);

  // Copy constructor
  G4PiMinusStopCo(const G4PiMinusStopCo& );

public:

  // Constructor
  G4PiMinusStopCo();

  // Destructor
  virtual ~G4PiMinusStopCo();

  // Definitions of absorption products
  //  virtual RWTValOrderedVector<G4String>* DefinitionVector();

  // 4-vectors of absorption products
  //  virtual RWTPtrOrderedVector<G4LorentzVector>* P4Vector();

  // Number of final nucleons, out of generated absorption products
  virtual G4double FinalNucleons();


private:

  static G4int eKinEntries;
  static G4int angleEntries;

  static G4double npRatio;
 
  static G4double nFinalNucleons;

  static G4double eMaxTot;

  static G4double eKinData[11];
  static G4double eKin[12];

  static G4double angleData[7];
  static G4double angle[8];

  G4double _clusterSize;

};

#endif


