// fcheckbox.cpp
// class FCheckBox

#include "fcheckbox.h"


//----------------------------------------------------------------------
// class FCheckBox
//----------------------------------------------------------------------

// constructor and destructor
//----------------------------------------------------------------------
FCheckBox::FCheckBox(FWidget* parent) : FToggleButton(parent)
{
}

//----------------------------------------------------------------------
FCheckBox::FCheckBox ( const FString& txt,
                       FWidget* parent ) : FToggleButton(txt, parent)
{
}

//----------------------------------------------------------------------
FCheckBox::~FCheckBox()  // destructor
{
}


// private methods of FCheckBox
//----------------------------------------------------------------------
void FCheckBox::draw()
{
  setUpdateVTerm(false);
  drawCheckButton();
  drawLabel();
  setUpdateVTerm(true);

  FToggleButton::draw();
}

//----------------------------------------------------------------------
void FCheckBox::drawCheckButton()
{
  if ( ! isVisible() )
    return;
  gotoxy (xpos+xmin-1, ypos+ymin-1);
  setColor (foregroundColor, backgroundColor);
  if ( checked )
  {
    if ( isNewFont() )
      print (CHECKBOX_ON);
    else
    {
      print ('[');
      print ('x');
      print (']');
    }
  }
  else
  {
    if ( isNewFont() )
      print (CHECKBOX);
    else
    {
      print ('[');
      print (' ');
      print (']');
    }
  }
}