#ifndef ILEVELELEMENT_H
#define ILEVELELEMENT_H

#include <QObject>
#include <QStringList>
#include <QVariant>

namespace WS::Levels {

    class ILevelElement {

        public:
            virtual const QString internalName() = NULL;

            virtual void setAttribute(QString name, QString value) = NULL;
            virtual QVariant getAttribute(QString name) = NULL;

        protected:
            QStringList attributeNames;

            virtual void setupAttributes() = NULL;
    };

}

#endif // ILEVELELEMENT_H
