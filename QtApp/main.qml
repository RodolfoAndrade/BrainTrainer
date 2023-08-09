import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Mnmonic 1.0
import MentalMath 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MentalMath {
        id: math
    }

    ColumnLayout {
        id: mainWindowLayout
        anchors.left: parent.left; anchors.right: parent.right
        spacing: 0
        Button {
            id: button1
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Mnemonic Technique"
            onClicked: {
                popup.open()
                digits.text = mnmonic.generateDigits()
            }
        }
        Button {
            id: button2
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Mental Math"
            onClicked: {
                mathPopup.open()
                equation.text = math.generateEquation()
            }
        }
    }

    Popup {
        id: mathPopup
        width: 200
        height: 300
        modal: true
        focus: true
        anchors.centerIn: parent
        ColumnLayout {
            width: parent.width
            Label {
                Layout.fillWidth: true
                text: "Calculate the following equation mentally:"
                wrapMode: Text.WordWrap
            }
            Label {
                id: equation
            }
            TextArea {
                focus: true
                id: answer
                Keys.onEnterPressed: checkAnswer.clicked()
                Keys.onReturnPressed: checkAnswer.clicked()
            }
            Button {
                id: checkAnswer
                text: "Check"
                onClicked: {
                    output.text = math.checkAnswer(answer.text) ? "Correct! Play it again!" : "Wrong! Try again!"
                    equation.text = math.generateEquation()
                    answer.text = ""
                }
            }
            Label {
                id: output
            }
        }
    }

    Mnmonic {
        id: mnmonic
    }

    Popup {
        id: popup
        width: 200
        height: 300
        modal: true
        focus: true
        anchors.centerIn: parent
        ColumnLayout {
            width: parent.width
            Label {
                Layout.fillWidth: true
                text: "Number of digits:"
                wrapMode: Text.WordWrap
            }
            SpinBox {
                id: numberDigits
                value: 4
                onValueChanged: mnmonic.setNumberDigits(numberDigits.value)
            }
            Label {
                Layout.fillWidth: true
                text: "Memorize this sequence of digits using Dominic O'Brien Mnemonic Technique:"
                wrapMode: Text.WordWrap
            }
            TextArea {
                focus: true
                id: digits
                text: "1234"
                Keys.onReturnPressed: {
                    okButton.visible ? okButton.clicked() : checkButton.clicked()
                }
                Keys.onEnterPressed: {
                    okButton.visible ? okButton.clicked() : checkButton.clicked()
                }
            }
            Button {
                id: okButton
                text: "OK"
                onClicked: {
                    digits.clear()
                    okButton.visible = false
                    checkButton.visible = true
                    result.text = ""
                    correctDigits.text = ""
                    givenDigits.text = ""
                }
            }
            Button {
                id: checkButton
                text: "Check"
                visible: false
                onClicked: {
                    correctDigits.text = "Answer: " + mnmonic.getDigits()
                    givenDigits.text = "Typed: " + digits.text
                    result.text = mnmonic.checkDigits(digits.text) ? "Correct! Play it again!" : "Wrong! Try again!"
                    digits.text = mnmonic.generateDigits()
                    okButton.visible = true
                    checkButton.visible = false
                }
            }
            Label {
                id: result
            }
            Label {
                id: correctDigits
            }
            Label {
                id: givenDigits
            }
        }
    }
}
