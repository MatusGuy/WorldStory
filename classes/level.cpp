#include "level.h"

using WS::Levels::Level;

Level* WS::Levels::loadLevel(QFile* levelFile) {
    if (levelFile->isOpen()) {
        if (levelFile->openMode() == QFile::WriteOnly) {
            qWarning("Level file is open in WriteOnly mode");
            return nullptr;
        }
    } else levelFile->open(QFile::ReadOnly);

    QXmlStreamReader reader(levelFile);

    if (reader.readNextStartElement()) {
        if (reader.name().toString() != "level") {
            reader.raiseError("token missing: level");
            return nullptr;
        }

        Level* out = new Level();

        QStringList lvlAtts = QStringList() << "name";
        QStringList tileAtts = QStringList() << "pos" << "img";

        for (const QXmlStreamAttribute& lvlAtt : reader.attributes()) {
            switch (lvlAtts.indexOf(lvlAtt.name())) {
                case 0: // name
                    out->name = lvlAtt.value().toString();
                    break;

                default: break;
            }
        }

        while (reader.readNextStartElement()) {
            QString name = reader.name().toString();
            if (name != "tile") {
                reader.raiseError("unknown token: "+name);
                delete out;
                return nullptr;
            }

            WS::Graphics::Tile* newTile = new WS::Graphics::Tile(out);

            for (const QXmlStreamAttribute& lvlAtt : reader.attributes()) {
                switch (tileAtts.indexOf(lvlAtt.name())) {
                    case 0: { // pos
                        QStringList pos = lvlAtt.value().toString().split(',');
                        newTile->setX(pos[0].toInt());
                        newTile->setY(pos[1].toInt());
                        break;
                    }

                    case 1: // img
                        newTile->setPixmap(QPixmap(lvlAtt.value().toString()));
                        break;

                    default: break;
                }
            }

            // tile already added by constructor
        }

        return out;
    } else {
        reader.raiseError("no tokens found");
        return nullptr;
    }
}
