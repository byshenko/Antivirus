import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    id: root

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: dock.top

        anchors.margins: 3
        spacing: 3

        Text {

        }

        TextField {
            id: path_to_file_or_dir
            Layout.fillWidth: true
            placeholderText: "Folder or File for Scan"
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                id: proccessButton
                Layout.fillWidth: true
                text: "Scan"

                onClicked: {
                    scanner.scan(path_to_file_or_dir.text)
                }
            }

            Button {
                id: virusTotalButton
                Layout.fillWidth: true
                text: "Scan via VirusTotal"

                onClicked: {
                    scanner.scan(path_to_file_or_dir.text)
                }
            }
        }

        ScrollView {
           ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
           ScrollBar.vertical.policy: ScrollBar.AlwaysOn
           ScrollBar.vertical.position: scrollPosition
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
        onClickedScan: { /* From page Scan can't go to page Scan */ }
        onClickedStatus: { stackView.replace(status_page) }
        onClickedUpdate: { stackView.replace(update_page) }
        onClickedQuarantine: { stackView.replace(quarantine_page) }
        onClickedSettings: { stackView.replace(settings_page) }
    }
}
