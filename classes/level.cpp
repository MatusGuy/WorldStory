#include "level.h"

using WS::Levels::Level;

Level WS::Levels::loadLevel(QFile* levelFile) {
    if (levelFile->isOpen()) {
        if (levelFile->openMode() == QFile::WriteOnly) {
            qWarning("Level file is open in WriteOnly mode");
            return Level();
        }
    } else levelFile->open(QFile::ReadOnly);

    QXmlStreamReader reader(levelFile);

    if (reader.readNextStartElement()) {
        if (reader.name().toString() != "level") {
            reader.raiseError("<level> token missing");
            return Level();
        }

        Level out;

        QStringList tokenNames;
        tokenNames << "name" << "content";

        while (reader.readNextStartElement()) {
            QString prop  = reader.name().toString();
            QString value = reader.text().toString();

            qDebug() << value;

            switch (tokenNames.indexOf(prop)) {
                case 0: // name
                    out.name = value;
                    break;

                case 1:  break; // content
                default: break;
            }
        }

        return out;
    } else {
        return Level();
    }
}
