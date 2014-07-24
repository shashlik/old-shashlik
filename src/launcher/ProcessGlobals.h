/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// SHASHLIK NOTE: This file contains as much as is needed from libs/binder/ProcessState.cpp
//                in frameworks-native to make main.cpp build.


#ifndef SHASHLIK_PROCESS_GLOBALS_H
#define SHASHLIK_PROCESS_GLOBALS_H

//#include <binder/IBinder.h>
//#include <utils/KeyedVector.h>
//#include <utils/String8.h>
//#include <utils/String16.h>

//#include <utils/threads.h>

// ---------------------------------------------------------------------------
namespace android {

// Global variables
extern int                 mArgC;
extern const char* const*  mArgV;
extern int                 mArgLen;

    
}; // namespace android

// ---------------------------------------------------------------------------

#endif // ANDROID_PROCESS_STATE_H
