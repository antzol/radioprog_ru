#include "aspectratiowidget.h"

#include <QResizeEvent>

//---------------------------------------------------------------------------------------
AspectRatioWidget::AspectRatioWidget(QWidget *widget, float width, float height, QWidget *parent) :
    QWidget(parent), arWidth(width), arHeight(height)
{
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->setContentsMargins(0, 0, 0, 0);

    // добавляем сначала заполнитель, затем свой виджет, затем снова заполнитель
    layout->addItem(new QSpacerItem(0, 0));
    layout->addWidget(widget);
    layout->addItem(new QSpacerItem(0, 0));
}

//---------------------------------------------------------------------------------------
void AspectRatioWidget::resizeEvent(QResizeEvent *event)
{
    float thisAspectRatio = (float)event->size().width() / event->size().height();
    int widgetStretch, outerStretch;

    if (thisAspectRatio > (arWidth/arHeight)) // слишком широкий
    {
        layout->setDirection(QBoxLayout::LeftToRight);
        widgetStretch = height() * (arWidth/arHeight); // т.е. ширина виджета
        outerStretch = (width() - widgetStretch) / 2 + 0.5;
    }
    else // слишком высокий
    {
        layout->setDirection(QBoxLayout::TopToBottom);
        widgetStretch = width() * (arHeight/arWidth); // т.е. высота виджета
        outerStretch = (height() - widgetStretch) / 2 + 0.5;
    }

    layout->setStretch(0, outerStretch);
    layout->setStretch(1, widgetStretch);
    layout->setStretch(2, outerStretch);
}

//---------------------------------------------------------------------------------------
