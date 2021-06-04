import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Quarantine")
    }

    Dock {
        onClickedScan: { stackView.replace(scan_page) }
        onClickedStatus: { stackView.replace(status_page) }
        onClickedUpdate: { stackView.replace(update_page) }
        onClickedQuarantine: { /* From page Quarantine can't go to page Quarantine */ }
        onClickedSettings: { stackView.replace(settings_page) }
    }
}
