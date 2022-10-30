#include "grid.h"

using namespace WS::Graphics;

Grid::Grid(QObject *parent) : QObject{parent} {}

Grid::~Grid() {
    if (clearOnDestruction) {
        for (QMap<int, Tile*>& column : content) {
            for (Tile* tile : column) delete tile;
        }
    }
}

void Grid::place(int x, int y, Tile* tile) {
    if (!content.contains(x)) { // lol
        content[x] = QMap<int, Tile*>();
    }

    content[x][y] = tile;
}
Tile* Grid::get(int x, int y) {
    if (!content.contains(x)) return nullptr;

    const QMap<int, Tile*>& column = content[x];
    if (!column.contains(y)) return nullptr;

    return column[y];
}

QMap<int, Tile*> Grid::row(int pos) {
    QMap<int, Tile*> out;
    for (int x : content.keys()) {
        out[x] = content[x][pos];
    }
    return out;
}

QMap<int, Tile*>& Grid::column(int pos) {
    return content[pos];
}

QList<Tile*> Grid::capture(const QPoint& topLeft, const QPoint& bottomRight) {
    QList<Tile*> out;

    for (int x = topLeft.x(); x < bottomRight.x(); x++) {
        for (int y = topLeft.y(); y < bottomRight.y(); y++) {
            Tile* tile = get(x,y);
            if (tile != nullptr) out.append(tile);
        }
    }

    return out;
}

