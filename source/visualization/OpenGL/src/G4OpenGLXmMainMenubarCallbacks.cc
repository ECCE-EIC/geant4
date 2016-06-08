// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenGLXmMainMenubarCallbacks.cc,v 1.3 1999/01/11 00:47:49 allison Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// Andrew Walkden  16th April 1997
// G4OpenGLXmMainMenubarCallbacks : 
//                       Collection of callback functions
//                       to handle events generated by the
//                       main OpenGLXm window menubar.
//
// See G4OpenGLXmMainMenubarCallbacks.hh for more information.


#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#include "G4Xt.hh"

#include "G4OpenGLXmViewer.hh"

#include "G4OpenGLXmRadioButton.hh"
#include "G4OpenGLXmSliderBar.hh"
#include "G4OpenGLXmFourArrowButtons.hh"
#include "G4OpenGLXmTextField.hh"
#include "G4OpenGLXmPushButton.hh"
#include "G4OpenGLXmBox.hh"
#include "G4OpenGLXmFramedBox.hh"
#include "G4OpenGLXmTopLevelShell.hh"
#include "G4OpenGLXmSeparator.hh"

#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif

void G4OpenGLXmViewer::actions_callback (Widget w, 
				       XtPointer clientData,
				       XtPointer)
{
  
  G4OpenGLXmViewer* pView;
  G4long choice = (G4long)clientData;
  
  
  XtVaGetValues (XtParent(w), 
		 XmNuserData, &pView, 
		 NULL);
  
  switch (choice) {
    
  case 0:
    
    {
      
      if (!pView->fprotation_top) {
	const int rot_len = 50;
	char* frot_Name = new char [rot_len];
	ostrstream rot_ost (frot_Name, rot_len);
	rot_ost.seekp (ios::beg);
	rot_ost << pView->GetScene()->GetSceneId() << '-' << pView->fViewId << ends;
	
	pView->fprotation_top = new G4OpenGLXmTopLevelShell (pView, 
							     frot_Name);
	pView->fprotation_button_box = new G4OpenGLXmBox ("Rotation button box", True);
	
	pView->fprotation_top->AddChild (pView->fprotation_button_box);
	
	XtCallbackRec* rot_cb_list = new XtCallbackRec[2];
	rot_cb_list[0].callback = G4OpenGLXmViewer::set_rot_subject_callback;
	rot_cb_list[0].closure = pView; 
	rot_cb_list[1].callback = NULL;
	
	pView->fprotation_button1 = new G4OpenGLXmRadioButton ("Object",
							       rot_cb_list,
							       True,
							       0);
	
	pView->fprotation_button2 = new G4OpenGLXmRadioButton ("Camera",
							       rot_cb_list,
							       False,
							       1);
	
	pView->fprotation_button_box->AddChild (pView->fprotation_button1);
	pView->fprotation_button_box->AddChild (pView->fprotation_button2);
	
	pView->fprotation_slider_box = new G4OpenGLXmBox ("Rotation slider box", False);
	pView->fprotation_top->AddChild (pView->fprotation_slider_box);
	
	XtCallbackRec* rot_slider_list = new XtCallbackRec[2];
	rot_slider_list[0].callback = G4OpenGLXmViewer::set_rot_sens_callback;
	rot_slider_list[0].closure = pView; 
	rot_slider_list[1].callback = NULL;
	
	pView->fprotation_slider = new G4OpenGLXmSliderBar ("Rotation slider",
							    rot_slider_list,
							    True,
							    2,
							    pView->rot_sens,
							    pView->rot_sens_limit,
							    0);
	pView->fprotation_slider_box->AddChild (pView->fprotation_slider);
	
	pView->fprotation_arrow_box = new G4OpenGLXmBox ("Rotation arrow box", False);
	pView->fprotation_top->AddChild (pView->fprotation_arrow_box);
	
	XtCallbackRec** rotation_callbacks = new XtCallbackRec*[4];
	for (G4int i = 0; i < 4; i++) {
	  rotation_callbacks[i] = new XtCallbackRec[2];
	}
	rotation_callbacks[0][0].callback = G4OpenGLXmViewer::phi_rotation_callback;
	rotation_callbacks[0][0].closure =  pView;
	rotation_callbacks[0][1].callback	= NULL;
	
	rotation_callbacks[1][0].callback = G4OpenGLXmViewer::phi_rotation_callback;
	rotation_callbacks[1][0].closure =  pView;
	rotation_callbacks[1][1].callback	= NULL;
	
	rotation_callbacks[2][0].callback = G4OpenGLXmViewer::theta_rotation_callback;
	rotation_callbacks[2][0].closure =  pView;
	rotation_callbacks[2][1].callback	= NULL;
	
	rotation_callbacks[3][0].callback = G4OpenGLXmViewer::theta_rotation_callback;
	rotation_callbacks[3][0].closure =  pView;
	rotation_callbacks[3][1].callback	= NULL;
	
	pView->fprotation_arrow = new G4OpenGLXmFourArrowButtons (rotation_callbacks);
	
	pView->fprotation_arrow_box->AddChild (pView->fprotation_arrow);
	
	pView->fprotation_top->Realize ();
      }
      break;
      
    }
  
  
  case 1:
    {

      if (!pView->fppanning_top) {
	const int pan_len = 50;
	char* fpan_Name = new char [pan_len];
	ostrstream pan_ost (fpan_Name, pan_len);
	pan_ost.seekp (ios::beg);
	pan_ost << pView->GetScene()->GetSceneId() << '-' << pView->fViewId << ends;
	
	pView->fppanning_top = new G4OpenGLXmTopLevelShell (pView, 
							    fpan_Name);
	
	pView->fppanning_box = new G4OpenGLXmFramedBox ("Pan up-down-left-right", 
							False);
	
	pView->fppanning_top->AddChild (pView->fppanning_box);
	
	XtCallbackRec** pan_callbacks = new XtCallbackRec*[4];
	for (G4int i = 0; i < 4; i++) {
	  pan_callbacks[i] = new XtCallbackRec[2];
	}
	pan_callbacks[0][0].callback = G4OpenGLXmViewer::pan_up_down_callback;
	pan_callbacks[0][0].closure = pView; 
	pan_callbacks[0][1].callback = NULL;
	
	pan_callbacks[1][0].callback = G4OpenGLXmViewer::pan_up_down_callback;
	pan_callbacks[1][0].closure = pView; 
	pan_callbacks[1][1].callback = NULL;
	
	pan_callbacks[2][0].callback = G4OpenGLXmViewer::pan_left_right_callback;
	pan_callbacks[2][0].closure = pView; 
	pan_callbacks[2][1].callback = NULL;
	
	pan_callbacks[3][0].callback = G4OpenGLXmViewer::pan_left_right_callback;
	pan_callbacks[3][0].closure = pView; 
	pan_callbacks[3][1].callback = NULL;
	
	pView->fppanning_arrows = new G4OpenGLXmFourArrowButtons (pan_callbacks);
	
	pView->fppanning_box->AddChild (pView->fppanning_arrows);
	
	XtCallbackRec* pan_slider_list = new XtCallbackRec[2];
	pan_slider_list[0].callback = G4OpenGLXmViewer::set_pan_sens_callback;
	pan_slider_list[0].closure = pView; 
	pan_slider_list[1].callback = NULL;
	
	pView->fppanning_slider = new G4OpenGLXmSliderBar ("Panning slider",
							   pan_slider_list,
							   True,
							   2,
							   pView->pan_sens = pView->GetScene()->GetScene()->GetExtent().GetExtentRadius() / 10.0,
							   pView->pan_sens_limit = pView->GetScene()->GetScene()->GetExtent().GetExtentRadius(),
							   0);
	pView->fppanning_box->AddChild (pView->fppanning_slider);
	
	pView->fpzoom_box = new G4OpenGLXmFramedBox ("Zoom", 
						     False);      
	pView->fppanning_top->AddChild (pView->fpzoom_box);
	
	XtCallbackRec* zoom_slider_list = new XtCallbackRec[2];
	zoom_slider_list[0].callback = G4OpenGLXmViewer::zoom_callback;
	zoom_slider_list[0].closure = pView; 
	zoom_slider_list[1].callback = NULL;
	
	pView->fpzoom_slider = new G4OpenGLXmSliderBar ("Zoom slider",
							zoom_slider_list,
							True,
							2,
							pView->fVP.GetZoomFactor(),
							pView->zoom_high,
							pView->zoom_low);
	pView->fpzoom_box->AddChild (pView->fpzoom_slider);
	
	pView->fpdolly_box = new G4OpenGLXmFramedBox ("Dolly", 
						      False);      
	pView->fppanning_top->AddChild (pView->fpdolly_box);
	
	XtCallbackRec* dolly_slider_list = new XtCallbackRec[2];
	dolly_slider_list[0].callback = G4OpenGLXmViewer::dolly_callback;
	dolly_slider_list[0].closure = pView; 
	dolly_slider_list[1].callback = NULL;
	
	pView->fpdolly_slider = new G4OpenGLXmSliderBar ("Dolly slider",
							 dolly_slider_list,
							 True,
							 2,
							 pView->fVP.GetDolly(),
							 pView->dolly_high = pView->GetScene()->GetScene()->GetExtent().GetExtentRadius(),
							 pView->dolly_low = -(pView->GetScene()->GetScene()->GetExtent().GetExtentRadius()));
	//							 pView->dolly_high,
	//							 pView->dolly_low);
	pView->fpdolly_box->AddChild (pView->fpdolly_slider);
	
	pView->fppanning_top->Realize ();
      }

      break;
      
    }
  case 2:
    {
      
      if (!pView->fpsetting_top) {
	const int set_len = 50;
	char* fset_Name = new char [set_len];
	ostrstream set_ost (fset_Name, set_len);
	set_ost.seekp (ios::beg);
	set_ost << pView->GetScene()->GetSceneId() << '-' << pView->fViewId << ends;
	
	pView->fpsetting_top = new G4OpenGLXmTopLevelShell(pView,
							   fset_Name);
	
	pView->fpsetting_box = new G4OpenGLXmFramedBox ("Set values for control panels",
							False);
	pView->fpsetting_top->AddChild (pView->fpsetting_box);
	
	pView->fppan_set = new G4OpenGLXmTextField ("Upper limit of pan sensitivity",
						    &(pView->pan_sens_limit));
	
	pView->fprot_set = new G4OpenGLXmTextField ("Upper limit of rotation sensitivity",
						    &(pView->rot_sens_limit));
	
	pView->fpzoom_upper = new G4OpenGLXmTextField ("Upper limit of zoom",
						       &(pView->zoom_high));
	
	pView->fpzoom_lower = new G4OpenGLXmTextField ("Lower limit of zoom",
						       &(pView->zoom_low));
	
	pView->fpdolly_upper = new G4OpenGLXmTextField ("Upper limit of dolly",
							&(pView->dolly_high));
	
	pView->fpdolly_lower = new G4OpenGLXmTextField ("Lower limit of dolly",
							&(pView->dolly_low));
	
	XtCallbackRec* ok_list = new XtCallbackRec[2];
	ok_list[0].callback = G4OpenGLXmViewer::update_panels_callback;
	ok_list[0].closure = pView; 
	ok_list[1].callback = NULL;
	
	
	pView->fpok_button = new G4OpenGLXmPushButton ("ok",
						       ok_list);
	
	pView->fpsetting_box->AddChild (pView->fppan_set);
	pView->fpsetting_box->AddChild (pView->fprot_set);
	pView->fpsetting_box->AddChild (pView->fpzoom_upper);
	pView->fpsetting_box->AddChild (pView->fpzoom_lower);
	pView->fpsetting_box->AddChild (pView->fpdolly_upper);
	pView->fpsetting_box->AddChild (pView->fpdolly_lower);
	pView->fpsetting_box->AddChild (pView->fpok_button);
	
	pView->fpsetting_top->Realize ();
	
      }

      break;
    }
  
  default:
    G4Exception("Unrecognised widget child of control_callback");
  }
  
  return;
}



