#ifndef SYNC_MY_L2P_BROWSER_TAB_WIDGET_H_
#define SYNC_MY_L2P_BROWSER_TAB_WIDGET_H_

#include <QStackedWidget>
#include <QMap>

#include "BrowserTabBar.h"

class BrowserTabWidget : public QWidget {
Q_OBJECT
 private:
  BrowserTabBar *tab_bar_top_ = nullptr;
  BrowserTabBar *tab_bar_bottom_ = nullptr;

  QStackedWidget *stacked_widget_central_ = nullptr;

  QMap <QString, QWidget*> bottom_tabs_;
  QMap <QString, QWidget*> top_tabs_;

  QWidget *currently_displayed = nullptr;

  void setupGui();

 private slots:

  void showFirstBarWidget(int index);
  void showSecondBarWidget(int index);

 public:
  explicit BrowserTabWidget(QWidget *parent = nullptr);

  void addPermanentTab(const QString name, const QIcon icon, QWidget* widget);
};

#endif //SYNC_MY_L2P_BROWSER_TAB_WIDGET_H_
