// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VMeson.cc,v 1.1 1999/01/07 16:10:20 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 class implementation file 
//
//      For information related to this code contact:
//      CERN, CN Division, ASD Group
//      History: first implementation, based on object model of
//      2nd December 1995, G.Cosmo
// --------------------------------------------------------------

#include "G4VMeson.hh"

const G4VMeson & G4VMeson::operator=(const G4VMeson &right)
{
  if (this != &right) {
  } return right;
}

