import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

Page {

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Scan")
    }

    Dock {
        onClickedScan: { /* From page Scan can't go to page Scan */ }
        onClickedStatus: { stackView.replace(status_page) }
        onClickedUpdate: { stackView.replace(update_page) }
        onClickedQuarantine: { stackView.replace(quarantine_page) }
        onClickedSettings: { stackView.replace(settings_page) }
    }
}
