#include <string>
#include <iostream>
#include <math.h>

#include "Image.h"


void Image::lighten() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.l + .1) <= 1) {
                p1.l +=.1;
            } else {
                p1.l =1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.l + amount) <= 1) {
                p1.l += amount;
            } else {
                p1.l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.l) <= .1) {
                p1.l = 0;
            } else {
                p1.l -= .1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.l) <= .1) {
                p1.l = 0;
            } else {
                p1.l -= amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.s + .1) <= 1) {
                p1.s += .1;
            } else {
                p1.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.s + amount) <= 1) {
                p1.s += amount;
            } else {
                p1.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.s) <= .1) {
                p1.s = 0;
            } else {
                p1.s -= .1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if ((p1.s) <= .1) {
                p1.s = 0;
            } else {
                p1.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            p1.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if((p1.h + degrees) > 360) {
                p1.h = (p1.h + degrees) - 360;
            } else if ((p1.h + degrees) >= 0){
                p1.h += degrees;
            } else {
                double rotate_val = p1.h + degrees;
                p1.h  = 360 + rotate_val;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int i=0; i<height();++i) {
        for (unsigned int j=0; j<width(); ++j) {
            HSLAPixel & p1= getPixel(j, i);
            if(p1.h >= 216) {
                p1.h = 216;
            } else if(p1.h <= 11) {
                p1.h = 11;
            } else {
                double h_io_diff = p1.h - 11;
                double h_ib_diff = 216 - p1.h;
                if (h_ib_diff < h_io_diff) {
                    p1.h = 216;
                } else {
                    p1.h = 11;
                }
            }
        }
    }
}

void Image::scale(double factor) {
    if (factor == 1) {
        return;
    }
    Image copy = Image(*this);
    unsigned int nwidth = width()*factor;
    unsigned int nheight = height()*factor;
    resize(nwidth, nheight);

    for (unsigned int i = 0; i < nheight; ++i) {
        for (unsigned int j = 0; j < nwidth; ++j) {
            HSLAPixel & p1= getPixel(j, i);
            HSLAPixel & p2 = copy.getPixel(j/factor, i/factor);
            p1 = p2;
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double width_ratio = (1.0* w)/width();
    double height_ratio = (1.0*h)/height();
    double min_scale = std::min(width_ratio, height_ratio);
    scale(min_scale);
}