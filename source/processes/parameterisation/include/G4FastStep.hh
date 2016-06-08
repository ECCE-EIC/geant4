// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4FastStep.hh,v 1.3 1999/04/19 14:27:44 mora Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
//---------------------------------------------------------------
//
//  G4FastStep.hh
//
//  Description:
//    The G4FastStep class insures a friendly interface
//    to manage the primary/secondaries final state for 
//    Fast Simulation Models. This includes final states of parent
//    particle (normalized direction of the momentum, energy, etc) and 
//    secondary particles generated by the parameterisation.
//
//    The G4FastStep class acts also as the G4ParticleChange
//    for the Fast Simulation Process. So it inherites from 
//    the G4VParticleChange class and redefines the four virtual 
//    methods :
//
//     virtual G4Step* UpdateStepForAtRest(G4Step* Step);
//     virtual G4Step* UpdateStepForAlongStep(G4Step* Step);
//     virtual G4Step* UpdateStepForPostStep(G4Step* Step);
//     virtual void Initialize(const G4Track&);
//
//  History:
//    Oct 97: Verderi && MoraDeFreitas - First Implementation.
//    Dec 97: Verderi - ForceSteppingHitInvocation(),
//                      Set/GetTotalEnergyDeposited() methods.
//    Apr 98: MoraDeFreitas - G4FastStep becomes the G4ParticleChange
//                      for the Fast Simulation Process.
//
//---------------------------------------------------------------


#ifndef G4FastStep_h
#define G4FastStep_h

#include "globals.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleMomentum.hh"
class G4DynamicParticle;
#include "G4VParticleChange.hh"
#include "G4FastTrack.hh"

//-------------------------------------------
//
//        G4FastStep class
//
//-------------------------------------------
class G4FastStep: public G4VParticleChange
{
public:
  //===================================================
  //Fast Simulation Model Interface (section for users)
  //===================================================
  //
  //                Particle management
  //                -------------------
  //
  //   The methods here provide an implementation of the
  // G4VParticleChange class for parameterisations.
  // They have to be filled to describe the FINAL STATE
  // of the particles.
  //
  //   To facilitate the developers work, changes of 
  // position/normalized direction of the momentum/polarization 
  // can be specified in the local coordinate system of the envelope 
  // or in the global one.
  //
  //   The default is local system coordinates.


  // -- The KillPrimaryTrack() set the kinetic energy of the
  // -- primary to zero, and set the "fStopAndKill" signal
  // -- used by the stepping.
  void KillPrimaryTrack();

  // -- Methods used to change the position, normalized direction of 
  // the momentum, time etc... of the primary.
  // .. space and time:
  void SetPrimaryTrackFinalPosition (const G4ThreeVector &, 
				     G4bool localCoordinates = true);
  void SetPrimaryTrackFinalTime (G4double);
  void SetPrimaryTrackFinalProperTime (G4double);

  // .. dynamics:
  // Be careful: the Track Final Momentum means the normalized direction 
  // of the momentum!
  void SetPrimaryTrackFinalMomentum (const G4ThreeVector &, 
				     G4bool localCoordinates = true);
  void SetPrimaryTrackFinalKineticEnergy (G4double);
  void SetPrimaryTrackFinalKineticEnergyAndDirection(G4double, 
						     const G4ThreeVector &, 
						     G4bool localCoordinates 
						     = true);
  void SetPrimaryTrackFinalPolarization(const G4ThreeVector &, 
					G4bool localCoordinates = true);

  // .. true path length of the primary during the FastStep:
  void SetPrimaryTrackPathLength (G4double);

  // Weight applied for event biasing mechanism:
  void SetPrimaryTrackFinalEventBiasingWeight (G4double);


  // ------------------------------
  // -- Management of secondaries:
  // ------------------------------

  // ----------------------------------------------------
  // -- The creation of secondaries is Done in two steps:
  // --      1) Give the total number of secondaries
  // --         that the FastStep returns
  // --         to the tracking using:
  // --         SetNumberOfSecondaryTracks()
  // --
  // --      2) Invoke the CreateSecondaryTrack() method
  // --         to create one secondary at each time.
  // ----------------------------------------------------

  // -- Total Number of secondaries to be created,
  // -- (to be called first)
  void SetNumberOfSecondaryTracks(G4int);

  // -- Number of secondaries effectively stored:
  // -- (incremented at each CreateSecondaryTrack()
  // -- call)
  G4int GetNumberOfSecondaryTracks();

  // -- Create a secondary: the arguments are:
  // --     * G4DynamicsParticle: see header file, many constructors exist
  // --                           (allow to set particle type + energy + 
  // -- the normalized direction of momentum...)
  // --     * G4ThreeVector     : Polarization (not in G4ParticleChange constructor)
  // --     * G4ThreeVector     : Position
  // --     * G4double          : Time
  // --     * G4bool            : says if Position/Momentum are given in the
  // --                           local coordinate system (true by default)
  // -- Returned value: pointer to the track created.
  G4Track* CreateSecondaryTrack(const G4DynamicParticle&,
				G4ThreeVector,
				G4ThreeVector,
				G4double,
				G4bool localCoordinates=true);
  
