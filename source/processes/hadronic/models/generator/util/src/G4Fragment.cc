// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4Fragment.cc,v 1.4 1999/04/15 11:13:06 larazb Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (May 1998)

#include "G4Fragment.hh"


// Default constructor
G4Fragment::G4Fragment() :
  theA(0),
  theZ(0),
  theExcitationEnergy(0.0),
  theMomentum(0),
  theAngularMomentum(0),
  numberOfExcitons(0),
  numberOfHoles(0),
  numberOfCharged(0),
  theParticleDefinition(0),
  theCreationTime(0.0)
{
  theAngularMomentum = IsotropicRandom3Vector();
}

// Copy Constructor
G4Fragment::G4Fragment(const G4Fragment &right) 
{
   theA = right.theA;
   theZ = right.theZ;
   theExcitationEnergy = right.theExcitationEnergy;
   theMomentum  = right.theMomentum;
   theAngularMomentum = right.theAngularMomentum;
   numberOfExcitons = right.numberOfExcitons;
   numberOfHoles = right.numberOfHoles;
   numberOfCharged = right.numberOfCharged;
   theParticleDefinition = right.theParticleDefinition;
   theCreationTime = right.theCreationTime;
}


G4Fragment::~G4Fragment()
{
}


G4Fragment::G4Fragment(const G4int A, const G4int Z, const G4LorentzVector aMomentum) :
  theA(A),
  theZ(Z),
  theMomentum(aMomentum),
  numberOfExcitons(0),
  numberOfHoles(0),
  numberOfCharged(0),
  theParticleDefinition(0),
  theCreationTime(0.0)
{
  theExcitationEnergy = theMomentum.mag() - G4ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass( theZ, theA );
  if( theExcitationEnergy < 0.0 )
    if( theExcitationEnergy > -10.0 * eV )
      theExcitationEnergy = 0.0;
    else 
    {
      cout << "A, Z, momentum, theExcitationEnergy"<<
           A<<" "<<Z<<" "<<aMomentum<<" "<<theExcitationEnergy<<endl;
      G4Exception( "G4Fragment::G4Fragment Excitation Energy < 0.0!" );
    }
}


// This constructor is for initialize photons
G4Fragment::G4Fragment(const G4LorentzVector aMomentum, G4ParticleDefinition * aParticleDefinition) :
  theA(0),
  theZ(0),
  theMomentum(aMomentum),
  numberOfExcitons(0),
  numberOfHoles(0),
  numberOfCharged(0),
  theParticleDefinition(aParticleDefinition),
  theCreationTime(0.0)

{
  theExcitationEnergy = CalculateExcitationEnergy(aMomentum);
  theAngularMomentum = IsotropicRandom3Vector();
}



// G4Fragment::G4Fragment(const G4int A, const G4int Z, const G4double anExEnergy, 
// 		       const G4LorentzVector aMomentum, 
// 		       const G4ThreeVector anAngularMomentum, const G4int aNumberOfExcitons, 
// 		       const G4int aNumberOfHoles, const G4int aNumberOfCharged) : 
//   theA(A),
//   theZ(Z),
//   theExcitationEnergy(anExEnergy),
//   theMomentum(aMomentum),
//   theAngularMomentum(anAngularMomentum),
//   numberOfExcitons(aNumberOfExcitons),
//   numberOfHoles(aNumberOfHoles),
//   numberOfCharged(aNumberOfCharged),
//   theParticleDefinition(0)
// {}

// G4Fragment::G4Fragment(const G4int A, const G4int Z, const G4double anExEnergy, 
// 		       const G4LorentzVector aMomentum, 
// 		       const G4ThreeVector anAngularMomentum, const G4int aNumberOfExcitons, 
// 		       const G4int aNumberOfHoles, const G4int aNumberOfCharged,
// 		       G4ParticleDefinition * aParticleDefinition) : 
//   theA(A),
//   theZ(Z),
//   theExcitationEnergy(anExEnergy),
//   theMomentum(aMomentum),
//   theAngularMomentum(anAngularMomentum),
//   numberOfExcitons(aNumberOfExcitons),
//   numberOfHoles(aNumberOfHoles),
//   numberOfCharged(aNumberOfCharged),
//   theParticleDefinition(aParticleDefinition)
// {}




const G4Fragment & G4Fragment::operator=(const G4Fragment &right)
{
  if (this != &right) {
    theA = right.theA;
    theZ = right.theZ;
    theExcitationEnergy = right.theExcitationEnergy;
    theMomentum  = right.theMomentum;
    theAngularMomentum = right.theAngularMomentum;
    numberOfExcitons = right.numberOfExcitons;
    numberOfHoles = right.numberOfHoles;
    numberOfCharged = right.numberOfCharged;
    theParticleDefinition = right.theParticleDefinition;
    theCreationTime = right.theCreationTime;
  }
  return *this;
}


G4bool G4Fragment::operator==(const G4Fragment &right) const
{
  return (this == (G4Fragment *) &right);
}

G4bool G4Fragment::operator!=(const G4Fragment &right) const
{
  return (this != (G4Fragment *) &right);
}


ostream& operator << (ostream &out, const G4Fragment *theFragment)
{
  long old_floatfield = out.setf(0,ios::floatfield);

  out 
    << "Fragment: A = " << setprecision(3) << theFragment->theA 
    << ", Z = " << setprecision(3) << theFragment->theZ ;
  out.setf(ios::scientific,ios::floatfield);
  out
    << ", U = " << theFragment->theExcitationEnergy/MeV 
    << " MeV" << endl
    << "          P = (" 
    << theFragment->theMomentum.x()/MeV << ","
    << theFragment->theMomentum.y()/MeV << ","
    << theFragment->theMomentum.z()/MeV 
    << ") MeV   E = " 
    << theFragment->theMomentum.t()/MeV << " MeV";

  // What about Angular momentum???

  if (theFragment->numberOfExcitons != 0) {
    out << endl;
    out << "          " 
	<< "#Excitons = " << theFragment->numberOfExcitons 
	<< ", #Holes = "   << theFragment->numberOfHoles
	<< ", #Charged = " << theFragment->numberOfCharged;
  }
  out.setf(old_floatfield,ios::floatfield);

  return out;
    
}

ostream& operator << (ostream &out, const G4Fragment &theFragment)
{
  out << &theFragment;
  return out; 
}



G4double G4Fragment::CalculateExcitationEnergy(const G4LorentzVector value) const
{
	G4double U = value.m() - GetGroundStateMass();
	if( U < 0.0 )
		if( U > -10.0 * eV )
			U = 0.0;
		else 
			G4Exception( "G4Fragment::G4Fragment Excitation Energy < 0!" );
	return U;
}

G4ThreeVector G4Fragment::IsotropicRandom3Vector(const G4double Magnitude) const
  // Create a unit vector with a random direction isotropically distributed
{

  G4double CosTheta = 1.0 - 2.0*G4UniformRand();
  G4double SinTheta = sqrt(1.0 - CosTheta*CosTheta);
  G4double Phi = twopi*G4UniformRand();
  G4ThreeVector Vector(Magnitude*cos(Phi)*SinTheta,
                       Magnitude*sin(Phi)*SinTheta,
                       Magnitude*CosTheta);

  return Vector;
		
}
