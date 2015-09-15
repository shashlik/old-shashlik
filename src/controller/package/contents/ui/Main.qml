/***************************************************************************
 *                                                                         *
 *   Copyright 2015 Dan Leinir Turthra Jensen <admin@leinir.dk>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

import QtQuick 2.2
import QtQuick.Dialogs 1.2

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.kquickcontrolsaddons 2.0

Rectangle {
    id: base;
    height: 600;
    width: 600;
    color: theme.backgroundColor

    Image {
        id: appBackground
        source: "image://appbackgrounds/standard"
        fillMode: Image.Tile
        asynchronous: true
        anchors.fill: parent;

        Item {
            id: contentsBase
            objectName: "contentsBase"
            state: "expanded"
            anchors.fill: parent

            property bool loading: false

            Item {
                id: navheader

                height: childrenRect.height
                anchors {
                    margins: units.gridUnit
                    bottomMargin: 0
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                PlasmaCore.IconItem {
                    id: topIcon
                    width: units.gridUnit * 2
                    height: width
                    opacity: loadingIndicator.running ? 0 : 1.0
                    Behavior on opacity { NumberAnimation { duration: units.shortDuration } }
                    source: "shashlik-controller"
                    anchors {
                        verticalCenter: title.verticalCenter
                        right: parent.right
                        margins: units.gridUnit
                        rightMargin: 0
                    }
                }

                PlasmaComponents.BusyIndicator {
                    id: loadingIndicator
                    anchors.fill: topIcon
                    opacity: running ? 1.0 : 0
                    Behavior on opacity { NumberAnimation { duration: units.shortDuration } }
                    running: contentsBase.loading
                }

                PlasmaExtras.Title {
                    id: title
                    anchors {
                        left: parent.left
                        right: topIcon.left
                    }
                    elide: Text.ElideRight
                    text: i18n("Android Runtime Controller")

                }

                PlasmaCore.SvgItem {
                    svg: PlasmaCore.Svg {imagePath: "widgets/line"}
                    elementId: "horizontal-line"
                    height: naturalSize.height
                    anchors {
                        top: title.bottom
                        topMargin: units.gridUnit / 2
                        left: parent.left
                        right: parent.right
                        leftMargin: -units.gridUnit
                        rightMargin: -units.gridUnit
                    }
                }
            }

            Item {
                id: runApkContainer;
                clip: true;
                height: runApkButton.enabled ? units.gridUnit * 4 : 0;
                Behavior on height { NumberAnimation { duration: 200; } }
                anchors {
                    top: navheader.bottom;
                    left: parent.left;
                    right: parent.right;
                }
                PlasmaComponents.Button {
                    id: runApkButton;
                    width: base.width / 2;
                    height: units.gridUnit * 2;
                    anchors.centerIn: parent;
                    text: "Run an apk...";
                    enabled: shashlikController.zygoteRunning;
                    onClicked: fileDialog.open();
                }
            }
            Column {
                id: serviceColumn;
                anchors {
                    top: runApkContainer.bottom;
                    left: parent.left;
                    right: parent.right;
                }
                height: childrenRect.height;
                ControlEntry {
                    text: "Zygote";
                    running: shashlikController.zygoteRunning;
                    onStartService: shashlikController.startZygote();
                }
                ControlEntry {
                    text: "Installer Daemon";
                    running: shashlikController.installdRunning;
                    onStartService: shashlikController.startInstalld();
                }
                ControlEntry {
                    text: "Android Debug Daemon";
                    running: shashlikController.adbdRunning;
                    onStartService: shashlikController.startAdbd();
                }
                ControlEntry {
                    text: "SurfaceFlinger";
                    running: shashlikController.surfaceflingerRunning;
                    onStartService: shashlikController.startSurfaceflinger();
                }
                ControlEntry {
                    text: "Service Manager";
                    running: shashlikController.servicemanagerRunning;
                    onStartService: shashlikController.startServicemanager();
                }
                ControlEntry {
                    text: "Bootanimation";
                    running: shashlikController.bootanimationRunning;
                    onStartService: shashlikController.startBootanimation();
                }
            }
            Row {
                id: serviceControlRow;
                anchors {
                    left: parent.left;
                    right: parent.right;
                    bottom: parent.bottom;
                }
                PlasmaComponents.Button {
                    width: base.width / 2;
                    height: units.gridUnit * 2;
                    text: stopButton.enabled ? "Restart all services" : "Start all services";
                    onClicked: shashlikController.restart();
                }
                PlasmaComponents.Button {
                    id: stopButton;
                    width: base.width / 2;
                    height: units.gridUnit * 2;
                    text: "Stop all services";
                    enabled: shashlikController.surfaceflingerRunning || shashlikController.servicemanagerRunning || shashlikController.installdRunning || shashlikController.adbdRunning || shashlikController.zygoteRunning || shashlikController.bootanimationRunning;
                    onClicked: shashlikController.stop();
                }
            }
        }
    }
    FileDialog {
        id: fileDialog;
        title: "Please Choose an Android package";
        folder: shortcuts.home;
        nameFilters: [ "Android packages (*.apk)", "All files (*)" ];
        onAccepted: {
            shashlikController.runApk(fileDialog.fileUrl);
        }
    }
}
