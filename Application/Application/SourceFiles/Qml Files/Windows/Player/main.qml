import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import "../../Styles/Screens"
import "../../Styles/Buttons"

// TEMP
import "../../Styles/ListsView"

import windows.fwindow 1.0

FWindow
{
    id: window;
    m_width: 1440;
    m_height: 960;
    m_minWidth: 1200;
    m_minHeight: 720;
    m_maxWidth: 1920;
    m_maxHeight: 1080

    visible: false;

    FontLoader { id: localFont; source: "qrc:/Resources/Fonts/Gilroy.ttf" }

    Connections
    {
        target: wpRoot;
    }

    /* #4C5458 - gray */
    /* #2ED297 - green */

    Row
    {
        anchors.fill: parent;
        spacing: 0;

        LeftField
        {
            id: left_field;
            height: parent.height;
        }

        Rectangle
        {
            width: parent.width - left_field.width;
            height: parent.height;
            color: "gray";
        }
    }
}
    

/*

        
        
        Item
        {
            id: right_field;
            width: parent.width - left_field.width;
            height: parent.height;

            Rectangle
            {
                id: background_right_field;
                color: Themes.FoneColor; // "#111";
                
                anchors.fill: parent;
            }

            Column
            {
                anchors.fill: parent;
                spacing: 0;

                Item
                {
                    id: upper_field
                    width: parent.width;
                    height: window.m_hTitleBar;

                    WinControlButtons
                    {
                        id: winControlButtons

                        m_width_cell: window.m_hTitleBar + 16;
                        m_height_cell: window.m_hTitleBar;

                        anchors.right: parent.right;
                        anchors.top: parent.top;
                    }
                }

                Item
                {
                    width: parent.width; 
                    height: parent.height - under_field.height - upper_field.height;

                    Loader
                    {
                        id: content_loader;
                        anchors.fill: parent;
                        source: "qrc:/SourceFiles/Qml Files/Styles/Screens/Songs.qml";

                        anchors.left: parent.left
                        anchors.leftMargin: 15;

                        anchors.top: parent.top
                        anchors.topMargin: 10;
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

                    /*Rectangle
                    {
                        anchors.fill: parent;
                        color: Themes.FoneColor;
                    }

                    Column
                    {
                        spacing: 4;

                        anchors.left: parent.left;
                        anchors.leftMargin: 35

                        anchors.verticalCenter: parent.verticalCenter;

                        Label
                        {
							Connections
                            {
								target: FooterPanel;
                            }

                            id: main_title_song
                            text: FooterPanel.title;
                            color: "#fff";
                            font.family: "Gilroy";
                            font.pixelSize: 16

                        }

                        Label
                        {
							Connections
                            {
								target: FooterPanel;
                            }
                            id: main_artist_song
                            text: FooterPanel.artist;
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

                                Connections
                                {
                                    target: mediaPlayer;

                                    onStarted:
                                    {
                                        img_play.source = "qrc:/Resources/Icons/pause.png"
                                    }

                                    onPaused:
                                    {
                                        img_play.source = "qrc:/Resources/Icons/play.png"
                                    }
                                }

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
                                            mediaPlayer.onPrevious();
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

                                    property bool state: false;

                                    gradient: Gradient {
                                        orientation: Gradient.Horizontal
                                        GradientStop { position: 0.0; color: "#2DCB90" }
                                        GradientStop { position: 1.0; color: "#06ACC7" }
                                    }

                                    Image
                                    {
                                        id: img_play;
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
                                            mediaPlayer.onPlay();
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
                                            mediaPlayer.onNext();
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
                                Connections
                                {
                                    target: FooterPanel;
                                }

                                id: elapsed_time
                                width: 32
                                font.pixelSize: 12
                                font.family: "Gilroy"
                                text: FooterPanel.currentTime == "" ? "0:00" : FooterPanel.currentTime;
                                color: "#676D7A"

                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Slider
                            {
                                id: slider;
                                value: 0;
                                to: 99;
                                from: 0;
                                width: 420;
                                height: 6;

                                Connections
                                {
                                    target: mediaPlayer;

                                    onPositionChanged:
                                    {
                                        slider.value = position;
                                    }

                                    onDurationChanged: 
                                    {
                                        slider.to = duration; 
                                    }
                                }

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
                                    height: 0;
                                    width: 0;
                                    visible: false;
                                }

                                onMoved:
                                {
                                    mediaPlayer.onSetPosition(slider.value);
                                }
                            }

                            Label
                            {
								Connections
                                {
                                    target: FooterPanel;
                                }

                                id: all_time
                                width: 32
                                font.pixelSize: 12
                                font.family: "Gilroy"
                                text: FooterPanel.time == "" ? "0:00" : FooterPanel.time;
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
                            id: repeat
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
                                property int state: 1;

                                onClicked:
                                {
                                    if (state == 1)
                                    {
                                        once.visible = false;
                                        parent.source = "qrc:/Resources/Icons/repeat_hovered.png"
                                        state = 2;
                                    }
                                    else if (state == 2)
                                    {
                                        once.visible = true;
                                        state = 3;
                                    }
                                    else
                                    {
                                        parent.source = "qrc:/Resources/Icons/repeat.png"
                                        once.visible = false;
                                        state = 1;
                                    }

                                    wpRoot.playModeChanged(state);
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



*/