void G4OpenGLXmViewer::misc_callback (Widget w, 
				    XtPointer clientData, 
				    XtPointer) 
{
  G4OpenGLXmViewer* pView;
  G4long choice = (G4long)clientData;
  XtVaGetValues (XtParent(w), 
		 XmNuserData, &pView, 
		 NULL);
  
  switch (choice) {
    
  case 0:
    {

      if (!pView->fpmiscellany_top) {
	
	const int misc_len = 50;
	char* fmisc_Name = new char [misc_len];
	ostrstream misc_ost (fmisc_Name, misc_len);
	misc_ost.seekp (ios::beg);
	misc_ost << pView->GetScene()->GetSceneId() << '-' << pView->fViewId << ends;
	
	pView->fpmiscellany_top = new G4OpenGLXmTopLevelShell (pView, 
							       fmisc_Name);
	pView->fpwobble_box = new G4OpenGLXmFramedBox ("Wobble view",
						       True);
	pView->fpmiscellany_top->AddChild (pView->fpwobble_box);
	
	XtCallbackRec* wob_cb_list = new XtCallbackRec[2];
	wob_cb_list[0].callback = G4OpenGLXmViewer::wobble_callback;
	wob_cb_list[0].closure = pView; 
	wob_cb_list[1].callback = NULL;
	
	
	pView->fpwobble_button = new G4OpenGLXmPushButton ("Wobble",
							   wob_cb_list);
	
	XtCallbackRec* wobble_slider_list = new XtCallbackRec[2];
	wobble_slider_list[0].callback = G4OpenGLXmViewer::set_wob_sens_callback;
	wobble_slider_list[0].closure = pView; 
	wobble_slider_list[1].callback = NULL;
	
	pView->fpwobble_slider = new G4OpenGLXmSliderBar ("Wobble slider",
							  wobble_slider_list,
							  True,
							  0,
							  20,
							  50,
							  0);
	pView->fpwobble_box->AddChild (pView->fpwobble_button);
	pView->fpwobble_box->AddChild (pView->fpwobble_slider);
	
	pView->fpreset_box = new G4OpenGLXmFramedBox ("Reset view",
						      True);
	pView->fpmiscellany_top->AddChild (pView->fpreset_box);
	
	XtCallbackRec* rst_cb_list = new XtCallbackRec[3];
	rst_cb_list[0].callback = G4OpenGLXmViewer::reset_callback;
	rst_cb_list[0].closure = pView; 
	rst_cb_list[1].callback = G4OpenGLXmViewer::update_panels_callback;
	rst_cb_list[1].closure = pView; 
	rst_cb_list[2].callback = NULL;
	
	pView->fpreset_button = new G4OpenGLXmPushButton ("Reset",
							  rst_cb_list);
	
	pView->fpreset_box->AddChild (pView->fpreset_button);
	
	pView->fpproj_style_box = new G4OpenGLXmFramedBox ("Projection style",
							   True);
	pView->fpmiscellany_top->AddChild (pView->fpproj_style_box);
	
	XtCallbackRec* proj_cb_list = new XtCallbackRec[2];
	proj_cb_list[0].callback = G4OpenGLXmViewer::projection_callback;
	proj_cb_list[0].closure = pView; 
	proj_cb_list[1].callback = NULL;
	
	pView->fporthogonal_button = new G4OpenGLXmRadioButton ("Orthographic",
								proj_cb_list,
								pView->fVP.GetFieldHalfAngle() > 0. ? False : True,
								0);
	
	pView->fpperspective_button = new G4OpenGLXmRadioButton ("Perspective",
								 proj_cb_list,
								 pView->fVP.GetFieldHalfAngle() > 0. ? True : False,
								 1);
	
	pView->fpfov_text = new G4OpenGLXmTextField ("Field of view 0.1 -> 89.5 degrees.",
						     &(pView->fov));
	
	pView->fpproj_style_box->AddChild (pView->fpperspective_button);
	pView->fpproj_style_box->AddChild (pView->fporthogonal_button);
	pView->fpproj_style_box->AddChild (pView->fpfov_text);
	
	pView->fpmiscellany_top->Realize ();

      }
      
      break;
    }
  
  case 1:
    {
      G4Xt::getInstance () -> RequireExitSecondaryLoop (OGL_EXIT_CODE);
      break;
    }
  
  case 2:
    {
      if (!pView->fpprint_top) {
	
	const int print_len = 50;
	char* fprint_Name = new char [print_len];
	ostrstream print_ost (fprint_Name, print_len);
	print_ost.seekp (ios::beg);
	print_ost << pView->GetScene()->GetSceneId() << '-' << pView->fViewId << ends;
	
	pView->fpprint_top = new G4OpenGLXmTopLevelShell (pView, 
							  fprint_Name);

	pView->fpprint_box = new G4OpenGLXmFramedBox ("Create EPS file of current view",
						       False);

	pView->fpprint_top->AddChild (pView->fpprint_box);
	
	pView->fpprint_col_box = new G4OpenGLXmFramedBox ("Colour choice",
							  True);
	pView->fpprint_top->AddChild (pView->fpprint_col_box);

	XtCallbackRec* prcol_cb_list = new XtCallbackRec[2];
	prcol_cb_list[0].callback = G4OpenGLXmViewer::set_print_colour_callback;
	prcol_cb_list[0].closure = pView; 
	prcol_cb_list[1].callback = NULL;
	
	pView->fpprint_col_radio1 = new G4OpenGLXmRadioButton ("Black and white",
							       prcol_cb_list,
							       pView->print_colour==false ? True : False,
							       0);
	
	pView->fpprint_col_radio2 = new G4OpenGLXmRadioButton ("Colour",
							       prcol_cb_list,
							       pView->print_colour==true ? True : False,
							       1);
	
	pView->fpprint_col_box->AddChild (pView->fpprint_col_radio1);
	pView->fpprint_col_box->AddChild (pView->fpprint_col_radio2);

	pView->fpprint_style_box = new G4OpenGLXmFramedBox ("File type",
							    True);
	pView->fpprint_top->AddChild (pView->fpprint_style_box);

	XtCallbackRec* prsty_cb_list = new XtCallbackRec[2];
	prsty_cb_list[0].callback = G4OpenGLXmViewer::set_print_style_callback;
	prsty_cb_list[0].closure = pView; 
	prsty_cb_list[1].callback = NULL;
	
	pView->fpprint_style_radio1 = new G4OpenGLXmRadioButton ("Screen dump (pixmap)",
								 prsty_cb_list,
								 pView->vectored_ps==false ? True : False,
								 0);
	
	pView->fpprint_style_radio2 = new G4OpenGLXmRadioButton ("PostScript",
								 prsty_cb_list,
								 pView->vectored_ps==true ? True : False,
								 1);
	
	pView->fpprint_style_box->AddChild (pView->fpprint_style_radio1);
	pView->fpprint_style_box->AddChild (pView->fpprint_style_radio2);
	
	pView->fpprint_text = new G4OpenGLXmTextField ("Name of .eps file to save",
						       (pView->print_string));
	pView->fpprint_box->AddChild (pView->fpprint_text);	
	
	pView->fpprint_line = new G4OpenGLXmSeparator ();
	pView->fpprint_box->AddChild (pView->fpprint_line);

	XtCallbackRec* pri_cb_list = new XtCallbackRec[2];
	pri_cb_list[0].callback = G4OpenGLXmViewer::print_callback;
	pri_cb_list[0].closure = pView; 
	pri_cb_list[1].callback = NULL;
	
	
	pView->fpprint_button = new G4OpenGLXmPushButton ("Create EPS file",
							  pri_cb_list);
	
	pView->fpprint_box->AddChild (pView->fpprint_button);
	pView->fpprint_top->Realize ();

      }
      
      ///ajw
      break;
    }
  
  default:
    G4Exception("Unrecognised widget child of misc_callback.");
  }
  
  return;
  
}

