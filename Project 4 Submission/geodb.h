//
//  geodb.hpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 7/3/2567 BE.
//

#ifndef GEODB_H
#define GEODB_H

#include <vector>
#include "base_classes.h"
#include "HashMap.h"


class GeoDatabase: public GeoDatabaseBase
{
public:
    
    GeoDatabase();
    virtual ~GeoDatabase();
    
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi,
                                  GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
    const;
    virtual std::string get_street_name(const GeoPoint& pt1,
                                        const GeoPoint& pt2) const;
private:

    // HashMap between POI name and its GeoPoint
    HashMap<GeoPoint> POI_map;
    
    // HashMap between GeoPoint (as a string) and a vector of connected GeoPoints
    HashMap<std::vector<GeoPoint>> Connected_Points_map;
    
    // HashMap between 2 GeoPoints (as a string) and a string representing the street name
    HashMap<std::string> Street_Name_map;
    
};

#endif // GEODB_H included
