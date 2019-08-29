// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef VIDEOPROPERTIES_H
#define VIDEOPROPERTIES_H

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * Configuration of the video
			 */
			class VideoProperties {

			public:
				static const VideoProperties DEFAULTPROPERTIES;
				// Max 32 Bits
				enum PROPERTIES {
				  DOUBLEBUFFER         = 0x00000001, // 001 - 0000001
				  FULLSCREEN           = 0x00000002, // 002 - 0000010
				  HARDWAREACCELERATED  = 0x00000004, // 004 - 0000100
				  RESIZABLE            = 0x00000008, // 008 - 0001000
				  NOFRAME              = 0x00000010  // 016 - 0010000
				};

				// Starts a video properties from a given property data
				VideoProperties( int iProperties );

				// Remove all defined properties
				void reset( );

				// Update the video properties with the given argument
				void setProperties( int iProperties );

				// Returns the defined properties
				int getProperties( ) const;

				// Sets true a given property
				void addProperty( PROPERTIES eProperty );

				// Sets false a given property
				void removeProperty( PROPERTIES eProperty );

				// Toggles the value of a given property
				void toggleProperty( PROPERTIES eProperty );

				// Checks if a given property was set or no
				bool isSet( PROPERTIES eProperty );

			private:
				int m_iProperties;
			};

		}; // video
	}; // service
}; // powergine


#endif
