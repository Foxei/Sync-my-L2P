/**
 * @author Simon Schaefer
 * @date 05.09.2019
 * @file main.cpp
 */
#define APPLICATION_NAME "SyncMyL2p"
#define MAJOR_VERSION 2
#define MINOR_VERSION 4
#define REVISION 1

#include <QApplication>
#include <QTranslator>
#include <QMessageLogger>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QDebug>
#include <QDateTime>
#include <QStyleFactory>

#include <memory>

#include "MainWindow.h"
#include "color_definitions.h"

MainWindow *main_window = nullptr;

struct MessageBuffer{
  QtMsgType type;
  QString context;
  QString msg;
};

std::vector<MessageBuffer> *message_buffer = nullptr;

void bufferMessage(QtMsgType type, const QString &context, const QString &msg){
  MessageBuffer buffer = {type, context, msg};
  message_buffer->push_back(buffer);
}

void clearMessageBuffer(){
  if(message_buffer->empty()) return;

  for(MessageBuffer &message : *message_buffer){
    main_window->redirectedMessage(message.type, message.context, message.msg);
  }
  message_buffer->clear();
}

void redirectToMain(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  if(main_window){
    clearMessageBuffer();
    main_window->redirectedMessage(type, QString(context.file), msg);
  }else{
    bufferMessage(type, context.file, msg);
  }
}

void redirectToConsole(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  const char *file = context.file ? context.file : "";
  switch (type) {
    case QtDebugMsg:
      fprintf(stderr, "Debug: %s (%s:%u)\n", localMsg.constData(), file, context.line);
      break;
    case QtInfoMsg:
      fprintf(stderr, "Info: %s (%s:%u)\n", localMsg.constData(), file, context.line);
      break;
    case QtWarningMsg:
      fprintf(stderr, "Warning: %s (%s:%u)\n", localMsg.constData(), file, context.line);
      break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s (%s:%u)\n", localMsg.constData(), file, context.line);
      break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s (%s:%u)\n", localMsg.constData(), file, context.line);
      break;
  }
}

/**
 * @brief Initiates background management.
 *
 */
void initiateDataManager() {
  QTranslator translator;
  if (translator.load(QLocale(), QLatin1String("sync-my-moodle"), QLatin1String("_"), QLatin1String(":/lang")))
    QApplication::installTranslator(&translator);
}

/**
 * @brief Load config files.
 *
 */
void loadConfigFiles() {}

/**
 * @brief Store config files.
 *
 */
void storeConfigFiles() {

}

/**
 * @brief Frees background management.
 */
void freeDataManager() {}

/**
 * @brief Setting style to dark theme and cross platform fonts
 * @param application Application were the style will be changed
 */
void setStyle(QApplication *application) {
  qInfo("Do app style processing");
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, Color::BACKGROUND);
  darkPalette.setColor(QPalette::WindowText, Color::BLACK);
  darkPalette.setColor(QPalette::Base, Color::BASE);
  darkPalette.setColor(QPalette::AlternateBase, Color::ALTERNATIVE_BASE);
  darkPalette.setColor(QPalette::ToolTipBase, Color::BASE);
  darkPalette.setColor(QPalette::ToolTipText, Color::BLACK);
  darkPalette.setColor(QPalette::Text, Color::BLACK);
  darkPalette.setColor(QPalette::Button, Color::BACKGROUND);
  darkPalette.setColor(QPalette::ButtonText, Color::BLACK);
  darkPalette.setColor(QPalette::BrightText, Color::WHITE);
  darkPalette.setColor(QPalette::Link, Color::BLUE);

  darkPalette.setColor(QPalette::Highlight, Color::BLUE);
  darkPalette.setColor(QPalette::HighlightedText, Color::CYAN);

  // Stylesheet
  qInfo("Loading Stylesheet: %s", "stylesheet.qss");
  QFile file_stylesheet(":stylesheet.qss");
  file_stylesheet.open(QFile::ReadOnly);
  QString stylesheet = QLatin1String(file_stylesheet.readAll());

  // Setup Fusion style
  qInfo("Loading Style: %s", "Fusion");
  QApplication::setPalette(darkPalette);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  application->setStyleSheet(stylesheet);

  qInfo("Setting font: %s", "WorkSans-Regular.ttf");
  QFileInfo file_font(":WorkSans-Regular.ttf");
  QFontDatabase::addApplicationFont(file_font.absoluteFilePath());

  QFileInfo file_icon(":icons/magnifier.png");
  QApplication::setWindowIcon(QIcon(file_icon.absoluteFilePath()));

  qInfo("Finished app style processing");
}

void loadLanguages(QApplication *application){
    // Sprache installieren
  QString locale = QLocale::system().name();
  qDebug() << "Language: " << locale;
  auto *translator = new QTranslator();
  if(!translator->load(":/lang/sync-my-l2p_" +locale)) {
     translator->load(":/lang/sync-my-l2p_en");
  }
  application->installTranslator(translator);
}

void redirectMessages(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  redirectToMain(type, context, msg);
  redirectToConsole(type, context, msg);
}

int main(int argc, char *argv[]) {
 // Create application and redirect logging.
  auto* application = new QApplication(argc, argv);
  message_buffer = new std::vector<MessageBuffer>;
  qInstallMessageHandler(redirectMessages);

  qInfo("Executing %s, version %i.%i.%i",
        APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);

  QApplication::setApplicationName(APPLICATION_NAME);
  QApplication::setApplicationVersion(
      QString(QString::number(MAJOR_VERSION) + "." + QString::number(MINOR_VERSION) + "." + QString::number(REVISION)));

  qInfo("Set application style");
  setStyle(application);
  qInfo("Load supported languages");
  loadLanguages(application);

  qInfo("Initiating background management");
  initiateDataManager();
  qInfo("Load config file");
  loadConfigFiles();

  main_window = new MainWindow();
  main_window->show();

  qInfo("Application running");
  int return_value = QApplication::exec();

  qInfo("Store config file");
  storeConfigFiles();
  qInfo("Free background management");
  freeDataManager();

  qInfo("Terminating %s", APPLICATION_NAME);
  return return_value;

}
