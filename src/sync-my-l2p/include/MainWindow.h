
#ifndef SYNC_MY_L2P_MAIN_WINDOW_H_
#define SYNC_MY_L2P_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QStackedWidget>

#include "widgets/BrowserTabWidget.h"
#include "widgets/InstructionsWidget.h"
#include "widgets/LoggingWidget.h"
#include "widgets/SettingsWidget.h"
#include "widgets/LoginWidget.h"

class MainWindow : public QMainWindow {
 Q_OBJECT
 private:
  BrowserTabWidget *browser_tab_widget_ = nullptr;
  InstructionsWidget *instructions_widget_ = nullptr;
  LoggingWidget *logging_widget_ = nullptr;
  SettingsWidget *settings_widget_ = nullptr;
  LoginWidget *login_widget_ = nullptr;
  QWidget *dialog_container_ = nullptr;

  void setupGui();
  void setupConnections();

  /**
   * @brief Will restore the window state from the last season.
   */
  void restoreWindowStates();

  /**
   * @brief Will store the window state from the current season.
   */
  void storeWindowState();

 protected:

  /**
   * @brief Will store the current window state to a file so it can be loaded
   * at the next start.
   * @param event Event with details about the circumstances of the close.
   */
  void closeEvent(QCloseEvent *event) override;

  void resizeEvent(QResizeEvent* event) override;

 public:
  explicit MainWindow(QWidget *parent = nullptr);

 signals:
  void redirectedMessage(QtMsgType type, const QString &context, const QString &msg);
};

#endif //SYNC_MY_L2P_MAIN_WINDOW_H_
