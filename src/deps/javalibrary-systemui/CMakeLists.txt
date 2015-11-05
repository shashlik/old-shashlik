project(javalibrary_systemui)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/packages/SystemUI)

# this should be generated, this is cheating...
set(systemui_eventlogtags_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/eventlogtags/com/android/systemui/EventLogTags.java
)

set(systemui_SRCS
    ${REPO_PATH}/src/com/android/systemui/ExpandHelper.java
    ${REPO_PATH}/src/com/android/systemui/DessertCaseDream.java
    ${REPO_PATH}/src/com/android/systemui/settings/BrightnessController.java
    ${REPO_PATH}/src/com/android/systemui/settings/ToggleSlider.java
    ${REPO_PATH}/src/com/android/systemui/settings/BrightnessDialog.java
    ${REPO_PATH}/src/com/android/systemui/settings/SettingsUI.java
    ${REPO_PATH}/src/com/android/systemui/settings/CurrentUserTracker.java
    ${REPO_PATH}/src/com/android/systemui/Gefingerpoken.java
    ${REPO_PATH}/src/com/android/systemui/media/NotificationPlayer.java
    ${REPO_PATH}/src/com/android/systemui/media/RingtonePlayer.java
    ${REPO_PATH}/src/com/android/systemui/DessertCaseView.java
    ${REPO_PATH}/src/com/android/systemui/DessertCase.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/tv/TvStatusBar.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/ServiceMonitor.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/CommandQueue.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/SystemBars.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/KeyguardTouchDelegate.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PhoneStatusBar.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/NotificationPanelView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettingsContainerView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PanelView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/IconMerger.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/StatusBarWindowView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettingsScrollView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettingsBasicTile.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettingsModel.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PhoneStatusBarTransitions.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/NavigationBarView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettings.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PhoneStatusBarPolicy.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/QuickSettingsTileView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/NavigationBarTransitions.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PhoneStatusBarView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/SettingsPanelView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PanelHolder.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/BarTransitions.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/Ticker.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/PanelBar.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/TickerView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/phone/DemoStatusIcons.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/SignalClusterView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/GestureRecorder.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/AnimatedImageView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/WimaxIcons.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/Clock.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/HeadsUpNotificationView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/DeadZone.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/TelephonyIcons.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/LocationController.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/WifiIcons.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/KeyButtonView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/BatteryController.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/BluetoothController.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/NetworkController.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/AccessibilityContentDescriptions.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/NotificationRowLayout.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/DateView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/RotationLockController.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/Prefs.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/policy/OnSizeChangedListener.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/DelegateViewHelper.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/StatusBarPanel.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/StatusBarIconView.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/BaseStatusBar.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/NotificationData.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/ExpandableNotificationRow.java
    ${REPO_PATH}/src/com/android/systemui/statusbar/LatestItemView.java
    ${REPO_PATH}/src/com/android/systemui/SwipeHelper.java
    ${REPO_PATH}/src/com/android/systemui/SystemUI.java
    ${REPO_PATH}/src/com/android/systemui/BatteryMeterView.java
    ${REPO_PATH}/src/com/android/systemui/screenshot/GlobalScreenshot.java
    ${REPO_PATH}/src/com/android/systemui/screenshot/TakeScreenshotService.java
    ${REPO_PATH}/src/com/android/systemui/SearchPanelView.java
    ${REPO_PATH}/src/com/android/systemui/Somnambulator.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsActivity.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsPanelView.java
    ${REPO_PATH}/src/com/android/systemui/recent/TaskDescription.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentTasksLoader.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsVerticalScrollView.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsPreloadReceiver.java
    ${REPO_PATH}/src/com/android/systemui/recent/FirstFrameAnimatorHelper.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsHorizontalScrollView.java
    ${REPO_PATH}/src/com/android/systemui/recent/FadedEdgeDrawHelper.java
    ${REPO_PATH}/src/com/android/systemui/recent/RecentsCallback.java
    ${REPO_PATH}/src/com/android/systemui/recent/ColorDrawableWithDimensions.java
    ${REPO_PATH}/src/com/android/systemui/recent/Recents.java
    ${REPO_PATH}/src/com/android/systemui/recent/Constants.java
    ${REPO_PATH}/src/com/android/systemui/BootReceiver.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbDisconnectedReceiver.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbStorageActivity.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbAccessoryUriActivity.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbPermissionActivity.java
    ${REPO_PATH}/src/com/android/systemui/usb/StorageNotification.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbResolverActivity.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbConfirmActivity.java
    ${REPO_PATH}/src/com/android/systemui/usb/UsbDebuggingActivity.java
    ${REPO_PATH}/src/com/android/systemui/DemoMode.java
    ${REPO_PATH}/src/com/android/systemui/SystemUIService.java
    ${REPO_PATH}/src/com/android/systemui/RecentsComponent.java
    ${REPO_PATH}/src/com/android/systemui/ImageWallpaper.java
    ${REPO_PATH}/src/com/android/systemui/LoadAverageService.java
    ${REPO_PATH}/src/com/android/systemui/power/PowerUI.java
    ${REPO_PATH}/src/com/android/systemui/net/NetworkOverLimitActivity.java
    ${CMAKE_CURRENT_BINARY_DIR}/com/android/systemui/R.java
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/com/android/systemui/R.java
    # build resources
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/dummy
    COMMAND jar cf package-export.apk dummy
    COMMAND zip -qd ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk dummy
    COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/dummy
#     COMMAND aapt package -u -z -c en_US,normal,ldpi,mdpi,hdpi,xhdpi,xxhdpi,nodpi --preferred-configurations hdpi -M ${REPO_PATH}/AndroidManifest.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk  --min-sdk-version 19 --target-sdk-version 19 --product default --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909   -F ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk
    COMMAND aapt package -u -z -c en_US,en_US,cs_CZ,da_DK,de_AT,de_CH,de_DE,de_LI,el_GR,en_AU,en_CA,en_GB,en_NZ,en_SG,eo_EU,es_ES,fr_CA,fr_CH,fr_BE,fr_FR,it_CH,it_IT,ja_JP,ko_KR,nb_NO,nl_BE,nl_NL,pl_PL,pt_PT,ru_RU,sv_SE,tr_TR,zh_CN,zh_HK,zh_TW,am_ET,hi_IN,en_US,fr_FR,it_IT,es_ES,de_DE,nl_NL,cs_CZ,pl_PL,ja_JP,zh_TW,zh_CN,ru_RU,ko_KR,nb_NO,es_US,da_DK,el_GR,tr_TR,pt_PT,pt_BR,rm_CH,sv_SE,bg_BG,ca_ES,en_GB,fi_FI,hi_IN,hr_HR,hu_HU,in_ID,iw_IL,lt_LT,lv_LV,ro_RO,sk_SK,sl_SI,sr_RS,uk_UA,vi_VN,tl_PH,ar_EG,fa_IR,th_TH,sw_TZ,ms_MY,af_ZA,zu_ZA,am_ET,hi_IN,mdpi,nodpi  -M ${REPO_PATH}/AndroidManifest.xml -S ${REPO_PATH}/res -A ${REPO_PATH}/res -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk --min-sdk-version 19 --target-sdk-version 19 --product tablet,nosdcard --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909   -F ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk
#     COMMAND aapt package -z -m  -J ${CMAKE_CURRENT_BINARY_DIR} -M ${REPO_PATH}/AndroidManifest.xml -P ${CMAKE_CURRENT_BINARY_DIR}/public_resources.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk -G ${CMAKE_CURRENT_BINARY_DIR}/proguard_options --min-sdk-version 19 --target-sdk-version 19 --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909
    COMMAND aapt package -z -m  -J ${CMAKE_CURRENT_BINARY_DIR} -M ${REPO_PATH}/AndroidManifest.xml -P ${CMAKE_CURRENT_BINARY_DIR}/public_resources.xml -S ${REPO_PATH}/res -A ${REPO_PATH}/res -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk --min-sdk-version 17 --target-sdk-version 17 --version-code 17 --version-name 4.4.4-eng.leinir.20150212.133909
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(SystemUI SOURCES ${systemui_SRCS} ${systemui_eventlogtags_SRC} INCLUDE_JARS core ext framework telephony-common)
