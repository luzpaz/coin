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
  \class SoIndexedNurbsSurface SoIndexedNurbsSurface.h Inventor/nodes/SoIndexedNurbsSurface.h
  \brief The SoIndexedNurbsSurface class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoIndexedNurbsSurface.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbName.h>

/*!
  \var SoSFInt32 SoIndexedNurbsSurface::numUControlPoints
  FIXME: write documentation for field
*/
/*!
  \var SoSFInt32 SoIndexedNurbsSurface::numVControlPoints
  FIXME: write documentation for field
*/
/*!
  \var SoMFInt32 SoIndexedNurbsSurface::coordIndex
  FIXME: write documentation for field
*/
/*!
  \var SoMFFloat SoIndexedNurbsSurface::uKnotVector
  FIXME: write documentation for field
*/
/*!
  \var SoMFFloat SoIndexedNurbsSurface::vKnotVector
  FIXME: write documentation for field
*/
/*!
  \var SoSFInt32 SoIndexedNurbsSurface::numSControlPoints
  FIXME: write documentation for field
*/
/*!
  \var SoSFInt32 SoIndexedNurbsSurface::numTControlPoints
  FIXME: write documentation for field
*/
/*!
  \var SoMFInt32 SoIndexedNurbsSurface::textureCoordIndex
  FIXME: write documentation for field
*/
/*!
  \var SoMFFloat SoIndexedNurbsSurface::sKnotVector
  FIXME: write documentation for field
*/
/*!
  \var SoMFFloat SoIndexedNurbsSurface::tKnotVector
  FIXME: write documentation for field
*/


// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoIndexedNurbsSurface)
SoType SoIndexedNurbsSurface::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoIndexedNurbsSurface node class.
*/
void *
SoIndexedNurbsSurface::createInstance(void)
{
  return new SoIndexedNurbsSurface;
}

/*!
  Returns the unique type identifier for the SoIndexedNurbsSurface class.
*/
SoType
SoIndexedNurbsSurface::getClassTypeId(void)
{
  return SoIndexedNurbsSurface::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoIndexedNurbsSurface::getTypeId(void) const
{
  return SoIndexedNurbsSurface::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoIndexedNurbsSurface::SoIndexedNurbsSurface()
{
//$ BEGIN TEMPLATE NodeConstructor(SoIndexedNurbsSurface)
  // Make sure the class has been initialized.
  assert(SoIndexedNurbsSurface::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(numUControlPoints, (0));
  SO_NODE_ADD_FIELD(numVControlPoints, (0));
  SO_NODE_ADD_FIELD(coordIndex, (0));
  SO_NODE_ADD_FIELD(uKnotVector, (0));
  SO_NODE_ADD_FIELD(vKnotVector, (0));
  SO_NODE_ADD_FIELD(numSControlPoints, (0));
  SO_NODE_ADD_FIELD(numTControlPoints, (0));
  SO_NODE_ADD_FIELD(textureCoordIndex, (-1));
  SO_NODE_ADD_FIELD(sKnotVector, (0));
  SO_NODE_ADD_FIELD(tKnotVector, (0));
}

/*!
  Destructor.
*/
SoIndexedNurbsSurface::~SoIndexedNurbsSurface()
{
}

/*!
  Does initialization common for all objects of the
  SoIndexedNurbsSurface class. This includes setting up the
  type system, among other things.
*/
void
SoIndexedNurbsSurface::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(IndexedNurbsSurface)
  // Make sure we only initialize once.
  assert(SoIndexedNurbsSurface::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoIndexedNurbsSurface::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "IndexedNurbsSurface",
                       &SoIndexedNurbsSurface::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoIndexedNurbsSurface::cleanClass(void)
{
}

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
/*!
  FIXME: write function documentation
*/
void
SoIndexedNurbsSurface::computeBBox(SoAction * action,
				 SbBox3f & box, SbVec3f & center)
{
  assert(0 && "FIXME: not implemented yet");
}
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION


#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedNurbsSurface::GLRender(SoGLRenderAction * action)
{
  assert(0 && "FIXME: not implemented");

  //
  // See comment in SoNurbsSurface::GLRender
  //

}
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SORAYPICKACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedNurbsSurface::rayPick(SoRayPickAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SORAYPICKACTION

#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedNurbsSurface::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedNurbsSurface::sendPrimitive(SoAction * ,  SoPrimitiveVertex *)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedNurbsSurface::generatePrimitives(SoAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION
