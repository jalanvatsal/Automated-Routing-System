//
//  HashMap.hpp
//  Project 4 CS 32
//
//  Created by Vatsal Jalan on 7/3/2567 BE.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include<vector>
#include<list>
#include<string>
#include<iostream>

template <typename T>
class HashMap
{
public:
    HashMap(double max_load = 0.75); // constructor
    
    ~HashMap(); // destructor; deletes all of the items in the hashmap
    
    // return the number of associations in the hashmap
    int size() const{
        return m_numAssoc;
    }
    
    // The insert method associates one item (key) with another (value).
    // If no association currently exists with that key, this method inserts
    // a new association into the hashmap with that key/value pair. If there is
    // already an association with that key in the hashmap, then the item
    // associated with that key is replaced by the second parameter (value).
    // Thus, the hashmap must contain no duplicate keys.
    void insert(const std::string& key, const T& value);
//    
//    // If no association exists with the given key, return nullptr; otherwise,
//    // return a pointer to the value associated with that key. This pointer can be
//    // used to examine that value or modify it directly within the map.
    const T* find(const std::string& key) const;
    
    // overloaded version
    T* find(const std::string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }
//
//    // Defines the bracket operator for HashMap, so you can use your map like this:
//    // your_map["david"] = 2.99;
//    // If the key does not exist in the hashmap, this will create a new entry in
//    // the hashmap and map it to the default value of type T. Then it will return a
//    // reference to the newly created value in the map.
    T& operator[](const std::string& key);
    
private:
    double m_loadFactor;
    
    // number of key, value pairs
    double m_numAssoc;
    
    // number of buckets in current container
    double num_buckets;
    
    // our contiguous array pointer (points to our container)
    std::list<std::pair<std::string, T>>* buckets;
    
    // leave these unimplemented
    HashMap(const HashMap&);
    HashMap& operator=(const HashMap&);
};

// constructor
template <typename T>
HashMap<T>::HashMap(double max_load){
    
    m_loadFactor = max_load;
    m_numAssoc = 0;
    
    // initialize starting number of buckets
    num_buckets = 10;
    
    // dynamically allocate a 10 element array
    // set buckets to point to it
    buckets = new std::list<std::pair<std::string, T>>[num_buckets];
    
    //Starts with 10 buckets, we will put 10 empty lists to indicate nothing is in the container yet
    for(int i = 0; i < 10; i++){
        buckets[i] = std::list<std::pair<std::string, T>>();
    }
    
}

// Destructor
template <typename T>
HashMap<T>::~HashMap() {
    // delete dynamically allocated array
    delete[] buckets;
}

// insert function
template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value){
        
    // check if we need to rehash
    double rehash_exp = ((m_numAssoc + 1) / (num_buckets));
    
    if(rehash_exp > m_loadFactor){
        
        // Perform rehashing
        double new_num_buckets = num_buckets * 2; // Double the number of buckets for new container
        std::list<std::pair<std::string, T>>* new_buckets = new std::list<std::pair<std::string, T>>[new_num_buckets];
        
        
        // Redistribute elements into the new container
        for (int i = 0; i < num_buckets; ++i) {
            
            auto it = buckets[i].begin();
            while (it != buckets[i].end()) {
                size_t new_bucket_index = std::hash<std::string>{}(it->first) % static_cast<size_t>(new_num_buckets);
                auto& destination_list = new_buckets[new_bucket_index];
                auto next_it = std::next(it);
                destination_list.splice(destination_list.begin(), buckets[i], it, next_it);
                it = next_it;
            }
        }
        
        // Update hashmap parameters
        delete[] buckets; // Free memory of old container
        buckets = new_buckets; // point to new container
        num_buckets = new_num_buckets;
        
        // now finally insert new item
        // Calculate the bucket index for the key
        size_t bucket_index = std::hash<std::string>{}(key) % static_cast<size_t>(num_buckets);
        // check if key is at that index, if it is then update its value
        for(auto& pair : buckets[bucket_index]){
            if(!buckets[bucket_index].empty() && pair.first == key){
                pair.second = value;
                return;
            }
        }
        
        //otherwise key is not in index linked list, add pair to the front of the list
        buckets[bucket_index].push_back(std::make_pair(key, value));
        //increment number of valid key/value pairs
        m_numAssoc++;
        
        
    } else {
        
        
        // we need to pass the key through the STL hash function
        size_t h = std::hash<std::string>()(key);
        // locate index for which we will do insertion into
        size_t index = h % static_cast<size_t>(num_buckets);
        
        for(auto& pair : buckets[index]){
            if(!buckets[index].empty() && pair.first == key){
                pair.second = value;
                return;
            }
        }
        
        //otherwise key is not in index list, push pair to the front of the list
        buckets[index].push_back(std::make_pair(key, value));
        //increment number of valid key/value pairs
        m_numAssoc++;
        

    }
    
}

template <typename T>
const T* HashMap<T>::find(const std::string& key) const{
    
    T * ptr = nullptr;
    
    // find the element in the associated linked list
    // we need to pass the key through the STL hash function
    size_t h = std::hash<std::string>()(key);
    // locate index for which we will search
    size_t index = h % static_cast<size_t>(num_buckets);
    
    for(auto& pair : buckets[index]){
        if(!buckets[index].empty() && pair.first == key){
            ptr = &(pair.second);
            return ptr;
        }
    }
    
    // we didn't find a matching key so just return nullptr
    return ptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key){
        
    T * ptr = this -> find(key);
    
    if(ptr == nullptr){
        
        // key doesn't exist so we do an insertion
        
        double rehash_exp = ((m_numAssoc + 1) / (num_buckets));
        
        if(rehash_exp > m_loadFactor){
            
            // Perform rehashing
            double new_num_buckets = num_buckets * 2; // Double the number of buckets for new container
            std::list<std::pair<std::string, T>>* new_buckets = new std::list<std::pair<std::string, T>>[new_num_buckets];
            
            
            // Redistribute elements into the new container
            for (int i = 0; i < num_buckets; ++i) {
                
                auto it = buckets[i].begin();
                while (it != buckets[i].end()) {
                    size_t new_bucket_index = std::hash<std::string>{}(it->first) % static_cast<size_t>(new_num_buckets);
                    auto& destination_list = new_buckets[new_bucket_index];
                    auto next_it = std::next(it);
                    destination_list.splice(destination_list.begin(), buckets[i], it, next_it);
                    it = next_it;
                }
            }
            
            // Update hashmap parameters
            delete[] buckets; // Free memory of old container
            buckets = new_buckets; // point to new container
            num_buckets = new_num_buckets;
            
            // now handle insertion of new item
            // Calculate the bucket index for the key
            size_t bucket_index = std::hash<std::string>{}(key) % static_cast<size_t>(num_buckets);

            
            // key is not in list, add pair to the back of the list
            buckets[bucket_index].push_back(std::make_pair(key, T()));
            
            //increment number of valid key/value pairs
            m_numAssoc++;
            
            // Getting an iterator to the end of the list
            typename std::list<std::pair<std::string, T>>::iterator it = buckets[bucket_index].end();
            
            // Decrementing the iterator to get the last element of the list
            --it;
            
            // return reference to the newest added value
            return ((*it).second);
            
        } else {
            
            // we need to pass the key through the STL hash function
            size_t h = std::hash<std::string>()(key);
            // locate index for which we will do insertion into
            size_t index = h % static_cast<size_t>(num_buckets);
            
            
            //key is not in index list, push pair to the back of the list
            buckets[index].push_back(std::make_pair(key, T()));
            
            //increment number of valid key/value pairs
            m_numAssoc++;
            
            // Getting an iterator to the end of the list
            typename std::list<std::pair<std::string, T>>::iterator it = buckets[index].end();
            
            // Decrementing the iterator to get the last element of the list
            --it;
            
            // return reference to the newest added value
            return ((*it).second);

        }
    }
    
    return *ptr;
}




#endif // HASHMAP_H included


