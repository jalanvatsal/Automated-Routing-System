//
//  router.hpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 10/3/2567 BE.
//

#ifndef router_h
#define router_h

#include "geodb.h"

class Router: public RouterBase
{
public:
    Router(const GeoDatabaseBase& geo_db);
    virtual ~Router();
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
                                        const GeoPoint& pt2) const;
private:
        
    // to access member functions of GeoDatabase
    const GeoDatabaseBase & m_database;
    
};

#endif // router.h is included
