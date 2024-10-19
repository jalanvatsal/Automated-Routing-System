//
//  geodb.cpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 7/3/2567 BE.
//



#include "geodb.h"
#include "geotools.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GeoDatabase::GeoDatabase(){
    // do nothing special for initialization
}

GeoDatabase::~GeoDatabase(){
    // do nothing
}

bool GeoDatabase::load(const std::string& map_data_file){
    
    // we will read in the data from mapdata.txt
    ifstream infile(map_data_file);
    if (!infile)                // Did opening/finding the file fail?
    {
        return false;
    }
    
    
    std::string s;
    // getline returns infile; the while tests its success/failure state
    while (getline(infile, s))
    {
        // read in first line (street name) of data block
        string streetName = s;
        
        // read in second line (starting and ending GeoPoints) of data block
        getline(infile, s);
        istringstream iss2(s);
        
        string geopoint1_start_str, geopoint1_end_str, geopoint2_start_str, geopoint2_end_str;
        
        if(!(iss2 >> geopoint1_start_str >> geopoint1_end_str >> geopoint2_start_str >> geopoint2_end_str)){
            return false;
        }
        
        GeoPoint start(geopoint1_start_str,geopoint1_end_str);
        GeoPoint end(geopoint2_start_str,geopoint2_end_str);
        
        
        // read in third line (#POI) of data block
        getline(infile, s);
        istringstream iss3(s);
        double num_poi;
        if(!(iss3 >> num_poi)){
            return false;
        }
        
        if(num_poi == 0){
            
            // NO POINTS OF INTEREST, so then update internal data structures and continue the loop
            
            // Update Street Name HashMap
            Street_Name_map[start.to_string() + end.to_string()] = streetName; // to ensure order of GeoPoints passed in doesn't make a difference
            Street_Name_map[end.to_string() + start.to_string()] = streetName;
            
            //Update Connected Points HashMap
            Connected_Points_map[start.to_string()].push_back(end);
            Connected_Points_map[end.to_string()].push_back(start);
            
            continue;
            
        } else {
    
            GeoPoint mid = midpoint(start, end);
            
            // establish connectedness both ways from start
            Connected_Points_map[start.to_string()].push_back(mid);
            Connected_Points_map[mid.to_string()].push_back(start);
            Street_Name_map[start.to_string() + mid.to_string()] = streetName;
            Street_Name_map[mid.to_string() + start.to_string()] = streetName;
            
            // establish connectedness both ways from end
            Connected_Points_map[end.to_string()].push_back(mid);
            Connected_Points_map[mid.to_string()].push_back(end);
            Street_Name_map[end.to_string() + mid.to_string()] = streetName;
            Street_Name_map[mid.to_string() + end.to_string()] = streetName;
            
            // loop through and handle POI data
            for(int i = 0; i < num_poi; i++){
                
                getline(infile, s);
                istringstream poi(s);
                
                string poi_name;
                string poi_location;
                
                int k = 0;
                while(s.at(k) != '|'){
                    poi_name += s.at(k);
                    k++;
                }
                
                k++; // so we are at position right after '|' char
                while(k < s.size()){
                    poi_location += s.at(k);
                    k++;
                }
                // poi_location is in this format now: 34.8765432 -118.9875554
                
                string lat;
                string lon;
                int q = 0;
                while(poi_location.at(q) != ' '){
                    lat += poi_location.at(q);
                    q++;
                }
                
                q++; // so we are at position right after ' ' char
                while(q < poi_location.size()){
                    lon += poi_location.at(q);
                    q++;
                }
                
                // update POI map
                GeoPoint POI_loc(lat, lon);
                POI_map[poi_name] = POI_loc;
                
                // establish connectedness both ways from start
                Connected_Points_map[POI_loc.to_string()].push_back(mid);
                Connected_Points_map[mid.to_string()].push_back(POI_loc);
                Street_Name_map[POI_loc.to_string() + mid.to_string()] = "a path";
                Street_Name_map[mid.to_string() + POI_loc.to_string()] = "a path";
                
            }
            
            // establish connectedness both ways for endpoints of segment
            Connected_Points_map[start.to_string()].push_back(end);
            Connected_Points_map[end.to_string()].push_back(start);
            Street_Name_map[start.to_string() + end.to_string()] = streetName;
            Street_Name_map[end.to_string() + start.to_string()] = streetName;

        }
    }
    
    return true;
}


bool GeoDatabase::get_poi_location(const std::string &poi, GeoPoint &point) const{
    
    const GeoPoint * ptr = POI_map.find(poi);
    
    if(ptr == nullptr){
        return false;
    }
    
    point = *ptr;
    
    return true;
    
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint &pt) const{
    
    const vector<GeoPoint> * ptr = Connected_Points_map.find(pt.to_string());
    
    if(ptr == nullptr){
        // empty vector should be returned
        return vector<GeoPoint>();
    }
    
    return *ptr;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1,
                                         const GeoPoint& pt2) const{
    
    const string * ptr = Street_Name_map.find(pt1.to_string() + pt2.to_string());
    
    if(ptr == nullptr){
        return "";
    }
    
    return *ptr;
    
}

