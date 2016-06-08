// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN01PhysicsList.hh,v 1.2 1999/04/16 10:48:49 kurasige Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
//
// ExN01PhysicsList
//  Construct/define particles and physics processes
//
//  Particle defined in ExampleN01
//    geantino
//
//  Process defined in ExampleN01
//    transportation
//

#ifndef ExN01PhysicsList_h
#define ExN01PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class ExN01PhysicsList: public G4VUserPhysicsList
{
  public:
    ExN01PhysicsList();
    ~ExN01PhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif







