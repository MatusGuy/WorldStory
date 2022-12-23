#ifndef ILEVELELEMENT_H
#define ILEVELELEMENT_H

#include <QStringList>
#include <QVariant>

namespace WS::Levels {
    class ILevelElement {

        public:
            virtual const QString internalName() = 0;

            virtual void setAttribute(QString name, QString value) = 0;
            virtual QVariant getAttribute(QString name) = 0;

            inline const QStringList& getAttributeNames() { return attributeNames; }

        protected:
            QStringList attributeNames;

            void setupAttributes(){}
    };

    typedef QPair<QString, QVariant> Attribute;
}

#endif // ILEVELELEMENT_H
