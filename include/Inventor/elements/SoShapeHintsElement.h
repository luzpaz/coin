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

#ifndef _SO_SHAPE_HINTS_ELEMENT_H_
#define _SO_SHAPE_HINTS_ELEMENT_H_

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SOSHAPEHINTSELEMENT)
#error "Configuration settings disable this class!"
#endif // COIN_EXCLUDE_SOSHAPEHINTSELEMENT

#include <Inventor/elements/SoElement.h>

class SoShapeHintsElement : public SoElement {
  typedef SoElement inherited;

//$ BEGIN TEMPLATE ElementHeader( SoShapeHintsElement )
public:
  static SoType classTypeId;
  static SoType getClassTypeId(void);
  static void * createInstance(void);
public:
  static int getClassStackIndex(void);
  virtual ~SoShapeHintsElement(void);

  static void initClass(void);
  static void cleanClass(void);

protected:
  SoShapeHintsElement(void);
  static int classStackIndex;
//$ END TEMPLATE ElementHeader

public:
  enum VertexOrdering {
    UNKNOWN_ORDERING,
    CLOCKWISE,
    COUNTERCLOCKWISE,
    ORDERING_AS_IS
  };

  enum ShapeType {
    UNKNOWN_SHAPE_TYPE,
    SOLID,
    SHAPE_TYPE_AS_IS
  };
  
  enum FaceType {
    UNKNOWN_FACE_TYPE,
    CONVEX,
    FACE_TYPE_AS_IS
  };

  virtual void init( SoState * state );
  virtual void push( SoState * state );

  virtual SbBool matches( const SoElement * element ) const;
  virtual SoElement *copyMatchInfo( void ) const;

  static void set(SoState * const state, SoNode * const node,
		  const VertexOrdering vertexOrdering,
		  const ShapeType shapeType, const FaceType faceType);
  static void set(SoState * const state,
		  const VertexOrdering vertexOrdering,
		  const ShapeType shapeType, const FaceType faceType);
  static void get(SoState * const state, VertexOrdering & vertexOrdering,
		  ShapeType & shapeType, FaceType & faceType);

  static VertexOrdering getVertexOrdering(SoState * const state);
  static ShapeType getShapeType(SoState * const state);
  static FaceType getFaceType(SoState * const state);

  static VertexOrdering getDefaultVertexOrdering();
  static ShapeType getDefaultShapeType();
  static FaceType getDefaultFaceType();

  virtual void print( FILE * file ) const;

protected:
  virtual void setElt(VertexOrdering vertexOrdering,
		      ShapeType shapeType, FaceType faceType);

  VertexOrdering vertexOrdering;
  ShapeType shapeType;
  FaceType faceType;

}; // class SoShapeHintsElement

#endif // ! _SO_SHAPE_HINTS_ELEMENT_H_
