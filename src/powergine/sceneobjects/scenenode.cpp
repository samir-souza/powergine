// Copyright (c) 2004 Samir Araujo <samir.araujo.com>
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


#include <powergine/sceneobjects/scenenode.h>

namespace powergine {
	namespace sceneobjects {   

// Constructors/Destructors
// Methods
SceneNode::SceneNode( const std::string &rkstrName ) :
   m_bNeedUpdateTransformation( false ),
   m_pParentNode( 0 ),
   m_pRenderEntity( 0 ),
   m_strName( rkstrName ),
   m_fWorldScaling( 0.0f ),
   m_oWorldRotation( primitives::Quaternion::IDENTITY ),
   m_oWorldTranslation( primitives::Vector3D::ORIGO ),
   m_oTransformation( primitives::Matrix4x4::IDENTITY ),
   m_oInverseTransformation( primitives::Matrix4x4::IDENTITY ) { } // SceneNode

void SceneNode::setRenderEntity( RenderEntity *pRenderEntity ) {
   m_pRenderEntity = pRenderEntity;   
}

RenderEntity* SceneNode::getRenderEntity( ) {
   return m_pRenderEntity;
}


SceneNode::~SceneNode( ) {
} // ~SceneNode

void SceneNode::setName( const std::string &rstrName ) {
   m_strName = rstrName;
} // setName

const std::string &SceneNode::getName( ) {
   return m_strName;
} // getName

Room* SceneNode::getRoom( ) {
   return m_pRoom;
}
void SceneNode::setRoom( Room *pRoom ) {   
   m_pRoom = pRoom;   
}

SceneNode* SceneNode::getParentNode( ) {
   return m_pParentNode;
} // getParentNode

void SceneNode::setParentNode( SceneNode* pParentNode ) {
   m_pParentNode = pParentNode;
} // setParentNode

bool SceneNode::addChildNode( SceneNode* pChildNode ) {
   std::vector<SceneNode*>::iterator ppNode = m_vpChildrenNodes.begin( );
   std::vector<SceneNode*>::iterator ppEnd = m_vpChildrenNodes.end( );
   
   while ( ppNode != ppEnd ) {
            if ( *ppNode == pChildNode ) {
                  return false; // item already exists in vector
            } // if		
            ppNode++;
   } // while
   m_vpChildrenNodes.push_back( pChildNode );
   return true; // TODO try catch block
} // addChildNode

bool SceneNode::removeChildNode( SceneNode* pChildNode ) {
   std::vector<SceneNode*>::iterator ppNode = m_vpChildrenNodes.begin( );
   std::vector<SceneNode*>::iterator ppEnd = m_vpChildrenNodes.end( );
   
   while ( ppNode != ppEnd ) {
      if ( *ppNode == pChildNode ) {
         m_vpChildrenNodes.erase( ppNode );
         return true; 
      } // if		
      ppNode++;
   } // while	
   return false; // item does not exists in vector
   // TODO try catch block

} // removeChildNode

bool SceneNode::removeFromParent( ) {
   // TODO try catch block to verify the pointer if null
   m_pParentNode->removeChildNode( this );
   return true;
} // removeFromParent

const std::vector<SceneNode*>& SceneNode::getChildrenNodes( ) {
	return m_vpChildrenNodes;
} // getChildrenNodes

void SceneNode::accept( const utils::EntityVisitor &rkEntityVisitor ) {
	// do a RTTI
} // accept

float SceneNode::getWorldScaling( ) {
   updateTransformation( );
   return m_fWorldScaling;
}

primitives::Vector3D& SceneNode::getWorldTranslation( ) {
   updateTransformation( );
   return m_oWorldTranslation;
}

primitives::Quaternion& SceneNode::getWorldRotation( ) {   
   updateTransformation( );   
   return m_oWorldRotation;
}
      
void SceneNode::doWorldTranslation( const primitives::Vector3D &rkTranslation ) {        
   SRTNode::setTranslation( rkTranslation + getTranslation( ) );
   m_bNeedUpdateTransformation = true;
}
  
void SceneNode::doWorldRotation( const primitives::Quaternion &rkRotation ) {      
   SRTNode::setRotation( rkRotation * getRotation( ) );
   m_bNeedUpdateTransformation = true;
}

bool SceneNode::updateTransformation( ) {
   if ( m_bNeedUpdateTransformation ) {
   
      // if has parent node, use the father node values plus the current node values
      if ( m_pParentNode ) {
         std::cout << "a: " << std::endl;
         float fParentWorldScaling = m_pParentNode->getWorldScaling( );
         std::cout << "b: " << std::endl;
         m_oWorldRotation    = m_pParentNode->getWorldRotation( ) * getRotation( );
         std::cout << "c: " << std::endl;
         m_fWorldScaling     = fParentWorldScaling * getScaling( );
         std::cout << "d: " << std::endl;
         m_oWorldTranslation = 
            m_pParentNode->getWorldTranslation( ) + 
               ( m_pParentNode->getWorldRotation( ).rotateVector3D( getTranslation( ) ) *
                  fParentWorldScaling );
         std::cout << "e: " << std::endl;
      } else {      
         m_oWorldTranslation = getTranslation( );
         m_oWorldRotation    = getRotation( );
         m_fWorldScaling     = getScaling( );   
      } // else
   
      // apply rotation cache
      //std::cout << "1) " << m_oWorldRotation.toMatrix4x4( ).toString( ) << std::endl;
      m_oTransformation = m_oWorldRotation.toMatrix4x4( );
      //std::cout << "2) " << m_oTransformation.toString( ) << std::endl;

      /*
         put the translation vector values at the follow positions
         | 0 0 0 x |
         | 0 0 0 y |
         | 0 0 0 z |
         | 0 0 0 0 |
      */                
      // apply translation cache
      m_oTransformation.setElement( 0, 3, m_oWorldTranslation.getX( ) );
      m_oTransformation.setElement( 1, 3, m_oWorldTranslation.getY( ) );
      m_oTransformation.setElement( 2, 3, m_oWorldTranslation.getZ( ) );
      
      /*
         multiply the scaling factor by the follow elements
         | s s s 0 |
         | s s s 0 |
         | s s s 0 |
         | 0 0 0 0 |
      */      
      
      m_oInverseTransformation = m_oTransformation.transpose( );
      m_oInverseTransformation.setElement( 3, 0, 0.0f );
      m_oInverseTransformation.setElement( 3, 1, 0.0f );
      m_oInverseTransformation.setElement( 3, 2, 0.0f );

      primitives::Vector3D oInvTranslation = ( m_oInverseTransformation * ( -m_oWorldTranslation ) );
      
      m_oInverseTransformation.setElement( 0, 3, oInvTranslation.getX( ) );
      m_oInverseTransformation.setElement( 1, 3, oInvTranslation.getY( ) );
      m_oInverseTransformation.setElement( 2, 3, oInvTranslation.getZ( ) );      
      
      // apply scaling cache       
      if( fabs( 1.0f - m_fWorldScaling ) > primitives::Quaternion::SQR_EPSILON ) {
         float *pfMatrix = reinterpret_cast<float*>( &m_oTransformation );
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix++ *= m_fWorldScaling; ++pfMatrix;
         
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix++ *= m_fWorldScaling; ++pfMatrix;
         
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix++ *= m_fWorldScaling; 
         *pfMatrix   *= m_fWorldScaling;            
         
         float fWorldScaling = 1.0f / m_fWorldScaling;
         pfMatrix = reinterpret_cast<float*>( &m_oInverseTransformation );
                 
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling;
         
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling;
         
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling;
         
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix++ *= fWorldScaling; 
         *pfMatrix   *= fWorldScaling;         
         
      } // if
      
      m_bNeedUpdateTransformation = false;
      return true;
   } // if
   return false;
}

void SceneNode::update( float fDeltaTime ) {
   std::vector<SceneNode*>::iterator ppNode = m_vpChildrenNodes.begin( );
   std::vector<SceneNode*>::iterator ppEnd = m_vpChildrenNodes.end( );
   
   while ( ppNode != ppEnd ) {      
      if ( (*ppNode)->isActive( ) ) {
         (*ppNode)->update( fDeltaTime );            
      } // if
      ppNode++;
   } // while	
}

primitives::Matrix4x4* SceneNode::getTransformation( ) {
   updateTransformation( );
   return const_cast<primitives::Matrix4x4*>( &m_oTransformation );
}

primitives::Matrix4x4* SceneNode::getInverseTransformation( ) {
   updateTransformation( );
   return const_cast<primitives::Matrix4x4*>( &m_oInverseTransformation );
}

void SceneNode::doScaling( float fScaling ) {
   SRTNode::doScaling( fScaling );
   m_bNeedUpdateTransformation = true;
} // setScaling

void SceneNode::doTranslation( const primitives::Vector3D &rkTranslation ) {	
   SRTNode::doTranslation( rkTranslation );
   m_bNeedUpdateTransformation = true;
} // setTranslation

void SceneNode::doRotation( const primitives::Quaternion &rkRotation ) {
   SRTNode::doRotation( rkRotation );
   m_bNeedUpdateTransformation = true;
} // setRotation

bool SceneNode::render( Frustum *pFrustum ) {
   if ( !RenderEntity::render( pFrustum ) ) {
      return false;
   } // if      
   
   if ( m_pRenderEntity ) {
      m_pRenderEntity->render( pFrustum );
   } // if
   
   std::vector<SceneNode* >::iterator ppNode = m_vpChildrenNodes.begin( );
   std::vector<SceneNode* >::iterator ppEnd = m_vpChildrenNodes.end( );
   
   while ( ppNode != ppEnd ) {            
      (*ppNode)->render( pFrustum );      
      //TODO: check bounding volume      
      ppNode++;
   } // while	
   
   return true;   
   
} // render

	}; // scenenode
}; // namespace powergine
