/*
 * Copyright (c) 2011, Kevin LeBlanc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */




//=============================================================================
#ifndef INCLUDE_TELEOP_SOURCE_JOYSTICK_HPP
#define INCLUDE_TELEOP_SOURCE_JOYSTICK_HPP
//=============================================================================




//=============================================================================
//Includes
//=============================================================================
#include <teleop_common.hpp>
#include <teleop_source.hpp>
#include <linux/joystick.h>




//=============================================================================
//Namespace
//=============================================================================
namespace teleop {




//=============================================================================
//Classes
//=============================================================================

/**
 * This class implements a joystick teleop source.
 */
class TeleopSourceJoystick : public TeleopSource {

public:

  /**
   * Constructor.
   *
   *   @param callback [in] - callback to call with updated teleop state
   *   @param device [in] - device file
   */
  TeleopSourceJoystick(TeleopSourceCallback callback, std::string device = getDefaultDevice());

  /**
   * Get default device
   *
   *   @return default device
   */
  static std::string getDefaultDevice();

private:

  /** Device */
  std::string mDevice;

  /** File descriptor*/
  int mFileDescriptor;

  /** Number of axes */
  uint8_t mNumAxes;

  /** Axis map */
  uint8_t mAxisMap[ABS_CNT];

  /** Number of buttons */
  uint8_t mNumButtons;

  /** Button map */
  uint16_t mButtonMap[KEY_MAX - BTN_MISC + 1];

  /**
   * Convert axis event value (from joystick) to teleop value ([-1.0,1.0]).
   *
   *   @param value [in] - event axis value to convert
   *
   *   @return teleop axis value
   */
  static float axisEventValueToTeleopValue(int16_t value);

  /**
   * Convert button event value (from joystick) to teleop value.
   *
   *   @param value [in] - event button value to convert
   *
   *   @return teleop button value
   */
  static int buttonEventValueToTeleopValue(int16_t value);

  /**
   * Convert axis event type (from joystick) to teleop axis type.
   *
   *   @param type [in] - event axis type to convert
   *
   *   @return teleop axis type
   */
  static int axisEventTypeToTeleopType(uint8_t type);

  /**
   * Convert button event type (from joystick) to teleop button type.
   *
   *   @param type [in] - event button type to convert
   *
   *   @return teleop button type
   */
  static int buttonEventTypeToTeleopType(uint16_t type);

  /**
   * Internal method for handling each event.
   *
   *   @param event [in] - event to handle
   *   @param teleop [in/out] - the current teleop output, to be updated
   *
   *   @return LISTEN_ERROR on error, LISTEN_STATE_UNCHANGED on timeout or no
   *           change to state, LISTEN_STATE_CHANGED if state updated
   */
  int handleEvent(js_event* event, TeleopState* teleopState);

  /**
   * Override virtual method from parent.
   */
  bool prepareToListen();

  /**
   * Override virtual method from parent.
   */
  int listen(int timeoutSeconds, TeleopState* teleop);

  /**
   * Override virtual method from parent.
   */
  bool doneListening();

}; //class




//=============================================================================
} //namespace
//=============================================================================




//=============================================================================
#endif //#ifndef INCLUDE_TELEOP_SOURCE_JOYSTICK_HPP
//=============================================================================
