import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Layouts 1.0

ColumnLayout {

    GroupBox {
        title: "Size"

        ColumnLayout {

            RowLayout {
                width: parent.width
                Text {
                    text: "Columns"
                    Layout.fillWidth: true
                }

                SpinBox {
                    value: 15
                    from: 3
                }
            }

            RowLayout {
                width: parent.width
                Text {
                    text: "Rows"
                    Layout.fillWidth: true
                }

                SpinBox {
                    value: 15
                    from: 3
                }
            }
        }
    }

    GroupBox {
        title: "Options"

        ColumnLayout {

            RowLayout {
                width: parent.width
                Text {
                    text: "Use adaptive threshold"
                    Layout.fillWidth: true
                }

                Switch {
                    checked: true
                }
            }

            RowLayout {
                width: parent.width
                Text {
                    text: "Normalize image"
                    Layout.fillWidth: true
                }

                Switch {
                    checked: true
                }
            }
        }
    }
}
