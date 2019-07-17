import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../../Styles/TextInputs"

import windows.fwindow 1.0

FWindow
{
    id: window
    m_width: 870;
    m_height: 720;
    m_minWidth: 870;
    m_minHeight: 720;
    m_maxWidth: 870;
    m_maxHeight: 720;

    visible: false

    FontLoader { id: localFont; source: "qrc:/Resources/Fonts/Gilroy.ttf" }

    Connections
    {
        target: wlRoot
        onDuplicateUsername:
        {
        	label_errors.visible = true;
        	label_errors.text = qsTr("That username is taken. Try another.");
        	field_username.m_colorUnderline = "red";
        }
        onUserIsNotFound:
        {
        	label_errors.visible = true;
        	label_errors.text = qsTr("Incorrect username or password.");
        }
    }

    Item
    {
        anchors.fill: parent;

        Item
        {
            id: left_field
            width: parent.width/2;
            height: parent.height;

            Image
            {
                anchors.fill: parent;
                source: "qrc:/Resources/Icons/background.png";
                sourceSize.width: parent.width;
                sourceSize.height: parent.height;
                smooth: true;

                Column
                {
                    anchors.fill: parent;
                    anchors.margins: 50;
                    spacing: 10;

                    Label
                    {
                        id: title
                        clip: true;
                        width: parent.width;
                        text: qsTr("Without music life would be a mistake");
                        font.pixelSize: 34;
                        font.bold: true;
                        wrapMode: Text.WordWrap
                        color: "#fff";
                        font.family: "Gilroy";
                    }

                    Item
                    {
                        width: parent.width;
                        height: 20;

                        Label
                        {
                            clip: true;
                            text: qsTr("Listen everywhere");
                            font.capitalization: Font.AllUppercase;
                            font.pixelSize: 11;
                            font.bold: true;
                            wrapMode: Text.WordWrap
                            color: "#307AF3";
                            font.family: "Gilroy";

                            anchors.left: parent.left;
                            anchors.leftMargin: 0;
                            anchors.verticalCenter: parent.verticalCenter;
                        }

                        Label
                        {
                            clip: true;
                            text: qsTr("Ad-free music");
                            font.capitalization: Font.AllUppercase;
                            font.pixelSize: 11;
                            font.bold: true;
                            wrapMode: Text.WordWrap
                            color: "#307AF3";
                            font.family: "Gilroy";

                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                        }

                        Label
                        {
                            clip: true;
                            text: qsTr("Download music");
                            font.capitalization: Font.AllUppercase;
                            font.pixelSize: 11;
                            font.bold: true;
                            wrapMode: Text.WordWrap
                            color: "#307AF3";
                            font.family: "Gilroy";

                            anchors.right: parent.right;
                            anchors.verticalCenter: parent.verticalCenter;
                        }
                    }
                }
            }
        }

        Item
        {
            id:  right_field;
            x:left_field.x + left_field.width;
            width: parent.width/2;
            height: parent.height;

            Item
            {
                width: parent.width;
                height: parent.height*3/4;

                RowLayout
                {
                    anchors.right: parent.right
                    height: 32
                    spacing: 0;

                    Rectangle
                    {
                        width: 48;
                        height: 32;
                        color: "transparent";

                        Image
                        {
                            id: substract
                            sourceSize.width: 10;
                            sourceSize.height: 10;
                            source: "qrc:/Resources/Icons/substract.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        MouseArea
                        {
                            anchors.fill: parent;
                            hoverEnabled: true;
                            property bool m_state: false;

                            onHoveredChanged:
                            {
                                m_state = m_state ? false : true;
                                parent.color = m_state ? "#E5E5E5" : "transparent";
                                substract.source = m_state ? "qrc:/Resources/Icons/substract_hovered.png" : "qrc:/Resources/Icons/substract.png";

                            }

                            onClicked:
                            {
                                window.showMinimized();
                            }
                        }
                    }

                    Rectangle
                    {
                        width: 48;
                        height: 32;
                        color: "transparent";

                        Image
                        {
                            id: cross
                            sourceSize.width: 10;
                            sourceSize.height: 10;
                            source: "qrc:/Resources/Icons/cross.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        MouseArea
                        {
                            anchors.fill: parent;
                            hoverEnabled: true;
                            property bool m_state: false;

                            onHoveredChanged:
                            {
                                m_state = m_state ? false : true;
                                parent.color = m_state ? "#E81123" : "transparent";
                                cross.source = m_state ? "qrc:/Resources/Icons/cross_hovered.png" : "qrc:/Resources/Icons/cross.png";
                            }

                            onClicked:
                            {
                                window.close();
                            }
                        }
                    }
                }


                Item
                {
                    id: upper;
                    anchors.fill: parent;
                    anchors.margins: 60;

                    Label
                    {
                        id: title_welcome
                        text: qsTr("Welcome to ");
                        font.pixelSize: 24;
                        font.bold: true;
                        color: "#778497";
                        font.family: "Gilroy";
                    }

                    Label
                    {
                        id: title_welcome_2;
                        x: title_welcome.x + title_welcome.width;
                        y: title_welcome.y;
                        text: qsTr("shezar");
                        font.pixelSize: 24;
                        font.bold: true;
                        color: "#307AF3";
                        font.family: "Gilroy";
                    }

                    Label
                    {
                        id: second_title
                        width: parent.width;
                        clip: true;
                        color: "#778497";
                        text: qsTr("Shezar gives you instant access to millions of songs – from old favorites to the latest hits. Just hit play to stream anything you like.");
                        wrapMode: Text.WordWrap
                        font.pixelSize: 13;

                        anchors.top: title_welcome.bottom;
                        anchors.topMargin: 35;
                    }

                    Label
                    {
                    	id: label_errors
                        clip: true;
                        text: qsTr("");
                        visible: true;
                        font.pixelSize: 13;
                        font.bold: true;
                        wrapMode: Text.WordWrap
                        color: "red";
                        font.family: "Gilroy";

                        anchors.top: second_title.bottom;
                        anchors.topMargin: 15;
                    }

                    TextLine
                    {
                        id: field_username
                        m_width: parent.width;
                        m_height: 35;
                        m_fontSize: 17;
                        m_holderText:  qsTr("username");
                        m_colorUnderline: "#4385F5";
                        m_fontColor: "#A6A6A6";
                        m_spacing: 0;

                        anchors.top: label_errors.bottom;
                        anchors.topMargin: 20;
                    }

                    TextLine
                    {
                        id: field_password
                        m_width: parent.width;
                        m_height: 35;
                        m_fontSize: 17;
                        m_holderText:  qsTr("password");
                        m_colorUnderline: "#4385F5";
                        m_fontColor: "#A6A6A6";
                        m_spacing: 0;
                        m_echoMode: TextInput.Password;

                        anchors.top: field_username.bottom;
                        anchors.topMargin: 40;
                    }

                    Item
                    {
                        anchors.top: field_password.bottom;
                        anchors.topMargin: 60;
                        width: parent.width;

                        Rectangle
                        {
                            id: button
                            width: 125;
                            height: 32;
                            color: "#D0E1FD";
                            radius: 12;
                            anchors.verticalCenter: parent.verticalCenter;

                            Label
                            {
                            	id: button_text;
                                color: "#518EF8";
                                text: "Log in"
                                font.pixelSize: 14;

                                anchors.verticalCenter: parent.verticalCenter;
                                anchors.horizontalCenter: parent.horizontalCenter;
                            }

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor
                                onClicked: 
                                { 
                                	if (field_username.m_text == "")
                                	{
                                		field_username.m_colorUnderline = "red";
                                		label_errors.visible = true;
                                		label_errors.text = qsTr("The username field should not be empty.");
                                	}
                                	else if (field_password.m_text == "")
                                	{
                                		field_password.m_colorUnderline = "red";
                                		label_errors.visible = true;
                                		label_errors.text = qsTr("The password field should not be empty.");
                                	}
                                	else
                                	{
                                		if (button_text.text == "Log in")
                                			wlRoot.getLoginAndPassword(field_username.m_text, field_password.m_text, 0);
                                		else
                                			wlRoot.getLoginAndPassword(field_username.m_text, field_password.m_text, 1);
                                	}
                                }
                            }
                        }

                        Label
                        {
                            color: "#518EF8";
                            text: qsTr("Forgot password");
                            anchors.right: parent.right;
                            font.underline: true;
                            font.pixelSize: 13;

                            anchors.verticalCenter: parent.verticalCenter;

                            MouseArea
                            {
                                anchors.fill: parent;
                                hoverEnabled : true;
                                cursorShape: Qt.PointingHandCursor
                                onClicked: { console.log("cliked"); }
                                onHoveredChanged: { cursorShape = Qt.PointingHandCursor; }
                            }
                        }
                    }
                }
            }

            Rectangle
            {
                id: under
                width: parent.width;
                height: parent.height/4;
                color: "#F4F5F7";

                anchors.bottom: parent.bottom;
                anchors.bottomMargin: 0;

                Row
                {
                	id: underRowText;
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    spacing: 0;

                    Label
                    {
                    	id: underlabel1;
                        color: "#A6A6A6";
                        text: qsTr("Still without account? ");
                        font.pixelSize: 13;
                    }

                    Label
                    {
                    	id: underlabel2;
                        color: "#518EF8";
                        text: qsTr("Create one");
                        font.pixelSize: 13;

                        MouseArea
                        {
                            anchors.fill: parent;
                            cursorShape: Qt.PointingHandCursor
                            onClicked: 
                            { 
                            	if (parent.text == "Create one")
                            	{
                            		button_text.text = qsTr("Sign up");
                            		underlabel1.text = qsTr("Already using shezar? ");
                            		underlabel2.text = qsTr("Log in");
                            	}
                            	else
                            	{
                            		button_text.text = qsTr("Log in");
                            		underlabel1.text = qsTr("Still without account? ");
                            		underlabel2.text = qsTr("Create one");
                            	}
                            }
                        }
                    }
                }
            }
        }
    }
}





