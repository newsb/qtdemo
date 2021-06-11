import QtQuick 2.12
import QtQuick.Window 2.12
//import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.14
Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        text: "Push Me"
        anchors.centerIn: parent
        onClicked: {
            console.log('xxxx:'+chb1.left)
        }
    }

    CheckBox {
        id: chb1
        text: "checked"
    }

    Rectangle {
        width: 200
        height: 100
        color: 'red'
    }


}
