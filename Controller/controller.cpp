
#include "controller.h"

Controller::Controller() : QWidget(nullptr),
                           model_(new Model()),
                           view_(new View(this, model_)){
  connect(&view_->GetLoadFile(), &QPushButton::clicked, this, &::Controller::RequestFilepath);
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

void Controller::RequestFilepath() {
  model_->LoadModel(QFileDialog::getOpenFileName(this));
}
