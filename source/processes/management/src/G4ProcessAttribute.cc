// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4ProcessAttribute.cc,v 1.2 1999/04/13 09:47:58 kurasige Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//	For information related to this code contact:
//	CERN, IT Division, ASD group
//	History: first implementation, based on object model of
//	2nd December 1997, H.Kurashige
//   ----------------  G4ProcessAttribute -----------------
// History:
//   adds copy constructor            27 June 1998 H.Kurashige
// ------------------------------------------------------------

#include "G4ProcessAttribute.hh"

G4ProcessAttribute::G4ProcessAttribute():
	 isActive(true)
{
  pProcess = 0;
  idxProcessList = -1;
}

// copy constructor //////////////////////////
G4ProcessAttribute::G4ProcessAttribute(const G4ProcessAttribute &right)
         :isActive(true)
{
  pProcess       = right.pProcess;
  idxProcessList = right.idxProcessList;
  // copy all contents in idxProcVector[] and ordProcVector[]
  //   deep copy 
  for (G4int idx=0; idx<G4ProcessManager::SizeOfProcVectorArray; idx++){
    idxProcVector[idx] = right.idxProcVector[idx];
    ordProcVector[idx] = right.ordProcVector[idx];
  }
}

 G4ProcessAttribute::~G4ProcessAttribute()
{
   // do nothing
}

G4ProcessAttribute & G4ProcessAttribute::operator=(G4ProcessAttribute &right)
{
  if (this != &right) {
    pProcess       = right.pProcess;
    idxProcessList = right.idxProcessList;
    isActive = right.isActive;
    // copy all contents in idxProcVector[] and ordProcVector[]
    //   deep copy 
    for (G4int idx=0; idx<G4ProcessManager::SizeOfProcVectorArray; idx++){
      idxProcVector[idx] = right.idxProcVector[idx];
      ordProcVector[idx] = right.ordProcVector[idx];
    }
  }
  return *this;
}



