import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Window 2.12

Item
{
    property int m_width: 200;
    property int m_height: 40;
    property int m_fontSize: 13;
    property string m_text: "";
    property int m_borderRadius: 9;
    property int m_borderSize: 1;
    property int m_spacing: -5;
    property int m_echoMode: TextInput.Normal;
    property int m_heightUnderline: 1;
    property string m_colorUnderline: "blue";
    property bool m_focus: false;
    property bool m_state: text_field.m_state;
    property string m_fontFamily: "Gilroy";
    property string m_fontColor: "black";
    property string m_holderText: "Username";
    property string m_holderTextColor: "lightgray";
    property string m_backgroudColor: "white";

    width: m_width
    height: m_height

    function reset()
    {
        if (text_field.text == "")
        {
            if (!text_field.m_state)
            {
                an_label_y.to = text_field.y - (m_fontSize - m_fontSize/4) * 1;
                an_label_y.start();

                fon.color = m_backgroudColor;

                an_label_fontSize.to = m_fontSize - m_fontSize/4;
                an_label_fontSize.start()

                label.color = m_colorUnderline;

                text_field.m_state = true;
            }
            else
            {
                an_label_y.to = text_field.y + text_field.height/2 - (m_fontSize+4)/2;
                an_label_y.start();

                fon.color = "transparent";

                an_label_fontSize.to = m_fontSize;
                an_label_fontSize.start()

                label.color = m_holderTextColor;

                text_field.m_state = false;
            }
        }
    }

    TextField
    {
        id: text_field
        width: m_width
        height: m_height
        text: m_text
        focus: m_focus
        echoMode: m_echoMode
        color: m_fontColor
        font.pixelSize: m_fontSize
        selectByMouse: true
        font.family: m_fontFamily
        padding: 0;

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        property bool m_state: false
        background: Rectangle
        {
            anchors.fill: parent;
            border.width: 0;
            color: "transparent";
        }
        onTextChanged:
        {
            m_text = text_field.text;
        }

        onFocusChanged:
        {
            m_focus = focus;
            reset();
        }
    }

    Rectangle
    {
        id: underline;
        x: text_field.x;
        y: text_field.y + text_field.height + m_spacing;
        width: m_width;
        height: m_heightUnderline;
        border.width: 0;
        color: m_colorUnderline;
    }

    Rectangle
    {
        id: fon
        width: label.width
        height: label.height
        color: "transparent";

        x: text_field.x;
        y: text_field.y + text_field.height/2 - (m_fontSize+4)/2

        Label
        {
            id: label
            text: m_holderText
            font.pixelSize: m_fontSize
            color: m_holderTextColor

            background: Rectangle
            {
                anchors.fill: parent;
                border.width: 0;
                color: "transparent";
            }

            font.family: m_fontFamily

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            verticalAlignment: Text.AlignHCenter

            NumberAnimation on font.pixelSize
            {
                id: an_label_fontSize
                duration: 100
                running: false
            }
        }

        NumberAnimation on x
        {
            id: an_label_x
            duration: 100
            running: false
        }

        NumberAnimation on y
        {
            id: an_label_y
            duration: 100
            running: false
        }
    }
}
