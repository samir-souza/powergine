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

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <vector>
#include <powergine/services/video/rendermode.h>
#include <powergine/services/video/videoproperties.h>

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * This class represents a window used by the renderer to
			 * render the scene. It has one or more render modes and
			 * some video properties.
			 */
			class RenderWindow {

			public:
				RenderWindow( RenderMode *pRenderMode,
							 const VideoProperties &rkProperties = VideoProperties::DEFAULTPROPERTIES );

				virtual ~RenderWindow( );

				// Returns the current render mode
				const RenderMode* getCurrentRenderMode( ) const;

				// Updates the current render mode
				bool setCurrentRenderMode( RenderMode *pRenderMode );

				// Adds a new render mode
				bool addRenderMode( RenderMode *pRenderMode );

				// Remove a registered render mode
				bool removeRenderMode( RenderMode *pRenderMode );

				// Returns a list with all available (registered) render modes
				std::vector<RenderMode*>& getRenderModes( );

				// Returns the current video properties
				VideoProperties* getProperties( ) const;

			private:

				RenderMode *m_pCurrentRenderMode;
				std::vector<RenderMode*> m_vRenderModes;
				VideoProperties m_oProperties;

			};

		}; // video
	}; // services
}; // namespace powergine

#endif //RENDERWINDOW_H
