#pragma once

#include <QtWidgets>
#include <vector>


using VectorQRgb = std::vector<QRgb>;

struct ImageParameters {
  double zoom_in_factor_;
  double zoom_out_factor_;
  double pan_percent_;

  double xc_;
  double yc_;
  double zoom_;

  bool mandelbrot_not_julia_;

  int width_;
  int height_;
  VectorQRgb colors_;
  int nb_threads_;

  ImageParameters() {
    //
    // prepare the color indexes based on pdf data
    //

    std::vector<double> xs{      0.,   0.16,   0.42,   0.6425,  0.8575};
    std::vector<double> yreds{   0.,  32.  , 237.  , 215.    ,  0.    };
    std::vector<double> ygreens{  7., 107.  , 255.  , 170.    , 10.    };
    std::vector<double> yblues{ 100., 183.  , 235.  ,  40.    , 15.    };

    // some student code here

    // default size for the image
    width_ = 600;
    height_ = 400;

    mandelbrot_not_julia_ = true;

    // image parameter
    xc_ = -0.5;
    yc_ =  0.0;
    zoom_ = 1.0;

    // zoom image parameter
    // xc_  =  -1.76857365629925778;
    // yc_  =  -0.000964296850972570525;
    // zoom_  = 0.0002;

    zoom_in_factor_ = 0.8;
    zoom_out_factor_ = 1. / zoom_in_factor_;
    pan_percent_ = .10;
    nb_threads_ = 1;
  }
  ~ImageParameters() = default;

  void zoom_in() {
    zoom_ *= zoom_in_factor_;
  }

  void zoom_out() {
    zoom_ *= zoom_out_factor_;
  }
  void pan_left() {
    pan(-pan_percent_, 0.);
  }
  void pan_right() {
    pan(pan_percent_, 0.);
  }
  void pan_up() {
    pan(0., pan_percent_);
  }

  void pan_down() {
    pan(0., -pan_percent_);
  }

  void toggle_curve() {
    mandelbrot_not_julia_ = !mandelbrot_not_julia_;
  }

  void pan(const double h_percent, const double v_percent) {
    qDebug() << "Not implemented";
  }

};
