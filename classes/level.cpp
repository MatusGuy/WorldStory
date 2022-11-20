#include "level.h"

using WS::Levels::Level;

Level* WS::Levels::loadLevel(QFile* levelFile) {
    if (levelFile->isOpen()) {
        if (levelFile->openMode() == QFile::WriteOnly) {
            qWarning("Level file is open in WriteOnly mode");
            return nullptr;
        }
    } else levelFile->open(QFile::ReadOnly);

    xmlReader.setDevice(levelFile);

    if (xmlReader.readNextStartElement()) {
        if (xmlReader.name().toString() != "level") {
            xmlReader.raiseError("token missing: level");
            return nullptr;
        }

        Level* out = new Level();

        QStringList lvlAtts = QStringList() << "name";
        QStringList tileNames = QStringList() << "tile" << "tilefield";
        //QStringList tileAtts = QStringList() << "pos" << "img" << "size";


        for (const QXmlStreamAttribute& lvlAtt : xmlReader.attributes()) {
            switch (lvlAtts.indexOf(lvlAtt.name())) {
                case 0: // name
                    out->name = lvlAtt.value().toString();
                    break;

                default: break;
            }
        }

        while (xmlReader.readNextStartElement()) {
            QString name = xmlReader.name().toString();
            // TODO: Optimize
            switch (tileNames.indexOf(name)) {
                case -1: { // unknown
                    if (tileNames.indexOf(name) != -1) {
                        xmlReader.raiseError("unknown token: "+name);
                        delete out;
                        return nullptr;
                    }
                }

                case 0: { // tile
                    WS::Graphics::Tile* newTile = new WS::Graphics::Tile();

                    for (const QXmlStreamAttribute& lvlAtt : xmlReader.attributes()) {
                        /*
                        switch (tileAtts.indexOf(lvlAtt.name())) {
                            case 0: { // pos
                                QStringList pos = lvlAtt.value().toString().split(',');
                                newTile->setX(pos[0].toInt());
                                newTile->setY(pos[1].toInt());
                                newTile->initPos = newTile->pos().toPoint();
                                break;
                            }

                            case 1: // img
                                newTile->setPixmap(QPixmap(lvlAtt.value().toString()));
                                break;

                            default: break;
                        }
                        */

                        newTile->setAttribute(
                            lvlAtt.name().toString(),
                            lvlAtt.value().toString()
                        );
                    }

                    out->content.place(
                        newTile->gridPos.x(),
                        newTile->gridPos.y(),
                        newTile
                    );

                    // tile already added by constructor
                }

                /*
                case 1: { // tile field
                    WS::Graphics::TileField* newTile = new WS::Graphics::TileField(out);

                    for (const QXmlStreamAttribute& lvlAtt : xmlReader.attributes()) {
                        switch (tileAtts.indexOf(lvlAtt.name())) {
                            case 0: { // pos
                                QStringList pos = lvlAtt.value().toString().split(',');
                                newTile->setX(pos[0].toInt());
                                newTile->setY(pos[1].toInt());
                                newTile->initPos = newTile->pos().toPoint();
                                break;
                            }

                            case 1: // img
                                newTile->setPixmap(QPixmap(lvlAtt.value().toString()));
                                break;

                            case 2: { // size
                                QStringList size = lvlAtt.value().toString().split(',');
                                newTile->size.setWidth(size[0].toInt());
                                newTile->size.setHeight(size[1].toInt());
                                break;
                            }

                            default: break;
                        }
                    }

                    // tile already added by constructor
                }
                */
            }

            if (xmlReader.readNext() != QXmlStreamReader::EndElement)
                xmlReader.raiseError("probably forgot to close token");
        }

        levelFile->close();

        return out;
    } else {
        xmlReader.raiseError("no tokens found");
        return nullptr;
    }
}
