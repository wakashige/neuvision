import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {

    SwipeView {
        id: swipeView
        Layout.fillHeight: true
        Layout.fillWidth: true
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    TabBar {
        id: tabBar
        Layout.fillWidth: true
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }

}
