#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <classes/gridscene.h>

#include "cursor.h"

namespace WS::Creator {

class EditorScene : public WS::Graphics::GridScene {
    public:
        explicit EditorScene(QObject *parent = nullptr);

        Cursor cursor;

    protected:
        void keyPressEvent(QKeyEvent* event) {Q_UNUSED(event)}

        protected slots:
            void draw();

};

}

#endif // EDITORSCENE_H
