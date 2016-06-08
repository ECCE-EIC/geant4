// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4Poisson.hh,v 1.2 1999/05/11 19:43:11 gcosmo Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file 
//
//      For information related to this code contact:
//      CERN, IT Division, ASD group
//
// ------------------------------------------------------------
// Description:
// -----------
// G4Poisson is the C++ implementation of the CERNLIB GPOISS algorithm
// for the generation of Gaussian distributed random numbers. It has been
// adapted to invoke HepRandom from CLHEP for the primary engine generators.
// GPOISS is recognized to be a faster algorithm, providing however a less
// accurate output, than the algorithm adopted in CLHEP.
// ------------------------------------------------------------
#ifndef G4POISSON_HH
#define G4POISSON_HH

#include "globals.hh"
#include "Randomize.hh"

G4long G4Poisson(G4double mean)
{
  G4long number = 0;
  const G4int border = 16;
  G4double limit = 2e9;

  if(mean <= border) {
    G4double position = RandFlat::shoot();
    G4double poissonValue = exp(-mean);
    G4double poissonSum = poissonValue;

    while(poissonSum <= position) {
      number++ ;
      poissonValue *= mean/number;
      poissonSum += poissonValue;
    }
    return number;
  } // the case of mean <= 16

  G4double value, t, y;
  t = sqrt(-2*log(RandFlat::shoot()));
  y = twopi*RandFlat::shoot();
  t *= cos(y);
  value = mean + t*sqrt(mean);
  if(value <= 0) {return 0;}
  if(value >= limit) { return G4long(limit);}
  return G4long(value);
}

#endif  /* G4POISSON_HH */
