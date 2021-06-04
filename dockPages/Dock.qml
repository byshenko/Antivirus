import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Item {
    id: root

    signal clickedScan()
    signal clickedStatus()
    signal clickedUpdate()
    signal clickedQuarantine()
    signal clickedSettings()
    signal clicked()

    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right

    height: parent.height / 5

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            DockButton {
                btn_text: "Scan"
                img_path: "img/radar.png"
                onClicked: root.clickedScan()
            }

            DockButton {
                btn_text: "Status"
                img_path: "img/status.png"
                onClicked: root.clickedStatus()
            }

            DockButton {
                btn_text: "Update"
                img_path: "img/update.png"
                onClicked: root.clickedUpdate()
            }

            DockButton {
                btn_text: "Quarantine"
                img_path: "img/quarantine.png"
                onClicked: root.clickedQuarantine()
            }

            DockButton {
                btn_text: "Settings"
                img_path: "img/settings.png"
                onClicked: {
                    root.clickedSettings()
                }
            }
        }
    }
}
