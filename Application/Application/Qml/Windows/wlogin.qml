import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Window
{
    id: window
    width: 1280
    height: 720
	visible: true
	flags: Qt.FramelessWindowHint | Qt.Window

    Connections
    {
        target: window_login
    }

    Rectangle
    {

        width: parent.width
        height: parent.height
        Image
        {
            id: cover
            source: "qrc:/image_space.jpg"
        }
        radius: 5
    }

    Item
    {
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width
        height: 32

        MouseArea {
            property var clickPos
            anchors.fill: parent
            onPressed: {
                clickPos = { x: mouse.x, y: mouse.y }
            }
            onPositionChanged: {
                window.x = window_login.cursorPos().x - clickPos.x
                window.y = window_login.cursorPos().y - clickPos.y
            }
        }

        Row
        {

           anchors.right: parent.right

            Rectangle
            {
                id: line
                width: 46
                height: 32
                color: "transparent"

                Image
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: 11
                    height: 11
                    source: "qrc:/Themes/White/line_button.svg"
                }

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true

                    property bool state: true

                    onHoveredChanged:
                    {
                        if (state) { parent.color = "gray"; state = false; } else { parent.color = "transparent"; state = true; }
                    }

                    onClicked:
                    {
                        window.showMinimized()
                    }
                }
            }

            Rectangle
            {
                id: square
                width: 46
                height: 32
                color: "transparent"

                Image
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 10
                    height: 10
                    source: "qrc:/Themes/White/square_button.svg"
                }

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true

                    property bool state: true

                    onHoveredChanged:
                    {
                        if (state) { parent.color = "gray"; state = false; } else { parent.color = "transparent"; state = true; }
                    }

                    onClicked:
                    {
                        // in processing...
                    }
                }
            }

            Rectangle
            {
                id: cross
                width: 46
                height: 32
                color: "transparent"

                Image
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 10
                    height: 10
                    source: "qrc:/Themes/White/cross_button.svg"
                }

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true

                    property bool state: true

                    onHoveredChanged:
                    {
                        if (state) { parent.color = "red"; state = false; } else { parent.color = "transparent"; state = true; }
                    }

                    onClicked:
                    {
                        window.close()
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: place
        width: 350
        height: 450

        color: "#152c4c"
        opacity: 0.85

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter



        Rectangle
        {
            id: second_place
            width: 270
            height: 370

            color: "transparent"

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Column
            {
                id: login_place

                spacing: 60


                Row
                {
                    spacing: 80

                    Column
                    {
                        id: login

                        spacing: 4

                        Label
                        {
                            id: login_label
                            text: "Login"
                            color: "white"
                            font.pixelSize: 18

                            MouseArea
                            {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor

                                onClicked:
                                {
                                    login_label.color = "white";
                                    login_plate.visible = true;

                                    register_label.color = "#8096b3";
                                    register_plate.visible = false;

                                    button_login_text.text = "Login";
                                }
                            }

                        }

                        Rectangle
                        {
                            id: login_plate
                            width: login_label.width
                            height: 2
                            visible: true
                            color: "white"
                        }
                    }

                    Column
                    {
                        id: register
                        spacing: 4

                        Label
                        {
                            id: register_label
                            text: "Register"
                            color: "#8096b3"
                            font.pixelSize: 18

                            MouseArea
                            {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor

                                onClicked:
                                {
                                    register_label.color = "white";
                                    register_plate.visible = true;

                                    login_label.color = "#8096b3";
                                    login_plate.visible = false;

                                    button_login_text.text = "Register";
                                }
                            }
                        }

                        Rectangle
                        {
                            id: register_plate
                            width: register_label.width
                            height: 2
                            visible: false
                            color: "white"
                        }
                    }
                }
            }

            Column
            {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 40

                Column
                {

                    Label
                    {
                        id: login_text
                        text: "Name"
                        color: "#8096b3"
                        font.pixelSize: 14
                    }

                    TextField
                    {
                        id: login_field
                        width: second_place.width
                        height: 36
                        color: "white"
                        font.pixelSize: 18
                        placeholderText: "User name"

                        anchors.left: parent.left
                        anchors.leftMargin: -10

                        background:
                            Rectangle
                            {
                                color: "transparent"
                            }
                    }

                    Rectangle
                    {
                        width: second_place.width
                        height: 1
                        color: "#aaa"
                    }
                }

                Column
                {
                    Label
                    {
                        id: password_text
                        text: "Password"
                        color: "#8096b3"
                        font.pixelSize: 14
                    }

                    TextField
                    {
                        id: password_field
                        width: second_place.width
                        height: 36
                        color: "white"
                        font.pixelSize: 18
                        echoMode: TextField.Password
                        placeholderText: "Password"

                        anchors.left: parent.left
                        anchors.leftMargin: -10

                        background:
                            Rectangle
                            {
                                color: "transparent"
                            }
                    }

                    Rectangle
                    {
                        width: second_place.width
                        height: 1
                        color: "#aaa"
                    }
                }

                Item
                {
                    width: 5
                    height: 45
                }
            }

            Rectangle
            {
                id: button_login
                width: second_place.width
                height: 40
                color: "#284974"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 25

                Label
                {
                    id: button_login_text
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Login"
                    color: "white"
                    font.pixelSize: 18
                }

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    property bool state: false

                    onHoveredChanged:
                    {
                        if (!state)
                        {
                            button_login.color = "#28498e"
                            state = true
                        }
                        else
                        {
                            button_login.color = "#284974"
                            state = false
                        }
                    }

                    onClicked:
                    {
                        if (login_plate.visible) window_login.getLoginAndPassword(login_field.text, password_field.text, 0)
                        else window_login.getLoginAndPassword(login_field.text, password_field.text, 1);
                    }
                }
            }
        }
    }
}
