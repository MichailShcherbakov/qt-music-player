import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0


Item
{
    id: root
    width: t1.width + spacing
    height: t1.height
    clip: true

    property alias text: t1.text
    property int spacing: 30
    property bool isRunning: true
    property int m_duration: 7000
    property string m_text: "4 Апреля - Всем напомнить (Песня дьявола)"

    Text
    {
        id: t1
        text: m_text

        NumberAnimation on x
        {
            id: anm
            running: isRunning;
            from: 0;
            to: -root.width;
            duration: m_duration;

            onRunningChanged:
            {
                if (anm.running)
                {
                    console.log("starting");
                }
                else
                {
                    console.log("finished");
                    timer.start();
                }
            }
        }

        Timer
        {
            id: timer
            interval: 800
            running: false

            property int iter: 0

            onTriggered: { ++iter; if (iter != 2) anm.restart(); }
        }

        Text
        {
            x: root.width
            text: t1.text
        }
    }
}
