#ifndef COIN_SOTEXTURECUBEMAP_H
#define COIN_SOTEXTURECUBEMAP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/elements/SoTextureImageElement.h>

class SoFieldSensor;
class SoSensor;
class SoTextureCubeMapP;

class COIN_DLL_API SoTextureCubeMap : public SoNode {
  typedef SoNode inherited;

  SO_NODE_HEADER(SoTextureCubeMap);

public:
  static void initClass(void);
  SoTextureCubeMap(void);

  enum Model {
    MODULATE = SoTextureImageElement::MODULATE,
    DECAL = SoTextureImageElement::DECAL,
    BLEND = SoTextureImageElement::BLEND,
    REPLACE = SoTextureImageElement::REPLACE
  };

  enum Wrap {
    REPEAT = SoTextureImageElement::REPEAT,
    CLAMP = SoTextureImageElement::CLAMP
  };

  SoSFString posXfilename;
  SoSFString negXfilename;
  SoSFString posYfilename;
  SoSFString negYfilename;
  SoSFString posZfilename;
  SoSFString negZfilename;

  SoSFImage posXimage;
  SoSFImage negXimage;
  SoSFImage posYimage;
  SoSFImage negYimage;
  SoSFImage posZimage;
  SoSFImage negZimage;

  SoSFEnum wrapS;
  SoSFEnum wrapT;
  SoSFEnum model;
  SoSFColor blendColor;

  virtual void doAction(SoAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void rayPick(SoRayPickAction * action);

  static SbBool readImage(const SbString & fname, int & w, int & h, int & nc,
                          unsigned char *& bytes);
protected:
  virtual ~SoTextureCubeMap();

  virtual SbBool readInstance(SoInput * in, unsigned short flags);
  virtual void notify(SoNotList * list);
  int getReadStatus(void);
  void setReadStatus(int s);

private:
  SbBool loadFilename(SoSFString * filename, SoSFImage * image);
  static void filenameSensorCB(void *, SoSensor *);

  SoTextureCubeMapP * pimpl;
};

#endif // !COIN_SOTEXTURECUBEMAP_H