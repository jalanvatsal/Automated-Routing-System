//
//  tour_generator.cpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 12/3/2567 BE.
//

#include "tour_generator.h"

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
:m_db(geodb), m_router(router)
{
    
}

TourGenerator::~TourGenerator(){
    // do nothing as of now
}


std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const{
    
    // initialize empty result vector
    std::vector<TourCommand> result;
    
    // loop through each POI
    for(int k = 0; k < stops.size(); k++){
        
        // initialize a Commentary Tour Command
        TourCommand command1;
        
        std::string poi;
        std::string commentary;
        
        stops.get_poi_data(k, poi, commentary);

        command1.init_commentary(poi, commentary);
        
        // add to end of result vector
        result.push_back(command1);
                
        
        // check if there is a poi following the current one
        if(k + 1 < stops.size()){
            
            // generate a route between the two points
            
            // convert poi into geopoint
            GeoPoint point1;
            m_db.get_poi_location(poi, point1);
        
            
            // get adjacent poi
            std::string poi2;
            std::string commentary2;
            stops.get_poi_data(k+1, poi2, commentary2);
            
            
            // convert second poi into geopoint
            GeoPoint point2;
            m_db.get_poi_location(poi2, point2);
            
            std::vector<GeoPoint> route = m_router.route(point1, point2);
            
            for(int j = 0; j < route.size(); j++){
                // check if adjacent geopoint exists
                if(j + 1 < route.size()){
                    
                    TourCommand proceed;
                    
                    double angle = angle_of_line(route[j], route[j+1]);
                    std::string dir;
                    if(0 <= angle && angle < 22.5){
                        dir = "east";
                    } else if(22.5 <= angle && angle < 67.5){
                        dir = "northeast";
                    } else if(67.5 <= angle && angle < 112.5){
                        dir = "north";
                    } else if(112.5 <= angle && angle < 157.5){
                        dir = "northwest";
                    } else if(157.5 <= angle && angle < 202.5){
                        dir = "west";
                    } else if(202.5 <= angle && angle < 247.5){
                        dir = "southwest";
                    } else if(247.5 <= angle && angle < 292.5){
                        dir = "south";
                    } else if(292.5 <= angle && angle < 337.5){
                        dir = "southeast";
                    } else if(angle >= 337.5){
                        dir = "east";
                    }
                    
                    std::string street_name = m_db.get_street_name(route[j], route[j+1]);
                    
                    double distance = distance_earth_miles(route[j], route[j+1]);
                    
                    // initialize a proceed command
                    proceed.init_proceed(dir, street_name, distance, route[j], route[j+1]);
                    // add to vector
                    result.push_back(proceed);
                    
                    
                    // handle turn command
                    bool turn_condition1 = false;
                    bool turn_condition2 = false;
                    bool turn_condition3 = false;
                    
                    if(j + 2 < route.size()){
                        turn_condition1 = true;
                    }
                    
                    std::string street_name2 = m_db.get_street_name(route[j+1], route[j+2]);
                    
                    if(turn_condition1 && street_name != street_name2){
                        turn_condition2 = true;
                    }
                    
                    double turn_angle = angle_of_turn(route[j], route[j+1], route[j+2]);
                    
                    if(turn_condition1 && turn_angle != 0){
                        turn_condition3 = true;
                    }
                    
                    if(turn_condition1 && turn_condition2 && turn_condition3){
                        TourCommand turn;
                        
                        if(turn_angle >= 1 && turn_angle < 180){
                            turn.init_turn("left", street_name2);
                        } else if(turn_angle >= 180 && turn_angle <= 359){
                            turn.init_turn("right", street_name2);
                        }
                        
                        //push back on vector
                        result.push_back(turn);
                        

                    }
                    
                    
                }
            }
            
        }
        
        
        
    }
    
    return result;
}

