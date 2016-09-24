import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Layouts 1.0

import "./configurations"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Z3D Camera Calibration")

    header: ToolBar {

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                visible: stackView.depth > 1
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/drawer.png"
                }
                onClicked: stackView.pop()
            }

            Label {
                id: titleLabel
                text: "Select calibration pattern"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                        onTriggered: settingsPopup.open()
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                }
            }

            Behavior on Layout.preferredWidth {
                NumberAnimation { duration: 1000 }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: calibrationTypeSelection
    }

    Component {
        id: calibrationTypeSelection
        CalibrationTypePage {
            anchors.fill: parent
            onCalibrationTypeSelected: {
                stackView.push(calibrationConfiguration, {text: id})
            }
        }
    }

    Component {
        id: calibrationConfiguration
        CheckerboardConfig {

            anchors.fill: parent
        }
    }
}
