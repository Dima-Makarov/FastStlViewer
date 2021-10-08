
#include "controller.h"

Controller::Controller() : QWidget(nullptr),
                           model_(new Model()),
                           view_(new View(model_)){
  resize(1500,700);
}

void Controller::keyPressEvent(QKeyEvent* event) {
  model_->HandleKeyPressEvent(event);
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  model_->HandleKeyReleaseEvent(event);
}

void Controller::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  view_->Update(&qp);
}

Controller::~Controller() {
  delete view_;
  delete model_;
}
