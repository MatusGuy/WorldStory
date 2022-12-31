#ifndef ILEVELELEMENT_H
#define ILEVELELEMENT_H

#include <QStringList>
#include <QVariant>
#include <QPoint>
#include <QUrl>

namespace WS::Levels {
    class ILevelElement : public QObject {

        Q_OBJECT

        public:
            virtual const QString internalName() = 0;

            virtual void setAttribute(QString name, QString value) = 0;
            virtual QVariant getAttribute(QString name) = 0;

            inline void setAttributeFromVariant(QString name, QVariant value) {
                QString out = "";

                switch ((QMetaType::Type) value.typeId()) {

                case QMetaType::QPoint: {
                    QPoint point = value.toPoint();
                    QString format = "%1,%2";
                    out = format.arg(point.x()).arg(point.y());
                    break;
                }

                case QMetaType::QUrl:
                    out = value.toUrl().path();
                    break;

                default:
                    out = value.toString();
                    break;

                }

                setAttribute(name, out);
            };

            inline const QStringList& getAttributeNames() { return attributeNames; }

            signals: void attributeChanged(QString name, QVariant oldVal, QVariant newVal);

        protected:
            QStringList attributeNames;

            void setupAttributes(){}
    };
}

#endif // ILEVELELEMENT_H
