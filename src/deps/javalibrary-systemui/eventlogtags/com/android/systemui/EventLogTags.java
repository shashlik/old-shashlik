/* This file is auto-generated.  DO NOT MODIFY.
 * Source file: frameworks/base/packages/SystemUI/src/com/android/systemui/EventLogTags.logtags
 */

package com.android.systemui;;

/**
 * @hide
 */
public class EventLogTags {
  private EventLogTags() { }  // don't instantiate

  /** 36000 sysui_statusbar_touch (type|1),(x|1),(y|1),(enabled|1) */
  public static final int SYSUI_STATUSBAR_TOUCH = 36000;

  /** 36010 sysui_panelbar_touch (type|1),(x|1),(y|1),(enabled|1) */
  public static final int SYSUI_PANELBAR_TOUCH = 36010;

  /** 36020 sysui_notificationpanel_touch (type|1),(x|1),(y|1) */
  public static final int SYSUI_NOTIFICATIONPANEL_TOUCH = 36020;

  /** 36030 sysui_quickpanel_touch (type|1),(x|1),(y|1) */
  public static final int SYSUI_QUICKPANEL_TOUCH = 36030;

  /** 36040 sysui_panelholder_touch (type|1),(x|1),(y|1) */
  public static final int SYSUI_PANELHOLDER_TOUCH = 36040;

  /** 36050 sysui_searchpanel_touch (type|1),(x|1),(y|1) */
  public static final int SYSUI_SEARCHPANEL_TOUCH = 36050;

  public static void writeSysuiStatusbarTouch(int type, int x, int y, int enabled) {
    android.util.EventLog.writeEvent(SYSUI_STATUSBAR_TOUCH, type, x, y, enabled);
  }

  public static void writeSysuiPanelbarTouch(int type, int x, int y, int enabled) {
    android.util.EventLog.writeEvent(SYSUI_PANELBAR_TOUCH, type, x, y, enabled);
  }

  public static void writeSysuiNotificationpanelTouch(int type, int x, int y) {
    android.util.EventLog.writeEvent(SYSUI_NOTIFICATIONPANEL_TOUCH, type, x, y);
  }

  public static void writeSysuiQuickpanelTouch(int type, int x, int y) {
    android.util.EventLog.writeEvent(SYSUI_QUICKPANEL_TOUCH, type, x, y);
  }

  public static void writeSysuiPanelholderTouch(int type, int x, int y) {
    android.util.EventLog.writeEvent(SYSUI_PANELHOLDER_TOUCH, type, x, y);
  }

  public static void writeSysuiSearchpanelTouch(int type, int x, int y) {
    android.util.EventLog.writeEvent(SYSUI_SEARCHPANEL_TOUCH, type, x, y);
  }
}
