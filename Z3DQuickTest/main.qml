import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import QuickVTK 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    /*
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        VtkViewer {
            mouseEnabled: true;
            smooth: true
            antialiasing: true
        }

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("VTK")
        }
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
*/
    StackView {
        id: stack
        anchors.fill: parent
        initialItem: mainView
    }

    Component {
        id: mainView

        Item {
            //            anchors.fill: parent

            VtkViewer {
                anchors.fill: parent
                mouseEnabled: true;
                smooth: true
                antialiasing: true
            }

            Button {
                anchors.centerIn: parent
                text: "click me"
                opacity: 0.5
                onClicked: stack.push(manualAlignView)
            }
        }
    }

    //    Component {
    Item {
        id: manualAlignView
        //                anchors.fill: parent
        visible: false

        RowLayout {
            anchors.fill: parent

            VtkViewer {
//                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 300
                Layout.minimumHeight: 300

                mouseEnabled: true;
                smooth: true
                antialiasing: true
            }

            VtkViewer {
//                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 300
                Layout.minimumHeight: 300

                mouseEnabled: true;
                smooth: true
                antialiasing: true
            }

            Button {
                text: "back"
                opacity: 0.5
                onClicked: stack.pop()
            }
        }
    }
}
