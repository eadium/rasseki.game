#include "session_data.h"
// #include "event_factory.h"
#include "mapscanner.h"

#include <algorithm>

using std::vector;

//---------------------------------------------------------
//---------------- SurfaceData ----------------------------
//---------------------------------------------------------

bool SurfaceData::Init() {
    // open map, read it
    // asign map pointers
    // init factories
    str locationName = SessionData::gameData.locationID;
    MapScanner scanner;
    MapData data = scanner.getMap(locationName);
    surfaceMatrix = data.surfaceMatrix;
    mapHeight = data.mapHeight;
    mapWidth = data.mapWidth;
    SessionData::gameData.mapHeight = mapHeight;
    SessionData::gameData.mapWidth = mapWidth;
    return true;
}

int SurfaceData::getWidth() {
    return mapWidth;
}

int SurfaceData::getHeight() {
    return mapHeight;
}

short SurfaceData::getSurface(coord& point) {
    if ((point.x <= 0 || point.x >= mapWidth) || (point.y <= 0 || point.y >= mapHeight))
        return -1;
    return surfaceMatrix[point.x][point.y];
}

bool SurfaceData::IsValidCoord(coord& point) {
    if ((point.x < 0 || point.x > mapWidth) || (point.y < 0 || point.y > mapHeight))
        return false;
    return true;
}

bool SurfaceData::IsValidRadius(coord& point, short radius) {
    if (
        (point.x - radius <= 0) || 
        (point.x + radius >= mapWidth) || 
        (point.y + radius >= mapHeight) ||
        (point.y - radius <= 0) ||
        (!IsValidCoord(point))
    ) return false;

    bool flag = false;
    coord temp;
    for (int i = point.x - radius; i < point.x + radius; i++) {
        for (int j = point.y - radius; j < point.y + radius; j++) {
            temp.x = i; temp.y = j;
            if (getSurface(temp)) flag = true;
        }
    }
    
    return flag;
}

bool SurfaceData::IsWalkable(coord& point) {
    if (getSurface(point)) return true;
    return false;
}

//---------------------------------------------------------
//----------------- EventsData ----------------------------
//---------------------------------------------------------

bool EventsData::Init() {
    EventFactory eFactory;
    str path = "tests/events";
    eFactory.InitAll(path, currentEventList); // hardcoded just for debugging
    // using unique_ptr for two-dim array isn't a good idea though
    // std::unique_ptr<Event[][]> eventMatrix (nullptr); 
    PulverizeEvents(currentEventList); 
    return true;
}

Event& EventsData::getEvent(const str key) {
    return currentEventList.at(key);
}

Event& EventsData::getEvent(coord point) {
    return eventMatrix[point.x][point.y]->front();
}

void EventsData::PulverizeEvents(std::unordered_map<str, Event>& list) {
/* 
parsing map - getting event and spraying it at the map. 
get event
add event to map
*/
    for (auto i : list) {
        Event event = i.second;
        
        int width = SessionData::gameData.mapWidth;
        int height = SessionData::gameData.mapHeight;

        coord eventCenter = event.GetCoord();
        if (eventCenter.x > width || eventCenter.y > height) throw "coordinates are out of range";
        if (eventCenter.x < 0 || eventCenter.y < 0) throw "invalid coordinates";

        for (int i = eventCenter.x - event.getRadius(); i <= eventCenter.x + event.getRadius(); i++) {
            for (int j = eventCenter.y - event.getRadius(); j <= eventCenter.y + event.getRadius(); j++) {
                
                if (
                    eventCenter.y + event.getRadius() > height ||
                    eventCenter.x + event.getRadius() > width  ||
                    eventCenter.y - event.getRadius() < 0      ||
                    eventCenter.x - event.getRadius() < 0      
                ) break; //total size of event mark exceeded the map

                // if (!SurfaceMap::getSurface(eventCenter)) break;

                if (!eventMatrix[eventCenter.x][eventCenter.y]) {
                    eventMatrix[eventCenter.x][eventCenter.y] = new std::vector<Event>;
                eventMatrix[eventCenter.x][eventCenter.y]->push_back(event);
                }
                else {
                    eventMatrix[eventCenter.x][eventCenter.y]->push_back(event);            
                    //here'll be sorting function
                    SortEventVector(eventMatrix[eventCenter.x][eventCenter.y]);
                }
            }
        }
    }
}
void EventsData::SortEventVector(std::vector<Event> * vector) {
    std::sort(vector->begin(), vector->end(), 
    [](Event& a, Event& b) -> bool {
        return a.getPriority() > b.getPriority();
    });
}

//---------------------------------------------------------
//---------------- ArtifactsData --------------------------
//---------------------------------------------------------

bool ArtifactsData::Init() {
    ArtifactFactory aFactory;
    str path = "tests/artifacts";
    aFactory.InitAll(path, currentArtifactsList);
    return true;
}

Artifact& ArtifactsData::getArtifact(const str key) {
    return currentArtifactsList.at(key);
}

//---------------------------------------------------------
//--------------------- GameData --------------------------
//---------------------------------------------------------

bool GameData::Init() {
    using namespace SessionData;
    return eventsData.Init() && surfaceData.Init() && artifactsData.Init();
}