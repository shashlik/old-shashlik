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

import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.components 2.0 as PlasmaComponents

Item {
    id: base;
    height: units.gridUnit * 2;
    width: parent.width;
    signal startService();
    property alias text: label.text;
    property bool running;

    PlasmaExtras.Title {
        id: label
        anchors {
            left: parent.left
            leftMargin: height / 3;
            right: indicator.left
        }
        elide: Text.ElideRight
    }
    Item {
        id: indicator;
        anchors {
            top: parent.top;
            right: parent.right;
            bottom: parent.bottom;
        }
        width: height;
        Rectangle {
            anchors.centerIn: parent;
            height: parent.height / 2;
            width: height;
            radius: height / 2;
            color: base.running ? "green" : "red";
        }
        PlasmaComponents.ToolButton {
            anchors {
                verticalCenter: parent.verticalCenter;
                right: parent.left;
            }
            iconSource: "media-playback-start"
            height: parent.height;
            width: height;
            opacity: base.running ? 0 : 1;
            Behavior on opacity { PropertyAnimation { duration: 200; } }
            onClicked: base.startService();
        }
    }
}
