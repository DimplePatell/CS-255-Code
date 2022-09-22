#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png

  Image cloud; cloud.readFromFile("../cloud_base.png");
  Image bird1;    bird1.readFromFile("../bird1.png");
  Image bird2;    bird2.readFromFile("../bird2.png");
  Image bird3;    bird3.readFromFile("../bird3.png");

  StickerSheet sheet(cloud, 5);
  sheet.addSticker(bird1, 20, 100);
  sheet.addSticker(bird2, 275, 300);
  sheet.addSticker(bird3, 500, 50);

  Image myImage = (sheet.render());
  myImage.writeToFile("../myImage.png");

  return 0;
}
