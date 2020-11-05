#include "widgets/BrowserTabBar.h"

#include <QDebug>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionTab>

BrowserTabBar::BrowserTabBar(QWidget *parent) : QTabBar(parent) {
  setShape(Shape::RoundedWest);
}

QSize BrowserTabBar::tabSizeHint(int index) const
{
  QSize size = QTabBar::size();
  QSize tab_size = QTabBar::tabSizeHint(index);
  tab_size.transpose();
  if(size.width() > tab_size.width()) tab_size.setWidth(size.width());
  return tab_size;
}

QSize BrowserTabBar::minimumSizeHint() const
{
  QSize min_size = QTabBar::minimumSize();
  QSize size = QTabBar::sizeHint();
  if(min_size.width() > size.width()){
    return min_size;
  }
  return size;
}

void BrowserTabBar::paintEvent(QPaintEvent *event)
{
  QStylePainter painter(this);
  QStyleOptionTab opt;

  for (int i = 0; i < this->count(); i++) {
    initStyleOption(&opt, i);
    painter.drawControl(QStyle::CE_TabBarTabShape, opt);
    painter.save();

    QSize s = opt.rect.size();
    s.transpose();
    QRect r(QPoint(), s);
    r.moveCenter(opt.rect.center());
    opt.rect = r;
    QPoint c = tabRect(i).center();
    painter.translate(c);
    painter.rotate(90);
    painter.translate(-c);
    painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
    painter.restore();
  }

  QWidget::paintEvent(event);
}
