/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Image.h"

using namespace std;

class StickerSheet {
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render() const;

    private:
        Image *picture_;
        vector<Image*> sticker_images;
        vector<unsigned> x_pos;
        vector<unsigned> y_pos;
        vector<unsigned> sticker_layers;
        void Clean();
        void Copy(const StickerSheet & other);
        unsigned max_stickers;
        unsigned sticker_count;
    };