/*
Keyboard.h
Copyright (c) 2005-2014 Arduino.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __KEYBOARDAPI__
#define __KEYBOARDAPI__

// to access the HID_SendReport via USBAPI.h, report number and the Print class
#include "Arduino.h"

//TODO workaround to access the weak sending function
void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
//================================================================================
//	Keyboard

#define KEY_PRINT			0xCE
#define KEY_NUM_LOCK		0xDB
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_LEFT_WINDOWS KEY_LEFT_GUI
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87
#define KEY_RIGHT_WINDOWS KEY_RIGHT_GUI

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD

#define LED_NUM_LOCK			0x01
#define LED_CAPS_LOCK			0x02
#define LED_SCROLL_LOCK			0x04

//	Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
	uint8_t modifiers;
	uint8_t reserved;
	uint8_t keys[6];
} KeyReport;

// extern accessible led out report
#if defined(HID_KEYBOARD_LEDS_ENABLED)
extern uint8_t hid_keyboard_leds;
#endif

class Keyboard_ : public Print
{
protected:
	KeyReport _keyReport;
	void sendReport(KeyReport* keys);
public:
	inline Keyboard_(void){
		// empty
	}

	inline void begin(void){
		// edit by NicoHood
		end();
	}

	inline void end(void){
		// edit by NicoHood
		releaseAll();
	}

	size_t write(uint8_t k);
	size_t press(uint8_t k);
	inline size_t release(uint8_t k);
	void releaseAll(void);

	size_t writeKeycode(uint8_t k);
	size_t pressKeycode(uint8_t k);
	size_t releaseKeycode(uint8_t k);
	size_t addKeycodeToReport(uint8_t k);
	size_t removeKeycodeFromReport(uint8_t k);

#if defined(HID_KEYBOARD_LEDS_ENABLED)
	inline uint8_t getLEDs(void){ return hid_keyboard_leds; }
#endif
};
extern Keyboard_ Keyboard;

#endif