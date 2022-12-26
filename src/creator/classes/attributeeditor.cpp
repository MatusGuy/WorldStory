#include "attributeeditor.h"

using namespace WS::Creator;

AttributeEditor::AttributeEditor(QWidget* parent) : QtTreePropertyBrowser(parent) {
	propManager.setParent(this);
	propEditFactory.setParent(this);

	setAlternatingRowColors(false);
	setFactoryForManager<QtVariantPropertyManager>(&propManager, &propEditFactory);

	connect(&propManager, &VariantManager::valueChanged,
		[this](QtProperty* prop, const QVariant& val) {
			if (!element()->getAttributeNames().contains(prop->propertyName()))
				return;
			
			setAttribute(prop, val);
		}
	);
}

AttributeEditor::~AttributeEditor() {
	propManager.clear();
	clear();
}

void AttributeEditor::loadElement(WS::Levels::ILevelElement* el) {
	if (el == element()) return;

	// clear (and destroy) all properties, prepare for the new target element
	clear();
	propManager.clear();

	levelElement = el;

	if (el == nullptr) return;

	auto atts = levelElement->getAttributeNames();
	for (int i = 0; i < atts.length(); i++) {
		QString attName = atts[i];
		QVariant attVal = element()->getAttribute(attName);

		QtVariantProperty* prop = propManager.addProperty(attVal.typeId(), attName);
		prop->setValue(attVal);
		addProperty(prop);
	}
}

QVariant AttributeEditor::attribute(const QtProperty* prop) {
	return element()->getAttribute(prop->propertyName());
}

void AttributeEditor::setAttribute(QtProperty* prop, const QVariant& value) {
	element()->setAttribute(prop->propertyName(), value);
}