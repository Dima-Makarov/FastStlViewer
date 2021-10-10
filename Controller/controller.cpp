
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
  if(e->button() == Qt::MouseButton::LeftButton) {
    is_lmb_pressed = true;
    lmb_prev_position_ = {e->x(), e->y()};
  }
  if(e->button() == Qt::MouseButton::RightButton) {
    is_rmb_pressed = true;
    rmb_prev_position_ = {e->x(), e->y()};
  }
}

void Controller::mouseMoveEvent(QMouseEvent* e) {
  if (is_lmb_pressed) {
    view_->MouseRotate(e->x() - lmb_prev_position_.first, e->y() - lmb_prev_position_.second);
    lmb_prev_position_ = {e->x(), e->y()};
    repaint();
  }
  if (is_rmb_pressed) {
    view_->MousePan(e->x() - rmb_prev_position_.first, e->y() - rmb_prev_position_.second);
    rmb_prev_position_ = {e->x(), e->y()};
    repaint();
  }
}

void Controller::mouseReleaseEvent(QMouseEvent* e) {
  if(e->button() == Qt::MouseButton::LeftButton) {
    is_lmb_pressed = false;
  }
  if(e->button() == Qt::MouseButton::RightButton) {
    is_rmb_pressed = false;
  }
}

void Controller::wheelEvent(QWheelEvent* e) {
  view_->MouseScale(static_cast<double>(e->angleDelta().y()) / 20);
  repaint();
}
