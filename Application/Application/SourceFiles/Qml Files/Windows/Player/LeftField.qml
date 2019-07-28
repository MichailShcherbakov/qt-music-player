import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

Item
{
	id: left_field;
	width: isActive ? 256 : 48;
	height: parent.height;

 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Black.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-BlackItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Bold.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-BoldItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-ExtraBold.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-ExtraBoldItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-ExtraLight.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-ExtraLightItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Light.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-BlackItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-LightItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Medium.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-MediumItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Regular.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-RegularItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-SemiBold.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-SemiBoldItalic.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-Thin.ttf"; }
 	FontLoader { source: "qrc:/Resources/Fonts/Poppins-ThinItalic.ttf"; }
	

	property bool isActive: false;

	Rectangle
	{
		id: background_left_field;
		anchors.fill: parent;
		color: Themes.LeftFieldBackground;

		Rectangle
		{
			id: control_button;
			width: 48;
			height: 48;
			color: Themes.LeftFieldBackground;

			anchors.top: parent.top;
			anchors.topMargin: 48;

			Image
	        {
	            id: imageControlButton;
	            width: 20;
	            height: 20;
	            source: "qrc:/Resources/Icons/list-menu.png";
	            smooth: true;

	            anchors.fill: control_button;
	            anchors.margins: 14;
	        }

			MouseArea
			{
				anchors.fill: parent;
				hoverEnabled: true;

				onEntered:
            	{
            		control_button.color = Themes.LeftFieldHoveredBackgroundItem;
            	}

            	onExited:
            	{
            		control_button.color = Themes.LeftFieldBackground;
            	}

				onClicked:
				{
					animathon_shift_left_field.stop();

					if (isActive)
					{
						animathon_shift_left_field.from = 256;
						animathon_shift_left_field.duration = 150;
						animathon_shift_left_field.to = 48;
						left_field.isActive = false;
					}
					else
					{
						animathon_shift_left_field.from = 48;
						animathon_shift_left_field.duration = 200;
						animathon_shift_left_field.to = 256;
						
						left_field.isActive = true;
					}
					animathon_shift_left_field.start();
				}
			}

			PropertyAnimation
			{
				id: animathon_shift_left_field;
				target: left_field;
				property: "width";
				running: false;
			}
		}

		ListView
		{
		    id: browse_music_list;
		    width: 256;
		    height: 48 * 4 + 10 * (4 - 1);
		    spacing: 10;
		    interactive: false;

		    anchors.top: control_button.bottom;

		    model: ListModel
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

		    delegate: Item
		    {
		        id: item_menu;
		        width: left_field.isActive ? 256 : 48;
		        height: 48;

		        Rectangle
		        {
		        	id: background_item;
		            anchors.fill: parent;
		            color: Themes.LeftFieldHoveredBackgroundItem;
		            visible: false;
		        }

		        Rectangle
		        {
		            id: sing_item;
		            width: 3;
		            height: parent.height;
		            color: Themes.LeftFieldSingItemMenu;
		            visible: browse_music_list.currentIndex == index;
		        }

		        /*DropShadow
		        {
		            id: shadow_sing_item;
		            anchors.fill: sing_item;
		            horizontalOffset: 0;
		            verticalOffset: 0;
		            radius: 10.0;
		            samples: 17;
		            color: Themes.ShadowSingItemMenu; //"#5CFFC3"
		            source: sing_item;
		            visible: false;
		        }*/

		        Image
		        {
		            id: image_item;
		            width: 20;
		            height: 20;
		            source: model.img;
		            smooth: true;

		            anchors.left: parent.left;
		            anchors.leftMargin: 12;
		            anchors.verticalCenter: parent.verticalCenter;
		        }

		        /*Image
		        {
		            id: imageItemHovered;
		            source: model.img_hovered;
		            sourceSize.width: 20;
		            sourceSize.height: 20;
		            opacity: 0;
		            smooth: true;

		            anchors.fill: imageItem;
		        }*/

		        Label
		        {
		            id: text_item
		            text: model.text;
		            color: Themes.FontColor; //"#4C5458";
		            font.family: "Poppins";
		            font.weight: Font.DemiBold;
		            font.pixelSize: 14;
		            //visible: left_field.isActive;

		            anchors.left: image_item.right;
		            anchors.leftMargin: 24;
		            anchors.verticalCenter: parent.verticalCenter;
		        }

		        /*Label
		        {
		            id: textItemHovered
		            text: model.text;
		            color: "#2ED297";
		            font.family: "Gilroy";
		            font.pixelSize: 14;
		            opacity: 0;

		            anchors.fill: textItem;
		        }*/

		        MouseArea
		        {
		            anchors.fill: parent;
		            hoverEnabled: true;

		            onEntered:
		            {
		            	background_item.visible = true;
		            }

		            onExited:
		            {
		            	background_item.visible = false;
		            }

		                /*animation_shadow.stop();
		                animation_item.stop();
		                animation_item_hovered.stop();

		                if (!local_state)
		                {
		                    // Hovered
		                    local_state = true;
		                    animation_shadow.to = 1;
		                    animation_item_hovered.to = 1;
		                    animation_item.to = 0;
		                }
		                else
		                {
		                    local_state = false;
		                    animation_shadow.to = 0;
		                    animation_item_hovered.to = 0;
		                    animation_item.to = 1;

		                }
		                animation_shadow.start();
		                animation_item.start();
		                animation_item_hovered.start();*/

		            onClicked:
		            {
		            	//console.log(browse_music_list.currentIndex);
		            	console.log(index);
		            	browse_music_list.currentIndex = index;
		                /*browseMusicList.cliked(textItem.text);*/
		            }
		        }

		        Component.onCompleted: {
				    browse_music_list.currentIndex = -1;
				}

		        /*PropertyAnimation
		        {
		            id: animation_shadow
		            target: shadow
		            property: "opacity"
		            duration: 200
		            easing.type: Easing.InOutQuad
		        }

		        PropertyAnimation
		        {
		            id: animation_item
		            targets: [imageItem, textItem]
		            property: "opacity"
		            duration: 200
		            easing.type: Easing.InOutQuad
		        }

		        PropertyAnimation
		        {
		            id: animation_item_hovered
		            targets: [imageItemHovered, textItemHovered]
		            property: "opacity"
		            duration: 200
		            easing.type: Easing.InOutQuad
		        }*/
		    }
		}
	}
}


                   /* Row
                    {
                        id: username_row;
                        height: 42;
                        spacing: 14;

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

                            /*OpacityMask
                            {
                                anchors.fill: image_user;
                                source: image_user;
                                maskSource: mask_image_user;
                            }*/
                            /*}

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

                ScrollView
                {
                    width: parent.width;
                    height: parent.height - username.height - 10 - main_cover.height;
                    clip: true;

                    ScrollBar.vertical.policy: ScrollBar.AlwaysOff;

                    anchors.top: username.bottom;

                    Column
                    {
                        anchors.fill: parent;
                        spacing: 0;

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

                                onCliked:
                                {
                                    if (title == "Songs")
                                    {
                                        content_loader.source = "qrc:/SourceFiles/Qml Files/Styles/Screens/Songs.qml";
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
                    id: main_cover;
                    width: 196;
                    height:  196;
                    visible: false;

					Connections
                    {
						target: FooterPanel;
					}

                    property string path: FooterPanel.coverID == "" ? "default" : FooterPanel.coverID;

                    Image
                    {
                        id: cover_image;
                        anchors.fill: parent;
                        source: isUnknown(main_cover.path);
                        smooth: true;

                        function isUnknown(text)
                        {
                            if (text == "default")
                            {
                                mask.visible = true;
                                unknown_cover.visible = true;
                                coverMask.visible = false;
                                shadow.source = mask;

                                return "qrc:/Resources/Icons/cover.jpg";
                            }
                            else
                            {
                                mask.visible = false;
                                unknown_cover.visible = false;
                                coverMask.visible = true;
                                shadow.source = coverMask;

                                return "image://rootImageDirectory/x196/" + text;
                            }
                        }
                    }

                    anchors.bottom: parent.bottom;
                    anchors.left: parent.left;
                    anchors.bottomMargin: 10;
                    anchors.leftMargin: 10;
                }

                Rectangle
                {
                    id: mask;
                    anchors.fill: main_cover;
                    radius: 7;
                    color: "#1B1D23";
                    visible: false;
                    z: 1;
                }

                Image
                {
                    id: unknown_cover;
                    width: 64;
                    height: 64;
                    source: "qrc:/Resources/Icons/cover_note.png";
                    smooth: true;
                    z: 1;
                    visible: false;

                    anchors.verticalCenter: mask.verticalCenter;
                    anchors.horizontalCenter: mask.horizontalCenter;
                }

                OpacityMask
                {
                    id: coverMask;
                    anchors.fill: main_cover;
                    source: main_cover;
                    maskSource: mask;
                    visible: false;
                }

                DropShadow
                {
                    id: shadow;
                    anchors.fill: mask;
                    horizontalOffset: 0;
                    verticalOffset: 4;
                    radius: 14.0;
                    samples: 17;
                    color: "#000";
                    source: coverMask;
                }
            }

        }*/