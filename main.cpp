#include "event_factory.h"
#include "artifact.h"
#include "session_data.h"
#include <iostream>

int main() {
    SessionData::gameData.Init();

    coord point(677,508);
    Event* ev = SessionData::eventsData.getEvent(point);
  /*   EventFactory ev_factory;
    str path = "resources/events";
    unordered_map<str, Event> events;
    int eventCount = ev_factory.InitAll(path, events);
    std::cout << std::endl << eventCount << " events loaded." << std::endl;
    // Event *ev = ev_factory.createFromJson(filename);
    // delete ev;

    ArtifactFactory ar_factory;
    path = "resources/artifacts";
    unordered_map<str, Artifact> artifacts;
    int artifactCount = ar_factory.InitAll(path, artifacts);
    std::cout << std::endl << artifactCount << " artifacts loaded." << std::endl; */

    return 0;
}