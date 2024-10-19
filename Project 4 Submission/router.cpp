//
//  router.cpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 10/3/2567 BE.
//

#include "router.h"
#include "geotools.h"
#include<queue>
#include<algorithm>

Router::Router(const GeoDatabaseBase& geo_db)
: m_database(geo_db)
{
}


Router::~Router(){
    // do nothing for now
}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1,
                                    const GeoPoint& pt2) const{
    
    // Queue for proccessing GeoPoints
    std::queue<GeoPoint> GeoPointQueue;
    
    // Maps a GeoPoint to where it came from (previous GeoPoint)
    HashMap<GeoPoint> locationOfPreviousWayPoint;
    
    std::vector<GeoPoint> path; // this represents the entire path from pt1 to pt2
    
    // push the starting GeoPoint into the queue
    GeoPointQueue.push(pt1);
    
    while(!GeoPointQueue.empty()){
        
        GeoPoint top = GeoPointQueue.front();
        if(!GeoPointQueue.empty()){
            GeoPointQueue.pop();
        }
        
        // we have reached the ending GeoPoint
        if(top.to_string() == pt2.to_string()){
            
            // Destination reached: Construct path and then return
            
            GeoPoint current = top;
            while(current.to_string() != pt1.to_string()){
                path.push_back(current);
                current = locationOfPreviousWayPoint[current.to_string()];
            }
            
            // add starting co-ord
            path.push_back(pt1);
            
            //reverse path vector for correct orientation
            reverse(path.begin(), path.end());
            return path;
        }
        
        // otherwise we want to look through the connected points of top and then rank them based on their distance to the ending geopoint
        
        std::vector <GeoPoint> connections = m_database.get_connected_points(top);
        
        
        // sort the connections vector by increasing distance to end point
        GeoPoint startPoint = pt1;
        GeoPoint endPoint = pt2;
        if(!connections.empty()){
            std::sort(connections.begin(), connections.end(), [startPoint, endPoint](const GeoPoint& a, const GeoPoint& b) {
                return distance_earth_miles(startPoint, a) + distance_earth_miles(a, endPoint) < distance_earth_miles(startPoint, b) + distance_earth_miles(b, endPoint);
            });
        }
        
        for(int k = 0; k < connections.size(); k++){
            // check that point is not in map before adding association
            if(locationOfPreviousWayPoint.find(connections[k].to_string()) == nullptr){
                GeoPointQueue.push(connections[k]);
                locationOfPreviousWayPoint[connections[k].to_string()] = top;
            }
        }
        
    }
    
    // Return an empty vector as no valid path was found
    return std::vector<GeoPoint>();
}
