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

template<class ClassType> inline Buffer<ClassType>::Buffer( int iNumElements ) :
   m_pucBuffer( new ClassType[ iNumElements ] ),
   m_iNumElements( iNumElements ),
   m_iTypeSize( sizeof( ClassType ) )
{
} // Buffer

template<class ClassType> ClassType inline &Buffer<ClassType>::getElementAt( int iIndex ) const {
   if ( iIndex < 0 || iIndex >= m_iNumElements ) {
      std::ostringstream sstrErrorMsg;
      sstrErrorMsg << iIndex;
      throw( std::out_of_range( sstrErrorMsg.str( ) ) );
   } // if
   return *( m_pucBuffer.get( ) + iIndex );
} // buffer

template<class ClassType> typename Buffer<ClassType>::iterator inline *Buffer<ClassType>::makeIterator( ) {
   return new BufferIterator( this );
} // makeIterator

template<class ClassType> unsigned char inline *Buffer<ClassType>::getData( ) {
   return reinterpret_cast<unsigned char*>( m_pucBuffer.get( ) );
} // getData



// implementation of buffer iterator
template<class ClassType> inline Buffer<ClassType>::BufferIterator::BufferIterator( const Buffer<ClassType> *pBuffer ) :
   m_pBuffer( pBuffer ),
   m_uiCursor( 0 )
{
} // BufferIterator

template<class ClassType> bool inline Buffer<ClassType>::BufferIterator::hasMore( ) const {
   return ( (int)m_uiCursor < m_pBuffer->getNumElements( ) );
} // hasMore

template<class ClassType> void inline Buffer<ClassType>::BufferIterator::goFirst( ) {
   m_uiCursor = 0;
} // goFirst

template<class ClassType> void inline Buffer<ClassType>::BufferIterator::goNext( ) {
   if ( this->hasMore( ) ) {
      ++m_uiCursor;
   } // if
} // goNext

template<class ClassType> ClassType inline &Buffer<ClassType>::BufferIterator::getCurrent( ) const {
   try {
      return m_pBuffer->getElementAt( m_uiCursor );
   } catch( std::out_of_range &ex ) {
      std::cerr << ex.what( ) << std::endl;
      return m_pBuffer->getElementAt( m_uiCursor - 1 );
   } // catch
} // getCurrent

