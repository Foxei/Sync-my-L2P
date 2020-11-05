#ifndef SYNC_MY_L2P_BROWSER_TAB_BAR_H_
#define SYNC_MY_L2P_BROWSER_TAB_BAR_H_

#include <QTabBar>

class BrowserTabBar : public QTabBar {
  Q_OBJECT
 protected:

  QSize minimumSizeHint() const override;

  void paintEvent(QPaintEvent *event) override;

 public:
  explicit BrowserTabBar(QWidget *parent = nullptr);

  QSize tabSizeHint(int index) const override;

};

#endif //SYNC_MY_L2P_BROWSER_TAB_BAR_H_
