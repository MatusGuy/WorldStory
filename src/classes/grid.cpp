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

void Grid::place(Tile* tile) {
    if (tile == nullptr) return;

    if (find(tile)) return;

    tile->world = this;
    QPoint pos = tile->gridPos;

    if (!content.contains(pos.x())) { // lol
        content[pos.x()] = QMap<int, Tile*>();
    }

    emit tileAdded(tile);
    content[pos.x()][pos.y()] = tile;
}

Tile* Grid::get(int x, int y) {
    if (!content.contains(x)) return nullptr;

    const QMap<int, Tile*>& column = content[x];
    if (!column.contains(y)) return nullptr;

    return column[y];
}

Tile* Grid::get(QPoint& pos) {
    return get(pos.x(), pos.y());
}

void Grid::remove(Tile* tile) {
    if (tile == nullptr) return;

    if (!content.contains(tile->gridPos.x())) return;
    content[tile->gridPos.x()].remove(tile->gridPos.y());
    tile->world = nullptr;

    emit tileRemoved(tile);
}

void Grid::move(Tile* tile, int x, int y) {
    if (tile == nullptr) return;

    if (!find(tile)) return;

    if ((tile->gridPos.x() == x) && (tile->gridPos.y() == y)) return;

    if (!content.contains(x)) {
        content[x] = QMap<int, Tile*>();
    }

    remove(get(x,y));
    content[x][y] = tile;
    tile->gridPos.setX(x);
    tile->gridPos.setY(y);

    emit tileMoved(tile);
}

void Grid::move(Tile* tile, QPoint& pos) {
    move(tile, pos.x(), pos.y());
}

bool Grid::find(Tile* tile) {
    if (tile == nullptr) return false;
    
    for (QMap<int, Tile*>& column : content) {
        for (Tile* t : column) {
            if (t == tile) return true;
        };
    }

    return false;
}

void Grid::sync(Tile* tile) {
    /*
    if (tile == nullptr) return;

    bool found = false;

    int x = 0, y = 0;

    QMap<int, QMap<int, Tile*>>::iterator ix;
    for (ix = content.begin(); ix != content.end(); ++ix) {
        x = ix.key();

        QMap<int, Tile*>::iterator iy;
        for (iy = content[x].begin(); iy != content[x].end(); ++iy) {

            y = iy.key();
            if (content[x][y] == tile) {
                found = true;
                if ((tile->gridPos.x() == x) && (tile->gridPos.y() == y)) return;
                break;
            };
        }

        if (found) break;
    }

    if (!found) return;

    content[tile->gridPos.x()].remove(tile->gridPos.y());
    content[x][y] = tile;
    */
    return move(tile, tile->gridPos);
}

QMap<int, Tile*> Grid::row(int pos) {
    QMap<int, Tile*> out;
    QMap<int, QMap<int, Tile*>>::iterator x;
    for (x = content.begin(); x != content.end(); x++) {
        out[x.key()] = x.value()[pos];
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

const QMap<int, QMap<int, Tile*>>& Grid::map() {
    return content;
}

