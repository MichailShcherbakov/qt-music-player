import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

ListView
{
    property ListModel m_model: ListModel {}
    property int m_width: 100;
    property int m_countItems: 4;


    id: browseMusicList
    width: m_width;
    height: 32 * m_countItems + 10 * (m_countItems - 1);
    spacing: 10;
    interactive: false

    model: m_model;

    delegate: Item
    {
        id: itemMenu
        width: parent.width;
        height: 32;

        Rectangle
        {
            id: rectItem
            width: 3;
            height: 32;
            color: "#2ED297";
            visible: false;
        }

        DropShadow
        {
            id: shadow
            anchors.fill: rectItem
            horizontalOffset: 0
            verticalOffset: 0
            radius: 10.0
            samples: 17
            color: "#5CFFC3"
            source: rectItem
            opacity: 0;
        }

        Image
        {
            id: imageItem;
            source: model.img;
            width: 20;
            height: 20;
            sourceSize.width: 20;
            sourceSize.height: 20;
            opacity: 1;
            smooth: true;

            anchors.left: rectItem.right;
            anchors.leftMargin: 20;
            anchors.verticalCenter: parent.verticalCenter;
        }

        Image
        {
            id: imageItemHovered;
            source: model.img_hovered;
            sourceSize.width: 20;
            sourceSize.height: 20;
            opacity: 0;
            smooth: true;

            anchors.fill: imageItem;
        }

        Label
        {
            id: textItem
            text: model.text;
            color: colorItems;
            font.family: "Gilroy";
            font.pixelSize: 14;
            opacity: 1;

            anchors.left: imageItem.right;
            anchors.leftMargin: 20;
            anchors.verticalCenter: parent.verticalCenter;
        }

        Label
        {
            id: textItemHovered
            text: model.text;
            color: colorHoveredItems;
            font.family: "Gilroy";
            font.pixelSize: 14;
            opacity: 0;

            anchors.fill: textItem;
        }

        MouseArea
        {
            anchors.fill: itemMenu;
            hoverEnabled: true;
            property bool local_state: false

            onHoveredChanged:
            {

                animation_shadow.stop();
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
                animation_item_hovered.start();
            }

            onClicked:
            {
                console.log("clicked");
            }
        }

         PropertyAnimation
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
        }
    }
}