  //-- Create a secondary: the difference with he above declaration
  //-- is that the Polarization is not given and is assumed already set
  //-- in the G4DynamicParticle.
  //-- Returned value: pointer to the track created
  G4Track* CreateSecondaryTrack(const G4DynamicParticle&,
				G4ThreeVector,
				G4double,
				G4bool localCoordinates=true);
  
  // -- Gives a pointer on the i-th secondary track created:
  G4Track* GetSecondaryTrack(G4int);

  //------------------------------------------------
  //
  //   Total energy deposit in the "fast Step"
  //   (a default should be provided in future,
  //    which can be:
  //      delta energy of primary -
  //      energy of the secondaries)
  //   This allow the user to Store a consistent
  //   information in the G4Trajectory.
  //
  //------------------------------------------------
  void SetTotalEnergyDeposited(G4double anEnergyPart);
  G4double GetTotalEnergyDeposited() const;

  //----------------------------------------------------
  //
  //   Control of the stepping manager Hit invocation:
  //   -----------------------------------------------
  //
  //     In a usual parameterisation, the control of
  //   the hits production is under the user
  //   responsability in his G4VFastSimulationModel
  //   (he generally produces several hits at once.)
  //
  //     However, in the particular case the G4Fast-
  //   Simulation user's model acts as the physics
  //   replacement only (ie replaces all the ***DoIt()
  //   and leads to the construction of a meaningful
  //   G4Step), the user can delegate to the
  //   G4SteppingManager the responsability to invoke
  //   the Hit()method of the current sensitive if any.
  //
  //     By default, the G4SteppingManager is asked to
  //   NOT invoke this Hit() method when parameterisation
  //   is invoked. (See Initialize() method of G4FastStep)
  //   
  //----------------------------------------------------
  void ForceSteppingHitInvocation();



  //=======================================================
  // Implementation section and kernel interfaces.
  //=======================================================
  //------------------------
  // Constructor/Destructor
  //------------------------
  G4FastStep();
  virtual ~G4FastStep();
  
  // equal/unequal operator
  G4bool operator==(const G4FastStep &right) const;
  G4bool operator!=(const G4FastStep &right) const;

protected:
  // hide copy constructor and assignment operator as protected
  G4FastStep (const G4FastStep &right);
  G4FastStep & operator= (const G4FastStep &right);

public:
  // ===============================================
  // Stepping interface.
  // ===============================================
  // --- the following methods are for updating G4Step -----   
  // Return the pointer to the G4Step after updating the Step information
  // by using final state information of the track given by a Model.
  //
  // The Fast Simulation Mechanism doesn't change the track's final 
  // state on the AlongDoIt loop, so the default one all we need.
  //virtual G4Step* UpdateStepForAlongStep(G4Step* Step);

  G4Step* UpdateStepForAtRest(G4Step* Step);
  G4Step* UpdateStepForPostStep(G4Step* Step);

  // A Model gives the final state of the particle 
  // based on information of G4FastTrack. So the
  // Initialize method is an interface to the 
  // G4FastSimulationManager to Initialize the 
  // G4FastStep.

  void Initialize(const G4FastTrack&);

private:
  //===================================================
  // Private Internal methods (implementation).
  //===================================================

  // G4FastStep should never be Initialized in this way
  // but we must define it to avoid compiler warnings.
  void Initialize(const G4Track&);

  //  -- Utility functions --
  //--- methods to keep information of the final state--
  //  IMPORTANT NOTE: Although the name of the class and methods are
  //   "Change", what it stores (and returns in get) are the "FINAL" 
  //   values of the Position, the normalized direction of Momentum, 
  //   etc.
  
  // Set theMomentumChange vector: it is the final unitary momentum 
  // direction.
  void SetMomentumChange(G4double Px, G4double Py, G4double Pz);
  void SetMomentumChange(const G4ThreeVector& Pfinal);
  
  //=====================================================
  // Data members.
  //=====================================================
  //  theMomentumChange is the vector containing the final momentum 
  //  direction after the invoked process. The application of the change
  //  of the momentum direction of the particle is not Done here.
  //  The responsibility to apply the change is up the entity
  //  which invoked the process.
  G4ParticleMomentum theMomentumChange;

  //  The changed (final) polarization of a given particle.
  G4ThreeVector thePolarizationChange;

  //  The final kinetic energy of the current particle.
  G4double theEnergyChange;

  //  The changed (final) position of a given particle.
  G4ThreeVector thePositionChange;

  //  The changed (final) global time of a given particle.
  G4double theTimeChange;

  //  The changed (final) proper time of a given particle.
  G4double theProperTimeChange;

  // The reference G4FastTrack
  const G4FastTrack* fFastTrack;

  // weight for event biasing mechanism:
  G4double theWeightChange;


public:
  // for Debug 
  void DumpInfo() const;
  G4bool CheckIt(const G4Track&);
};

//*******************************************************************
//
//  Inline functions
//
//*******************************************************************

#include "G4FastStep.icc"

#endif
