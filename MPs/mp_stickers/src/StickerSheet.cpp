#include "StickerSheet.h"
#include "Image.h"
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

void StickerSheet::Clean() {
    for (unsigned i = 0; i <max_stickers; ++i) {
        if (sticker_layers.at(i) != 0) {
            delete sticker_images.at(i);
            sticker_images.at(i) = NULL;
        }
    }
    sticker_images.clear();
    x_pos.clear();
    y_pos.clear();
    sticker_layers.clear();
    delete picture_;
    picture_ = NULL;
}

void StickerSheet::Copy(const StickerSheet & other) {
    max_stickers = other.max_stickers;
    sticker_count = other.sticker_count;
    for (unsigned i = 0; i < other.max_stickers; ++i) {
        if (other.sticker_layers.at(i) != 0) {
            sticker_images.push_back(new Image(*(other.sticker_images.at(i))));
            x_pos.push_back(other.x_pos.at(i));
            y_pos.push_back(other.y_pos.at(i));
            sticker_layers.push_back(other.sticker_layers.at(i));
        } else {
            x_pos.push_back(0);
            y_pos.push_back(0);
            sticker_images.push_back(NULL);
            sticker_layers.push_back(0);
        }
    }
    picture_ = new Image(*(other.picture_));
}

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_stickers = max;
    sticker_count = 0;
    for (unsigned i = 0; i < max; ++i) {
        sticker_images.push_back(NULL);
        x_pos.push_back(0);
        y_pos.push_back(0);
        sticker_layers.push_back(0);
    }
    picture_ = new Image();
    *picture_ = picture;
}

StickerSheet::~StickerSheet () {
    Clean();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    Copy(other);
}


const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        Clean();
        Copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max >= max_stickers) {
        for (unsigned i = 0; i < (max-max_stickers); ++i) {
            sticker_images.push_back(NULL);
            x_pos.push_back(0);
            y_pos.push_back(0);
            sticker_layers.push_back(0);
        }
    } else {
        for (unsigned j = 0; j < max; ++j) {
            if (j > (max-1)) {
                delete sticker_images.at(j);
                sticker_images.at(j) = NULL;
                x_pos.at(j) = 0;
                y_pos.at(j) = 0;
                sticker_layers.at(j) = 0;
            }
        }
    }
    max_stickers = max;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (sticker_count < max_stickers) {
        for (unsigned i = 0; i < max_stickers; ++i) {
            if (sticker_layers.at(i) == 0) {
                sticker_images.at(i) = new Image(sticker);
                x_pos.at(i) = x;
                y_pos.at(i) = y;
                sticker_layers.at(i) += 1;
                sticker_count++;
                return i;
            }
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index > sticker_images.size() || (sticker_layers.at(index) == 0)) {
        return false;
    }
    x_pos.at(index) = x;
    y_pos.at(index) = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < (sticker_layers.size())) {
        delete sticker_images.at(index);
        sticker_images.at(index) = NULL;
        x_pos.at(index) = 0;
        y_pos.at(index) = 0;
        sticker_layers.at(index) = 0;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >=max_stickers ||index > (sticker_layers.size()-1)) {
        return NULL;
    }
    return sticker_images.at(index);
}

Image StickerSheet::render() const {
    unsigned nwidth = picture_->width();
    unsigned nheight = picture_->height();

    for (unsigned i = 0; i < max_stickers; ++i) {
        if (sticker_layers.at(i) != 0) { // resize image for width and height
            nwidth = std::max(nwidth, x_pos.at(i) + sticker_images.at(i)->width());
            nheight = std::max(nheight, y_pos.at(i) + sticker_images.at(i)->height());
        }
    }
    Image *finalImage = new Image(*picture_);
    finalImage->resize(nwidth, nheight);
    // create new image with stickers

    for (unsigned j = 0; j < max_stickers; ++j) {
        if (sticker_layers.at(j) != 0) {
            Image sticker_to_add = *sticker_images.at(j);
            for (unsigned x = x_pos.at(j); x < (x_pos.at(j) + sticker_to_add.width()); ++x) {
                for (unsigned y = y_pos.at(j); y < (y_pos.at(j)+ sticker_to_add.height()); ++y) {
                    HSLAPixel & p1 = sticker_to_add.getPixel(x-x_pos.at(j), y-y_pos.at(j));
                    HSLAPixel & p2= finalImage->getPixel(x, y);
                    if (p1.a != 0) {
                        p2 = p1;
                    }
                }
            }
        }
    }
    
    Image output = *finalImage;
    delete finalImage;
    finalImage = NULL;
    return output;
}