import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.12

import models 1.0

Window
{
    id: window
    width: 1280
    height: 720
    visible: true
    color: "white"
    flags: Qt.FramelessWindowHint | Qt.Window

    property string main_color: "#fff"
    property string main_font_color: "#000"
    property string int_color: "#ff2152"

    FontLoader { id: localFont; source: "qrc:/Fonts/Gilroy.ttf" }

    Connections
    {
        target: window_player
        onPositionChanged: slider.value = pos
        onMediaChanged: slider.to = size
        onChangeImagePlayButton: play_button.source = path
        onChangeImageCover: cover_image.source = "image://imageProvider/x196/" + media
    }

    Item
    {
        width: parent.width
        height: 32

        anchors.right: parent.right
        anchors.top: parent.top

        MouseArea
        {
            property var clickPos
            anchors.fill: parent

            onPressed:
            {
                clickPos = { x: mouse.x, y: mouse.y }
            }
            onPositionChanged:
            {
                window.x = window_player.cursorPos().x - clickPos.x
                window.y = window_player.cursorPos().y - clickPos.y
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
                        if (state) { parent.color = "lightgray"; state = false; } else { parent.color = "transparent"; state = true; }
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
                        if (state) { parent.color = "lightgray"; state = false; } else { parent.color = "transparent"; state = true; }
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

    property int sizeImages: 16
    property int fontSize: 14

    Item
    {
        id: left_place
        width: 216
        height:  parent.height

        Label
        {
            text: "MUSIC"
            color: "lightgray"
            font.family: "Gilroy"
            font.pixelSize: 14
            font.bold: true

            anchors.top: parent.top
            anchors.left: parent.left

            anchors.topMargin: 90
            anchors.leftMargin: 35

        }

        Rectangle
        {
            id: cover
            width: 196
            height:  196
            visible: false

            Image
            {
                id: cover_image
                width: 196
                height:  196
                anchors.fill: parent
                source: "image://coversForPoster/image"
                cache: false
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


        Column
        {
            spacing: 20

            anchors.top: parent.top
            anchors.left: parent.left

            anchors.topMargin: 130
            anchors.leftMargin: 35

            Row
            {
                spacing: 25

                Image
                {
                    width: sizeImages
                    height: sizeImages
                    source: "qrc:/Themes/White/note.svg"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Label
                {
                    text: "Songs"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: fontSize
                    font.bold: true

                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
                        }
                    }
                }


            }

            Row
            {
                spacing: 25

                Image
                {
                    width: sizeImages
                    height: sizeImages
                    source: "qrc:/Themes/White/albums.svg"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Label
                {
                    text: "Albums"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: fontSize
                    font.bold: true

                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
                        }
                    }
                }
            }

            Row
            {
                spacing: 25

                Image
                {
                    width: sizeImages
                    height: sizeImages
                    source: "qrc:/Themes/White/microphone.svg"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Label
                {
                    text: "Artists"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: fontSize
                    font.bold: true

                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
                        }
                    }
                }
            }

            Row
            {
                spacing: 25

                Image
                {
                    width: sizeImages
                    height: sizeImages
                    source: "qrc:/Themes/White/folder.svg"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Label
                {
                    text: "Local Files"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: fontSize
                    font.bold: true

                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
							window_player.button_local_files();
                        }
                    }
                }
            }

            Row
            {
                spacing: 25

                Image
                {
                    width: sizeImages
                    height: sizeImages
                    source: "qrc:/Themes/White/heart.svg"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Label
                {
                    text: "Liked"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: fontSize
                    font.bold: true

                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
                        }
                    }
                }
            }
        }
    }

    Column
    {
        width: parent.width - left_place.width
        height: parent.height

        anchors.right: parent.right

        Item
        {
            id: right_place
            width: parent.width
            height:  parent.height

            Column
            {
                spacing: 6

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 50
                anchors.leftMargin: 15

                Label
                {
                    text: "Playlists"
                    color: "#676D7A"
                    font.family: "Gilroy"
                    font.pixelSize: 14
                    font.bold: true
                }
                Label
                {
                    text: "Recently Added"
                    color: "#000"
                    font.family: "Gilroy"
                    font.pixelSize: 24
                    font.bold: true
                }
            }

            DropShadow
            {
                anchors.fill: space_table
                horizontalOffset: -70
                verticalOffset: 100
                radius: 30
                samples: 18
                color: "#20000000"
                source: space_table
            }

            Rectangle
            {
                id: space_table
                width: parent.width
                height: right_place.height - 100

                anchors.top: parent.top
                anchors.topMargin: 100

                Item
                {
                    width: parent.width
                    height: space_table.height

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 25
                    anchors.leftMargin: 15
                    anchors.bottomMargin: 15
                    anchors.rightMargin: 15

                    Item
                    {
                        id: table
                        width: parent.width
                        height: 25

                        anchors.left: parent.left
                        anchors.leftMargin: 16

                        Item
                        {
                            width: parent.width
                            height: table.height

                            Label
                            {
                                id: title_table
                                text: "Title"
                                color: "gray"
                                font.family: "Gilroy"
                                height: parent.height
                                font.pixelSize: 12
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignHCenter

                                anchors.left: parent.left
                                anchors.leftMargin: 57
                            }

                            Label
                            {
                                id: artist_table
                                text: "Artist"
                                color: "gray"
                                font.family: "Gilroy"
                                font.pixelSize: 12
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignHCenter

                                anchors.left: title_table.right
                                anchors.leftMargin: 150
                            }

                            Label
                            {
                                id: album_table
                                text: "Album"
                                color: "gray"
                                font.family: "Gilroy"
                                font.pixelSize: 12
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignHCenter

                                anchors.left: artist_table.right
                                anchors.leftMargin: 76
                            }

                            Label
                            {
                                id: added_table
                                text: "Added"
                                color: "gray"
                                font.family: "Gilroy"
                                font.pixelSize: 12
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignHCenter

                                anchors.left: album_table.right
                                anchors.leftMargin: 72
                            }

                        }

                    }
                    ScrollView
                    {
                        width: 605
                        height: parent.height - under_place.height - 2

                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        anchors.top: table.bottom

                        ListView
                        {
                            id: list
                            width: parent.width
                            height: parent.height
                            clip: true
                            spacing: 5

                            model: CModel
							{
								list: cList
							}

                            delegate: Item
                            {
                                width: list.width
                                height: 52

                                Rectangle
                                {
                                    id: item_list
                                    width: 605
                                    height: parent.height
                                    radius: 7
                                    color: main_color

                                    Image
                                    {
                                        id: cover_list
                                        width: 32
                                        height:  32
                                        source: "image://imageProvider/x48/" + model.image
                                        visible: false
                                        smooth: true

                                        anchors.left: parent.left

                                        anchors.verticalCenter: parent.verticalCenter

                                        anchors.leftMargin: 10
                                    }

                                    Rectangle
                                    {
                                        id: mask_list_image
                                        width: cover_list.width
                                        height:  cover_list.height
                                        radius: 5
                                        visible: false
                                    }

                                    OpacityMask
                                    {
                                        anchors.fill: cover_list
                                        source: cover_list
                                        maskSource: mask_list_image
                                    }

                                    Item
                                    {
                                        anchors.left: cover_list.right
                                        anchors.leftMargin: 15
                                        anchors.verticalCenter: parent.verticalCenter

                                        Label
                                        {
                                            id: title_label_list
                                            text: model.text
                                            font.bold: true
                                            font.family: "Gilroy"
                                            width: 160
                                            font.pixelSize: 14
                                            color: "#676D7A"
                                            anchors.verticalCenter: parent.verticalCenter
                                        }

                                        Label
                                        {
                                            id: author_label_list
                                            font.pixelSize: 12
                                            text: model.artist
                                            font.family: "Gilroy"
                                            color: "#676D7A"
                                            font.bold: true
                                            width: 85
                                            anchors.verticalCenter: parent.verticalCenter

                                            anchors.left: title_label_list.right
                                            anchors.leftMargin: 16
                                        }

                                        Label
                                        {
                                            id: album_label_list
                                            font.pixelSize: 12
                                            text: model.album
                                            color: "#676D7A"
                                            font.family: "Gilroy"
                                            font.bold: true
                                            width: 75
                                            anchors.verticalCenter: parent.verticalCenter

                                            anchors.left: author_label_list.right
                                            anchors.leftMargin: 25
                                        }

                                        Label
                                        {
                                            id: added_label_list
                                            font.pixelSize: 12
                                            text: model.added
                                            color: "#676D7A"
                                            font.family: "Gilroy"
                                            font.bold: true
                                            width: 55
                                            anchors.verticalCenter: parent.verticalCenter

                                            anchors.left: album_label_list.right
                                            anchors.leftMargin: 35
                                        }

                                        Label
                                        {
                                            id: time_label_list
                                            font.pixelSize: 12
                                            text: "4:31"
                                            color: "#C1C4C9"
                                            font.family: "Gilroy"
                                            font.bold: true
                                            width: 35
                                            anchors.verticalCenter: parent.verticalCenter

                                            anchors.left: added_label_list.right
                                            anchors.leftMargin: 55
                                        }
                                    }

                                    MouseArea
                                    {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        property bool state: true

                                        onHoveredChanged:
                                        {
                                          if (state)
                                          {
                                              item_list.color = "#3B75FF";
                                              title_label_list.color = "#fff";
                                              author_label_list.color = "#fff";
                                              album_label_list.color = "#fff";
                                              added_label_list.color = "#fff";
                                              time_label_list.color = "#fff";
                                              state = false;
                                          }
                                          else
                                          {
                                              item_list.color = main_color;
                                              title_label_list.color = "#676D7A";
                                              author_label_list.color = "#676D7A";
                                              album_label_list.color = "#676D7A";
                                              added_label_list.color = "#676D7A";
                                              time_label_list.color = "#C1C4C9";
                                              state = true;
                                          }
                                        }
                                        onClicked:
                                        {
                                            window_player.list_view(author_label_list.text, title_label_list.text);
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


    Rectangle
    {
        anchors.bottom: under_place.top

        anchors.left: parent.left
        anchors.leftMargin: 216

        width: parent.width - 216
        height: 2
        color: "#EFEFEF"
    }

    Rectangle
    {
        id: under_place
        width: parent.width - 216
        height: 75
        color: "#FAFAFA"

        anchors.left: parent.left
        anchors.leftMargin: 216
        anchors.bottom: parent.bottom

        Image
        {
            id: cover_heart
            width: 16
            height:  16
            source: "qrc:/Themes/White/heart.png"
            smooth: true

            anchors.left: parent.left
            anchors.leftMargin: 35

            anchors.top: parent.top
            anchors.topMargin: 20
        }

        Column
        {
            spacing: 5

            anchors.left: cover_heart.left
            anchors.leftMargin: 35
            anchors.verticalCenter: parent.verticalCenter

            Label
            {
                id: title_label
                objectName: "title_label"
                text: "Title"
                font.family: "Gilroy"
                font.bold: true
                font.pixelSize: 19
                color: main_font_color

            }

            Label
            {
                id: author_label
                objectName: "author_label"
                font.pixelSize: 13
                font.family: "Gilroy"
                text: "Author"
                color: "#B5BBC5"
            }
        }

        Row
        {
            spacing: 30

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: -2

            Image
            {
                width: 16
                height: 16
                source: "qrc:/Themes/White/back_button.png"
                anchors.verticalCenter: parent.verticalCenter
                smooth: true

                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: window_player.button_back();
                }
            }

            Image
            {
                id: play_button
                width: 24
                height: 24
                source: "qrc:/Themes/White/play_button.png"
                anchors.verticalCenter: parent.verticalCenter
                smooth: true

                MouseArea
                {
                    anchors.fill: parent
                    property bool state: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: window_player.button_play();
                }
            }

            Image
            {
                width: 16
                height: 16
                source: "qrc:/Themes/White/next_button.png"
                anchors.verticalCenter: parent.verticalCenter
                smooth: true

                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: window_player.button_next();
                }
            }
        }

        Row
        {
            spacing: 15

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: 15

            Label
            {
                id: elapsed_time
                font.pixelSize: 12
                font.family: "Gilroy"
                text: "1:23"
                color: "#676D7A"

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
                    width: slider.availableWidth
                    height: parent.height
                    radius: 5
                    color: "#E9E8E8"

                    Rectangle
                    {
                        id: lineSlider
                        width: slider.visualPosition * slider.availableWidth
                        height: slider.height
                        radius: 5
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop { position: 0.0; color: "#264FFD" }
                            GradientStop { position: 1.0; color: "#F003FB" }
                        }
                    }
                }
                handle: Rectangle
                {
                    visible: false
                }
                onMoved:
                {
                    window_player.positionChanging(slider.value);
                }
            }

            Label
            {
                id: all_time
                font.pixelSize: 12
                font.family: "Gilroy"
                text: "4:31"
                color: "#676D7A"

            }
        }

        Item
        {
            width: 150
            height: 24
            anchors.right: parent.right
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: -2

            Image
            {
                id: repeat_button
                width: 20
                height: 20
                source: "qrc:/Themes/White/repeat_off_button.png"
                anchors.verticalCenter: parent.verticalCenter
                smooth: true

                Label
                {
                    id: one
                    text: "1"
                    font.pixelSize: 11
                    color: "#3B75FF"
                    font.family: "Gilroy"
                    //font.bold: true
                    visible: false

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }

                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    property int state: 1
                    onClicked:
                    {
                        if(state === 1)
                        {
                            repeat_button.source = "qrc:/Themes/White/repeat_button.png";
                            state = 2;
                        }
                        else if (state === 2)
                        {
                            one.visible = true;
                            state = 3;
                        }
                        else
                        {
                            one.visible = false;
                            repeat_button.source = "qrc:/Themes/White/repeat_off_button.png";
                            state = 1;
                        }

                        //window_player.button_repeat();
                    }
                }
            }

            Image
            {
                id: icon_speaker
                width: 20
                height: 20
                source: "qrc:/Themes/White/speaker.png"
                anchors.verticalCenter: parent.verticalCenter
                smooth: true

                anchors.left: repeat_button.right
                anchors.leftMargin: 25
            }

            Slider
            {
                id: load_slider
                value: 45
                to: 99
                from: 0
                width: 60
                height: 5

                anchors.left: icon_speaker.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10

                background: Rectangle
                {
                    width: load_slider.availableWidth
                    height: parent.height
                    radius: 5
                    color: "#E9E8E8"

                    Rectangle
                    {
                        id: lineSliderLoad
                        width: load_slider.visualPosition * load_slider.availableWidth
                        height: load_slider.height
                        radius: 5
                        color: "black"
                    }
                }
                handle: Rectangle
                {
                    visible: false
                }
                onMoved:
                {
                    //window_player.positionChanging(load_slider.value);
                }
            }
        }
    }
}
