/*
 *  This is a Browse Loading Animation Component, whenever loading is required to before showing
 *  Browse button, this Component can be used.
 */

import QtQuick 2.2
import QtGraphicalEffects 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idBrowseLoadingComponent

    width: 76
    height: 76

    /* Browse Loading animation */
    AnimatedImage
    {
        id: idAnimatedImage

        source: enabled
                ? "qrc:/image/BrowseButtonAnimation/Browse_Loading_PNG_Sequence_72x72_X0_n.gif"
                : "qrc:/image/BrowseButtonAnimation/Browse_Loading_PNG_Sequence_72x72_X0_nd.gif"
    }


}
