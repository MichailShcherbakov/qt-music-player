import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import tools.mousearea 1.0

ListView
{
	property var m_model: ListModel{}
	property int m_spacing: 32;
	property int m_width: 900;
	property int m_height: 200;
	property int m_cover_width: 144;
	property int m_cover_height: 200;
	property string m_background_color: "#1A1B21";
	property int m_background_radius: 5;
	property int m_first_title_font_size: 15;
	property int m_second_title_font_size: 12;
	property string m_first_title_font_color: "#fff";
	property string m_second_title_font_color: "#676D7A";
	property int m_spacing_cover_and_titles: 10;
	property int m_spacing_titles: 2;
	property int m_border_size: 2;
	property int m_max_length_first_title: 14;
	property int m_max_length_second_title: 14;
	property int m_left_padding_titles: 10;
	property string m_font_family: "Gilroy";
	property string m_color_hovered_shadow: "#000";
	property string m_color_unknown_cover: "#1B1D23";
	property string m_source_unknown_cover: "qrc:/Resources/Icons/cover_note.png"; 
	property string m_source_button_play: "qrc:/Resources/Icons/play-button.png"; 
	property string m_source_button_like: "qrc:/Resources/Icons/like.png";

	signal clickedPlayButton();
	signal clickedLikeButton();

	id: list;
    width: m_width;
	height: m_height;
	clip: true;
	spacing: m_spacing;
	orientation: ListView.Horizontal;

	model: m_model;

	delegate: Item
	{
		id: list_item;
		width: m_cover_width + m_border_size*2;
		height: m_border_size + cover.height + m_border_size + m_spacing_cover_and_titles + m_first_title_font_size + m_border_size + m_second_title_font_size + m_spacing_cover_and_titles;

	    opacity: 1;

	    function isDefualt(title)
		{
			if (title == "default")
			{
			 	opacity_mask.visible = false;
				mask_cover.visible = true;
				unknown_cover.visible = true;
			}
			else
			{
				opacity_mask.visible = true;
				mask_cover.visible = false;
				unknown_cover.visible = false;
			}
			return title;
		}

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

	    Column
	    {
	        spacing: m_spacing_cover_and_titles;

	        Item
	        {
	            width: list_item.width;
	            height: list_item.width;

	            Image
	            {
	                id: cover;
	                anchors.fill: parent;
	                source: "image://rootImageDirectory/x144/" + isDefualt(model.cover_key);
	                smooth: true;
	                visible: false;

	                anchors.left: parent.left
	                anchors.leftMargin: m_border_size;

	                anchors.top: parent.top
	                anchors.topMargin: m_border_size;

	                anchors.right: parent.right
	                anchors.rightMargin: m_border_size;

	                anchors.bottom: parent.bottom
	                anchors.bottomMargin: m_border_size;
	            }

	            Rectangle
	            {
	                id: background;
	                width: list_item.width;
	                height:  list_item.height;
	                radius: m_background_radius;
	                color: m_background_color;
	                opacity: 0;
	            }

	            DropShadow
	            {
	                id: background_shadow;
	                anchors.fill: background;
	                horizontalOffset: 0;
	                verticalOffset: 2;
	                radius: 12;
	                samples: 17;
	                spread: 0.0;
	                color: m_color_hovered_shadow;
	                source: background;
	                opacity: 0;
	            }    

	            Rectangle
	            {
	                id: mask_cover;
	                width: cover.width;
	                height:  cover.height;
	                radius: 3;
	                color: m_color_unknown_cover;
	                visible: false;
	            }

	            OpacityMask
	            {
	                id: opacity_mask;
	                anchors.fill: cover;
	                source: cover;
	                maskSource: mask_cover;
				}

				Image
	            {
	               	id: unknown_cover;
	                width: 64;
	                height: 64;
	                source: m_source_unknown_cover;
	                smooth: true;

	                anchors.verticalCenter: opacity_mask.verticalCenter;
	                anchors.horizontalCenter: opacity_mask.horizontalCenter;
	            }
								
				Image
		        {
		       		id: image_button_play;
		      		source: m_source_button_play;
		      		width: 40;
		      		height: 40;
		     		smooth: true;
		        	opacity: 0;

		     		anchors.verticalCenter:  cover.verticalCenter;
		         	anchors.horizontalCenter: cover.horizontalCenter;

		           	MouseArea
		            {
		                anchors.fill: parent;
		           		cursorShape: Qt.PointingHandCursor;

		             	onClicked:
		          		{
		              		list.clickedPlayButton();
		                }
					}
		    	}

		        Image
		        {
		            id: image_button_like;
		            source: m_source_button_like;
		            width: 16;
		            height: 16;
		            smooth: true;
		            opacity: 0;

					anchors.verticalCenter:  image_button_play.verticalCenter;
		            anchors.left:  image_button_play.right;
		            anchors.leftMargin: parent.width/4 - image_button_like.width;

		            MouseArea
		            {
		            	anchors.fill: parent;
		            	cursorShape: Qt.PointingHandCursor;

		            	onClicked:
		          		{
		              		list.clickedLikeButton();
		                }
		            }
		        }
	                                               	

			    PropertyAnimation
				{
					id: animation_opacity_image_buttons;
					targets: [ image_button_play, image_button_like, background, background_shadow];
					property: "opacity";
					duration: 200;
					easing.type: Easing.InOutQuad;
				}

	            UnblockedMouseArea
	            {
	                id: mouse_area;
	                anchors.fill: cover;

	                onEntered:
	                {
	                	animation_opacity_image_buttons.stop();
	                	animation_opacity_image_buttons.to = 1;
	                	animation_opacity_image_buttons.start();
	                }

	                onExited:
	                {
	                    animation_opacity_image_buttons.stop();
	                    animation_opacity_image_buttons.to = 0;
	                    animation_opacity_image_buttons.start();
	                }
	            }
	        }

	        Column
	        {
	            spacing: m_spacing_titles;

	            Label
	            {
	                id: first_title;
	                font.pixelSize: m_first_title_font_size;
	                font.family: m_font_family;
	                text: points(model.text_line_first, m_max_length_first_title);
	                color: m_first_title_font_color;
	                leftPadding: m_left_padding_titles;
	            }

	            Label
	            {
	                id: second_title;
	                font.pixelSize: m_second_title_font_size;
	                font.family: m_font_family;
	                text:  points(model.text_line_second, m_max_length_second_title);
	                color: m_second_title_font_color;
	                leftPadding: m_left_padding_titles;
	        	}
	    	}
	    }

	    PropertyAnimation
		{
		    id: animation_opacity;
		    targets: [ list_item, opacity_mask ];
		    to: 1;
		    property: "opacity";
		    duration: 200;
		    easing.type: Easing.InOutQuad;
		}

	    Component.onCompleted:
	    {
			opacity_mask.opacity = 0;
			animation_opacity.start();
        }
    }
}