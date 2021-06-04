import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Status")
    }

    Dock {
        onClickedScan: { stackView.replace(scan_page) }
        onClickedStatus: { /* From page Status can't go to page Status */ }
        onClickedUpdate: { stackView.replace(update_page) }
        onClickedQuarantine: { stackView.replace(quarantine_page) }
        onClickedSettings: { stackView.replace(settings_page) }
    }

}