void G4OpenGLXmViewer::set_wob_sens_callback (Widget w, 
					    XtPointer clientData, 
					    XtPointer callData) 
{
  XmScaleCallbackStruct *cbs = (XmScaleCallbackStruct*) callData;
  G4OpenGLXmViewer* pView = (G4OpenGLXmViewer*) clientData;
  short dp = -1;
  G4float ten_to_the_dp = 10.;
  
  XtVaGetValues (w, 
		 XmNdecimalPoints, &dp,
		 NULL);
  
  if (dp == 0) {
    ten_to_the_dp = 1.;
  } else if ( dp > 0) {
    for (G4int i = 1; i < (G4int)dp; i++) {
      ten_to_the_dp *= 10.;
    }
  } else {
    G4Exception("Bad value returned for dp in set_rot_sens_callback");
  }
  
  pView->wob_sens = (G4float)(cbs->value) / ten_to_the_dp;
}  

void G4OpenGLXmViewer::update_panels_callback (Widget, 
					     XtPointer clientData, 
					     XtPointer) 
{
  G4OpenGLXmViewer* pView = (G4OpenGLXmViewer*) clientData;
  
  if (pView->fppanning_slider) {
    pView->fppanning_slider->SetMaxValue (pView->pan_sens_limit);
  }
  if (pView->fprotation_slider) {
    pView->fprotation_slider->SetMaxValue (pView->rot_sens_limit);
  }
  
  if (pView->fpzoom_slider) {
    pView->fpzoom_slider->SetMaxValue (pView->zoom_high);
    pView->fpzoom_slider->SetMinValue (pView->zoom_low);
    pView->fpzoom_slider->SetInitialValue (pView->fVP.GetZoomFactor());
  }
  
  if (pView->fpdolly_slider) {
    pView->fpdolly_slider->SetMaxValue (pView->dolly_high);
    pView->fpdolly_slider->SetMinValue (pView->dolly_low);
  }
}

#endif
