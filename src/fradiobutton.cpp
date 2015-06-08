// fradiobutton.cpp
// class FRadioButton

#include "fapp.h"
#include "fradiobutton.h"


//----------------------------------------------------------------------
// class FRadioButton
//----------------------------------------------------------------------

// constructor and destructor
//----------------------------------------------------------------------
FRadioButton::FRadioButton(FWidget* parent) : FToggleButton(parent)
{
}

//----------------------------------------------------------------------
FRadioButton::FRadioButton ( const FString& txt,
                             FWidget* parent ) : FToggleButton(txt, parent)
{
}

//----------------------------------------------------------------------
FRadioButton::~FRadioButton()  // destructor
{
}


// private methods of FRadioButton
//----------------------------------------------------------------------
void FRadioButton::draw()
{
  setUpdateVTerm(false);
  drawRadioButton();
  drawLabel();
  setUpdateVTerm(true);

  FToggleButton::draw();
}

//----------------------------------------------------------------------
void FRadioButton::drawRadioButton()
{
  if ( ! isVisible() )
    return;
  gotoxy (xpos+xmin-1, ypos+ymin-1);
  setColor (foregroundColor, backgroundColor);
  if ( checked )
  {
    if ( isNewFont() )
      print (CHECKED_RADIO_BUTTON);
    else
    {
      print ('(');
      print (fc::Bullet);  // Bullet •
      print (')');
    }
  }
  else
  {
    if ( isNewFont() )
      print (RADIO_BUTTON);
    else
    {
      print ('(');
      print (' ');
      print (')');
    }
  }
}
