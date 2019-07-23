import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import "../../Styles/ListsView"

import models.verticalModel1 1.0

Item
{
    id: center_field;
    anchors.fill: parent;

    Column
    {
        anchors.fill: parent;
        spacing: 0;

        anchors.top: parent.top;
        anchors.topMargin: 20;

        anchors.right: parent.right;
        anchors.rightMargin: 5;

        Item
        {
            width: parent.width;
            height: sort_button.height;

            Rectangle
            {
                id: sort_button;
                width: 110;
                height: 25;
                radius: 5
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: "#2DCB90" }
                    GradientStop { position: 1.0; color: "#06ACC7" }
                }

                anchors.right: parent.right;
                anchors.rightMargin: 32;

                Label
                {
                    font.pixelSize: 13;
                    font.family: "Gilroy";
                    text: "Sort order"
                    color: "#fff";
                    
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.horizontalCenter: parent.horizontalCenter;
                }

                MouseArea
                {
                    anchors.fill: parent;
                    cursorShape: Qt.PointingHandCursor;

                    onClicked:
                    {
                        menu.open();
                    }
                }

                ActionGroup { id: order }
                ActionGroup { id: upDown }

                Menu 
                {
                    id: menu

                    Connections
                    {
                        target: sortListSection;

                        onSetCheckType:
                        {
                            var MenuTypes = 
                            {
                                Alphabetical: 1,
                                Album : 2,
                                Artist : 3,
                                DateAdded : 4
                            }

                            switch(type)
                            {
                            case MenuTypes.Alphabetical:
                                alphabeticalSort.checked = true;
                                break;

                            case MenuTypes.Album:
                                albumSort.checked = true;
                                break;

                            case MenuTypes.Artist:
                                artistSort.checked = true;
                                break;

                            case MenuTypes.DateAdded:
                                dateAddedlSort.checked = true;
                                break;         
                            }
                        }

                        onSetCheckState:
                        {
                            var MenuStates = 
                            {
                                Ascending : 1,
                                Descending : 2
                            }

                            switch(state)
                            {  
                            case MenuStates.Ascending:
                                ascendingSort.checked = true;
                                break;  

                            case MenuStates.Descending:
                                descendingSort.checked = true;
                                break;          
                            }
                        }
                    }

                    Component.onCompleted:
                    {
                        sortListSection.onUpdate();
                    }

                    Action 
                    { 
                        id: alphabeticalSort
                        text: qsTr("Alphabetical"); 
                        checkable: true; 
                        ActionGroup.group: order;

                        onTriggered:
                        {
                            var MenuTypes = 
                            {
                                Alphabetical: 1,
                                Album : 2,
                                Artist : 3,
                                DateAdded : 4
                            }

                            sortListSection.onSetType(MenuTypes.Alphabetical);
                        }
                    }

                    Action 
                    {
                        id: albumSort
                        text: qsTr("Album"); 
                        checkable: true; 
                        ActionGroup.group: order;

                        onTriggered:
                        {
                            var MenuTypes = 
                            {
                                Alphabetical: 1,
                                Album : 2,
                                Artist : 3,
                                DateAdded : 4
                            }

                            sortListSection.onSetType(MenuTypes.Album);
                        }
                    }

                    Action 
                    { 
                        id: artistSort
                        text: qsTr("Artist"); 
                        checkable: true; 
                        ActionGroup.group: order;

                        onTriggered:
                        {
                            var MenuTypes = 
                            {
                                Alphabetical: 1,
                                Album : 2,
                                Artist : 3,
                                DateAdded : 4
                            }

                            sortListSection.onSetType(MenuTypes.Artist);
                        }
                    }

                    Action 
                    { 
                        id: dateAddedlSort
                        text: qsTr("Date added"); 
                        checkable: true; 
                        ActionGroup.group: order;

                        onTriggered:
                        {
                            var MenuTypes = 
                            {
                                Alphabetical: 1,
                                Album : 2,
                                Artist : 3,
                                DateAdded : 4
                            }

                            sortListSection.onSetType(MenuTypes.DateAdded);
                        }
                    }
                    
                    MenuSeparator 
                    {
                        contentItem: Rectangle 
                        {
                            implicitWidth: 180;
                            implicitHeight: 1
                            gradient: Gradient {
                                orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: "#2DCB90" }
                                GradientStop { position: 1.0; color: "#06ACC7" }
                            }
                        }
                    }

                    Action 
                    { 
                        id: ascendingSort
                        text: qsTr("Ascending"); 
                        checkable: true; 
                        ActionGroup.group: upDown;

                        onTriggered:
                        {
                            var MenuStates = 
                            {
                                Ascending : 1,
                                Descending : 2
                            }

                            sortListSection.onSetState(MenuStates.Ascending);
                        }
                    }

                    Action 
                    { 
                        id: descendingSort
                        text: qsTr("Descending"); 
                        checkable: true;
                        ActionGroup.group: upDown; 

                        onTriggered:
                        {
                            var MenuStates = 
                            {
                                Ascending : 1,
                                Descending : 2
                            }

                            sortListSection.onSetState(MenuStates.Descending);
                        }
                    }


                    topPadding: 2
                    bottomPadding: 2

                    delegate: MenuItem 
                    {
                        id: menuItem
                        implicitWidth: 200
                        implicitHeight: 30

                        arrow: Canvas 
                        {
                            x: parent.width - width
                            implicitWidth: 30
                            implicitHeight: 30
                            visible: menuItem.subMenu

                            onPaint: 
                            {
                                var ctx = getContext("2d")
                                ctx.fillStyle = menuItem.highlighted ? "#ffffff" : "#1B1D23"
                                ctx.moveTo(15, 15)
                                ctx.lineTo(width - 15, height / 2)
                                ctx.lineTo(15, height - 15)
                                ctx.closePath()
                                ctx.fill()
                            }
                        }

                        indicator: Item 
                        {
                            x: parent.width - width

                            implicitWidth: 30
                            implicitHeight: 30

                            Rectangle 
                            {
                                width: 20
                                height: 20
                                anchors.centerIn: parent
                                visible: menuItem.checkable
                                border.width: 3;
                                border.color: menuItem.checked ? "#1B1D23" : "#fff";
                                radius: 50

                                Rectangle 
                                {
                                    width: 8
                                    height: 8
                                    anchors.centerIn: parent
                                    visible: menuItem.checked
                                    color: "#1B1D23"
                                    radius: 50

                                    anchors.verticalCenter: parent.verticalCenter;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                }
                            }
                        }

                        contentItem: Text 
                        {
                            leftPadding: 10;
                            rightPadding: menuItem.arrow.width
                            text: menuItem.text
                            font.family: "Gilroy";
                            font.pixelSize: 12;
                            opacity: enabled ? 1.0 : 0.3
                            color: "#ffffff";
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle 
                        {
                            implicitWidth: 200
                            implicitHeight: 30
                            opacity: enabled ? 1 : 0.3
                            color: menuItem.highlighted ? "#4C5458" : "transparent";
                        }
                    }

                    background: Rectangle 
                    {
                        implicitWidth: 200
                        implicitHeight: 30
                        color: "#1B1D23"
                        //border.color: "#4C5458"
                        radius: 2
                    }
                }
            }
        }

        Item
        {
            id: header;
            width: parent.width;
            height: title.height + 32;

            Label
            {
                id: title;
                font.pixelSize: 15;
                font.family: "Gilroy";
                text: "Title"
                color: "#737F85";

                anchors.left: header.left;
                anchors.leftMargin: 24 + 66;

                anchors.verticalCenter: parent.verticalCenter;
            }

            Label
            {
                id: artist;
                font.pixelSize: 15;
                font.family: "Gilroy";
                text: "Artist"
                color: "#737F85";

                anchors.left: title.left;
                anchors.leftMargin: parent.width/4 + 24;

                anchors.verticalCenter: parent.verticalCenter;
            }

            Label
            {
                id: album;
                font.pixelSize: 15;
                font.family: "Gilroy";
                text: "Album"
                color: "#737F85";

                anchors.left: artist.left;
                anchors.leftMargin: parent.width/4 + 24;

                anchors.verticalCenter: parent.verticalCenter;
            }
        }

        ScrollView
        {
            width: parent.width;
            height: parent.height - header.height - 32;
            clip: true;

            Ver1ListView
            {
                m_width: parent.width;
                m_height: parent.height;

                m_model: VerticalModel1
                {
                    list: songsModelList;
                }
            }
        }
    }
}