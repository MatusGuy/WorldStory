#ifndef SCENEGRIDOVERLAY_H
#define SCENEGRIDOVERLAY_H

#include <QGraphicsItem>
#include <QPainter>

#include "editorscene.h"

namespace WS::Creator {

class SceneGridOverlay: public QGraphicsItem {
	public:
		SceneGridOverlay(EditorScene* e);

		EditorScene* editor;

		// Inherited via QGraphicsItem
		virtual QRectF boundingRect() const override;
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	private:
		QPen gridPen;
};

}

#endif // SCENEGRIDOVERLAY_H