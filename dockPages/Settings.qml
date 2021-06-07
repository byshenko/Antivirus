import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: dock.top

        anchors.margins: 3
        spacing: 3

        Text {
            // empty
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: virusTotalApiKey
                Layout.fillWidth: true
                placeholderText: "VirusTotal API Key"
            }

            Button {
                id: virusTotalButton
                text: "Save"

                onClicked: {
                    scanner.saveVirustotalApiKey(virusTotalApiKey.text)
                }
            }
        }

        ScrollView {
           ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
           ScrollBar.vertical.policy: ScrollBar.AlwaysOn
           Layout.fillHeight: true
           Layout.fillWidth: true
           TextArea {
               id: data
               anchors.fill: parent
               text: scanner.scanProgress
               readOnly: true
               selectByMouse: true
           }
        }
    }

    Dock {
        id: dock
        onClickedScan: { stackView.replace(scan_page) }
        onClickedStatus: { stackView.replace(status_page) }
        onClickedUpdate: { stackView.replace(update_page) }
        onClickedQuarantine: { stackView.replace(quarantine_page) }
        onClickedSettings: { /* From page Settings can't go to page Settings */ }
    }

}
