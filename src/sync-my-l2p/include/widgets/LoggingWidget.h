#ifndef SYNC_MY_L2P_LOGGING_WIDGET_H_
#define SYNC_MY_L2P_LOGGING_WIDGET_H_

#include <QWidget>
#include <QPlainTextEdit>

class LoggingWidget : public QWidget {
 Q_OBJECT
 private:
  QTextEdit *logging_text_edit_ = nullptr;

  void setupGui();

 public:
  explicit LoggingWidget(QWidget *parent = nullptr);

 public slots:
  void handelRedirectedMessage(QtMsgType type, const QString &context, const QString &msg);
};

#endif //SYNC_MY_L2P_LOGGING_WIDGET_H_
