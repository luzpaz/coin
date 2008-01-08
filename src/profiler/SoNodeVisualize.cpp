/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2008 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/annex/Profiler/nodekits/SoNodeVisualize.h>

#include <map>
#include <string>

#include <boost/scoped_ptr.hpp>

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/annex/Profiler/nodes/SoProfilerStats.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoVertexProperty.h>

// texture maps with node type symbols
#include "inventormaps.cpp"

// *************************************************************************

// for debugging

#define PRINT_FUNCTION()

// *************************************************************************

namespace {
  class TextureDict {
  public:
    TextureDict()
    {
    }

    ~TextureDict()
    {
      clear();
    }
  
    SoTexture2 * createTexture(const char ** buf)
    {
      SoInput in;
      in.setStringArray(buf);
      SoSeparator * top = SoDB::readAll(&in);
      assert(top && "Didn't get node");
      SoNode * tex = (*top->getChildren())[0];
      assert(tex->isOfType(SoTexture2::getClassTypeId()));
      return (SoTexture2*)tex;
    }

    void clear() {
      std::map<const char **, SoTexture2 *>::iterator it, end;
      for (it = this->nodemap.begin(), end = this->nodemap.end();
           it != end; ++it) {
        it->second->unref();
        it->second = NULL;
      }
      this->nodemap.clear();
    }

    SoTexture2 * operator[](const char ** buf) 
    {
      std::map<const char **, SoTexture2 *>::iterator e;
      e = this->nodemap.find(buf);
      if (e == this->nodemap.end()) {
        // not found, create
        SoTexture2 * node = TextureDict::createTexture(buf);
        node->ref();
        this->nodemap[buf] = node;
        return node;
      } else {
        return e->second;
      }
    }
    

  private:
    std::map<const char **, SoTexture2 *> nodemap;
  };
}

// *************************************************************************

class SoNodeVisualizeP {
public:
  SoNodeVisualizeP(void) {
  }
  
  static TextureDict textures;
};

TextureDict SoNodeVisualizeP::textures;

// *************************************************************************

SO_KIT_SOURCE(SoNodeVisualize);

// *************************************************************************

