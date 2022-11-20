#ifndef ILEVELELEMENT_H
#define ILEVELELEMENT_H

#include <QStringList>
#include <QVariant>

namespace WS::Levels {

    class ILevelElement {

        public:
            virtual const QString internalName() = NULL;

            virtual void setAttribute(QString name, QString value) = NULL;
            virtual QVariant getAttribute(QString name) = NULL;

            inline const QStringList& getAttributeNames() { return attributeNames; };

        protected:
            QStringList attributeNames;

            void setupAttributes(){};
    };

}

#endif // ILEVELELEMENT_H
