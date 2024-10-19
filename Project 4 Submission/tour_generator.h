//
//  tour_generator.hpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 12/3/2567 BE.
//

#ifndef tour_generator_h
#define tour_generator_h

#include "geodb.h"
#include "router.h"
#include "tourcmd.h"
#include "stops.h"
#include "geotools.h"

class TourGenerator: public TourGeneratorBase
{
public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
    virtual ~TourGenerator();
    virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const GeoDatabaseBase &m_db;
    const RouterBase &m_router;
    
};

#endif // tour_generator_h included
