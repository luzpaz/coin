#ifndef COIN_SOGLARBSHADEROBJECT_H
#define COIN_SOGLARBSHADEROBJECT_H

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

#ifndef COIN_INTERNAL
#error this is a private header file
#endif

// *************************************************************************

#include <Inventor/nodes/SoGLShaderParameter.h>
#include "SoGLShaderObject.h"

// *************************************************************************

class SoGLARBShaderObject : public SoGLShaderObject
{
public:
  virtual SbBool isLoaded(void) const;
  virtual void load(const char *sourceString);
  virtual void unload(void);
  virtual SoGLShader::ShaderType shaderType(void) const;
  virtual SoGLShaderParameter * getParameter(int index, const char * name,
                                             SoGLShader::ValueType type);

public:
  SoGLARBShaderObject(const cc_glglue * g);
  virtual ~SoGLARBShaderObject();
  void enable(void);
  void disable(void);

private:
  GLuint arbProgramID;
  GLenum target; // either GL_FRAGMENT_PROGRAM_ARB or GL_VERTEX_PROGRAM_ARB
};

#endif /* ! COIN_SOGLARBSHADEROBJECT_H */