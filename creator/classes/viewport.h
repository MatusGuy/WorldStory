#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <classes/gamedisplay.h>
#include <classes/gridscene.h>

namespace WS::Creator {

class Viewport : public WS::Core::GameDisplay {
    public:
        explicit Viewport(QWidget* parent = nullptr);

        WS::Graphics::GridScene gridscene;
};

}

#endif // VIEWPORT_H
