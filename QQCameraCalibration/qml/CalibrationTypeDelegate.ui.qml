import QtQuick 2.7
import QtQuick.Layouts 1.1

Item {
    id: root

    property alias title: title
    property alias image: image
    signal clicked(string id)

    Rectangle {
        id: rectangle1
        color: mouseArea.containsMouse ? "#f3f3f3" : "#ffffff"
        anchors.fill: parent

        ColumnLayout {
            id: column
            anchors.rightMargin: 4
            anchors.bottomMargin: 4
            anchors.leftMargin: 4
            anchors.topMargin: 4
            spacing: 10
            anchors.fill: parent

            Text {
                id: title
                Layout.fillWidth: true

                text: qsTr("Text")
                font.pixelSize: 12
            }

            Image {
                id: image
                Layout.fillHeight: true
                Layout.fillWidth: true

                fillMode: Image.PreserveAspectFit
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton
            onClicked: {
                root.clicked(name)
            }
        }
    }
}
