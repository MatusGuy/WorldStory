#include "attributeeditor.h"

using namespace WS::Creator;

AttributeEditor::AttributeEditor(QWidget* parent): QtAbstractPropertyBrowser(parent) {
	setFactoryForManager(&propManager, &propEditFactory);
}

void AttributeEditor::loadElement(WS::Levels::ILevelElement* el) {
	clear(); // clear all properties, prepare for the new target element

	levelElement = el;

	if (el == nullptr) return;

	auto atts = levelElement->getAttributeNames();
	for (int i = 0; i < atts.length(); i++) {
		QString attName = atts[i];
		QVariant attVal = element()->getAttribute(attName);

		propManager.addProperty(attVal.typeId(), attName);
	}
}

QVariant AttributeEditor::attribute(const QtProperty* prop) {
	return element()->getAttribute(prop->propertyName());
}

void AttributeEditor::setAttribute(QtProperty* prop, const QString& value) {
	element()->setAttribute(prop->propertyName(), value);
}