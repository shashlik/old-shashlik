/*
 * Copyright (C) 2007 The Android Open Source Project
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

package com.android.commands.launch;

import android.app.ActivityManager;
import android.app.ActivityManagerNative;
import android.app.IActivityController;
import android.app.IActivityManager;
import android.app.IInstrumentationWatcher;
import android.app.Instrumentation;
import android.content.ComponentName;
import android.content.Context;
import android.content.IIntentReceiver;
import android.content.Intent;
import android.content.pm.IPackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.SystemProperties;
import android.os.UserHandle;
import android.util.AndroidException;
import android.view.Display;
import android.view.IWindowManager;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.URISyntaxException;
import java.util.HashSet;
import java.util.List;
import android.util.Log;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageUserState;
import android.content.pm.PackageParser;
import android.util.DisplayMetrics;

/**
 * Launch  <xxx.apk>
 */

public class Launch {
    private static final String TAG = "Launch";
    private IPackageManager mPM;
    private IActivityManager mAm;

    /**
     * Command-line entry point.
     *
     * @param args The command-line arguments
     */
    public static void main(String[] args) {
        (new Launch()).run(args);
    }
    private void init() throws AndroidException {
        IPackageManager mPM = IPackageManager.Stub.asInterface(ServiceManager.getService("package"));
        mAm = ActivityManagerNative.getDefault();
        if (mAm == null) {
            throw new AndroidException("Can't connect to activity manager; is the system running?");
        }
    }

    private void run(String[] args) {
        try {
            init();
        }
        catch(AndroidException e) {
            log("Activity manager is null - this is not a viable situation when we need to launch activities!");
            return;
        }
        if (args.length <1) {
            showUsage();
            return;
        }

        String command = args[0];
        if(args.length == 1){
            PackageInfo info = getPackageArchiveInfo(command, PackageManager.GET_ACTIVITIES);
            if(info != null){
                ApplicationInfo appInfo = info.applicationInfo;
                String packageName = appInfo.packageName;
                String className = info.activities[0].name;
                log("-->packageName=" + packageName);
                log("-->className=" + className);
                log("-->all activities:");
                for(int i = 0; i <info.activities.length; i++){
                    log(info.activities[i]);
                }
                startApp(packageName, className);
                //String execCmd= "am start -n " + packageName + "/" + className;
                //log(execCmd);
                //runLinuxCmd(execCmd);
            }
            return ;
        }
        System.err.println("Error: Invalid arguments for command: " + command);
        showUsage();
    }


    private PackageInfo getPackageArchiveInfo(String archiveFilePath, int flags) {
        PackageParser packageParser = new PackageParser(archiveFilePath);
        DisplayMetrics metrics = new DisplayMetrics();
        metrics.setToDefaults();
        final File sourceFile = new File(archiveFilePath);
        PackageParser.Package pkg = packageParser.parsePackage(
                sourceFile, archiveFilePath, metrics, 0);
        if (pkg == null) {
            return null;
        }
        if ((flags & PackageManager.GET_SIGNATURES) != 0) {
            packageParser.collectCertificates(pkg, 0);
        }
        PackageUserState state = new PackageUserState();
        return PackageParser.generatePackageInfo(pkg, null, flags, 0, 0, null, state);
    }

    private Process runLinuxCmd(String cmd){
        Process process = null;
        try{
            process = Runtime.getRuntime().exec(cmd);
            return process;
        } catch(IOException e){
            Log.d(TAG, "runLinuxCmd error:" +e);
        }
        return process;
    }

    private void startApp(String packageName, String className){
        log("Creating intent...");
        Intent intent = new Intent();
        log("Adding new task activity flag");
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        log("Creating component for this package and class: " + packageName + " " + className);
        ComponentName comp = new ComponentName(packageName, className);
        log("Setting component for the intent");
        intent.setComponent(comp);
        try{
            //mAm.startActivityAndWait(null, null, intent, mimeType,
            //                    null, null, 0, mStartFlags, mProfileFile, fd, null, mUserId);
            log("Attempt to start the activity for this package using activity manager " + mAm);
            mAm.startActivityAndWait(null, null, intent, "",
                                null, null, 0, 0, "", null, null, 0);
        }catch(RemoteException e){
            log("startApp error:"  + e);
        }
    }

    private void showUsage() {
        System.err.println("usage: input ...");
        System.err.println("       launch <path of apk>");
    }

    private void log(Object o){
        System.err.println("" + o);
    }
}
