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

#ifndef KEYEVENT_H
#define KEYEVENT_H

namespace powergine {
	namespace services {
		namespace input {
			namespace events {

			/**
			 * It represents an event produced by a Keyboard action
			 */
			class KeyEvent {

			public:

			   // Keyboar ASCII Codes
			   enum KBD_CODE {
				  KBD_BACKSPACE	= 8,
				  KBD_TAB		= 9,
				  KBD_CLEAR		= 12,
				  KBD_RETURN	= 13,
				  KBD_PAUSE		= 19,
				  KBD_ESCAPE	= 27,
				  KBD_SPACE		= 32,
				  KBD_EXCLAIM	= 33,
				  KBD_QUOTEDBL	= 34,
				  KBD_HASH		= 35,
				  KBD_DOLLAR	= 36,
				  KBD_AMPERSAND	= 38,
				  KBD_QUOTE		= 39,
				  KBD_LEFTPAREN	= 40,
				  KBD_RIGHTPAREN	= 41,
				  KBD_ASTERISK	= 42,
				  KBD_PLUS		= 43,
				  KBD_COMMA		= 44,
				  KBD_MINUS		= 45,
				  KBD_PERIOD	= 46,
				  KBD_SLASH		= 47,
				  KBD_0		= 48,
				  KBD_1		= 49,
				  KBD_2		= 50,
				  KBD_3		= 51,
				  KBD_4		= 52,
				  KBD_5		= 53,
				  KBD_6		= 54,
				  KBD_7		= 55,
				  KBD_8		= 56,
				  KBD_9		= 57,
				  KBD_COLON		= 58,
				  KBD_SEMICOLON	= 59,
				  KBD_LESS		= 60,
				  KBD_EQUALS	= 61,
				  KBD_GREATER	= 62,
				  KBD_QUESTION	= 63,
				  KBD_AT		= 64,

				  // upper case letters
				  KBD_A		= 65,
				  KBD_B		= 66,
				  KBD_C		= 67,
				  KBD_D		= 68,
				  KBD_E		= 69,
				  KBD_F		= 70,
				  KBD_G		= 71,
				  KBD_H		= 72,
				  KBD_I		= 73,
				  KBD_J		= 74,
				  KBD_K		= 75,
				  KBD_L		= 76,
				  KBD_M		= 77,
				  KBD_N		= 78,
				  KBD_O		= 79,
				  KBD_P		= 80,
				  KBD_Q		= 81,
				  KBD_R		= 82,
				  KBD_S		= 83,
				  KBD_T		= 84,
				  KBD_U		= 84,
				  KBD_V		= 86,
				  KBD_W		= 87,
				  KBD_X		= 88,
				  KBD_Y		= 89,
				  KBD_Z		= 90,
				  KBD_LEFTBRACKET	= 91,
				  KBD_BACKSLASH	= 92,
				  KBD_RIGHTBRACKET	= 93,
				  KBD_CARET		= 94,
				  KBD_UNDERSCORE	= 95,
				  KBD_BACKQUOTE	= 96,
				  // begin lower case letters
				  KBD_a		= 97,
				  KBD_b		= 98,
				  KBD_c		= 99,
				  KBD_d		= 100,
				  KBD_e		= 101,
				  KBD_f		= 102,
				  KBD_g		= 103,
				  KBD_h		= 104,
				  KBD_i		= 105,
				  KBD_j		= 106,
				  KBD_k		= 107,
				  KBD_l		= 108,
				  KBD_m		= 109,
				  KBD_n		= 110,
				  KBD_o		= 111,
				  KBD_p		= 112,
				  KBD_q		= 113,
				  KBD_r		= 114,
				  KBD_s		= 115,
				  KBD_t		= 116,
				  KBD_u		= 117,
				  KBD_v		= 118,
				  KBD_w		= 119,
				  KBD_x		= 120,
				  KBD_y		= 121,
				  KBD_z		= 122,


				  KBD_DELETE	= 127,

				  // Numeric keypad
				  KBD_KP0		= 256,
				  KBD_KP1		= 257,
				  KBD_KP2		= 258,
				  KBD_KP3		= 259,
				  KBD_KP4		= 260,
				  KBD_KP5		= 261,
				  KBD_KP6		= 262,
				  KBD_KP7		= 263,
				  KBD_KP8		= 264,
				  KBD_KP9		= 265,
				  KBD_KP_PERIOD	= 266,
				  KBD_KP_DIVIDE	= 267,
				  KBD_KP_MULTIPLY	= 268,
				  KBD_KP_MINUS	= 269,
				  KBD_KP_PLUS	= 270,
				  KBD_KP_ENTER	= 271,
				  KBD_KP_EQUALS	= 272,

				  // Arrows + Home/End pad
				  KBD_UP		= 273,
				  KBD_DOWN		= 274,
				  KBD_RIGHT		= 275,
				  KBD_LEFT		= 276,
				  KBD_INSERT	= 277,
				  KBD_HOME		= 278,
				  KBD_END		= 279,
				  KBD_PAGEUP	= 280,
				  KBD_PAGEDOWN	= 281,

				  // Function keys
				  KBD_F1		= 282,
				  KBD_F2		= 283,
				  KBD_F3		= 284,
				  KBD_F4		= 285,
				  KBD_F5		= 286,
				  KBD_F6		= 287,
				  KBD_F7		= 288,
				  KBD_F8		= 289,
				  KBD_F9		= 290,
				  KBD_F10		= 291,
				  KBD_F11		= 292,
				  KBD_F12		= 293,
				  KBD_F13		= 294,
				  KBD_F14		= 295,
				  KBD_F15		= 296,

				  // Key state modifier keys
				  KBD_NUMLOCK	= 300,
				  KBD_CAPSLOCK	= 301,
				  KBD_SCROLLOCK	= 302,
				  KBD_RSHIFT	= 303,
				  KBD_LSHIFT	= 304,
				  KBD_RCTRL		= 305,
				  KBD_LCTRL		= 306,
				  KBD_RALT		= 307,
				  KBD_LALT		= 308,
				  KBD_RMETA		= 309,
				  KBD_LMETA		= 310,
				  KBD_LSUPER	= 311,	// Left "Windows" key
				  KBD_RSUPER	= 312,	// Right "Windows" key
				  KBD_MODE		= 313,	// "Alt Gr" key
				  KBD_COMPOSE	= 314,	// Multi-key compose key

				  // Miscellaneous function keys
				  KBD_HELP		= 315,
				  KBD_PRINT		= 316,
				  KBD_SYSREQ	= 317,
				  KBD_BREAK		= 318,
				  KBD_MENU		= 319,
				  KBD_POWER		= 320,	// Power Macintosh power key
				  KBD_EURO		= 321,	// Some european keyboards
				  KBD_UNDO		= 322,	// Atari keyboard has Undo

			   };

			   enum KEY_STATE {
				  KEY_RELEASED   = 0,
				  KEY_PRESSED    = 1
			   };


			   inline KeyEvent( int iCode, int iState ) :
				  m_iCode( iCode ), m_iState( iState ) { };

			   // Returns the key code
			   inline int getCode( ) const { return m_iCode; }

			   // Returns the state of the event
			   inline int getState( ) const { return m_iState; }

			private:
			   int m_iCode;
			   int m_iState;
			};

			}; // events
		}; // input
	}; // services
}; // powergine

#endif //KEYEVENT_H
