#ifndef ATTRIBUTEEDITOR_H
#define ATTRIBUTEEDITOR_H

#include <levelelement.h>

#include <variantmanager.h>

namespace WS::Creator {

class AttributeEditor : public QtAbstractPropertyBrowser {

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

        void loadElement(WS::Levels::ILevelElement* el);
        inline WS::Levels::ILevelElement* element() { return levelElement; }

        signals:
            void elementChanged();
    
    public:
        QVariant attribute(const QtProperty* prop);

        public slots:
            void setAttribute(QtProperty* prop, const QString& value);

    private:
        WS::Levels::ILevelElement* levelElement = nullptr;

        VariantManager propManager;
        QtVariantEditorFactory propEditFactory;

        virtual void itemInserted(QtBrowserItem* item, QtBrowserItem* afterItem) override;
        virtual void itemRemoved(QtBrowserItem* item) override;
        virtual void itemChanged(QtBrowserItem* item) override;
};

}

#endif // ATTRIBUTEEDITOR_H
