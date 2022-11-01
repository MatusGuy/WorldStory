#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <classes/gamedisplay.h>

//#include <classes/gridscene.h>
#include "editorscene.h"

namespace WS::Creator {

class Viewport : public WS::Core::GameDisplay {
    public:
        explicit Viewport(QWidget* parent = nullptr);

        WS::Creator::EditorScene editorScene;
};

}

#endif // VIEWPORT_H
