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

#ifndef CORE_H
#define CORE_H

#include <powergine/services/video/videomanager.h>
#include <powergine/services/input/inputmanager.h>
#include <powergine/services/comm/communicationmanager.h>

#include <powergine/services/video/opengl/oglvideomanager.h>
#include <powergine/services/input/sdl/sdlinputmanager.h>

#include <powergine/primitives/vertexelement.h>

#include <powergine/primitives/vertex.h>

#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/vertexnormal.h>
#include <powergine/primitives/vertextexture.h>

#include <powergine/primitives/vertexdiffusenormal.h>
#include <powergine/primitives/vertextexturenormal.h>
#include <powergine/primitives/vertextexturediffuse.h>

#include <powergine/primitives/vertextexturediffusenormal.h>

namespace powergine {

	/**
	 * Class Core
	 * This class is a singleton. It contains a shortcut for all
	 * services of the Engine. You must access the services
	 * through this class.
	 */
	class Core {
	public:
		// Static method for retrieving the class singleton object
		static Core* get( );

		// Getter of the video manager
		services::video::VideoManager* getVideoManager( ) const;

		// Getter of the input manager
		services::input::InputManager* getInputManager( ) const;

		// Getter of the communication manager (network)
		services::comm::CommunicationManager* getCommManager( );

		virtual ~Core( );

		// Instantiate a new video manager and registers it
		void createVideoManager( services::video::RenderMode *pRenderMode,
								services::video::VideoManager::MANAGER_TYPE eManagerType =
								services::video::VideoManager::MANAGER_OPENGL );

		// Instantiate a new input manager and registers it
		void createInputManager( services::input::InputManager::MANAGER_TYPE eManagerType =
								services::input::InputManager::MANAGER_SDL );

		// Initialization method. You must pass the main() arguments
		// to this mechod
		virtual int initialize( int argc, char* argv[] );

		// Close all services and finalize the Engine
		virtual void finalize( ) { };

		// Make the system sleeps for a given number of milliseconds
		virtual void sleep( long lMilliseconds ) = 0;

	protected:
		// Protected constructor to avoid the existence of more than one instance
		// of this class
		inline Core( ) : m_pVideoManager( 0 ), m_pInputManager( 0 ) { }

	private:
		// Singleton attribute
		static Core *m_pSingleton;

		services::video::VideoManager *m_pVideoManager;
		services::input::InputManager *m_pInputManager;
		services::comm::CommunicationManager *m_pCommManager;
	};

}; // powergine

#endif //CORE_H
