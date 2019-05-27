import QtQuick 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12

import "../Styles"

import models 1.0

Window
{
    id: window
    width: 720
    height: 480
    color: "#fff"
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Window

    property int previousX
    property int previousY

    /* Connectiond with C++ */
    Connections
    {
        target: dialog_file

        onSetTitle: { 
            if (!text_line_title.m_state && title != "") text_line_title.reset(); 
            text_line_title.m_text = title;
            if (text_line_title.m_state && title == "") text_line_title.reset(); } 

        onSetArtist: { 
            if (!text_line_artist.m_state && artist != "") text_line_artist.reset(); 
            text_line_artist.m_text = artist; 
            if (text_line_artist.m_state && artist == "") text_line_artist.reset(); } 

        onSetAlbum: { 
            if (!text_line_album.m_state && album != "") text_line_album.reset(); 
            text_line_album.m_text = album; 
            if (text_line_album.m_state && album == "") text_line_album.reset(); }  

        onSetGenre: { 
            if (!text_line_genre.m_state && genre != "") text_line_genre.reset(); 
            text_line_genre.m_text = genre; 
            if (text_line_genre.m_state && genre == "") text_line_genre.reset(); } 

        onSetYear: { 
            if (!text_line_year.m_state && year != "") text_line_year.reset(); 
            text_line_year.m_text = year; 
            if (text_line_year.m_state && year == "") text_line_year.reset(); } 

        onSetImage: {
            if (image != "standard_cover") cover.source = "image://imageProviderDF/x128/" + image;
            else cover.source = "qrc:/Themes/White/standard_cover.jpg";
        }
    }

    /* Load Font */
    FontLoader { id: localFont; source: "qrc:/Fonts/Gilroy.ttf" }


    /* Upper Controls Button */
    Item
    {
        id: controlButtons
        width: parent.width
        height: 32

        anchors.right: parent.right
        anchors.top: parent.top

        MouseArea
        {
            anchors.fill: parent
            property var clickPos

            onPressed: clickPos = { x: mouse.x, y: mouse.y }
            onPositionChanged:
            {
                window.x = dialog_file.cursorPos().x - clickPos.x
                window.y = dialog_file.cursorPos().y - clickPos.y
            }
        }

        Rectangle
        {
            id: cross_buttom
            width: 46
            height: 32
            color: "transparent"

            anchors.right: parent.right

            Image
            {
                width: 10
                height: 10
                source: "qrc:/Themes/White/cross_button.svg"

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
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
                        parent.color = "red";
                        state = false;
                    }
                    else
                    {
                        parent.color = "transparent";
                        state = true;
                    }
                }
                onClicked: window.close()
            }
        }
    }

    /* File Dialog for choosing music files */
    FileDialog
    {
        id: fileDialogMusic
        title: "Please choose a music"
        folder: shortcuts.desktop
        nameFilters: [ "Music files (*.mp3)"]
        selectMultiple: true

        onAccepted:
        {
            /* The animation shift drop place to the left */
            an_drop_place_x.start();

            /* The animation is showing list*/
            list.visible = true;
            an_list_show.start();

            /* The animation is showing buttom Next-Back*/
            buttom.visible = true;
            an_buttom_opacity.start();

            rec.mBorderColor = "#000";
			
			dialog_file.getFiles(fileDialogMusic.fileUrls);
        }
    }

    /* File Dialog for choosing music cover  */
    FileDialog
    {
        id: fileDialogCover
        title: "Please choose a cover"
        folder: shortcuts.desktop
        nameFilters: [ "Image files (*.jpg)"]

        onAccepted:
        {
            cover.source = fileDialogCover.fileUrl;

            dialog_file.saveImage(fileDialogCover.fileUrl);
        }
    }

    /* Main container with items window */
    Item
    {
        id: main_container

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 15
        anchors.topMargin: 15

        Label
        {
            id: title_dialog
            text: "Music Upload"
            font.family: "Gilroy"
            font.pixelSize: 26
            font.bold: true
            color: "black"

            anchors.horizontalCenter: window.horizontalCenter
        }

        Rectangle
        {
            id: line
            color: "gray"
            width: parent.width
            height: 2
            radius: 5

            anchors.top: title_dialog.bottom
            anchors.topMargin: 10
        }

        Item
        {
            id: drop_place
            width: 200
            height: 200
            visible: true

            x: window.width / 2 - rec.width / 2
            y: window.height / 2 - drop_place.height / 2

            NumberAnimation on x
            {
                id: an_drop_place_x
                from: drop_place.x
                to: 35
                duration: 400
                running: false
            }

            NumberAnimation on opacity
            {
                id: an_drop_place_opacity
                from: drop_place.opacity
                to: 0
                duration: 400
                running: false
            }

            DottedRectangle
            {
                id: rec
                width: 200
                height: 200
                mWidth: 200
                mHeight: 200
                mBorderDottedSpacing: 20
                mBorderLenght: 4

                DropArea
                {
                    width: parent.width
                    height: parent.height

                    enabled: true

                    onEntered:
                    {
                        parent.mBorderColor = "#2675FF";
                    }

                    onExited:
                    {
                        parent.mBorderColor = "#000";
                    }

                    onDropped:
                    {
                        an_drop_place_x.start();

                        list.visible = true;
                        an_list_show.start();

                        buttom.visible = true;
                        an_buttom_opacity.start();

                        dialog_file.getFiles(fileDialogMusic.fileUrls);

                        parent.mBorderColor = "#000";
                    }
                }


                Column
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    spacing: 7

                    Image
                    {
                        source: "qrc:/Themes/White/circle.png"
                        width: 64
                        height: 64
                        anchors.horizontalCenter: parent.horizontalCenter
                        smooth: true
                    }

                    Label
                    {
                        text: "Drag files to upload\n your music"
                        font.family: "Gilroy"
                        font.pixelSize: 16
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignHCenter
                        color: "lightgray"
                    }
                }
            }

            Rectangle
            {
                width: rec.width - (rec.width/5)
                height: 30
                color: "#2675FF"
                radius: 10

                anchors.top: rec.bottom
                anchors.topMargin: 10

                anchors.horizontalCenter: parent.horizontalCenter

                Label
                {
                    text: "Choose file"
                    font.family: "Gilroy"
                    font.pixelSize: 14
                    font.bold: true
                    color: "white"

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                    onClicked: fileDialogMusic.open();

                }
            }
        }

        Item
        {
            id: music_property

            x: window.width / 2
            y: 100

            opacity: 0

            visible: false

            NumberAnimation on opacity
            {
                id: an_music_property_opacity
                from: music_property.opacity
                to: 100
                running: false
            }

            Rectangle
            {
            id: buttom_save
                width: 100
                height: 25
                color: "#2675FF"
                radius: 10

                x: coverMask.x + coverMask.width/2 - width/2
                y: coverMask.y + coverMask.height + 25

                Label
                {
                    id: lable_buttom_save
                    text: "Save"
                    font.family: "Gilroy"
                    font.pixelSize: 14
                    font.bold: true
                    color: "white"

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                    onClicked:
                    {
                        var checkLines = true;

                        if (text_line_title.m_text == "")
                        {
                            text_line_title.m_borderColor = "red";
                            checkLines = false;
                        }
                        else
                        {
                            text_line_title.m_borderColor = "lightgray";
                            checkLines = checkLines ? true : false;
                        }

                        if (text_line_artist.m_text == "")
                        {
                            text_line_artist.m_borderColor = "red";
                            checkLines = false;
                        }
                        else
                        {
                            text_line_artist.m_borderColor = "lightgray";
                            checkLines = checkLines ? true : false;
                        }

                        if (text_line_album.m_text == "")
                        {
                            text_line_album.m_borderColor = "red";
                            checkLines = false;
                        }
                        else 
                        {
                            text_line_album.m_borderColor = "lightgray";
                            checkLines = checkLines ? true : false;
                        }

                        if (text_line_genre.m_text == "")
                        {
                            text_line_genre.m_borderColor = "red";
                            checkLines = false;
                        }
                        else 
                        {
                            text_line_genre.m_borderColor = "lightgray";
                            checkLines = checkLines ? true : false;
                        }

                        if (text_line_year.m_text == "")
                        {
                            text_line_year.m_borderColor = "red";
                            checkLines = false;
                        }
                        else
                        {
                            text_line_year.m_borderColor = "lightgray";
                            checkLines = checkLines ? true : false;
                        }
                        
                        if (checkLines)
                            dialog_file.saveFeatures(text_line_title.m_text, text_line_artist.m_text, text_line_album.m_text, text_line_genre.m_text, text_line_year.m_text);
                    }
                }
            } 

            Item
            {
                Item
                {
                    id: image_cover
                    width: 128
                    height: 128

                    anchors.top: parent.top

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked: { fileDialogCover.open(); }
                    }

                    Image
                    {
                        id: cover
                        width: 128
                        height: 128
                        source: "qrc:/Themes/White/standard_cover.jpg"
                        visible: false
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
                        color: "#676D7A"
                        source: coverMask
                    }
                }

                ColumnLayout
                {
                    spacing: 10

                    anchors.left: image_cover.right
                    anchors.leftMargin: 15

                    TextLine
                    {
                        id: text_line_title
                        m_height: 32
                        m_width: 160
                        m_fontSize: 15
                        m_holderText: "Title"
                        m_focusedColor: "#2675FF"

                    }

                    TextLine
                    {
                        id: text_line_artist
                        m_height: 32
                        m_width: 160
                        m_fontSize: 15
                        m_holderText: "Artist"
                        m_focusedColor: "#2675FF"
                    }

                    TextLine
                    {
                        id: text_line_album
                        m_height: 32
                        m_width: 160
                        m_fontSize: 15
                        m_holderText: "Album"
                        m_focusedColor: "#2675FF"
                    }

                    TextLine
                    {
                        id: text_line_year
                        m_height: 32
                        m_width: 160
                        m_fontSize: 15
                        m_holderText: "Year"
                        m_focusedColor: "#2675FF"
                    }

                    TextLine
                    {
                        id: text_line_genre
                        m_height: 32
                        m_width: 160
                        m_fontSize: 15
                        m_holderText: "Genre"
                        m_focusedColor: "#2675FF"
                    }

                    ComboBox {
                        id: control
                        model: ["Comming soon...", "Second", "Third", "Fouth", "Fifth"]

                        delegate: ItemDelegate {
                            width: control.background.width
                            height: control.background.height
                            contentItem: Text {
                                text: modelData
                                color: "#2675FF"
                                font.pixelSize: 15
                                font.family: "Gilroy"
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            highlighted: control.highlightedIndex === index
                        }

                        indicator: Canvas {
                            id: canvas
                            width: 12
                            height: 8
                            contextType: "2d"

                            anchors.right: control.background.right
                            anchors.rightMargin: 15

                            anchors.verticalCenter: control.background.verticalCenter

                            Connections {
                                target: control
                                onPressedChanged: canvas.requestPaint()
                            }

                            onPaint: {
                                context.reset();
                                context.moveTo(0, 0);
                                context.lineTo(width, 0);
                                context.lineTo(width / 2, height);
                                context.closePath();
                                context.fillStyle = control.pressed ? "#2675FF" : "lightgray";
                                context.fill();
                            }
                        }

                        contentItem: Text
                        {
                            text: control.displayText
                            font.pixelSize: 15
                            font.family: "Gilroy"
                            color: control.pressed ? "#2675FF" : "lightgray"
                            verticalAlignment: Text.AlignVCenter

                            anchors.left: control.background.left
                            anchors.leftMargin: 15

                            anchors.verticalCenter: control.background.verticalCenter
                        }

                        background: Rectangle
                        {
                            width: 160
                            height: 32
                            border.color: "#2675FF"
                            radius: 9
                        }

                        popup: Popup
                        {
                            y: control.background.y + control.background.height + 5
                            width: control.background.width
                            height: 160

                            contentItem: ListView
                            {
                                clip: true
                                implicitHeight: contentHeight
                                model: control.popup.visible ? control.delegateModel : null
                                currentIndex: control.highlightedIndex

                                ScrollIndicator.vertical: ScrollIndicator { }
                            }

                            background: Rectangle {
                                border.color: "#2675FF"
                                radius: 4
                            }
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id: buttom_finish
            width: 100
            height: 25
            color: "#2675FF"
            radius: 10

            visible: false

            opacity: 0

            x: main_container.width - buttom.width
            y: main_container.height - buttom.height

            Label
            {
                id: lable_buttom_finish
                text: "Finish"
                font.family: "Gilroy"
                font.pixelSize: 14
                font.bold: true
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            NumberAnimation on opacity
            {
                id: an_buttom_finish_opacity
                from: 0
                to: 100
                duration: 400
                running: false
            }

            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                onClicked:
                {
                    dialog_file.finish();
                }
            }
        }

        Rectangle
        {
            id: buttom
            width: 100
            height: 25
            color: "#2675FF"
            radius: 10

            visible: false

            opacity: 0

            x: main_container.width - buttom.width
            y: main_container.height - buttom.height

            Label
            {
                id: lable_button
                text: "Next"
                font.family: "Gilroy"
                font.pixelSize: 14
                font.bold: true
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            NumberAnimation on x
            {
                id: an_buttom_x
                from: buttom.x
                to: drop_place.x
                duration: 400
                running: false
            }

            NumberAnimation on opacity
            {
                id: an_buttom_opacity
                from: buttom.opacity
                to: 100
                duration: 400
                running: false
            }

            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                property bool state: false

                onClicked:
                {
                    an_music_property_opacity.stop();
                    an_drop_place_opacity.stop();
                    an_buttom_x.stop();
                    an_buttom_finish_opacity.stop();

                    if (!state)
                    {
                        lable_button.text = "Back";

                        buttom_finish.visible = true;
                        music_property.visible = true;

                        list.width = 295;

                        drop_place.opacity = 100;
                        an_drop_place_opacity.to = 0;
                        an_drop_place_opacity.duration = 40000;
                        an_drop_place_opacity.start();

                        an_list_x.to = 15;
                        an_list_x.duration = 400;
                        an_list_x.start();

                        music_property.opacity = 0;
                        an_music_property_opacity.to = 100;
                        an_music_property_opacity.duration = 40000;
                        an_music_property_opacity.start();

                        an_buttom_x.to = main_container.x;
                        an_buttom_x.start();

                        buttom_finish.opacity = 0;
                        an_buttom_finish_opacity.to = 100;
                        an_buttom_finish_opacity.duration = 40000;
                        an_buttom_finish_opacity.start();

                        drop_place.visible = false;
                        listview.isVisibleIcon = false;

                        state = true;
                    }
                    else
                    {

                        text_line_title.m_text = "";
                        text_line_artist.m_text = ""; 
                        text_line_album.m_text = ""; 
                        text_line_genre.m_text = ""; 
                        text_line_year.m_text = "";

                        if (text_line_title.m_state) if (text_line_title.m_focus) text_line_title.m_focus = false; else text_line_title.reset();
                        if (text_line_artist.m_state) if (text_line_artist.m_focus) text_line_artist.m_focus = false; else text_line_artist.reset();
                        if (text_line_album.m_state) if (text_line_album.m_focus) text_line_album.m_focus = false; else text_line_album.reset();
                        if (text_line_genre.m_state) if (text_line_genre.m_focus) text_line_genre.m_focus = false; else text_line_genre.reset();
                        if (text_line_year.m_state) if (text_line_year.m_focus) text_line_year.m_focus = false; else text_line_year.reset();

                        text_line_title.m_focus ? false : true;

                        cover.source = "qrc:/Themes/White/standard_cover.jpg"
                        
                        lable_button.text = "Next";

                        drop_place.visible = true;
                        music_property.visible = false;

                        drop_place.opacity = 0;
                        an_drop_place_opacity.to = 100;
                        an_drop_place_opacity.start();

                        list.width = 400;
                        an_list_x.to = window.width - 35 - 400;
                        an_list_x.duration = 400;
                        an_list_x.start();

                        music_property.opacity = 100;
                        an_music_property_opacity.to = 0;
                        an_music_property_opacity.duration = 40000;
                        an_music_property_opacity.start();

                        an_buttom_x.to = main_container.width - buttom.width;
                        an_buttom_x.start();

                        listview.isVisibleIcon = true;

                        an_buttom_finish_opacity.to = 0;
                        an_buttom_finish_opacity.start();

                        buttom_finish.visible = false;

                        state = false;
                    }
                }
            }

        }

        Item
        {
            id: list
            width: 400
            height: 350

            visible: false

            opacity: 0

            anchors.top: parent.top
            anchors.topMargin: 75

            x: window.width - 35 - width

            NumberAnimation on opacity
            {
                id: an_list_show
                from: list.opacity
                to: 100
                duration: 30000
                running: false
            }

            NumberAnimation on x
            {
                id: an_list_x
                from: list.x
                to: drop_place.x
                duration: 400
                running: false
            }

            NumberAnimation on width
            {
                id: an_list_width
                duration: 400
                running: false
            }

            Row
            {
                id: names
                spacing: 9

                anchors.left: parent.left
                anchors.leftMargin: 10

                Label
                {
                    text: "Chosen"
                    font.family: "Gilroy"
                    font.pixelSize: 18
                    font.bold: true
                    color: "Black"
                }

                Label
                {
                    text: listview.count + " files"
                    font.family: "Gilroy"
                    font.pixelSize: 15
                    color: "gray"

                    anchors.top: parent.top
                    anchors.topMargin: 3
                }
            }

            Item
            {
                id: titles_table

                anchors.top: names.bottom
                anchors.topMargin: 20

                anchors.left: parent.left
                anchors.leftMargin: 10

                Label
                {
                    id: fileName
                    text: "File name"
                    font.family: "Gilroy"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#D0D1D5"
                }

                Label
                {
                    id: fileSize
                    text: "Size"
                    font.family: "Gilroy"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#D0D1D5"

                    anchors.left: fileName.right
                    anchors.leftMargin: 145
                }
            }

            ScrollView
            {
                width: parent.width
                height: parent.height - titles_table.height - 100

                anchors.top: titles_table.bottom
                anchors.topMargin: fileName.height + 15

                anchors.horizontalCenter: parent.horizontalCenter

                ListView
                {
                    id: listview
                    width: parent.width
                    height: parent.height

                    property bool isVisibleIcon: true;
                    property bool isClicked: false;

                    clip: true
                    spacing: 3

                    /*model: ListModel
                    {
                        id: listmodel
                        ListElement { text: "first.mp3" }
                        ListElement { text: "second.mp3" }
                        ListElement { text: "third.mp3" }
                        ListElement { text: "first.mp3" }
                        ListElement { text: "second.mp3" }
                        ListElement { text: "third.mp3" }
                        ListElement { text: "first.mp3" }
                        ListElement { text: "second.mp3" }
                        ListElement { text: "third.mp3" }
                        ListElement { text: "first.mp3" }
                        ListElement { text: "second.mp3" }
                        ListElement { text: "third.mp3" }
                        ListElement { text: "first.mp3" }
                        ListElement { text: "second.mp3" }
                        ListElement { text: "third.mp3" }
                    }*/
					
					model: CModel
					{
						list: listNewMusic
					}

                    delegate: Item
                    {
                        width: parent.width - 10
                        height: 26

                        property bool isVisibleIcon2: listview.isVisibleIcon;

                        DropShadow
                        {
                            anchors.fill: item_fone
                            horizontalOffset: 3
                            verticalOffset: 3
                            radius: 8.0
                            samples: 17
                            color: "#40000000"
                            source: item_fone
                        }

                        Rectangle
                        {
                            id: item_fone
                            width: parent.width
                            height: parent.height
                            color: model.reserve ? "#1E87DA" : "transparent"
                            radius: 5

                            anchors.verticalCenter: parent.verticalCenter

                            MouseArea
                            {
                                anchors.fill: parent
                                hoverEnabled: true

                                property bool isHovered: false

                                onHoveredChanged:
                                {
                                    if (!model.reserve)
                                    {
                                        if (!isHovered)
                                        {
                                            item_fone.color = "#2675FF";
                                            title_item.color = "#fff";
                                            size_item.color = "#fff";
                                            icon_item.source = "qrc:/Themes/White/delete_off.png";
                                            isHovered = true;
                                        }
                                        else
                                        {
                                            item_fone.color = "transparent";
                                            title_item.color = "#000";
                                            size_item.color = "#000";
                                            icon_item.source = "qrc:/Themes/White/delete_on.png";
                                            isHovered = false;
                                        }
                                    }
                                }
                                onClicked:
                                {
                                    if (lable_button.text == "Back")
                                        dialog_file.onClickedItem(model.namefile);
                                }
                            }

                            Image
                            {
                                id: icon_item
                                source: model.reserve ? "qrc:/Themes/White/delete_off.png" : "qrc:/Themes/White/delete_on.png"

                                anchors.right: parent.right
                                anchors.rightMargin: 15

                                visible: isVisibleIcon2

                                anchors.verticalCenter: parent.verticalCenter

                                MouseArea
                                {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor

                                    onClicked:
                                    {
                                        dialog_file.onRemoveItem(title_item.text);
                                    }
                                }
                            }

                            Item
                            {
                                width: item_fone.width
                                height: item_fone.height

                                anchors.left: parent.left
                                anchors.leftMargin: 10

                                anchors.verticalCenter: parent.verticalCenter

                                Text
                                {
                                    id: title_item
                                    text: model.namefile
                                    width: 200
                                    clip: true
                                    font.family: "Gilroy"
                                    font.pixelSize: 15
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: model.reserve ? "#fff" : "#000"

                                    /*function cutLine(text)
                                    {
                                        var line = "";
                                        if (text.length > 21)
                                        {
                                            for (var i = 0; i < 21; i++)
                                                line += text.charAt(i);
                                            line += "...";
                                            return line;
                                        }
                                        return text;
                                    }*/
                                }

                                Text
                                {
                                    id: size_item
                                    text: model.size + " Mb"
                                    font.family: "Gilroy"
                                    font.pixelSize: 13
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: model.reserve ? "#fff" : "#000"

                                    anchors.left: parent.left
                                    anchors.leftMargin: 218
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
