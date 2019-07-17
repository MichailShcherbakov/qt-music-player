import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

ListView
{
	property var m_model: ListModel{}

    anchors.fill: parent;
    spacing: 10;
    clip: true;

	model: m_model;

	Connections
	{
		target: listSongsSection;
	}

    delegate: Item
	{
		width: parent.width;
		height: 10 + cover.height + 10;

		Component.onDestruction:
        {
            listSongsSection.DeleteImageItem(model.id);
        }

        Component.onCompleted:
        {
            listSongsSection.LoadImageItem(model.id);
        }

		Rectangle
		{
			id: list_item;
			anchors.fill: parent;
			color: "#111";
			radius: 8;

			function points(str, size)
			{
				if (str.length > size)
				{
					var newStr = new String("");

					for (var i = 0; i < size; ++i)
					{
						newStr += str[i];
					}

					newStr += "...";
					return newStr;
				}
				else
				{
					return str;
				}
			}

			Rectangle
		    {
		        id: item_background;
		        anchors.fill: parent;
		        radius: 8;
		        color: "#000";
		        opacity: 0;
		    }

			MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;

                onEntered:
                {
                	hover_animation.stop();
                	hover_animation_background_cover_play.stop();

                	if (!play_sign.visible)
                	{
                		hover_animation.targets = [ item_background, cover_play ];
                	}
                	else
                	{
                		hover_animation.targets = [ item_background ];
                	}

                	hover_animation.to = 1;
                	hover_animation_background_cover_play.to = 0.5;

					hover_animation_background_cover_play.start();
                	hover_animation.start();
                }

                onExited:
                {
                	hover_animation.stop();
                	hover_animation_background_cover_play.stop();

                	if (!play_sign.visible)
                	{
                		hover_animation.targets = [ item_background, cover_play ];
                	}
                	else
                	{
                		hover_animation.targets = [ item_background ];
                	}

                	hover_animation.to = 0;

                	if (!play_sign.visible)
                	{
                		hover_animation_background_cover_play.to = 0;
                	}

                	hover_animation_background_cover_play.start();
                	hover_animation.start();
                }
            }

            PropertyAnimation
	        {
	            id: hover_animation;
	            targets: [ item_background, cover_play ];
	            property: "opacity";
	            duration: 100;
	            easing.type: Easing.InOutQuad;
	        }

	        PropertyAnimation
	        {
	            id: hover_animation_background_cover_play;
	            target: background_cover_play;
	            property: "opacity";
	            duration: 100;
	            easing.type: Easing.InOutQuad;
	        }

			Image
			{
				id: cover;
				width: 50;
				height: 50;
				source: "image://rootImageDirectory/x50/" + isDefualt(model.cover_key);
				smooth: true;
				visible: false;

				function isDefualt(title)
				{
					if (title == "default")
					{
						background.visible = true;
						unknown_cover.visible = true;
						opacity_mask.visible = false;
					}
					else
					{
						background.visible = false;
						unknown_cover.visible = false;
						opacity_mask.visible = true;
					}
					return title;
				}

				anchors.left: parent.left;
		        anchors.leftMargin: 16;

				anchors.verticalCenter: parent.verticalCenter;
			}

			Rectangle
			{
				id: background_cover_play;
				anchors.fill: opacity_mask;
				color: "#000";
				z: 1;
				opacity: model.expression ? 0.5 : 0;
			}

			Image
	        {
	        	id: cover_play;
				width: 24;
				height: 24;
				source: "qrc:/Resources/Icons/play-button.png";
				smooth: true;
				z: 1;
				opacity: 0;

				anchors.verticalCenter: opacity_mask.verticalCenter;
			    anchors.horizontalCenter: opacity_mask.horizontalCenter;

			    MouseArea
			    {
			    	anchors.fill: parent;
			    	cursorShape: Qt.PointingHandCursor;

			    	onClicked:
			    	{
			    		wpRoot.clickedItem(1, model.id); // 1 - ListSongsScreen::ETypeSection::ListSongsSection
			    		background.visible = true;
			    	}
			    }
	        }

			Rectangle
		    {
		        id: background;
		        anchors.fill: cover;
		        radius: 3;
		        color: "#1B1D23";
		        visible: false;
		    }

		    Image
		    {
		        id: unknown_cover;
		        width: 16;
		        height: 16;
		        source: "qrc:/Resources/Icons/cover_note.png";
		        smooth: true;
		        visible: false;

		        anchors.verticalCenter: background.verticalCenter;
		        anchors.horizontalCenter: background.horizontalCenter;
		    }

		    OpacityMask
		    {
		        id: opacity_mask;
		        anchors.fill: cover;
		        source: cover;
		        maskSource: background;
			}

			Item
			{
				id: play_sign;
				width: 15;
				height: 20;
				z: 1;

				anchors.verticalCenter: background.verticalCenter;
		        anchors.horizontalCenter: background.horizontalCenter;

				property int m_spacing: 1;
				property bool isRunning: model.expression;
				visible: model.expression;

				Rectangle
				{
					id: first;
					width: (play_sign.width - 3*parent.m_spacing) / 4;
					height: 17;
					color: "#fff"

					anchors.left: play_sign.left;
					anchors.bottom: parent.bottom;

					PropertyAnimation
					{
						id: animathon_first;
						target: first;
						to: 10;
						duration: 150;
						property: "height";
						//loops: Animation.Infinite;
						running: play_sign.isRunning;

						property string state: "down"

						onFinished:
						{
							if (state == "down")
							{
								animathon_first.to = 18;
								animathon_first.duration = 200;
								state = "up";
								animathon_first.restart();
							}
							else if (state == "up")
							{
								animathon_first.to = 10;
								animathon_first.duration = 230;
								state = "middle";
								animathon_first.restart();
							}
							else if (state == "middle")
							{
								animathon_first.to = 15;
								animathon_first.duration = 170;
								state = "forth";
								animathon_first.restart();
							}
							else if (state == "forth")
							{
								animathon_first.to = 4;
								animathon_first.duration = 235;
								state = "down";
								animathon_first.restart();
							}
						}
					}
				}

				Rectangle
				{
					id: second;
					width: (play_sign.width - 3*parent.m_spacing) / 4;
					height: 12;
					color: "#fff"

					anchors.left: first.right;
					anchors.leftMargin: parent.m_spacing;
					anchors.bottom: parent.bottom;

					PropertyAnimation
					{
						id: animathon_second;
						target: second;
						to: 13;
						duration: 150;
						property: "height";
						//loops: Animation.Infinite;
						running: play_sign.isRunning;

						property string state: "middle"

						onFinished:
						{
							if (state == "down")
							{
								animathon_second.to = 21;
								animathon_second.duration = 252;
								state = "up";
								animathon_second.restart();
							}
							else if (state == "up")
							{
								animathon_second.to = 10;
								animathon_second.duration = 262;
								state = "middle";
								animathon_second.restart();
							}
							else if (state == "middle")
							{
								animathon_second.to = 4;
								animathon_second.duration = 235;
								state = "forth";
								animathon_second.restart();
							}
							else if (state == "forth")
							{
								animathon_second.to = 8;
								animathon_second.duration = 266;
								state = "down";
								animathon_second.restart();
							}
						}
					}
				}

				Rectangle
				{
					id: third;
					width: (play_sign.width - 3*parent.m_spacing) / 4;
					height: 20;
					color: "#fff"

					anchors.left: second.right;
					anchors.leftMargin: parent.m_spacing;
					anchors.bottom: parent.bottom;

					PropertyAnimation
					{
						id: animathon_third;
						target: third;
						to: 21;
						duration: 150;
						property: "height";
						//loops: Animation.Infinite;
						running: play_sign.isRunning;

						property string state: "up"

						onFinished:
						{
							if (state == "down")
							{
								animathon_third.to = 21;
								animathon_third.duration = 262;
								state = "up";
								animathon_third.restart();
							}
							else if (state == "up")
							{
								animathon_third.to = 18;
								animathon_third.duration = 267;
								state = "middle";
								animathon_third.restart();
							}
							else if (state == "middle")
							{
								animathon_third.to = 19;
								animathon_third.duration = 295;
								state = "forth";
								animathon_third.restart();
							}
							else if (state == "forth")
							{
								animathon_third.to = 8;
								animathon_third.duration = 229;
								state = "down";
								animathon_third.restart();
							}
						}
					}
				}

				Rectangle
				{
					id: fourth;
					width: (play_sign.width - 3*parent.m_spacing) / 4;
					height: 8;
					color: "#fff"

					anchors.left: third.right;
					anchors.leftMargin: parent.m_spacing;
					anchors.bottom: parent.bottom;

					PropertyAnimation
					{
						id: animathon_fourth;
						target: fourth;
						to: 16;
						duration: 150;
						property: "height";
						//loops: Animation.Infinite;
						running: play_sign.isRunning;

						property string state: "forth"

						onFinished:
						{
							if (state == "down")
							{
								animathon_fourth.to = 8;
								animathon_fourth.duration = 242;
								state = "up";
								animathon_fourth.restart();
							}
							else if (state == "up")
							{
								animathon_fourth.to = 11;
								animathon_fourth.duration = 228;
								state = "middle";
								animathon_fourth.restart();
							}
							else if (state == "middle")
							{
								animathon_fourth.to = 19;
								animathon_fourth.duration = 286;
								state = "forth";
								animathon_fourth.restart();
							}
							else if (state == "forth")
							{
								animathon_fourth.to = 10;
								animathon_fourth.duration = 311;
								state = "down";
								animathon_fourth.restart();
							}
						}
					}
				}
			}

			Label
			{
				id: first_title;
		        font.pixelSize: 13;
		        font.family: "Gilroy";
		        text: model.text_line_first;
		        color: "#fff";

		        anchors.left: cover.right;
		        anchors.leftMargin: 24;

		        anchors.verticalCenter: parent.verticalCenter;
			}

			Label
			{
				id: second_title;
		        font.pixelSize: 13;
		        font.family: "Gilroy";
		        text: model.text_line_second;
		        color: "#4C5458";

		        anchors.left: first_title.left;
		        anchors.leftMargin: parent.width/4 + 24;

		        anchors.verticalCenter: parent.verticalCenter;
			}

			Label
			{
				id: third_title;
		        font.pixelSize: 13;
		        font.family: "Gilroy";
		        text: model.text_line_third;
		        color: "#4C5458";

		        anchors.left: second_title.left;
		        anchors.leftMargin: parent.width/4 + 24;

		        anchors.verticalCenter: parent.verticalCenter;
			}

			Label
			{
				id: fourth_title;
		        font.pixelSize: 13;
		        font.family: "Gilroy";
		        text: model.text_line_fourth;
		        color: "#4C5458";

		        anchors.left: third_title.left;
		        anchors.leftMargin: parent.width/4 + 24;

		        anchors.verticalCenter: parent.verticalCenter;
			}

			Image
	        {
	        	id: edit_button;
				width: 16;
				height: 16;
				source: "qrc:/Resources/Icons/dotted_button_item.png";
				smooth: true;

				anchors.left: fourth_title.left;
		        anchors.leftMargin: 64;

				anchors.verticalCenter: parent.verticalCenter;

				MouseArea
				{
					anchors.fill: parent;
					cursorShape: Qt.PointingHandCursor;

					onClicked:
					{
						menu.open()
					}
				}

			    Menu 
			    {
				    id: menu

				    Action { text: qsTr("Play"); }
				    Action { text: qsTr("Play next"); }
				    Action { text: qsTr("Album"); }
				    Action { text: qsTr("Artist"); }
				    Action { text: qsTr("Add to playlist"); }
				    Action { text: qsTr("Add to queue"); }
				    Action { text: qsTr("Edit tags"); }
				    Action { text: qsTr("Delete"); }

				    /*MenuSeparator 
				    {
				        contentItem: Rectangle 
				        {
				            implicitWidth: 200
				            implicitHeight: 1
				            color: "#21be2b"
				        }
				    }

				    Menu 
				    {
				        title: qsTr("Advanced")
				    }*/

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
				                ctx.fillStyle = menuItem.highlighted ? "#ffffff" : "#4C5458"
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
				                border.color: "#4C5458"
				                radius: 50

				                Rectangle 
				                {
				                    width: 8
				                    height: 8
				                    anchors.centerIn: parent
				                    visible: menuItem.checked
				                    color: "#4C5458"
				                    radius: 50
				                }
				            }
				        }

				        contentItem: Text 
				        {
				            leftPadding: menuItem.indicator.width
				            rightPadding: menuItem.arrow.width
				            text: menuItem.text
				            font.family: "Gilroy";
				            font.pixelSize: 14;
				            opacity: enabled ? 1.0 : 0.3
				            color: menuItem.highlighted ? "#ffffff" : "#4C5458"
				            horizontalAlignment: Text.AlignLeft
				            verticalAlignment: Text.AlignVCenter
				            elide: Text.ElideRight
				        }

				        background: Rectangle 
				        {
				            implicitWidth: 200
				            implicitHeight: 30
				            opacity: enabled ? 1 : 0.3
				            color: menuItem.highlighted ? "#4C5458" : "transparent"
				        }
				    }

				    background: Rectangle 
				    {
				        implicitWidth: 200
				        implicitHeight: 30
				        color: "#1B1D23"
				        border.color: "#4C5458"
				        radius: 2
				    }
				}
	        }
		}
		/*DropShadow
		{
		    id: shadow;
		    anchors.fill: parent;
		    horizontalOffset: 0;
		    verticalOffset: 3;
		    radius: 12;
		    samples: 17;
		    spread: 0.0;
		    color: "#000";
		    source: list_item;
		}*/
	}
}