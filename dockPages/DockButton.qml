import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

RowLayout {
    id: root

    property string img_path
    property string btn_text

    signal clicked()

    Button {
        icon.source: img_path
        icon.width: parent.width
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: {
            root.clicked()
        }

        Text {
            text: btn_text
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
        }
    }
}
