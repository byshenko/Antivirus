import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Item {

    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right

    height: parent.height / 5

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Button {
                icon.source: "img/radar.png"
                icon.width: parent.width
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Scan"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                }
            }

            Button {
                icon.source: "img/status.png"
                icon.width: parent.width
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Status"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                }
            }

            Button {
                icon.source: "img/update.png"
                icon.width: parent.width
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Update"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                }
            }

            Button {
                icon.source: "img/quarantine.png"
                icon.width: parent.width
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Quarantine"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                }
            }

            Button {
                icon.source: "img/settings.png"
                icon.width: parent.width
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Settings"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                }
            }
        }
    }
}
