/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoPolygonOffsetElement Inventor/elements/SoPolygonOffsetElement.h
  \brief The SoPolygonOffsetElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoPolygonOffsetElement.h>

#include <Inventor/SbName.h>

#include <assert.h>

/*!
  \fn SoPolygonOffsetElement::Style

  FIXME: write doc.
*/

/*!
  \fn SoPolygonOffsetElement::style

  FIXME: write doc.
*/

/*!
  \fn SoPolygonOffsetElement::active

  FIXME: write doc.
*/

/*!
  \fn SoPolygonOffsetElement::offsetfactor

  FIXME: write doc.
*/

/*!
  \fn SoPolygonOffsetElement::offsetunits

  FIXME: write doc.
*/

//$ BEGIN TEMPLATE ElementSource( SoPolygonOffsetElement )

/*!
  \var SoPolygonOffsetElement::classTypeId

  This is the static class type identifier for the
  SoPolygonOffsetElement class.
*/

SoType SoPolygonOffsetElement::classTypeId = SoType::badType();

/*!
  This method returns the SoType object for the element class of
  the instance.
*/
SoType
SoPolygonOffsetElement::getClassTypeId(void)
{
  return SoPolygonOffsetElement::classTypeId;
}

/*!
  This static method creates an object instance of the SoPolygonOffsetElement class.
*/
void *
SoPolygonOffsetElement::createInstance(void)
{
  return (void *) new SoPolygonOffsetElement;
}

/*!
  \var SoPolygonOffsetElement::classStackIndex

  This is the static state stack index for the
  SoPolygonOffsetElement class.
*/
int SoPolygonOffsetElement::classStackIndex;

/*!
  This static method returns the state stack index for the SoPolygonOffsetElement class.
*/
int
SoPolygonOffsetElement::getClassStackIndex(void)
{
  return SoPolygonOffsetElement::classStackIndex;
}
//$ END TEMPLATE ElementSource

/*!
  This static method initializes static data for the SoPolygonOffsetElement
  class.
*/

void
SoPolygonOffsetElement::initClass( // static
    void )
{
//$ BEGIN TEMPLATE InitElementSource( SoPolygonOffsetElement )
  assert(SoPolygonOffsetElement::classTypeId == SoType::badType());
  assert(inherited::getClassTypeId() != SoType::badType());

  SoPolygonOffsetElement::classTypeId = SoType::createType(
    inherited::getClassTypeId(),
    "SoPolygonOffsetElement",
    &SoPolygonOffsetElement::createInstance);

  if (inherited::classStackIndex < 0) {
    SoPolygonOffsetElement::classStackIndex =
      createStackIndex( SoPolygonOffsetElement::classTypeId );
  } else {
    SoPolygonOffsetElement::classStackIndex =
      inherited::classStackIndex;
  }
//$ END TEMPLATE InitElementSource
} // initClass()

/*!
  This static method cleans up static data for the SoPolygonOffsetElement class.
*/

void
SoPolygonOffsetElement::cleanClass( // static
    void )
{
//$ BEGIN TEMPLATE CleanElementSource( SoPolygonOffsetElement )
//$ END TEMPLATE CleanElementSource
} // cleanClass()

/*!
  A constructor.  Can't be used directly.

  \sa void * SoPolygonOffsetElement::createInstance( void )
*/

SoPolygonOffsetElement::SoPolygonOffsetElement( // protected
    void )
{
    setTypeId( SoPolygonOffsetElement::classTypeId );
    setStackIndex( SoPolygonOffsetElement::classStackIndex );
} // SoPolygonOffsetElement()

/*!
  The destructor.
*/

SoPolygonOffsetElement::~SoPolygonOffsetElement( // virtual
    void )
{
} // ~SoPolygonOffsetElement()

//! FIXME: write doc.

void
SoPolygonOffsetElement::init( // virtual
    SoState * state )
{
  inherited::init( state );

  SoPolygonOffsetElement::getDefault(this->offsetfactor,
				     this->offsetunits,
				     this->style,
				     this->active);
} // init()

//! FIXME: write doc.

void
SoPolygonOffsetElement::push( // virtual
    SoState * state )
{
    inherited::push( state );
} // push()

//! FIXME: write doc.

SbBool
SoPolygonOffsetElement::matches( // virtual
    const SoElement * element ) const
{
  assert(0 && "FIXME: not implemented");
  return FALSE;
} // matches()

//! FIXME: write doc.

SoElement *
SoPolygonOffsetElement::copyMatchInfo( // virtual
    void ) const
{
  assert(0 && "FIXME: not implemented");
  return NULL;
} // copyMatchInfo()

//! FIXME: write doc.

void
SoPolygonOffsetElement::set( // static
    SoState * state,
    SoNode * node, float factor, float units, Style styles, SbBool on)
{
  SoPolygonOffsetElement *elem = (SoPolygonOffsetElement *)
    SoElement::getElement(state, classStackIndex);
  elem->setElt(factor, units, styles, on);

  // FIXME: what are we supposed to do with "node"? Pass on to
  // SoReplacedElement? 990307 mortene.
}

//! FIXME: write doc.

void
SoPolygonOffsetElement::get( // static
    SoState * state,
    float & factor, float & units, Style & styles, SbBool & on)
{
  const SoPolygonOffsetElement *elem = (SoPolygonOffsetElement *)
    SoElement::getConstElement(state, classStackIndex);

  factor = elem->offsetfactor;
  units = elem->offsetunits;
  styles = elem->style;
  on = elem->active;
}

//! FIXME: write doc.

void
SoPolygonOffsetElement::setElt(float factor, float units,
			       Style styles, SbBool on)
{
  this->offsetfactor = factor;
  this->offsetunits = units;
  this->style = styles;
  this->active = on;
}

//! FIXME: write doc.

void
SoPolygonOffsetElement::getDefault(float & factor, float & units,
				   Style & styles, SbBool & on)
{
  factor = 0.0f;
  units = 0.0f;
  styles = SoPolygonOffsetElement::FILLED;
  on = FALSE;
}

