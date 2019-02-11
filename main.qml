import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CommandClient")

    Component.onCompleted: dataModel.append({"name": "Search"})

    Connections {
        target: client

        onSignalToQmlHost: {
            dataModel2.append({"name": str})
        }

        onSignalToQmlConnect: {
            dataModel.clear()
            dataModel.append({"name": "Reboot"})
            dataModel.append({"name": "Shutdown"})
        }

        onSignalToQmlDisconnect: {
            dataModel.clear()
            dataModel2.clear()
            dataModel.append({"name": "Search"})
        }
    }

    function changeFunc(i) {
        if (i === 0) {
            client.sendDatagram()
        } else  if (i === 1){
            dataModel2.append({"name": "first"})
            dataModel2.append({"name": "seecond"})
            dataModel2.append({"name": "third"})
        } else if (i === 2) {
            dataModel.clear()
            dataModel2.clear()
            dataModel.append({"name": "Start"})
        }
    }

    Column {
        id: mainButton
        width: parent.width
        height: parent.height / 3
        anchors {
            top: parent.top
            topMargin: parent.height / 5
        }
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
                    if (dataModel.count < 2)
                        changeFunc(index)
                    else
                        client.sendCommand(name)
                }
            }
        }
    }

    Column {
        id: hostsButton
        width: parent.width
        anchors {
            top: mainButton.bottom
            topMargin: parent.height / 15
            bottom: parent.bottom
        }
        ListView {
            id: listViewHostsButton
            anchors.fill: parent
            spacing: 10
            model: ListModel {
                id: dataModel2
            }
            delegate: Button {
                height: listViewHostsButton.height / 5
                width: listViewHostsButton.width
                text: name
                onClicked: {
                    client.connectHost(index)
                }
            }
        }
    }
}
