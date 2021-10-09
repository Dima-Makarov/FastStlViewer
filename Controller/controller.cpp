
#include "controller.h"

Controller::Controller() : QWidget(nullptr),
                           model_(new Model()),
                           view_(new View(this, model_)) {
  connect(&view_->GetLoadFileButton(), &QPushButton::clicked, this, &::Controller::RequestFilepath);
  resize(1500, 700);
  repaint();
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
  view_->UpdateTriangles(model_->GetTriangles());
}

void Controller::mousePressEvent(QMouseEvent* e) {
  is_lkm_pressed = true;
}

void Controller::mouseMoveEvent(QMouseEvent* e) {
  if (is_lkm_pressed) {
    if(previous_x_position_ == 0 && previous_y_position_ == 0) {
      previous_x_position_ = e->x();
      previous_y_position_ = e->y();
    }
    view_->MouseMove(e->x() - previous_x_position_, e->y() - previous_y_position_);
    previous_x_position_ = e->x();
    previous_y_position_ = e->y();
    repaint();
  }
}

void Controller::mouseReleaseEvent(QMouseEvent* e) {
  is_lkm_pressed = false;
}
