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

#define LOG_TAG "ProcessState"

//#include <cutils/process_name.h>

//#include <binder/ProcessState.h>

//#include <utils/Atomic.h>
//#include <binder/BpBinder.h>
//#include <binder/IPCThreadState.h>
//#include <utils/Log.h>
//#include <utils/String8.h>
//#include <binder/IServiceManager.h>
//#include <utils/String8.h>
//#include <utils/threads.h>

//#include <private/binder/binder_module.h>
//#include <private/binder/Static.h>

//#include <errno.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>
//#include <sys/stat.h>

#define BINDER_VM_SIZE ((1*1024*1024) - (4096 *2))


// SHASHLIK NOTE: This file contains as much as is needed from libs/binder/ProcessState.cpp
//                in frameworks-native to make main.cpp build.


// ---------------------------------------------------------------------------

namespace android {
 
// Global variables
int                 mArgC;
const char* const*  mArgV;
int                 mArgLen;

        
}; // namespace android
