#ifndef SYNC_MY_L2P_LOGIN_WIDGET_H_
#define SYNC_MY_L2P_LOGIN_WIDGET_H_

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

class LoginWidget : public QFrame {
 Q_OBJECT
 private:

  QWidget *dialog_container_ = nullptr;
  QPushButton *login_button_ = nullptr;
  QPushButton *close_button_ = nullptr;
  QCheckBox *remember_me_checkbox_ = nullptr;

  void setupGui();
  void setupConnections();

 private slots:
  void handleLoginPressed();

 public:
  explicit LoginWidget(QWidget *parent = nullptr);

};

#endif //SYNC_MY_L2P_LOGIN_WIDGET_H_
