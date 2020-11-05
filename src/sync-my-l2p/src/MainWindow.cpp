#include "MainWindow.h"

#include <QSettings>
#include <QVBoxLayout>

void MainWindow::restoreWindowStates() {
  QSettings settings
      (QSettings::IniFormat, QSettings::UserScope, "Sync-My-L2p", "Window");
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("window_state").toByteArray());
}

void MainWindow::storeWindowState() {
  QSettings settings
      (QSettings::IniFormat, QSettings::UserScope, "Sync-My-L2p", "Window");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("window_state", saveState());
}

void MainWindow::closeEvent(QCloseEvent *event) {
  storeWindowState();
  QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);

  login_widget_->resize(event->size());
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setupGui();
  setupConnections();
}

void MainWindow::setupGui() {
  setMinimumSize(600,400);
  setWindowTitle( "Sync-My-L2p");
  setAcceptDrops(false);
  setAnimated(true);
  restoreWindowStates();

  dialog_container_ = new QWidget(this);
  auto *dialog_container_layout = new QVBoxLayout(this);
  dialog_container_layout->setContentsMargins(0,0,0,0);
  dialog_container_->setLayout(dialog_container_layout);

  browser_tab_widget_ = new BrowserTabWidget(dialog_container_);
  instructions_widget_ = new InstructionsWidget(browser_tab_widget_);
  logging_widget_ = new LoggingWidget(browser_tab_widget_);
  settings_widget_ = new SettingsWidget(browser_tab_widget_);

  dialog_container_layout->addWidget(browser_tab_widget_);
  login_widget_ = new LoginWidget(dialog_container_);
  login_widget_->show();
  login_widget_->setMinimumSize(size());

  browser_tab_widget_->addPermanentTab(tr("Settings"), QIcon(":icons/settings.png"), settings_widget_);
  browser_tab_widget_->addPermanentTab(tr("Instructions"), QIcon(":icons/tutorial.png"), instructions_widget_);
  browser_tab_widget_->addPermanentTab(tr("Logging"), QIcon(":icons/logs.png"), logging_widget_);
  setCentralWidget(dialog_container_);
}

void MainWindow::setupConnections() {
  connect(this, &MainWindow::redirectedMessage, logging_widget_, &LoggingWidget::handelRedirectedMessage);
}
