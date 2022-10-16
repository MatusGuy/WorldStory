#include "viewport.h"

using WS::Creator::Viewport;

Viewport::Viewport(QWidget* parent): WS::Core::GameDisplay(parent) {
    setScene(&gridscene);
}
