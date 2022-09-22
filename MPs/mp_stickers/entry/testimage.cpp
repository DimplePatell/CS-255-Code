#include "Image.h"
#include "StickerSheet.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.lighten(0.2);
  alma.writeToFile("../lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.saturate(0.2);
  alma.writeToFile("../saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(2);
  alma.writeToFile("../scale2x.png");

  ////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Using Image::alma to create `stickersheet.png`..." << std::endl;
  Image i;
  alma.readFromFile("../alma.png");
  i.readFromFile("../i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 50, 500);

  sheet.changeMaxStickers(7);
  sheet.removeSticker(1);
  sheet.changeMaxStickers(4);
  const Image &renderXBound = sheet.render();
  std::cout << "render_width(+800): " << renderXBound.width() << "   i_width: "<< i.width()<<std::endl;
  std::cout << "render_height: " << renderXBound.height() << "    alma_height: "<< alma.height()<<std::endl;

  return 0;
}
