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
//Includes
//=============================================================================
#include <teleop_common.hpp>
#include <teleop_source.hpp>
#include <teleop_source_keyboard.hpp>
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <sys/select.h>




//=============================================================================
//Namespace
//=============================================================================
namespace teleop {




//=============================================================================
//Method definitions
//=============================================================================
TeleopSourceKeyboard::TeleopSourceKeyboard(TeleopSourceCallback callback,
                                           int steps)
  : TeleopSource(callback), mSteps(steps) {
  //Clamp steps
  if (STEPS_MIN > mSteps) {
    mSteps = STEPS_MIN;
  } else if (STEPS_MAX < mSteps) {
    mSteps = STEPS_MAX;
  }

  //Compute step size
  mStepSize = (float)(TELEOP_AXIS_MAX - TELEOP_AXIS_MIN)/(2*mSteps);
}
//=============================================================================
bool TeleopSourceKeyboard::prepareToListen() {
  //Raw termios settings
  struct termios rawTermios;

  //Remember old termios settings for stdin
  tcgetattr(STDIN_FILENO, &mOldTermios);
  memcpy(&rawTermios, &mOldTermios, sizeof(struct termios));

  //Update stdin to use raw mode
  rawTermios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &rawTermios);

  //Print welcome message
  printf("Use arrow keys to move and space to stop...\n");

  //Return result
  return true;
}
//=============================================================================
int TeleopSourceKeyboard::listen(int timeoutSeconds, TeleopState* teleopState) {
  //Sanity check
  if (NULL == teleopState) {
    printf("TeleopSourceKeyboard::listen: NULL teleop state\n");
    return LISTEN_ERROR;
  }

  //Ensure state has correct number of axes and buttons
  if (2 != teleopState->axes.size()) {
    TeleopAxis teleopAxisEmpty = {0, 0.0};
    teleopState->axes.resize(2, teleopAxisEmpty);
    teleopState->axes[0].type  = TELEOP_AXIS_TYPE_LIN_X;
    teleopState->axes[0].value = 0.0;
    teleopState->axes[1].type  = TELEOP_AXIS_TYPE_LIN_Y;
    teleopState->axes[1].value = 0.0;
  }
  if (0 != teleopState->buttons.size()) {
    teleopState->buttons.clear();
  }

  //Initialise a file descriptor set with stdin for select
  fd_set fileDescriptorSet;
  FD_ZERO (&fileDescriptorSet);
  FD_SET (STDIN_FILENO, &fileDescriptorSet);

  //Initialise timeout value in seconds for select
  struct timeval timeout;
  timeout.tv_sec = timeoutSeconds;
  timeout.tv_usec = 0;

  //Use select to see if anything shows up before timeout
  char c;
  int result = select(1, &fileDescriptorSet, NULL, NULL, &timeout);
  switch (result) {
    case 0:
      //Timeout
      return LISTEN_STATE_UNCHANGED;
    case -1:
      //Error
      printf("TeleopSourceKeyboard::listen: error in select() (%d)\n", errno);
      return LISTEN_ERROR;
    default:
      //Data available
      if(read(STDIN_FILENO, &c, 1) <= 0) {
        printf("TeleopSourceKeyboard::listen: error in read()\n");
        return LISTEN_ERROR;
      }
  }

  //Handle known keys
  switch(c) {
    case KEYCODE_UP:
      if (teleopState->axes[0].value >= TELEOP_AXIS_MAX) {
        return LISTEN_STATE_UNCHANGED;
      }
      teleopState->axes[0].value += mStepSize;
      if (teleopState->axes[0].value > TELEOP_AXIS_MAX) {
        teleopState->axes[0].value = TELEOP_AXIS_MAX;
      }
      return LISTEN_STATE_CHANGED;
    case KEYCODE_DOWN:
      if (teleopState->axes[0].value <= TELEOP_AXIS_MIN) {
        return LISTEN_STATE_UNCHANGED;
      }
      teleopState->axes[0].value -= mStepSize;
      if (teleopState->axes[0].value < TELEOP_AXIS_MIN) {
        teleopState->axes[0].value = TELEOP_AXIS_MIN;
      }
      return LISTEN_STATE_CHANGED;
    case KEYCODE_LEFT:
      if (teleopState->axes[1].value <= TELEOP_AXIS_MIN) {
        return LISTEN_STATE_UNCHANGED;
      }
      teleopState->axes[1].value -= mStepSize;
      if (teleopState->axes[1].value < TELEOP_AXIS_MIN) {
        teleopState->axes[1].value = TELEOP_AXIS_MIN;
      }
      return LISTEN_STATE_CHANGED;
    case KEYCODE_RIGHT:
      if (teleopState->axes[1].value >= TELEOP_AXIS_MAX) {
        return LISTEN_STATE_UNCHANGED;
      }
      teleopState->axes[1].value += mStepSize;
      if (teleopState->axes[1].value > TELEOP_AXIS_MAX) {
        teleopState->axes[1].value = TELEOP_AXIS_MAX;
      }
      return LISTEN_STATE_CHANGED;
    case KEYCODE_SPACE:
      teleopState->axes[0].value = 0.0;
      teleopState->axes[1].value = 0.0;
      return LISTEN_STATE_CHANGED;
  }

  //Return no change
  return LISTEN_STATE_UNCHANGED;
}
//=============================================================================
bool TeleopSourceKeyboard::doneListening() {
  //Restore stdin to old values
  tcsetattr(STDIN_FILENO, TCSANOW, &mOldTermios);

  //Return result
  return true;
}
//=============================================================================




//=============================================================================
} //namespace
//=============================================================================
