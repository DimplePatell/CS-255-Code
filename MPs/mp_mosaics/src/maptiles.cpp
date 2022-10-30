/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> points;
     map<Point<3>, TileImage*> tempMap; 
     for (int x = 0; x < int(theTiles.size()); ++x) {
                LUVAPixel l1 = theTiles.at(x).getAverageColor();
                Point<3> p1 = convertToXYZ(l1);
                points.push_back(p1);
                tempMap[p1] = &theTiles.at(x);
    }
    KDTree<3> k1(points);
    MosaicCanvas* newMosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     for(int i = 0; i < newMosaic->getRows(); ++i) {
        for (int j = 0; j < newMosaic->getColumns(); ++j) {
            Point<3> temp = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> nearestNeighbor = k1.findNearestNeighbor(temp);
            TileImage* tImg = tempMap[nearestNeighbor];
            newMosaic->setTile(i, j, tImg);
        }
     }
    return newMosaic;
}

