// Copyright (c) 2004 Samir Araujo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <powergine/sceneobjects/srtnode.h>

namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods
SRTNode::SRTNode( ) :
   m_fScaling( 1.0f ),
   m_oRotation( primitives::Quaternion::IDENTITY ),
   m_oTranslation( primitives::Vector3D::ORIGO )
   
{
   
} // SRTNode

SRTNode::~SRTNode( ) {

} // ~SRTNode

float SRTNode::getScaling( ) const {
   return m_fScaling;
} // getScaling

const primitives::Vector3D& SRTNode::getTranslation( ) const {
   return m_oTranslation;
} // getTranslation

const primitives::Quaternion& SRTNode::getRotation( ) const {
   return m_oRotation;
} // getRotation

void SRTNode::setScaling( float fScaling ) {
   m_fScaling = fScaling;
} // setScaling

void SRTNode::setTranslation( const primitives::Vector3D &rkTranslation ) {
   m_oTranslation = rkTranslation;
} // setTranslation

void SRTNode::setRotation( const primitives::Quaternion &rkRotation ) {
   m_oRotation = rkRotation;
} // setRotation


void SRTNode::doScaling( float fScaling ) {
   setScaling( m_fScaling * fScaling );
   /*
   if ( m_fScaling != 0.0f ) {
      m_fScaling *= fScaling;
   } else {
      m_fScaling = fScaling;      
   } // else
   */
} // setScaling

void SRTNode::doTranslation( const primitives::Vector3D &rkTranslation ) {         
   setTranslation( m_oTranslation + (~m_oRotation).rotateVector3D( rkTranslation ) );
   //m_oTranslation += ( (~m_oRotation).rotateVector3D( rkTranslation ) );
} // setTranslation

void SRTNode::doRotation( const primitives::Quaternion &rkRotation ) {   
   //m_oRotation *= rkRotation;
   setRotation( m_oRotation * rkRotation );
} // setRotation

void SRTNode::accept( const utils::EntityVisitor &rkVisitor ) {
   //TODO
}

	}; // sceneobjects
}; // namespace powergine
