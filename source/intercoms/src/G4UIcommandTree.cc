// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4UIcommandTree.cc,v 1.1 1999/01/07 16:09:27 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#include "G4UIcommandTree.hh"
#include "G4ios.hh"

G4UIcommandTree::G4UIcommandTree()
:guidance(NULL)
{ }

G4UIcommandTree::G4UIcommandTree(G4String thePathName)
:guidance(NULL)
{
  pathName = thePathName;
}

G4UIcommandTree::G4UIcommandTree(char * thePathName)
:guidance(NULL)
{
  pathName = thePathName;
}

G4UIcommandTree::~G4UIcommandTree()
{
  int i;
  int n_treeEntry = tree.entries();
  for( i=0; i < n_treeEntry; i++ )
  { delete tree[i]; }
}

int G4UIcommandTree::operator==(const G4UIcommandTree &right) const
{
  return ( pathName == right.GetPathName() );
}

int G4UIcommandTree::operator!=(const G4UIcommandTree &right) const
{
  return ( pathName != right.GetPathName() );
}

void G4UIcommandTree::AddNewCommand(G4UIcommand *newCommand)
{
  G4String commandPath = newCommand->GetCommandPath();
  G4String remainingPath = commandPath;
  remainingPath.remove(0,pathName.length());
  if( remainingPath.isNull() )
  {
    guidance = newCommand;
    return;
  }
  int i = remainingPath.first('/');
  if( i == RW_NPOS )
  {
    // Find command
    int n_commandEntry = command.entries();
    for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
    {
      if( remainingPath == command[i_thCommand]->GetCommandName() )
      { return; }
    }
    command.insert( newCommand );
    return;
  }
  else
  {
    // Find path
    G4String nextPath = pathName;
    nextPath.append(remainingPath(0,i+1));
    int n_treeEntry = tree.entries();
    for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
    {
      if( nextPath == tree[i_thTree]->GetPathName() )
      { 
	tree[i_thTree]->AddNewCommand( newCommand );
	return; 
      }
    }
    G4UIcommandTree * newTree = new G4UIcommandTree( nextPath );
    tree.insert( newTree );
    newTree->AddNewCommand( newCommand );
    return;
  }
}

void G4UIcommandTree::RemoveCommand(G4UIcommand *aCommand)
{
  G4String commandPath = aCommand->GetCommandPath();
  G4String remainingPath = commandPath;
  remainingPath.remove(0,pathName.length());
  if( remainingPath.isNull() )
  {
    guidance = NULL;
  }
  else
  {
    int i = remainingPath.first('/');
    if( i == RW_NPOS )
    {
      // Find command
      int n_commandEntry = command.entries();
      for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
      {
        if( remainingPath == command[i_thCommand]->GetCommandName() )
        { 
          command.remove(command[i_thCommand]); 
          break;
        }
      }
    }
    else
    {
      // Find path
      G4String nextPath = pathName;
      nextPath.append(remainingPath(0,i+1));
      int n_treeEntry = tree.entries();
      for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
      {
        if( nextPath == tree[i_thTree]->GetPathName() )
        { 
    	  tree[i_thTree]->RemoveCommand( aCommand );
    	  int n_commandRemain = tree[i_thTree]->GetCommandEntry();
    	  if(n_commandRemain==0)
    	  {
    	    G4UIcommandTree * emptyTree = tree[i_thTree];
    	    tree.remove(tree[i_thTree]);
    	    delete emptyTree;
    	  }
    	  break;
        }
      }
    }
  }
}

G4UIcommand * G4UIcommandTree::FindPath(G4String commandPath)
{
  if( commandPath.index( pathName ) == RW_NPOS )
  { return NULL; }
  G4String remainingPath = commandPath;
  remainingPath.remove(0,pathName.length());
  int i = remainingPath.first('/');
  if( i == RW_NPOS )
  {
    // Find command
    int n_commandEntry = command.entries();
    for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
    {
      if( remainingPath == command[i_thCommand]->GetCommandName() )
      { return command[i_thCommand]; }
    }
  }
  else
  {
    // Find path
    G4String nextPath = pathName;
    nextPath.append(remainingPath(0,i+1));
    int n_treeEntry = tree.entries();
    for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
    {
      if( nextPath == tree[i_thTree]->GetPathName() )
      { return tree[i_thTree]->FindPath( commandPath ); }
    }
  }
  return NULL;
}

void G4UIcommandTree::ListCurrent()
{
  G4cout << "Command directory path : " << pathName << endl;
  if( guidance != NULL ) guidance->List();
  int i = 0;
  G4cout << " Sub-directories : " << endl;
  int n_treeEntry = tree.entries();
  for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
  {
    G4cout << "   " << tree[i_thTree]->GetPathName() 
	 << "   " << tree[i_thTree]->GetTitle() << endl;
  }
  G4cout << " Commands : " << endl;
  int n_commandEntry = command.entries();
  for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
  {
    G4cout << "   " << command[i_thCommand]->GetCommandName() 
	 << " * " << command[i_thCommand]->GetTitle() << endl;
  }
}

void G4UIcommandTree::ListCurrentWithNum()
{
  G4cout << "Command directory path : " << pathName << endl;
  if( guidance != NULL ) guidance->List();
  int i = 0;
  G4cout << " Sub-directories : " << endl;
  int n_treeEntry = tree.entries();
  for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
  {
    i++;
    G4cout << " " << i << ") " << tree[i_thTree]->GetPathName() 
	 << "   " << tree[i_thTree]->GetTitle() << endl;
  }
  G4cout << " Commands : " << endl;
  int n_commandEntry = command.entries();
  for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
  {
    i++;
    G4cout << " " << i << ") " << command[i_thCommand]->GetCommandName() 
	 << " * " << command[i_thCommand]->GetTitle() << endl;
  }
}

void G4UIcommandTree::List()
{
  ListCurrent();
  int n_commandEntry = command.entries();
  for( int i_thCommand = 0; i_thCommand < n_commandEntry; i_thCommand++ )
  {
    command[i_thCommand]->List();
  }
  int n_treeEntry = tree.entries();
  for( int i_thTree = 0; i_thTree < n_treeEntry; i_thTree++ )
  {
    tree[i_thTree]->List();
  }
}


