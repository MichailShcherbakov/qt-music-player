import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import "../../Styles/ListsView"

import my.window 1.0

import horizontalModel1 1.0

FWindow
{
    id: window
    m_width: 1200;
    m_height: 720;
    m_minWidth: 1200;
    m_minHeight: 720;
    m_maxWidth: 1980;
    m_maxHeight: 1080;

    visible: false

    FontLoader { id: localFont; source: "qrc:/Resources/Fonts/Gilroy.ttf" }

    Connections
    {
        target: wpRoot;
    }

    /* #4C5458 - gray */
    /* #2ED297- green */

    property string colorHoveredItems: "#2ED297";
    property string colorItems: "#4C5458";

    Row
    {
        anchors.fill: parent;
        spacing: 0;

        Item
        {
            id: left_field;
            width: 220;
            height: parent.height;

            Rectangle
            {
                anchors.fill: parent;
                color: "#1B1D23";

                ScrollView
                {
                    width: parent.width;
                    height: parent.height - 206;
                    clip: true;

                    ScrollBar.vertical.policy: ScrollBar.AlwaysOff;

                    Column
                    {
                        anchors.fill: parent;
                        spacing: 0;

                        Item
                        {
                            id: username
                            width: parent.width;
                            height: 120;

                            MouseArea
                            {
                                anchors.fill: row;
                                cursorShape: Qt.PointingHandCursor;

                                onClicked:
                                {
                                    console.log("clicked");
                                }
                            }

                            Row
                            {
                                id: row
                                spacing: 14;
                                height: 42;
                                anchors.left: parent.left;
                                anchors.leftMargin: 23;
                                anchors.verticalCenter: parent.verticalCenter;

                                Item
                                {
                                    width: 42;
                                    height: 42;
                                    anchors.verticalCenter: parent.verticalCenter;

                                    Image
                                    {
                                        id: image_user;
                                        anchors.fill: parent;
                                        source: "qrc:/Resources/Icons/cover.jpg";
                                        smooth: true;
                                        visible: false;
                                    }

                                    Rectangle
                                    {
                                        id: mask_image_user
                                        anchors.fill: image_user;
                                        radius: 50;
                                        visible: false;
                                    }

                                    Rectangle
                                    {
                                        id: image_user_border;
                                        width: 44;
                                        height: 44;
                                        radius: 50;
                                        gradient: Gradient {
                                            orientation: Gradient.Horizontal
                                            GradientStop { position: 0.0; color: "#2DCB90" }
                                            GradientStop { position: 1.0; color: "#06ACC7" }
                                        }

                                        anchors.left: image_user.left;
                                        anchors.leftMargin: -1;
                                        anchors.top: image_user.top;
                                        anchors.topMargin: -1;
                                    }

                                    OpacityMask
                                    {
                                        anchors.fill: image_user;
                                        source: image_user;
                                        maskSource: mask_image_user;
                                    }
                                }

                                Label
                                {
                                    text: "Jeremiah Evans";
                                    color: "#fff";
                                    font.family: "Gilroy";
                                    font.pixelSize: 12;

                                    anchors.verticalCenter: parent.verticalCenter;
                                }

                                Image
                                {
                                    id: user_button;
                                    width: 12;
                                    height: 12;
                                    source: "qrc:/Resources/Icons/user_button.png";
                                    smooth: true;

                                    anchors.verticalCenter: parent.verticalCenter;
                                }
                            }
                        }

                        Item
                        {
                            width: parent.width;
                            height: 250;

                            Label
                            {
                                id: browseMusic
                                text: "Browse Music";
                                color: "#fff";
                                font.family: "Gilroy";
                                font.pixelSize: 15;

                                anchors.left: parent.left;
                                anchors.leftMargin: 23;
                            }

                            ListViewMenu
                            {
                                id: browseMusicList
                                m_width: left_field.width;

                                anchors.top: browseMusic.bottom;
                                anchors.topMargin: 15;

                                m_model: ListModel
                                {
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/songs.png";
                                        img_hovered: "qrc:/Resources/Icons/songs_hovered.png";
                                        text: "Songs";
                                    }
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/playlist.png";
                                        img_hovered: "qrc:/Resources/Icons/playlist_hovered.png";
                                        text: "Playlists";
                                    }
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/genres.png";
                                        img_hovered: "qrc:/Resources/Icons/genres_hovered.png";
                                        text: "Genres";
                                    }
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/microphone.png";
                                        img_hovered: "qrc:/Resources/Icons/microphone_hovered.png";
                                        text: "Artists";
                                    }
                                }
                            }
                        }

                        Item
                        {
                            width: parent.width;
                            height: 150;

                            Label
                            {
                                id: yourMusic
                                text: "Your Music";
                                color: "#fff";
                                font.family: "Gilroy";
                                font.pixelSize: 15;

                                anchors.left: parent.left;
                                anchors.leftMargin: 23;
                            }

                            ListViewMenu
                            {
                                id: yourMusicList
                                m_width: left_field.width;
                                m_countItems: 2;

                                anchors.top: yourMusic.bottom;
                                anchors.topMargin: 15;

                                m_model: ListModel
                                {
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/heart.png";
                                        img_hovered: "qrc:/Resources/Icons/heart_hovered.png";
                                        text: "Favourites";
                                    }
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/history.png";
                                        img_hovered: "qrc:/Resources/Icons/history_hovered.png";
                                        text: "History";
                                    }
                                }
                            }
                        }

                        Item
                        {
                            width: parent.width;
                            height: 200;

                            Label
                            {
                                id: yourPlaylists
                                text: "Your Playlists";
                                color: "#fff";
                                font.family: "Gilroy";
                                font.pixelSize: 15

                                anchors.left: parent.left;
                                anchors.leftMargin: 23;
                            }

                            ListViewMenu
                            {
                                id: yourPlaylistsList
                                m_width: left_field.width;
                                m_countItems: 3;

                                anchors.top: yourPlaylists.bottom;
                                anchors.topMargin: 15;

                                m_model: ListModel
                                {
                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/add.png";
                                        img_hovered: "qrc:/Resources/Icons/add_hovered.png";
                                        text: "New Playlist";
                                    }

                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/add_play.png";
                                        img_hovered: "qrc:/Resources/Icons/add_play_hovered.png";
                                        text: "Sample Playlist";
                                    }

                                    ListElement
                                    {
                                        img: "qrc:/Resources/Icons/add_play.png";
                                        img_hovered: "qrc:/Resources/Icons/add_play_hovered.png";
                                        text: "Sample Playlist 2";
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle
                {
                    id: cover
                    width: 196
                    height:  196
                    visible: true

                    Image
                    {
                        id: cover_image
                        anchors.fill: parent
                        source: "qrc:/Resources/Icons/cover.jpg"
                        smooth: true;                    
                    }

                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 10
                }

                Rectangle
                {
                    id: mask
                    width: cover.width
                    height:  cover.height
                    radius: 7
                    visible: false
                }

                OpacityMask
                {
                    id: coverMask
                    anchors.fill: cover
                    source: cover
                    maskSource: mask
                }

                DropShadow
                {
                    anchors.fill: coverMask
                    horizontalOffset: 0
                    verticalOffset: 10
                    radius: 14.0
                    samples: 17
                    color: "#20000000"
                    source: coverMask
                }
            }

        }
        
        Item
        {
            id: right_field;
            width: parent.width - left_field.width;
            height: parent.height;

            Column
            {
                anchors.fill: parent;
                spacing: 0;

                Item
                {
                    id: center_field;
                    width: parent.width;
                    height: parent.height - under_field.height

                    Rectangle
                    {
                        anchors.fill: parent;
                        color: "#111";
                    }

                    Row
                    {
                        id: searching
                        spacing: 15;
                        anchors.left: parent.left;
                        anchors.leftMargin: 10;
                        anchors.top: parent.top;
                        anchors.topMargin: 10;

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

                    Row
                    {
                        id: controlsButtons
                        anchors.right: parent.right;
                        anchors.top: parent.top;

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
                            width: 48;
                            height: 32;
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
                                anchors.fill: parent;
                                hoverEnabled: true;
                                property bool m_state: false;

                                onHoveredChanged:
                                {
                                    m_state = m_state ? false : true;
                                    parent.color = m_state ? "#2ED297" : "transparent";
                                    checkbox.source = m_state ? "qrc:/Resources/Icons/checkbox_hovered.png" : "qrc:/Resources/Icons/checkbox.png";
                                }

                                onClicked:
                                {
                                    wRoot.clicked();
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
                        id: contentsContaner

                        width: parent.width;
                        height: parent.height - controlsButtons.height - 10;

                        anchors.bottom: parent.bottom;

                        Column
                        {
                            spacing: 0;
                            width: parent.width - 32;
                            height: parent.height - 32;
                            anchors.top: parent.top;
                            anchors.topMargin: 32;
                            anchors.left: parent.left;
                            anchors.leftMargin: 32;

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
                                        font.pixelSize: 22
                                        font.family: "Gilroy"
                                        text: "Albums"
                                        color: "#2ED297"
                                    }

                                    ListView
                                    {
                                        width: contentsContaner.width - 32;
                                        height: 200;
                                        clip: true;
                                        spacing: 32;
                                        orientation: ListView.Horizontal;

                                        model: HorizontalModel1
										{
											list: albumsModelList
										}

                                        delegate: Item
                                        {
                                            id: album
                                            width: 128;

                                            Column
                                            {
                                                spacing: 10;
                                                Item
                                                {
                                                    width: album.width;
                                                    height: 128;

                                                    Image
                                                    {
                                                        id: cover_album
                                                        anchors.fill: parent;
                                                        source: "qrc:/Resources/Icons/cover.jpg";
                                                        smooth: true;
                                                        visible: true;
                                                    }

                                                    Rectangle
                                                    {
                                                        id: mask_cover_album
                                                        width: cover_album.width
                                                        height:  cover_album.height
                                                        radius: 4
                                                        visible: false
                                                    }

                                                    OpacityMask
                                                    {
                                                        id: opacityMaskAlbum
                                                        anchors.fill: cover_album
                                                        source: cover_album
                                                        maskSource: mask_cover_album
                                                    }

                                                    DropShadow
                                                    {
                                                        anchors.fill: opacityMaskAlbum
                                                        horizontalOffset: 0
                                                        verticalOffset: 10
                                                        radius: 12.0
                                                        samples: 17
                                                        color: "#9FF0D2"
                                                        source: opacityMaskAlbum
                                                    }
                                                }

                                                Column
                                                {
                                                    spacing: 2;
                                                    Label
                                                    {
                                                        font.pixelSize: 15
                                                        font.family: "Gilroy"
                                                        text: model.text_line_first;
                                                        color: "#fff"
                                                        leftPadding: 10;
                                                    }

                                                    Label
                                                    {
                                                        font.pixelSize: 12
                                                        font.family: "Gilroy"
                                                        text: model.text_line_second;
                                                        color: "#676D7A"
                                                        leftPadding: 10;
                                                    }
                                                }
                                            }
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
                                        width: contentsContaner.width - 32;
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

                                                OpacityMask
                                                {
                                                    anchors.fill: cover_list
                                                    source: cover_list
                                                    maskSource: mask_cover_list
                                                }
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
                }

                Item
                {
                    id: under_field;
                    width: parent.width;
                    height: 75;

                    /*FastBlur
                    {
                        source: center_field;
                        anchors.fill: parent;
                        radius: 16;
                    }*/

                    Rectangle
                    {
                        anchors.fill: parent;
                        color: "#16171B";
                    }

                    Column
                    {
                        spacing: 4;

                        anchors.left: parent.left;
                        anchors.leftMargin: 35

                        anchors.verticalCenter: parent.verticalCenter;

                        Label
                        {
                            text: "Rainin' With You"
                            color: "#fff";
                            font.family: "Gilroy";
                            font.pixelSize: 16

                        }

                        Label
                        {
                            text: "Heize"
                            color: "#61646B";
                            font.family: "Gilroy";
                            font.pixelSize: 16
                        }
                    }

                    Column
                    {
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.horizontalCenter: parent.horizontalCenter;

                        Item
                        {
                            id: playButtons
                            width: parent.width;
                            height: 48;

                            Item
                            {
                                anchors.horizontalCenter: parent.horizontalCenter;
                                height: 40;

                                Image
                                {
                                     width: 16;
                                     height: 16;
                                     smooth: true;
                                     source: "qrc:/Resources/Icons/back.png"

                                     anchors.right: play_background.left;
                                     anchors.rightMargin: 15
                                     anchors.verticalCenter: parent.verticalCenter;

                                     MouseArea
                                     {
                                         anchors.fill: parent;
                                         cursorShape: Qt.PointingHandCursor;

                                         onClicked:
                                         {
                                             console.log("clicked");
                                         }
                                     }
                                }

                                Rectangle
                                {
                                    id: play_background;
                                    width: 40;
                                    height: 40;
                                    radius: 50;

                                    anchors.horizontalCenter: parent.horizontalCenter;

                                    gradient: Gradient {
                                        orientation: Gradient.Horizontal
                                        GradientStop { position: 0.0; color: "#2DCB90" }
                                        GradientStop { position: 1.0; color: "#06ACC7" }
                                    }

                                    Image
                                    {
                                         width: 16;
                                         height: 16;
                                         smooth: true;
                                         source: "qrc:/Resources/Icons/play.png"

                                         anchors.left: parent.left;
                                         anchors.leftMargin: 13
                                         anchors.verticalCenter: parent.verticalCenter;
                                    }

                                    MouseArea
                                    {
                                        anchors.fill: parent;
                                        cursorShape: Qt.PointingHandCursor;

                                        onClicked:
                                        {
                                            console.log("clicked");
                                        }
                                    }
                                }

                                Image
                                {
                                     width: 16;
                                     height: 16;
                                     smooth: true;
                                     source: "qrc:/Resources/Icons/next.png"

                                     anchors.left: play_background.right;
                                     anchors.leftMargin: 15
                                     anchors.verticalCenter: parent.verticalCenter;

                                     MouseArea
                                     {
                                         anchors.fill: parent;
                                         cursorShape: Qt.PointingHandCursor;

                                         onClicked:
                                         {
                                             console.log("clicked");
                                         }
                                     }

                                }
                            }
                        }

                        Row
                        {
                            spacing: 15;

                            Label
                            {
                                id: elapsed_time
                                font.pixelSize: 12
                                font.family: "Gilroy"
                                text: "1:23"
                                color: "#676D7A"

                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Slider
                            {
                                id: slider
                                value: 0
                                to: 99
                                from: 0
                                width: 420
                                height: 6

                                anchors.verticalCenter: parent.verticalCenter

                                background: Rectangle
                                {
                                    width: parent.width
                                    height: parent.height
                                    radius: 5
                                    color: "#30353A"//"#E9E8E8"

                                    Rectangle
                                    {
                                        id: lineSlider
                                        width: slider.visualPosition * slider.width
                                        height: slider.height
                                        radius: 5
                                        gradient: Gradient {
                                            orientation: Gradient.Horizontal
                                            GradientStop { position: 0.0; color: "#2DCB90" }
                                            GradientStop { position: 1.0; color: "#06ACC7" }
                                        }
                                    }
                                }
                                handle: Rectangle
                                {
                                    visible: false
                                }
                                onMoved:
                                {

                                }
                            }

                            Label
                            {
                                id: all_time
                                font.pixelSize: 12
                                font.family: "Gilroy"
                                text: "4:31"
                                color: "#676D7A"

                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }

                    Row
                    {
                        spacing: 20;

                        anchors.right: parent.right;
                        anchors.rightMargin: 35;
                        anchors.verticalCenter: parent.verticalCenter

                        Image
                        {
                            id: shuffle
                            width: 20;
                            height: 20;
                            source: "qrc:/Resources/Icons/shuffle.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor;
                                property bool state: false;

                                onClicked:
                                {
                                    if (!state)
                                    {
                                        parent.source = "qrc:/Resources/Icons/shuffle_hovered.png"
                                        state = true;
                                    }
                                    else
                                    {
                                        parent.source = "qrc:/Resources/Icons/shuffle.png"
                                        state = false;
                                    }
                                }
                            }
                        }

                        Image
                        {
                            id: reapet
                            width: 16;
                            height: 16;
                            source: "qrc:/Resources/Icons/repeat.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter

                            Rectangle
                            {
                                id: once
                                width: 10;
                                height: 10;
                                radius: 50;
                                color: "#2ED297";
                                visible: false;

                                anchors.bottom: parent.bottom;
                                anchors.bottomMargin: -2;
                                anchors.right: parent.right;
                                anchors.rightMargin: -3;

                                Label
                                {
                                    text: "1";
                                    font.pixelSize: 8;
                                    color: "#595A5C";
                                    font.family: "Gilroy"

                                    anchors.verticalCenter: parent.verticalCenter;
                                    anchors.horizontalCenter: parent.horizontalCenter;

                                }
                            }

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor;
                                property int state: 0;

                                onClicked:
                                {
                                    if (state == 0)
                                    {
                                        once.visible = false;
                                        parent.source = "qrc:/Resources/Icons/repeat_hovered.png"
                                        state = 1;
                                    }
                                    else if (state == 1)
                                    {
                                        once.visible = true;
                                        state = 2;
                                    }
                                    else
                                    {
                                        parent.source = "qrc:/Resources/Icons/repeat.png"
                                        once.visible = false;
                                        state = 0;
                                    }

                                }
                            }
                        }

                        Image
                        {
                            id: add
                            width: 20;
                            height: 20;
                            source: "qrc:/Resources/Icons/add.png"
                            smooth: true;

                            anchors.verticalCenter: parent.verticalCenter

                            MouseArea
                            {
                                anchors.fill: parent;
                                cursorShape: Qt.PointingHandCursor;

                                onClicked:
                                {
                                    console.log("clikced");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



