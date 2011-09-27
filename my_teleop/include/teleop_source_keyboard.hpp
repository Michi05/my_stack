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
#ifndef INCLUDE_TELEOP_SOURCE_KEYBOARD_HPP
#define INCLUDE_TELEOP_SOURCE_KEYBOARD_HPP
//=============================================================================




//=============================================================================
//Includes
//=============================================================================
#include <teleop_common.hpp>
#include <teleop_source.hpp>
#include <termios.h>




//=============================================================================
//Namespace
//=============================================================================
namespace teleop {




//=============================================================================
//Classes
//=============================================================================

/**
 * This class implements a keyboard teleop source.  The arrow keys are used as
 * linear X and linear Y axes, and the space bar acts as a stop button.  The
 * key presses are detected by reading raw standard input using termios.  If
 * this class is used, other uses of standard input from within the same
 * process should be handled carefully.
 *
 * An alternative could be to detect low-level key press and release events,
 * but this would probably require either access to the X server (which we
 * shouldn't need for a keyboard teleop device), or access to linux inputs in
 * the /dev/input/event* files (which normally requires elevated privileges).
 */
class TeleopSourceKeyboard : public TeleopSource {

public:

  /** Default number of steps to reach the maximum level for each axis */
  static const int STEPS_DEFAULT = 5;

  /** Minimum number of steps allowed */
  static const int STEPS_MIN = 1;

  /** Maximum number of steps allowed */
  static const int STEPS_MAX = 10;

  /**
   * Constructor.
   *
   *   @param callback [in] - callback to call with updated teleop state
   *   @param steps [in] - number of steps needed to reach max value for each axis
   */
  TeleopSourceKeyboard(TeleopSourceCallback callback, int steps=STEPS_DEFAULT);

private:

  /**@{ Keycodes */
  static const int KEYCODE_SPACE = 0x20;
  static const int KEYCODE_UP    = 0x41;
  static const int KEYCODE_DOWN  = 0x42;
  static const int KEYCODE_RIGHT = 0x43;
  static const int KEYCODE_LEFT  = 0x44;
  /**@}*/

  /** Number of steps needed to reach max value for each axis */
  int mSteps;

  /** Size of each step for each axis */
  float mStepSize;

  /** Old termios settings */
  struct termios mOldTermios;

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
#endif //#ifndef INCLUDE_TELEOP_SOURCE_KEYBOARD_HPP
//=============================================================================