/*!
   Constructor

   Note, this constructor is not public, as it sets up the class in an
   internally inconsistent way, this also ensures that we do not try
   to analyze ourself, which may do strange things to our state.

   //FIXME: Should perhaps make a public constructor which takes the
   //same parameters as visualize tree
*/
SoNodeVisualize::SoNodeVisualize(void)
{
  SO_KIT_CONSTRUCTOR(SoNodeVisualize);
  
  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, FALSE, this, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(childrenVisible, SoSwitch, FALSE, topSeparator, shape, FALSE);
  
  //NOTE: This setup also rotates our own geometry, which wasn't by
  //design, but I'm not totally unhappy with the behaviour.
  SO_KIT_ADD_CATALOG_ENTRY(rotSwitch, SoSwitch, FALSE, childrenVisible, lineSep, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(rotation, SoRotation, FALSE, rotSwitch, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(lineSep, SoSeparator, FALSE, childrenVisible, childGeometry, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(lines, SoIndexedLineSet, FALSE, lineSep, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(childGeometry, SoSeparator, FALSE, childrenVisible, color, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(color, SoMaterial, FALSE, childrenVisible, "", FALSE);
  
  SO_KIT_ADD_CATALOG_ENTRY(texture, SoTexture2, TRUE, topSeparator, shape, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(textureTransform, SoTexture2Transform, FALSE, topSeparator, shape, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(shape, SoSphere, FALSE, topSeparator, "", FALSE);
  
  SO_KIT_INIT_INSTANCE();
  
  //Setup some default stuff
  SoTexture2Transform *tt=static_cast<SoTexture2Transform*>(this->getAnyPart("textureTransform",FALSE));
  tt->scaleFactor.setValue(2, 1);
  tt->center.setValue(.5,0);

  SoSwitch* sw=static_cast<SoSwitch*>(this->getAnyPart("childrenVisible",TRUE));
  sw->whichChild=SO_SWITCH_ALL;

  SoMaterial *color=static_cast<SoMaterial*>(this->getAnyPart("color",TRUE));
  color->diffuseColor=SbVec3f(1,1,0);

  sw=static_cast<SoSwitch*>(this->getAnyPart("rotSwitch",TRUE));
  sw->whichChild=SO_SWITCH_NONE;
  
  /*
    ISSUE: Currently we are making all rotations in one direction,
    meaning that the concept of right sibling will have changed by 180
    degrees if we descend two levels with alternate on.
   */
  //FIXME: We should reuse this node, instead of creating it for every single node.
  SoRotation *rot=static_cast<SoRotation*>(this->getAnyPart("rotation",TRUE));
  rot->rotation.setValue(SbVec3f(0, 1, 0), 1.5707963f);
  
  this->parent=NULL;
  this->dirty=true;
  this->node=NULL;

}

SoNodeVisualize*
SoNodeVisualize::visualize(SoNode * node) {
  this->node=node;
  if (node!=NULL) {
    // FIXME: from what i can see, one can replace this homemade type
    // hierarchy traversal thing with invocations of
    // SoType::isDerivedFrom(). -mortene.
    for (SoType type = node->getTypeId(); type != SoNode::getClassTypeId(); 
         type = type.getParent()) {
      //FIXME: Replace this with a switch.
      //FIXME: Exhange all the named textures, with images
      //FIXME: Make the images better fitting for its shape
      //FIXME: Check if cubes are better options for some of the nodetypes
      //FIXME: Make smaller textures
      if(type == SoMaterial::getClassTypeId()) {
        this->setAnyPart("texture", SoNodeVisualizeP::textures[material_1]);
        SoTexture2Transform * tt = 
          static_cast<SoTexture2Transform*>(this->getAnyPart("textureTransform",FALSE));
        tt->scaleFactor.setValue(1,5);

      } else if (type == SoShape::getClassTypeId()) {
        // FIXME 20071107 rolvs: Currently, this->shape is a SoMFField, and 
        // ::shape is a const * char. This will be 'resolved' when we change 
        // ::shape to Shape. And hem... maybe add some prefix to the texture 
        // names in the staticglobalfile.
        this->setAnyPart("texture", SoNodeVisualizeP::textures[::shape]);

      } else if (type == SoSeparator::getClassTypeId()) {
        this->setAnyPart("texture", SoNodeVisualizeP::textures[geometry_root]);

      } else if (type == SoBaseKit::getClassTypeId()) {
        this->setAnyPart("texture", SoNodeVisualizeP::textures[NodeKit]);

      } else if (type == SoSwitch::getClassTypeId()) {
        this->setAnyPart("texture", SoNodeVisualizeP::textures[Switch]);

      } else if (type == SoTransformation::getClassTypeId()) {
        this->setAnyPart("texture", SoNodeVisualizeP::textures[top_transform]);

      } else if (type.isDerivedFrom(SoTexture::getClassTypeId())){
        this->setAnyPart("texture", node);
      }
    }
  }
  return this;
}

void
SoNodeVisualize::setupChildCatalog(SoNode * node,int depth) {
  SoSeparator * sep=static_cast<SoSeparator*>(this->getAnyPart("childGeometry",TRUE));
  SoNodeList * children=node->getChildren();
  unsigned int numNodeChildren=this->nodeNumChildren();

  --depth;

  for (unsigned int i=0;i<numNodeChildren;++i) {
    sep->addChild(new SoTranslation());
    SoNodeVisualize * nv=visualizeTree((*children)[i],depth);
    nv->parent=this;
    sep->addChild(nv);
  }

  //Construct the indexes of the lineset
  SoIndexedLineSet * lineS=static_cast<SoIndexedLineSet*>(this->getAnyPart("lines",TRUE));
  lineS->coordIndex.setNum((numNodeChildren+1)*3);

  int32_t * ind = lineS->coordIndex.startEditing();
  for (unsigned int i=1;i<=numNodeChildren;++i) {
    *ind++=0;
    *ind++=i;
    *ind++=-1;
  }
  lineS->coordIndex.finishEditing();

  //The lineSet should not have any vertex property yet
  assert(lineS->vertexProperty.getValue()==NULL);

  //Lets assign a vertex property with the proper length
  SoVertexProperty *vp=new SoVertexProperty();
  vp->vertex.setNum(numNodeChildren+1);
  lineS->vertexProperty=vp;

}

SoNodeVisualize *
SoNodeVisualize::visualizeTree(SoNode * node,int depth) {
  SoNodeVisualize * nv=new SoNodeVisualize();
  nv->visualizeSubTree(node,depth);
  nv->recalculate();
  return nv;
}

void
SoNodeVisualize::recalculate() {
  //At this point we must shall have a node
  assert(node);

  //FIXME: Perhaps not the right place to set dirty
  this->dirty = true;
  SoNodeList * geometryChildren = getChildGeometry();

  //No need to do anything if we have no children
  if (geometryChildren->getLength()) {

    //Before we do any calculation on our own, we recalculate all our children
    SoNodeList * nodeChildren=node->getChildren();
    for (int i = 0; i < nodeChildren->getLength(); ++i)
      static_cast<SoNodeVisualize *>((*geometryChildren)[2 * i + 1])->recalculate();

    //The child geometry should contain exactly one translation and
    //one SoNodeVisualize node per nodeChildren
    int numNodeChildren = this->nodeNumChildren();
    assert((numNodeChildren * 2) == geometryChildren->getLength());

    //First we set up the Y translation, to the next level and the right X translation
    //If we are alternating, we get rotated values for our own
    //boundingbox, we need to pick the Z component for the X
    //translation
    SoTranslation * trans = static_cast<SoTranslation *>((*geometryChildren)[0]);
    trans->translation.setValue(1.5f * this->getWidth()[this->isAlternating()?1:0],
                                -3.0f, 0.0f);

    for (int i = 0; i < nodeChildren->getLength(); ++i) {
      //We translate this node left for half the boundingbox's X component
      SoNodeVisualize * nv = static_cast<SoNodeVisualize*>((*geometryChildren)[2*i+1]);
      trans->translation = 
        trans->translation.getValue() + SbVec3f(-1.5f * nv->getWidth()[0], 
                                                0.0f,
                                                0.0f);
      //If this is not the last node
      if (i < (numNodeChildren - 1)) {
        //we translate the subsequent node for half of this ones X component
        trans = static_cast<SoTranslation *>((*geometryChildren)[2 * i + 2]);
        trans->translation = SbVec3f(-1.5f * nv->getWidth()[0], 0.0f, 0.0f);
      }
    }

    SoIndexedLineSet * lineS = 
      static_cast<SoIndexedLineSet*>(this->getAnyPart("lines",FALSE));

    assert(lineS->vertexProperty.getValue()!=NULL && 
           "No vertexProperty available from setupChildCatalog");

    //Sets up the vertices of the lines between the nodes
    SoVertexProperty * vp=
      static_cast<SoVertexProperty*>(lineS->vertexProperty.getValue());
    
    SbVec3f * dst = vp->vertex.startEditing();
    *dst = SbVec3f(0,0,0);
    for (int i = 0; i < numNodeChildren; ++i)
      dst[i + 1] = dst[i] + 
        static_cast<SoTranslation *>((*geometryChildren)[2 * i])->translation.getValue();
    vp->vertex.finishEditing();
  }
}

/*!
   Visualizes a subtree, stops at depth 1

   If no argument given, visualizes everything

   WARNING: Allthough the default is to visualize everything, it is
   recommended to set a limit on how deep you want to traverse. If you
   go to deep, the memory requirements, and recalculation may become
   so heavy it grinds to a halt. Additionally it is difficult to see,
   when there is too much information on the screen at once.
*/
void
SoNodeVisualize::visualizeSubTree(SoNode * node,int depth) {
  if (!this->node)
    this->visualize(node);
  //We have reached the max visualization depth, don't expand anymore
  if (depth == 1) {
    //Always display a node without children as expanded
    if (this->nodeNumChildren())
      static_cast<SoSwitch*>(this->getAnyPart("childrenVisible",TRUE))->whichChild = 
        SO_SWITCH_NONE;
    return;
  }
  
  //If we have children set up their catalog as well
  if (this->nodeNumChildren()) {
    SoNodeList *children = this->getChildGeometry();
    
    //Only set up the catalog if we haven't done it before
    if((this->nodeNumChildren() * 2) != (unsigned int)children->getLength())
      this->setupChildCatalog(node, depth);

    assert((this->nodeNumChildren() * 2) == (unsigned int)children->getLength());
  }
}

void
SoNodeVisualize::traverse(SoProfilerStats * stats)
{
  // FIXME 20071109 rolvs: This is just crammed in here, during the last hours of the hackathon. 
  // And I'm quite sure that a better way to do this alltogeher might be
  // conjured. its also more than possible that I duplicate some functionality somewhere here... 
  // And phew. Cut and paste programming. Darn. 
  
  // check if this->node is a cache-separator. In that case, find it's material and set it. 
  //this->getChildrenGeometry()
  assert(stats && "Stats not set.");
  SoMaterial * material = static_cast<SoMaterial *>(this->color.getValue());
  if (material == NULL) {
    material = new SoMaterial;
    material->diffuseColor = SbVec3f(1.0f, 1.0f, 0.0f);
    material->transparency = 0.0f;
    this->setAnyPart("color", material);
  }

  assert(material->diffuseColor.getNum() == 1);
  assert(material->transparency.getNum() == 1);
  SbColor color = material->diffuseColor[0];
  float transparency = material->transparency[0];

  float green = 0.0f;
  if ((parent != NULL) && (this->node != NULL)) {
    const unsigned long CRITICAL = 10;

    SoNode * parent = this->parent->node;
    unsigned long msec = stats->getTotalProfilingTime(parent, this->node).getMsecValue();
    msec = SbMax<unsigned long>(CRITICAL, msec);
    green = 1.0f - (float)msec / (float)CRITICAL;
  }
               
  if(this->node->isOfType(SoSeparator::getClassTypeId()) && 
     stats->hasGLCache((SoSeparator *)this->node)) {
    // FIXME All children are cached. Make them inherit material
    color = SbVec3f(0.0f, green, 1.0f);
    transparency = 0.0f;
  }
  
  if (this->node->getTypeId().getName() == SbName("ScenarioSimulator"))
    color = SbVec3f(1.0f, green, 0.0f);

  /*  else if(stats->separatorsCullRoots.findNode(this->node)!=-1){
    // FIXME All children are culled. Make them inherit material
    printf("Culled: %p / %s\n", this->node, this->node->getName().getString());

    color->transparency = 0.7;
  }
  */
  
  if (material->diffuseColor[0] != color)
    material->diffuseColor = color;

  if (material->transparency[0] != transparency)
    material->transparency = transparency;
  
  SoNodeList * geometryChildren = this->getChildGeometry();
  int numGeometryChildren = geometryChildren->getLength();
  if( numGeometryChildren == 0 || 
    static_cast<SoSwitch*>(this->getAnyPart("childrenVisible",FALSE))->whichChild.getValue() == SO_SWITCH_NONE)
    return;
    
  for (int i = 1; i < numGeometryChildren; i += 2) {
    // FIXME 20071109 using index value to iterate over this geometry is kind of... errh. 
    // sucky.
    SoNodeVisualize * viz = static_cast<SoNodeVisualize*>((*geometryChildren)[i]);
    viz->traverse(stats);
  }
}
/*!
   Calculates the size of a bounding box for this subtree
*/
SbVec2s
SoNodeVisualize::recalculateWidth() {
  PRINT_FUNCTION();

  SoNodeList * geometryChildren=this->getChildGeometry();

  int numGeometryChildren = geometryChildren->getLength();
  // check that numGeometryChildren is a even number
  assert(!(numGeometryChildren & 0x1));

  SoSwitch * childrenswitch = static_cast<SoSwitch *>(this->childrenVisible.getValue());

  //If we have no childgeometry, or it is invisible, we occupy a 1x1 box
  if ((numGeometryChildren == 0) ||
      (childrenswitch == NULL) ||
      (childrenswitch->whichChild.getValue() == SO_SWITCH_NONE))
    return SbVec2s(1,1);
  
  //If we have children, we occupy the maximum of all our children in the z direction
  //and the sum of our children in the x direction
  short accum = 0;
  short max = 0;

  for (int i = 1; i < numGeometryChildren; i += 2) {
    SbVec2s tmp = static_cast<SoNodeVisualize*>((*geometryChildren)[i])->getWidth();
    accum += tmp[0];
    if (tmp[1] > max)
      max = tmp[1];
  }
  
  return SbVec2s(accum, max);

  //If we are alternating, the box should be rotated 90 degrees, before returned
                                                      //  return (!this->isAlternating()?
                                                      //          SbVec2s(accum, max):
                                                      //          SbVec2s(max, accum));
}

//This should usually always be turned on
//turning it off should only be useful for debugging
#undef CACHING
//#define CACHING

/*!
   Returns the size of a bounding box for this subtree
*/
SbVec2s
SoNodeVisualize::getWidth() {
  PRINT_FUNCTION();
#ifdef CACHING
  if (this->dirty) {
#endif
    this->width=recalculateWidth();
#ifdef CACHING
    this->dirty=false;
  }
#endif
  return width;
}

/*!
   Destructor
*/
SoNodeVisualize::~SoNodeVisualize()
{
}

/*!
   Standard intialization for node catalog
*/
void
SoNodeVisualize::initClass(void)
{
  static int first = 1;
  if (first) {
    first = 0;
    SO_KIT_INIT_CLASS(SoNodeVisualize, SoBaseKit, "BaseKit");
  }
}

/*!
   Changes the state of a node with children
*/
bool
SoNodeVisualize::clicked() {
  PRINT_FUNCTION();
  SoSwitch* sw=static_cast<SoSwitch*>(this->getAnyPart("childrenVisible",TRUE));
  assert(sw->whichChild.getValue()==SO_SWITCH_NONE||sw->whichChild.getValue()==SO_SWITCH_ALL);

  //If we have no children, we always want the open state
  //Don't allow any changes
  if (!this->nodeHasChildren())
    return true;

  //First if we are at on already
  if (sw->whichChild.getValue()==SO_SWITCH_ALL) {
    sw->whichChild=SO_SWITCH_NONE;
    //We only need to recalculate if we have a node above us
    if (parent)
      getSoNodeVisualizeRoot()->recalculate();
    return false;
  }

  //If we are off now
  sw->whichChild=SO_SWITCH_ALL;
  SoNodeList *children=this->getChildGeometry();

  //Lazy instantiation
  if (children && this->nodeNumChildren()!=(unsigned int)children->getLength()) {
    this->visualizeSubTree(node, 2);
    this->setAlternate(this->isAlternating());
  }

  getSoNodeVisualizeRoot()->recalculate();

  return true;
}

/*!
   Checks for intersection with the shape part of the node
*/
void
SoNodeVisualize::handleEvent(SoHandleEventAction * action)
{
  inherited::handleEvent(action);

  if (!SO_MOUSE_PRESS_EVENT(action->getEvent(), BUTTON1)) { return; }

  const SoPickedPoint * pp = action->getPickedPoint();
  if (!pp) { return; }

  SoFullPath * path = static_cast<SoFullPath*>(pp->getPath());
  SoShape* shape = static_cast<SoShape*>(this->getAnyPart("shape",TRUE));

  //REVIEW: BFG - Not sure what I'm doing here, the getDetail is
  //from an example source
  if (path->containsNode(shape) && pp->getDetail(shape) == NULL) {
    SbVec3f point = pp->getPoint();
    this->clicked();
  }
}

/*!
   Returns the uppermost connected parent
*/
SoNodeVisualize*
SoNodeVisualize::getSoNodeVisualizeRoot() {
  SoNodeVisualize *nv;
  for (nv=this;nv->parent;nv=nv->parent);
  assert(nv);
  return nv;
}

/*!
   Turns on the alternating direction state for all children
*/
void
SoNodeVisualize::setAlternate(bool alternate) {
  this->internalAlternating(alternate,0);
  this->getSoNodeVisualizeRoot()->recalculate();
}

/*!
   Traverses all nodes, and turns on the alternating state,

   May need a recalculation afterwards
*/
void
SoNodeVisualize::internalAlternating(bool alternate,int direction) {
  PRINT_FUNCTION();
  
  static_cast<SoSwitch*>(this->getAnyPart("rotSwitch",TRUE))
    ->whichChild=(alternate)?SO_SWITCH_ALL:SO_SWITCH_NONE;
  
  SoNodeList * children=this->getChildGeometry();
  int l;
  if (!children ||
      (l=children->getLength())==0 ||
      static_cast<SoSwitch*>(this->getAnyPart("childrenVisible",FALSE))->whichChild.getValue()==SO_SWITCH_NONE)
    return;

  ++direction;
  for (int i=1;i<l;i+=2)
    static_cast<SoNodeVisualize*> ((*children)[i])->internalAlternating(alternate,direction);
}

/*!
   Does the associated node have any children?
*/
bool
SoNodeVisualize::nodeHasChildren() {
  return (nodeNumChildren() > 0);
}

/*!
   Number of children of the associated node
 */
unsigned int
SoNodeVisualize::nodeNumChildren() {
  assert(this->node);
  SoNodeList * children=node->getChildren();
  if (!children) return 0;
  return children->getLength();
}

/*!
  Resets the datastructure in anticipation of a reanalysis

  This puts the structure in the same inconsistent structure as the empty constructor
*/
void
SoNodeVisualize::reset() {
  this->node=NULL;
  SoSeparator * sep=static_cast<SoSeparator*>(this->getAnyPart("childGeometry",TRUE));
  sep->removeAllChildren();
}

bool
SoNodeVisualize::isAlternating() const {
  return static_cast<SoSwitch*>(
           const_cast<SoNodeVisualize*>(this)
           ->getAnyPart("rotSwitch",FALSE)
           )->whichChild.getValue()==SO_SWITCH_ALL;
}

SoNodeList *
SoNodeVisualize::getChildGeometry() {
  SoNodeList * childgeometry=
    static_cast<SoSeparator*>(this->getAnyPart("childGeometry",FALSE))
    ->getChildren();
  assert(childgeometry);
  return childgeometry;
}