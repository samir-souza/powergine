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


#include <powergine/sceneobjects/camera.h>

namespace powergine {
	namespace sceneobjects {
	
Camera *Camera::s_pCurrentActiveCamera = 0;
	
// Constructors/Destructors
Camera::Camera( std::string strName ) :
	SceneNode( strName )
{
  
}

void Camera::lookAt( const primitives::Vector3D &rkViewingDirection, const primitives::Vector3D &rkUpDirection ) {
   primitives::Vector3D oVD = rkViewingDirection;
   primitives::Vector3D oZAxis = getWorldTranslation( ) - rkViewingDirection;
   oZAxis.normalize( );

   //This is unstable if new oZAxis equals oUp vector
   primitives::Vector3D oXAxis = oVD ^ oZAxis;
   oXAxis.normalize( );

   primitives::Vector3D oYAxis = oZAxis ^ oXAxis;
   oYAxis.normalize( );

   primitives::Matrix4x4 oMatrix;

   oMatrix.setElement( 0, 0, oXAxis.getX( ) );
   oMatrix.setElement( 1, 0, oXAxis.getY( ) );
   oMatrix.setElement( 2, 0, oXAxis.getZ( ) );
   oMatrix.setElement( 3, 0, 0.0f );

   oMatrix.setElement( 0, 1, oYAxis.getX( ) );
   oMatrix.setElement( 1, 1, oYAxis.getY( ) );
   oMatrix.setElement( 2, 1, oYAxis.getZ( ) );
   oMatrix.setElement( 3, 1, 0.0f );

   oMatrix.setElement( 0, 2, oZAxis.getX( ));
   oMatrix.setElement( 1, 2, oZAxis.getY( ) );
   oMatrix.setElement( 2, 2, oZAxis.getZ( ) );
   oMatrix.setElement( 3, 2, 0.0f );

   oMatrix.setElement( 0, 3, 0.0f );
   oMatrix.setElement( 1, 3, 0.0f );
   oMatrix.setElement( 2, 3, 0.0f );
   oMatrix.setElement( 3, 3, 1.0f );
   
   setRotation( primitives::Quaternion( oMatrix ) );

}

void Camera::update( float fDeltaTime ) {
   if ( m_pRoom->isActive( ) ) {
      m_pRoom->update( fDeltaTime );
   } // if
} // update

bool Camera::render( Frustum *pFrustum ) {

   if ( !Core::get( ) ) {
      throw( std::string( "Get core failed" ) );
   } // if
   if ( !m_pRoom ) {
      throw( std::string( "Room is not defined to camera" ) );
   } // if

   setActive( );   

   Frustum oFrustum;
   
   const primitives::Matrix4x4 &rkProjection =
      Core::get( )->getVideoManager( )->getProjectionMatrix( );   
   
   float fZNear = Core::get( )->getVideoManager( )->getZNear( );
   float fZFar = Core::get( )->getVideoManager( )->getZFar( );   
     
   float fWidth  = 2.0f * fZNear / rkProjection.getElement( 0, 0 );   
   float fHeight = 2.0f * fZNear / rkProjection.getElement( 1, 1 );   

   
   primitives::Quaternion oWorldRotation = getWorldRotation( );
   primitives::Vector3D   oWorldPosition = getWorldTranslation( );
   
   primitives::Vector3D oVecOne;
   primitives::Vector3D oVecTwo;
   primitives::Vector3D oNormal;
   float fDistance;
   
   const primitives::Matrix4x4 &rkViewProjection = oWorldRotation.toMatrix4x4( );   
      
   
   //Left clipping plane
   oVecOne.setX( -fWidth * 0.5f );
   oVecOne.setY( fHeight * 0.5f );
   oVecOne.setZ( -fZNear );

   oVecTwo.setX( -fWidth * 0.5f );
   oVecTwo.setY( -fHeight * 0.5f );
   oVecTwo.setZ( -fZNear );
   
   oNormal = oVecOne ^ oVecTwo;
   oNormal.normalize( );
   oNormal = rkViewProjection * oNormal;
   
   // dot product to find distance between plane and position
   fDistance = -( oNormal * oWorldPosition );
   
   oFrustum.getPlane( Frustum::PLANE_LEFT ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_LEFT ).setDistanceToOrigo( fDistance );
   

   //Right clipping plane
   oVecOne.setX(  fWidth * 0.5f );
   oVecOne.setY( -fHeight * 0.5f );
   oVecOne.setZ( -fZNear );

   oVecTwo.setX(  fWidth * 0.5f );
   oVecTwo.setY(  fHeight * 0.5f );
   oVecTwo.setZ( -fZNear );

   oNormal   = oVecOne ^ oVecTwo;
   oNormal.normalize( );
   oNormal   = rkViewProjection * oNormal;
   
   fDistance = -( oNormal * oWorldPosition );
   
   oFrustum.getPlane( Frustum::PLANE_RIGHT ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_RIGHT ).setDistanceToOrigo( fDistance );

   //Top clipping plane
   oVecOne.setX(  fWidth * 0.5f );
   oVecOne.setY( fHeight * 0.5f );
   oVecOne.setZ( -fZNear );

   oVecTwo.setX(  -fWidth * 0.5f );
   oVecTwo.setY( fHeight * 0.5f );
   oVecTwo.setZ( -fZNear );

   oNormal   = oVecOne ^ oVecTwo;
   oNormal.normalize( );
   oNormal   = rkViewProjection * oNormal;
   
   fDistance = -( oNormal * oWorldPosition );
   
   oFrustum.getPlane( Frustum::PLANE_TOP ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_TOP ).setDistanceToOrigo( fDistance );  

   //Bottom clipping plane
   oVecOne.setX(  -fWidth * 0.5f );
   oVecOne.setY( -fHeight * 0.5f );
   oVecOne.setZ( -fZNear );

   oVecTwo.setX(  fWidth * 0.5f );
   oVecTwo.setY( -fHeight * 0.5f );
   oVecTwo.setZ( -fZNear );

   oNormal   = oVecOne ^ oVecTwo;
   oNormal.normalize( );
   oNormal   = rkViewProjection * oNormal;

   fDistance = -( oNormal * oWorldPosition );
   oFrustum.getPlane( Frustum::PLANE_BOTTOM ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_BOTTOM ).setDistanceToOrigo( fDistance );

   // Near clipping plane
   // get second colum of projection matrix
   oNormal.setX( rkViewProjection.getElement( 0, 2 ) );
   oNormal.setY( rkViewProjection.getElement( 1, 2 ) );
   oNormal.setZ( rkViewProjection.getElement( 2, 2 ) );

   oVecOne   = oWorldPosition;
   oVecOne  += oNormal * -fZNear;
   fDistance    = -( oNormal * oVecOne );
   
   oFrustum.getPlane( Frustum::PLANE_NEAR ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_NEAR ).setDistanceToOrigo( fDistance );


   // Far clipping plane
   // get negative values from second colum of projection matrix
   oNormal.setX( -rkViewProjection.getElement( 0, 2 ) );
   oNormal.setY( -rkViewProjection.getElement( 1, 2 ) );
   oNormal.setZ( -rkViewProjection.getElement( 2, 2 ) );

   oVecOne   = oWorldPosition;
   oVecOne  += oNormal * fZFar;
   fDistance    = -( oNormal * oVecOne );
   
   oFrustum.getPlane( Frustum::PLANE_FAR ).setNormal( oNormal );
   oFrustum.getPlane( Frustum::PLANE_FAR ).setDistanceToOrigo( fDistance );
   

/*
   for( int i = 0; i < 6; i++ ) {
      oFrustum.m_aiPVertexSign[i][0] = ( oFrustum.m_aoPlanes[i].m_oNormal.x < 0.0f ) ? 1 : 0;  //1 means negative sign
      oFrustum.m_aiPVertexSign[i][1] = ( oFrustum.m_aoPlanes[i].m_kNormal.y < 0.0f ) ? 1 : 0;
      oFrustum.m_aiPVertexSign[i][2] = ( oFrustum.m_aoPlanes[i].m_oNormal.z < 0.0f ) ? 1 : 0;
   
      oFrustum.m_aiNVertexSign[i][0] = ( oFrustum.m_aoPlanes[i].m_oNormal.x < 0.0f ) ? 0 : 1;
      oFrustum.m_aiNVertexSign[i][1] = ( oFrustum.m_aoPlanes[i].m_oNormal.y < 0.0f ) ? 0 : 1;
      oFrustum.m_aiNVertexSign[i][2] = ( oFrustum.m_aoPlanes[i].m_oNormal.z < 0.0f ) ? 0 : 1;
   } // for
*/

   //Store data
   oFrustum.setTranslation(   getWorldTranslation( ) );
   oFrustum.setRotation(      getWorldRotation( ) );
   oFrustum.setViewDirection( oFrustum.getPlane( Frustum::PLANE_FAR ).getNormal( ) );
   oFrustum.setZNear(         fZNear );
   oFrustum.setZFar(          fZFar );
  
   //oFrustum.renderOutlines( primitives::Color::BLUE );
   return m_pRoom->render( &oFrustum );
} // render

Camera* Camera::getActive( ) {
   return s_pCurrentActiveCamera;
}

void Camera::setActive( ) {
   s_pCurrentActiveCamera = this;
}

primitives::Matrix4x4* Camera::getTransformation( ) {
   return SceneNode::getInverseTransformation( );
}


	}; // sceneobjects
}; // namespace powergine
