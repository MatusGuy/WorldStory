#ifndef SCENEGRIDOVERLAY_H
#define SCENEGRIDOVERLAY_H

#include <QGraphicsRectItem>
#include <QPainter>

#include "editorscene.h"

namespace WS::Creator {

class SceneGridOverlay: public QGraphicsRectItem {
	public:
		SceneGridOverlay(EditorScene* e);

		EditorScene* editor;

		// Inherited via QGraphicsItem
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	private:
		QPen gridPen;
};

}

#endif // SCENEGRIDOVERLAY_H
