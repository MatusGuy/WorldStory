#ifndef WRITER_H
#define WRITER_H

#include <QXmlStreamWriter>

#include <level.h>
#include <tile.h>

namespace WS::Creator {

includeglobal QXmlStreamWriter xmlWriter;

inline void writeLevel(QFile* levelFile, WS::Levels::Level* lvl) {
    using WS::Graphics::Tile;

    if (levelFile->isOpen()) {
        if (levelFile->openMode() == QFile::ReadOnly) {
            qCritical() << "passed file is write-only";
            return;
        }
    } else if (!levelFile->exists()) {
        qCritical() << "passed file doesn't exist";
        return;
    } else levelFile->open(QFile::WriteOnly);

    xmlWriter.setDevice(levelFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("level");
    xmlWriter.writeAttribute("name", lvl->name);
    for (QMap<int, Tile*> column : lvl->content.map()) {
        for (Tile* tile : column) {
            xmlWriter.writeEmptyElement(tile->internalName());
            for (QString attribute : tile->getAttributeNames()) {
                xmlWriter.writeAttribute(
                    attribute,
                    WS::Levels::getReadableFormat(tile->getAttribute(attribute))
                );
            }
        }
    }
    xmlWriter.writeEndElement(); // level

    xmlWriter.writeEndDocument();

    levelFile->close();
}

}

#endif // WRITER_H
