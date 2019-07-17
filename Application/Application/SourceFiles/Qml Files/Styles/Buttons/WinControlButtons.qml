import QtQuick 2.12
import QtQuick.Controls 2.12

Row
{
    property int m_width_cell: 48;
    property int m_height_cell: 32;

    Rectangle
    {
        width: m_width_cell;
        height: m_height_cell;
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
                parent.color = m_state ? "#2ED297" : "transparent";
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
        width: m_width_cell;
        height: m_height_cell;
        color: "transparent";

        Image
        {
            id: checkbox
            sourceSize.width: 10;
            sourceSize.height: 10;
            source: "qrc:/Resources/Icons/checkbox.png"
            smooth: true;

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea
        {
            property bool m_state: false;
            property int oldWidth: 0;
            property int oldHeight: 0;
            property bool typeShow: true;

            anchors.fill: parent;
            hoverEnabled: true;

            onHoveredChanged:
            {
                m_state = m_state ? false : true;
                parent.color = m_state ? "#2ED297" : "transparent";
                checkbox.source = m_state ? "qrc:/Resources/Icons/checkbox_hovered.png" : "qrc:/Resources/Icons/checkbox.png";
            }

            onClicked:
            {
                if (typeShow)
                {
                    window.showFullScreen();
                    typeShow = false;
                }
                else
                {
                    window.showNormal();   
                    typeShow = true;        
                }
            }
        }
    }

    Rectangle
    {
        width: m_width_cell;
        height: m_height_cell;
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