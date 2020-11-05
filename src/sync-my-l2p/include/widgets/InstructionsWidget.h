#ifndef SYNC_MY_L2P_INSTRUCTIONS_WIDGET_H_
#define SYNC_MY_L2P_INSTRUCTIONS_WIDGET_H_

#include <QWidget>
#include <QLabel>

class InstructionsWidget : public QWidget {
  Q_OBJECT
 private:
  QLabel *instructions_label_ = nullptr;

  void setupGui();

 public:
  explicit InstructionsWidget(QWidget *parent = nullptr);
};

#endif //SYNC_MY_L2P_INSTRUCTIONS_WIDGET_H_
