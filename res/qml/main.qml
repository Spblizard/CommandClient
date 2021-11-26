import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CommandClient")

    Component.onCompleted: client.sendDatagram()

    Connections {
        target: client

        onSignalToQmlHost: {
            dataModel.append({"name": str})
        }
    }

    Item {
        id: mainButton
        width: parent.width
        height: parent.height / 3
        anchors.centerIn: parent
        ListView {
            id: listViewMainButton
            anchors.fill: parent
            spacing: 15
            model: ListModel {
                id: dataModel
            }
            delegate: Button {
                height: listViewMainButton.height / 5
                width: listViewMainButton.width
                text: name
                onClicked: {
                    client.sendCommand(name)
                }
            }
        }
    }
}
