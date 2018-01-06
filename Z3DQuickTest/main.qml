import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

import QtGraphicalEffects 1.0

import QuickVTK 1.0

ApplicationWindow {
    id: registerWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Z3D")
    background: Rectangle { color: backgroundColor }

    property color backgroundColor: Qt.rgba(0.925, 0.925, 0.925, 1)

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            id: leftToolbar
            z: 2
            width: 68
            Layout.fillHeight: true

            Item {
                width: 200
                height: parent.height
                x: mouseArea.containsMouse ? 0 : parent.width - width

                Behavior on x {
                    NumberAnimation {
                        duration: 300
                        easing.type: Easing.OutExpo
                    }
                }

                MouseArea {
                    id: mouseArea
                    hoverEnabled: true
                    anchors.fill: parent

                    Rectangle {
                        anchors.fill: parent
                        color: Qt.rgba(0.2, 0.2, 0.2, 1)

                        Button {
                            id: fileButton
                            width: parent.width
                            text: "Open file"
                            onClicked: {
                                fileDialog.open()
                            }

                            FileDialog {
                                id: fileDialog
                                title: "Please choose a file"
                                folder: shortcuts.home
                                nameFilters: [ "Point cloud files (*.pcd *.ply)", "All files (*)" ]
                                onAccepted: {
                                    console.log("You chose: " + fileDialog.fileUrls)
                                }
                                onRejected: {
                                    console.log("Canceled")
                                }
                            }
                        }
                    }

                    /*Item {
                        visible: mouseArea.containsMouse
                        anchors.right: parent.right
                        anchors.rightMargin: -2
                        height: parent.height
                        width: 3

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.height
                            height: 3
                            rotation: -90
                            transformOrigin: Item.Center
                            gradient: Gradient {
                                GradientStop {
                                    position: 0.0;
                                    color: Qt.rgba(0, 0, 0, 1)
                                }
                                GradientStop {
                                    position: 1.0;
                                    color: Qt.rgba(0.2, 0.2, 0.2, 0)
                                }
                            }
                        }
                    }*/
                }
            }
        }

        StackView {
            id: stack
            z: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 200

            initialItem: mainView

            pushEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 200
                    easing.type: Easing.OutExpo
                }
                PropertyAnimation {
                    property: "x"
                    from: 100
                    to: 0
                    duration: 200
                    easing.type: Easing.OutExpo
                }
            }
            pushExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to: 0.5
                    duration: 200
                    easing.type: Easing.OutExpo
                }
            }
            popEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0.5
                    to: 1
                    duration: 200
                    easing.type: Easing.OutExpo
                }
            }
            popExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 200
                    easing.type: Easing.OutExpo
                }
                PropertyAnimation {
                    property: "x"
                    from: 0
                    to: 100
                    duration: 200
                    easing.type: Easing.OutExpo
                }
            }

            Component {
                id: mainView

                Item {
                    VtkViewer {
                        anchors.fill: parent
                        mouseEnabled: true;
                    }

                    Button {
                        anchors.centerIn: parent
                        text: "click me"
                        opacity: 0.5
                        onClicked: stack.push(settingsView)
                    }
                }
            }

            Component {
                id: settingsView

                Item {
                    Rectangle {
                        anchors.fill: parent
                        color: backgroundColor
                    }

                    Button {
                        anchors.centerIn: parent
                        text: "back"
                        onClicked: stack.pop()
                    }
                }
            }
        }
    }
}
