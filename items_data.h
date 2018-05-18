#ifndef ITEMSDATA
#define ITEMSDATA

#include <string>
#include <unordered_map>

#include "units.h"
#include "event_factory.h"
#include "artifact.h"
// #include "artifact_factory.h"
#include "surface.h" //here is SurfaceData, temporary solution.

class SystemData {
public:
    str resourcesDirectory; // directory with all the resources
    str nextLocationName; // ID of a map going to be loaded
    str currentLocationName; // ID of a map loaded
    str mapName; // name of the .bmp file
};

class GameData {
// stores finished events and other stuff
public:
    bool Init(); 
    bool Init(str);
    int mapHeight;
    int mapWidth;
};

class EventsData {
public:
    bool Init();
    Event* getEvent(const str);
    Event* getEvent(coord);
    bool EventExists(str);
    void RemoveFrontEvent(coord); // no realization yet
    // more methods coming in future
private:
    void PulverizeEvents(std::unordered_map<str, Event>&); //pulverizes events from eventList
    std::vector<Event> ***eventMatrix;
    // std::unique_ptr<Event[][]> eventMatrix;
    std::unordered_map<str, Event> currentEventList;
    // std::unordered_map<str, Event> globalEventList;
};

class ArtifactsData {
public:
    bool Init();
    bool ArtifactExists(str);
    Artifact* getArtifact(const str);
private:
    std::unordered_map<str, Artifact> currentArtifactsList;
    // std::unordered_map<str, Artifact> globalArtifactsList;
};



#endif //SESSION