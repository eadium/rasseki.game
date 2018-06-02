#include "session_data.h"
#include <iostream>

namespace SessionData {
    SystemData systemData;
    GameData gameData;
    SurfaceData surfaceData;
    EventsData eventsData;
    ArtifactsData artifactsData;

    str diaryString;
    str writer;

    // hero initialization
    std::string name = "Moleque";
    std::string id = "super_hero";
    Coord start(651, 414);
    Hero hero(id, name, 1, 10, start);
}

