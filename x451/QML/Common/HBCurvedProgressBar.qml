import QtQuick 2.7
import QtQuick.Controls 2.2

Item {
    id: idMainRec
    /*
     * These properties are used to change default width and height of progressbar
     */
    width: 800
    height: 94

    /*
     * This property is used to set the appropriate coordinates in PathInterpolator relative to actual width and height of progress bar.
     * This property sets the dimensions of the Component relative to the window size
     */
    property double widthFact: width / 800
    property double heightFact: height / 94

    /*
    * This property holds the current progress along the path.
    *facilitates to control and animate the progress on progressbar
    * The range of progress lies from 0 to 1.
    */
    property alias progress: idMotionPath.progress

    /*
     * This property is used to set the image of the curved progress bar
     */
    property alias progressBarImage: idProgressBar.source

    /*
     * This property is used to set the image of the pointer indicating progress on progress bar
     */
    property alias pointerImage: idPointer.source

    /* This image Component is used for progress bar image */
    Image {
        id: idProgressBar
        source: ""
        width: idMainRec.width
        height: idMainRec.height
    }

    /* This image Component is used for pointer image */
    Image {
        id: idPointer
        source: ""
        width: idMainRec.width * 0.08
        height: idMainRec.height * 0.6
        antialiasing: true

        //bind our attributes to follow the path as progress changes
        x: idMotionPath.x
        y: idMotionPath.y

        rotation: idMotionPath.angle
        transform: Translate {
            x: -idPointer.width / 2
            y: -idPointer.height / 2
        }
    }

    /*
     * PathInterpolator provides x, y, and angle information for a
     * particular progress along a path.
     * It specifies how to manually animate along a path
     * Typical usage of PathInterpolator is to set the progress (often via a NumberAnimation), and read the corresponding values
     * for x, y, and angle (often via bindings to these values).
     */
    PathInterpolator {
        id: idMotionPath
        objectName: "mProgress"

        /*
         * The absolute values are aligned to the widthFact(width/800) and heightFact(height/94)
         */
        path: Path {
            startX: (64 * idMainRec.widthFact)
            startY: (24 * idMainRec.heightFact)

            PathLine {
                x: (82 * idMainRec.widthFact)
                y: (51 * idMainRec.heightFact)
            }
            PathQuad {
                x: (116 * idMainRec.widthFact)
                y: (63 * idMainRec.heightFact)
                controlX: (90 * idMainRec.widthFact)
                controlY: (59 * idMainRec.heightFact)
            }
            PathLine {
                x: (682 * idMainRec.widthFact)
                y: (63 * idMainRec.heightFact)
            }
            PathQuad {
                x: (715 * idMainRec.widthFact)
                y: (51 * idMainRec.heightFact)
                controlX: (703 * idMainRec.widthFact)
                controlY: (59 * idMainRec.heightFact)
            }
            PathLine {
                x: (733 * idMainRec.widthFact)
                y: (24 * idMainRec.heightFact)
            }
        }
    }
}
