#include "widgets/LoggingWidget.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextStream>
#include <QDateTime>

LoggingWidget::LoggingWidget(QWidget *parent) : QWidget(parent) {
  setupGui();
}

void LoggingWidget::setupGui() {
  logging_text_edit_ = new QTextEdit(this);
  logging_text_edit_->document()->setDocumentMargin(10);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(logging_text_edit_);
  layout->setContentsMargins(0,0,0,0);

  setLayout(layout);
}

void LoggingWidget::handelRedirectedMessage(QtMsgType type, const QString &context, const QString &msg) {
  if(!logging_text_edit_) return;

  // Open stream file writes
  QString full_message;
  QTextStream out(&full_message);
  // Write the date of recording
  out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
  // By type determine to what level belongs message
  switch (type)
  {
    case QtInfoMsg:     out << "[INFO] \t"; break;
    case QtDebugMsg:    out << "[DEBUG] \t"; break;
    case QtWarningMsg:  out << "[WARN] \t"; break;
    case QtCriticalMsg: out << "[CRIT] \t"; break;
    case QtFatalMsg:    out << "[FATAL] \t"; break;
  }
  // Write to the output category of the message and the message itself
  out << ": " << msg;
  out.flush();
  logging_text_edit_->append(full_message);
}