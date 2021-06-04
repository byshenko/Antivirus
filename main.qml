import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

import './dockPages'

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Open Source Antivirus")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: scan_page

        pushEnter: topTransition // empty animation for stackView.push
        replaceEnter: topTransition // empty animation for stackView.replace

        Transition {
            id: topTransition
        }
    }

    Scan {
        id: scan_page
        visible: true
    }

    Status {
        id: status_page
        visible: false
    }

    Update {
        id: update_page
        visible: false
    }

    Quarantine {
        id: quarantine_page
        visible: false
    }

    Settings {
        id: settings_page
        visible: false
    }




}
