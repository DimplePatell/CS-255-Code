#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  current_ = Point(-1, -1);
  visited.push_back(1);

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  std::cout<< "++" << std::endl;
  if(!traversal_ -> empty()){
    current_ = traversal_ -> pop();
    unsigned currx = current_.x;
    unsigned curry = current_.y;

    visited.at(currx+curry*png_ -> width()) = true;
    unsigned tempx = current_.x;
    unsigned tempy = current_.y;
    HSLAPixel & p2 = png_ -> getPixel(start_.x, start_.y);
    if(tempx + 1 < png_ -> width()){
      HSLAPixel & p1 = png_ -> getPixel(tempx + 1, tempy);
      if(calculateDelta(p1, p2) < tolerance_){
        traversal_ -> add(Point(tempx + 1, tempy));
      }
    }
    if(int(tempy) - 1 >= 0){
      HSLAPixel & p3 = png_ -> getPixel(tempx, tempy - 1);
      if(calculateDelta(p3, p2) < tolerance_){
        traversal_ -> add(Point(tempx, tempy - 1));
      }
    }
    if(int(tempx) - 1 >= 0){
      HSLAPixel & p4 = png_ -> getPixel(tempx - 1, tempy);
      if(calculateDelta(p4, p2) < tolerance_){
        traversal_ -> add(Point(tempx - 1, tempy));
      }
    }
    if(tempy + 1 < png_ -> height()){
      HSLAPixel & p5 = png_ -> getPixel(tempx, tempy + 1);
      if(calculateDelta(p5, p2) < tolerance_){
        traversal_ -> add(Point(tempx, tempy + 1));
      }
    }
    current_ = traversal_ -> peek();
    currx = current_.x;
    curry = current_.y;
    while(visited.at(currx+curry*png_ -> width())== true){
      traversal_ -> pop();
      current_ = traversal_ -> peek();
      currx = current_.x;
      curry = current_.y;
      if(int(currx) == -1 && int(curry) == -1){
        this -> current_ = Point(-1,-1);
        traversal_ -> pop();
        return * this;
      }
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start, PNG & png, double tolerance): traversal_(&traversal), start_(start), png_(&png) {
  current_ = traversal.peek();
  tolerance_ = tolerance;
  for (unsigned i = 0; i < (png_->width() * png_->height()); i++) {
    visited.push_back(0);
  }
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(current_ == other.current_);
}

