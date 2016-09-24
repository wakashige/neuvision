import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ListView {

    signal calibrationTypeSelected(string id)

    model: ListModel {
        ListElement {
            name: "checkerboard"
        }
        ListElement {
            name: "circleGrid"
        }
        ListElement {
            name: "incompleteCircleGrid"
        }
    }

    delegate: CalibrationTypeDelegate {
        title.text: name
        height: 120
        width: parent.width
        onClicked: {
            console.log("clicked:" + id)
            calibrationTypeSelected(id)
        }
    }
}
