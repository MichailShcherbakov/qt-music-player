import QtQuick 2.4


Item
{
    property int mWidth: 150
    property int mHeight: 150
    property int mRadius: 10
    property int mBorderWidth: 2
    property int mBorderLenght: 8
    property string mColor: "transparent"
    property string mBorderColor: "black"
    property string mBorderDottedColor: "white"
    property int mBorderDottedSpacing: 9

    width: mWidth
    height: mHeight


    Rectangle
    {
        width: mWidth
        height: mHeight
        radius: mRadius
        color: mColor
        border.color: mBorderColor
        border.width: mBorderWidth

        Row
        {
            spacing: mBorderDottedSpacing

            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }
        }

        Column
        {
            spacing: mBorderDottedSpacing

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right


            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }
        }

        Row
        {
            spacing: mBorderDottedSpacing

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderLenght
                height: mBorderWidth
                color: mBorderDottedColor
            }
        }

        Column
        {
            spacing: mBorderDottedSpacing

            anchors.verticalCenter: parent.verticalCenter

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }

            Rectangle
            {
                width: mBorderWidth
                height: mBorderLenght
                color: mBorderDottedColor
            }
        }
    }

}



