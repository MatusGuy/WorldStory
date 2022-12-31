#ifndef ATTRIBUTEEDITOR_H
#define ATTRIBUTEEDITOR_H

#include <levelelement.h>

#include <variantmanager.h>
#include <variantfactory.h>
#include <QtTreePropertyBrowser>

namespace WS::Creator {

class AttributeEditor : public QtTreePropertyBrowser {

    Q_OBJECT

    Q_PROPERTY(
        WS::Levels::ILevelElement* levelElement
        READ element
        WRITE loadElement
        MEMBER levelElement
        NOTIFY elementChanged
    )

    public:
        AttributeEditor(QWidget* parent = nullptr);
        ~AttributeEditor();

        void loadElement(WS::Levels::ILevelElement* el);
        void updateProperties();
        inline WS::Levels::ILevelElement* element() { return levelElement; }

        signals:
            void elementChanged();
    
    public:
        QVariant attribute(const QtProperty* prop);

        public slots:
            void setAttribute(QtProperty* prop, const QVariant& value);

    private:
        WS::Levels::ILevelElement* levelElement = nullptr;

        VariantManager propManager;
        VariantFactory propEditFactory;
};

}

#endif // ATTRIBUTEEDITOR_H
