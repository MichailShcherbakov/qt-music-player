import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import "../../Styles/ListsView"

import models.verticalModel1 1.0

Item
{
    id: center_field;
    anchors.fill: parent;

    Item
    {
        anchors.fill: parent;

        Ver1ListView
        {
            m_model: VerticalModel1
            {
                list: songsModelList;
            }
        }
    }

}