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
  \class SoDirectionalLightElement Inventor/eleemnts/SoDirectionalLightElement.h
  \brief The SoDirectionalLightElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoDirectionalLightElement.h>

#include <Inventor/SoType.h>

#include <assert.h>

//$ BEGIN TEMPLATE ElementSource( SoDirectionalLightElement )

/*!
  \var SoDirectionalLightElement::classTypeId

  This is the static class type identifier for the
  SoDirectionalLightElement class.
*/

SoType SoDirectionalLightElement::classTypeId = SoType::badType();

/*!
  This method returns the SoType object for the element class of
  the instance.
*/
SoType
SoDirectionalLightElement::getClassTypeId(void)
{
  return SoDirectionalLightElement::classTypeId;
}

/*!
  This static method creates an object instance of the SoDirectionalLightElement class.
*/
void *
SoDirectionalLightElement::createInstance(void)
{
  return (void *) new SoDirectionalLightElement;
}

/*!
  \var SoDirectionalLightElement::classStackIndex

  This is the static state stack index for the
  SoDirectionalLightElement class.
*/
int SoDirectionalLightElement::classStackIndex;

/*!
  This static method returns the state stack index for the SoDirectionalLightElement class.
*/
int
SoDirectionalLightElement::getClassStackIndex(void)
{
  return SoDirectionalLightElement::classStackIndex;
}
//$ END TEMPLATE ElementSource

/*!
  This static method initializes static data for the
  SoDirectionalLightElement class.
*/

void
SoDirectionalLightElement::initClass( // static
    void )
{
//$ BEGIN TEMPLATE InitElementSource( SoDirectionalLightElement )
  assert(SoDirectionalLightElement::classTypeId == SoType::badType());
  assert(inherited::getClassTypeId() != SoType::badType());

  SoDirectionalLightElement::classTypeId = SoType::createType(
    inherited::getClassTypeId(),
    "SoDirectionalLightElement",
    &SoDirectionalLightElement::createInstance);

  if (inherited::classStackIndex < 0) {
    SoDirectionalLightElement::classStackIndex =
      createStackIndex( SoDirectionalLightElement::classTypeId );
  } else {
    SoDirectionalLightElement::classStackIndex =
      inherited::classStackIndex;
  }
//$ END TEMPLATE InitElementSource
} // initClass()

/*!
  This static method cleans up static data for the
  SoDirectionalLightElement class.
*/

void
SoDirectionalLightElement::cleanClass( // static
    void )
{
//$ BEGIN TEMPLATE CleanElementSource( SoDirectionalLightElement )
//$ END TEMPLATE CleanElementSource
} // cleanClass()

/*!
  A constructor.  Can't be used directly.

  \sa void * SoDirectionalLightElement::createInstance( void )
*/

SoDirectionalLightElement::SoDirectionalLightElement(
    void )
{
    setTypeId( SoDirectionalLightElement::classTypeId );
    setStackIndex( SoDirectionalLightElement::classStackIndex );
} // SoDirectionalLightElement()

/*!
  The destructor.
*/

SoDirectionalLightElement::~SoDirectionalLightElement(
    void )
{
} // ~SoDirectionalLightElement()

//! FIXME: write doc.

void
SoDirectionalLightElement::init( // virtual
    SoState * state )
{
    inherited::init( state );
} // init()

//! FIXME: write doc.

void
SoDirectionalLightElement::push( // virtual
    SoState * state )
{
    inherited::push( state );
} // push()

//! FIXME: write doc.

void
SoDirectionalLightElement::pop( // virtual
    SoState * state,
    const SoElement * prevTopElement )
{
    inherited::pop( state, prevTopElement );
} // pop()

//! FIXME: write doc.

SbBool 
SoDirectionalLightElement::matches(
    const SoElement * element ) const
{
  element;
  assert(0 && "FIXME: not implemented");
  return FALSE;
}

//! FIXME: write doc.

SoElement *
SoDirectionalLightElement::copyMatchInfo( void ) const
{
  assert(0 && "FIXME: not implemented");
  return FALSE;
}

