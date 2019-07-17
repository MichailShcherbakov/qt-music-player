import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import "../../Styles/ListsView"

import models.horizontalModel1 1.0

Item
{
    id: center_field;
    anchors.fill: parent;

    Column
    {
        id: contents_contaner
        anchors.fill: parent;
        spacing: 0;

        Item
        {
            id: searching
            width: parent.width;
            height: 32;

            Row
            {
                spacing: 15;

                Row
                {
                    spacing: 10;

                    anchors.verticalCenter: parent.verticalCenter;

                    Rectangle
                    {
                        width: 32;
                        height: 32;
                        radius: 50;
                        color: "#1D1E24";

                        Image
                        {
                            id: arrowBack;
                            width: 18;
                            height: 18;
                            source:"qrc:/Resources/Icons/arrow_back.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                        }
                    }

                    Rectangle
                    {
                        width: 32;
                        height: 32;
                        radius: 50;
                        color: "#1D1E24";

                        Image
                        {
                            id: arrowNext;
                            width: 18;
                            height: 18;
                            source:"qrc:/Resources/Icons/arrow_next.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                        }
                    }
                }

                Rectangle
                {
                    width: 300;
                    height: 32;
                    radius: 50;
                    color: "#2E353A";
                    opacity: .5;

                    Image
                    {
                        id: magnifier;
                        width: 16;
                        height: 16;
                        source:"qrc:/Resources/Icons/magnifier.png"
                        smooth: true;

                        anchors.left: parent.left;
                        anchors.leftMargin: 10;
                        anchors.verticalCenter: parent.verticalCenter;
                    }

                    TextField
                    {
                        width: parent.width - magnifier.width * 3;
                        selectByMouse: true
                        placeholderText: "Search"
                        font.family: "Gilroy";
                        color: "#fff";
                        placeholderTextColor: "#656970";
                        font.pixelSize: 14;

                        anchors.left: magnifier.right;
                        anchors.leftMargin: 10;
                        anchors.verticalCenter: parent.verticalCenter;

                        background: Rectangle
                        {
                            visible: false;
                        }
                    }
                }
            }
        }

        Item
        {
            id: albumsList;
            width: parent.width;
            height: 300;

            Column
            {
                spacing: 10;

                Label
                {
                    font.pixelSize: 13
                    font.family: "Gilroy"
                    text: "Featured"
                    color: "#676D7A"
                }

                Label
                {
                    id: title_albums
	                font.pixelSize: 22
	                font.family: "Gilroy"
	                text: "Albums"
	                color: "#2ED297"
	            }

	            Hor1ListView
                {
                    m_width: center_field.width;

                    m_model: HorizontalModel1
                    {
                        list: albumsModelList;
                    }

                    onClickedPlayButton:
                    {
                        console.log("cliked play");
                    }

                    onClickedLikeButton:
                    {
                        console.log("cliked like");
                    }
                }
            }
        }

        Item
        {
            id: playLists
            width: parent.width;
            height: parent.height - albumsList.height;

            Column
            {
                spacing: 10;
                anchors.fill: parent;

                Label
                {
                    font.pixelSize: 13
                    font.family: "Gilroy"
                    text: "Playlists"
                    color: "#676D7A"
                }

                Label
                {
                    font.pixelSize: 22
                    font.family: "Gilroy"
                    text: "Recently Added"
                    color: "#2ED297"
                }

                ListView
                {
                    width: contents_contaner.width - 32;
                    height: parent.height - 70;
                    clip: true;
                    spacing: 24;

                    model: ListModel
                    {
                        ListElement { img: "qrc:/1.jpg"}
                        ListElement { img: "qrc:/2.jpg"}
                        ListElement { img: "qrc:/3.jpg"}
                        ListElement { img: "qrc:/4.jpg"}
                        ListElement { img: "qrc:/5.jpg"}
                        ListElement { img: "qrc:/1.jpg"}
                        ListElement { img: "qrc:/2.jpg"}
                        ListElement { img: "qrc:/3.jpg"}
                        ListElement { img: "qrc:/5.jpg"}
                        ListElement { img: "qrc:/4.jpg"}
                    }

                    delegate: Item
                    {
                        id: itemList;
                        width: parent.width;
                        height: 40;

                        MouseArea
                        {
                            anchors.fill: itemList;
                            hoverEnabled: true;
                            property bool state: false

                            onHoveredChanged:
                            {
                                if (!state)
                                {
                                    play_list.visible = true;
                                    id.visible = false;
                                    state = true;
                                }
                                else
                                {
                                    play_list.visible = false;
                                    id.visible = true;
                                    state = false;
                                }
                            }

                            onClicked:
                            {
                                console.log("clicked")
                            }
                        }

                        Label
                        {
                            id: id
                            text: "01";
                            font.pixelSize: 12;
                            font.family: "Gilroy"
                            color: "#4C5458"

                            anchors.left: itemList.left;
                            anchors.leftMargin: 15;

                            anchors.verticalCenter: parent.verticalCenter;
                        }

                        Image
                        {
                            id: play_list
                            width: 14;
                            height: 14;
                            source: "qrc:/Resources/Icons/play_list.png"
                            visible: false;

                            anchors.left: itemList.left;
                            anchors.leftMargin: 15;

                            anchors.verticalCenter: parent.verticalCenter;
                        }

                        Image
                        {
                            id: plus
                            width: 13;
                            height: 13;
                            source: "qrc:/Resources/Icons/plus.png"
                            smooth: true;

                            anchors.left: id.right;
                            anchors.leftMargin: 20;

                            anchors.verticalCenter: parent.verticalCenter;

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor;
                                hoverEnabled: true;

                                onHoveredChanged:
                                {
                                    play_list.visible = false;
                                    id.visible = true;
                                }

                                onClicked:
                                {
                                    console.log("clicked")
                                }
                            }
                        }

                        Item
                        {
                            id: coverImageList
                            width: 40;
                            height: 40;

                            anchors.left: plus.right;
                            anchors.leftMargin: 20;

                            Image
                            {
                                id: cover_list
                                width: 40;
                                height: 40;
                                source: model.img;
                                smooth: true;
                                cache: false
                                visible: false
                            }

                            Rectangle
                            {
                                id: mask_cover_list
                                anchors.fill: cover_list
                                radius: 2
                                visible: false
                            }

                                /*OpacityMask
                                {
                                    anchors.fill: cover_list
                                    source: cover_list
                                    maskSource: mask_cover_list
                                 }*/
                        }

                        Column
                        {
                            id: titleAndArtist
                            spacing: 5;
                            width: 300;

                            anchors.left: coverImageList.right;
                            anchors.leftMargin: 15;

                            anchors.verticalCenter: parent.verticalCenter;

                            Label
                            {
                                text: "Take a Chance (feat. Little Dragon)";
                                font.pixelSize: 13;
                                font.family: "Gilroy"
                                 color: "#fff"
                            }

                            Label
                            {
                                text: "Else";
                                font.pixelSize: 11;
                                font.family: "Gilroy"
                                color: "#5C5F67"
                                }
                        }

                        Label
                        {
                            id: time
                            text: "06:21";
                            font.pixelSize: 11;
                            font.family: "Gilroy"
                            color: "#5C5F67"

                            anchors.left: titleAndArtist.right;
                            anchors.leftMargin: 15;

                            anchors.verticalCenter: parent.verticalCenter;
                        }

                        Image
                            {
                            id: dottedButton
                            width: 14;
                            height: 14;
                            source: "qrc:/Resources/Icons/dotted_button.png"
                            smooth: true;

                            anchors.left: time.right;
                            anchors.leftMargin: 25;

                            anchors.verticalCenter: parent.verticalCenter;

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor;
                                hoverEnabled: true;

                                onHoveredChanged:
                                {
                                    play_list.visible = false;
                                    id.visible = true;
                                }

                                onClicked:
                                {
                                    console.log("clicked")
                                }
                            }
                        }
                    }
                }
             }
        }
    }
}