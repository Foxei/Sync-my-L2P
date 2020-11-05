#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QIcon>
#include <QDebug>

#include "widgets/BrowserTabWidget.h"
#include "widgets/BrowserTabBar.h"


BrowserTabWidget::BrowserTabWidget(QWidget *parent) : QWidget(parent) {
  setupGui();

  tab_bar_bottom_->addTab("");
  tab_bar_bottom_->setTabEnabled(0,false);

  tab_bar_top_->addTab("");
  tab_bar_top_->setTabEnabled(0,false);

  tab_bar_top_->addTab(QIcon(":icons/semester.png"),"Winter 15");
  tab_bar_top_->addTab(QIcon(":icons/semester.png"), "Summer 16");
}

void BrowserTabWidget::setupGui(){
  tab_bar_top_ = new BrowserTabBar(this);
  tab_bar_bottom_ = new BrowserTabBar(this);

  stacked_widget_central_ = new QStackedWidget(this);

  auto *widget_left = new QWidget(this);
  widget_left->setAccessibleName("alternative-background");
  widget_left->setAutoFillBackground(true);

  auto *layout_left = new QVBoxLayout;
  auto *layout = new QHBoxLayout;
  layout_left->setMargin(0);
  layout_left->setContentsMargins(0,0,0,0);

  layout->setMargin(0);
  layout->setContentsMargins(0,0,0,0);

  layout_left->addWidget(tab_bar_top_);
  layout_left->addStretch(1);
  layout_left->addWidget(tab_bar_bottom_);

  widget_left->setLayout(layout_left);
  layout->addWidget(widget_left);
  layout->addWidget(stacked_widget_central_);

  setLayout(layout);

  connect(tab_bar_top_, &QTabBar::currentChanged, this, &BrowserTabWidget::showFirstBarWidget);
  connect(tab_bar_bottom_, &QTabBar::currentChanged, this, &BrowserTabWidget::showSecondBarWidget);

}

void BrowserTabWidget::showFirstBarWidget(int index) {
  if(index == 0) return;
  tab_bar_bottom_->setCurrentIndex(0);

  switch(index) {}
}

void BrowserTabWidget::showSecondBarWidget(int index) {
  if(index == 0) return;
  tab_bar_top_->setCurrentIndex(0);

  QString tab_to_display = tab_bar_bottom_->tabText(index);
  if(QWidget* widget = bottom_tabs_[tab_to_display]){
    stacked_widget_central_->setCurrentWidget(widget);
  }
  qInfo() << "Selected tab changed to:" << tab_to_display;
}

void BrowserTabWidget::addPermanentTab(const QString name, const QIcon icon, QWidget *widget) {
  bottom_tabs_.insert(name, widget);
  int index = tab_bar_bottom_->addTab(icon, name);
  stacked_widget_central_->addWidget(widget);

  tab_bar_bottom_->setCurrentIndex(index);
}
