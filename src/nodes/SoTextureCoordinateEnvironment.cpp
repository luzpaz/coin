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
  \class SoTextureCoordinateEnvironment SoTextureCoordinateEnvironment.h Inventor/nodes/SoTextureCoordinateEnvironment.h
  \brief The SoTextureCoordinateEnvironment class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbName.h>

#if !defined(COIN_EXCLUDE_SOTEXTURECOORDINATEELEMENT)
#include <Inventor/elements/SoTextureCoordinateElement.h>
#endif

#if !defined(COIN_EXCLUDE_SOACTION)
#include <Inventor/actions/SoGLRenderAction.h>
#endif

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <GL/gl.h>
#endif // ! COIN_EXCLUDE_SOGLRENDERACTION

// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoTextureCoordinateEnvironment)
SoType SoTextureCoordinateEnvironment::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoTextureCoordinateEnvironment node class.
*/
void *
SoTextureCoordinateEnvironment::createInstance(void)
{
  return new SoTextureCoordinateEnvironment;
}

/*!
  Returns the unique type identifier for the SoTextureCoordinateEnvironment class.
*/
SoType
SoTextureCoordinateEnvironment::getClassTypeId(void)
{
  return SoTextureCoordinateEnvironment::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoTextureCoordinateEnvironment::getTypeId(void) const
{
  return SoTextureCoordinateEnvironment::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoTextureCoordinateEnvironment::SoTextureCoordinateEnvironment()
{
//$ BEGIN TEMPLATE NodeConstructor(SoTextureCoordinateEnvironment)
  // Make sure the class has been initialized.
  assert(SoTextureCoordinateEnvironment::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor
}

/*!
  Destructor.
*/
SoTextureCoordinateEnvironment::~SoTextureCoordinateEnvironment()
{
}

/*!
  Does initialization common for all objects of the
  SoTextureCoordinateEnvironment class. This includes setting up the
  type system, among other things.
*/
void
SoTextureCoordinateEnvironment::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(TextureCoordinateEnvironment)
  // Make sure we only initialize once.
  assert(SoTextureCoordinateEnvironment::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoTextureCoordinateEnvironment::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "TextureCoordinateEnvironment",
                       &SoTextureCoordinateEnvironment::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoTextureCoordinateEnvironment::cleanClass(void)
{
}

/*!
  FIXME: write function documentation
*/
const SbVec4f &
SoTextureCoordinateEnvironment::generate(void * userdata,
				   const SbVec3f & p,
				   const SbVec3f & n)
{
  assert(0 && "FIXME: not implemented yet");
  return SbVec4f(0,0,0,1);
}

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write function documentation
*/
void 
SoTextureCoordinateEnvironment::doAction(SoAction * action)
{
  SoTextureCoordinateElement::setFunction(action->getState(), this,
					  generate,
					  this);
}
#endif // !COIN_EXCLUDE_SOACTION

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write function documentation
*/
void 
SoTextureCoordinateEnvironment::GLRender(SoGLRenderAction * action)
{
  SoTextureCoordinateEnvironment::doAction((SoAction *)action);
  SoGLTextureCoordinateElement::setTexGen(action->getState(),
					  this, handleTexgen);
}
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SOCALLBACKACTION)
/*!
  FIXME: write function documentation
*/
void 
SoTextureCoordinateEnvironment::callback(SoCallbackAction * action)
{
  SoTextureCoordinateEnvironment::doAction((SoAction *)action);
}
#endif // !COIN_EXCLUDE_SOCALLBACKACTION

#if !defined(COIN_EXCLUDE_SOPICKACTION)
/*!
  FIXME: write function documentation
*/
void 
SoTextureCoordinateEnvironment::pick(SoPickAction * action)
{
  SoTextureCoordinateEnvironment::doAction((SoAction *)action);
}
#endif // !COIN_EXCLUDE_SOPICKACTION

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
void 
SoTextureCoordinateEnvironment::handleTexgen(void *data)
{
#if 0 // from red book
  glTexGenfv(GL_S, GL_SPHERE_MAP, 0);
  glTexGenfv(GL_T, GL_SPHERE_MAP, 0);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
#else // from siggraph 96
  glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
#endif
}
#endif // ! COIN_EXCLUDE_SOGLRENDERACTION
