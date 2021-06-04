import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Update")
    }

    Dock {
        onClickedScan: { stackView.replace(scan_page) }
        onClickedStatus: { stackView.replace(status_page) }
        onClickedUpdate: { /* From page Update can't go to page Update */ }
        onClickedQuarantine: { stackView.replace(quarantine_page) }
        onClickedSettings: { stackView.replace(settings_page) }
    }

}
