#include "widgets/LoginWidget.h"

#include <QGridLayout>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) : QFrame(parent) {
  setupGui();
  setupConnections();
}

void LoginWidget::setupGui() {
  QString TEXT = "<html>"
                 "<body>"
                 "<p>This application uses the <a href=\"https://www.rwth-aachen.de/cms/root/Studium/Im-Studium/~ehw/Online-Dienste/lidx/1/\">RWTH Single Sign-On</a>. To log in, a user account must be available at the RWTH. Access to the L2P and Moodle is automatically granted after logging in.</p>"
                 "</body>"
                 "</html>";
  setAutoFillBackground(true);
  setAccessibleName("dialog-background");

  dialog_container_ = new QWidget(this);
  dialog_container_->setAutoFillBackground(true);
  dialog_container_->setAccessibleName("dialog-container");

  auto *login_label_ = new QLabel(dialog_container_);
  login_label_->setText("Login");
  login_label_->setAccessibleName("headline");

  auto *login_description_label_ = new QLabel(dialog_container_);
  login_description_label_->setText(TEXT);
  login_description_label_->setWordWrap(true);
  login_description_label_->setAccessibleName("description");
  login_description_label_->setFixedWidth(400);
  login_description_label_->setOpenExternalLinks(true);


  login_button_ = new QPushButton(dialog_container_);
  login_button_->setText("Login with RWTH-SSO");
  login_button_->setIcon(QIcon(":icons/login.png"));
  login_button_->setAccessibleName("login-button");

  remember_me_checkbox_ = new QCheckBox(dialog_container_);
  remember_me_checkbox_->setText("Remember me");

  auto dialog_layout = new QVBoxLayout(dialog_container_);
  //dialog_layout->addWidget(close_button_,1, Qt::AlignRight);
  dialog_layout->addWidget(login_label_, 3, Qt::AlignLeft);
  dialog_layout->addSpacerItem(new QSpacerItem(400,10,QSizePolicy::Minimum, QSizePolicy::Minimum));
  dialog_layout->addWidget(login_description_label_, 3, Qt::AlignLeft);
  dialog_layout->addSpacerItem(new QSpacerItem(400,20,QSizePolicy::Minimum, QSizePolicy::Minimum));
  dialog_layout->addWidget(login_button_,2, Qt::AlignCenter);
  dialog_layout->addWidget(remember_me_checkbox_, 2, Qt::AlignCenter);
  dialog_layout->addSpacerItem(new QSpacerItem(400,20,QSizePolicy::Minimum, QSizePolicy::Minimum));
  dialog_layout->setMargin(10);

  dialog_container_->setLayout(dialog_layout);
  dialog_container_->setMaximumSize(dialog_container_->sizeHint());


  auto *layout = new QVBoxLayout(this);
  auto *second_layout = new QHBoxLayout(this);
  layout->addLayout(second_layout);
  second_layout->addWidget(dialog_container_);

  setLayout(layout);
}

void LoginWidget::setupConnections() {
  connect(login_button_, &QPushButton::clicked, this, &LoginWidget::handleLoginPressed);
}

void LoginWidget::handleLoginPressed() {
  qInfo() << "User requested a login process.";
  this->hide();
}

