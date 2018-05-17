#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

//for error printing, should be changed to QT error printer
#include <iostream>
using std::cout;
using std::endl;

#include "session_data.h"
#include "event_factory.h"

using namespace SessionData;

bool EventFactory::isValid(EventData &ev_data) {
    if (/* checking if such event already exists */0) {
        cout << "such event already exists" << endl;
        return 0;
    } else if (ev_data.level <= 0) {
        cout << "level is not valid" << endl;
        return 0;
    } else if (ev_data.priority > 6 && ev_data.priority <= 0) {
        cout << "level is not valid" << endl;
        return 0;
    } else if (!surfaceData.RadiusIsValid(ev_data.coordinate, ev_data.radius)) {
        cout << "radius or coord are not valid" << endl; 
        return 0;
    }
    for (auto it : ev_data.actions) {
        if (it.subjectID != "hero") {
            cout << "subjectID is not valid" << endl;
            return 0;
        } else if (artifactsData.ArtifactExists(ev_data.ID)) {
            cout << "object [artifact] is not valid" << endl;
            return 0;
        } else if (commandList.find(it.command) == commandList.end()) {
            cout << "command is not valid" << endl;
            return 0;
        } else if (conditionList.find(it.condition) == conditionList.end() 
            && it.condition != "") {
            cout << "condition is not valid" << endl;
            return 0;
        } else if (it.duration < 0 || it.duration > 10) {
            cout << "duration is not valid" << endl;
            return 0;
        }
    }
    return 1;
}

Event* EventFactory::Create(EventData &ev_data) {
    vector<Action> actions;
    for (auto it : ev_data.actions) {
        Action newAction(
            &hero,
            it.command,
            artifactsData.getArtifact(it.objectID),
            it.diaryNote,
            it.condition,
            it.duration
        );
        actions.push_back(newAction);
    }
    Event *ev = new Event(
        ev_data.ID, ev_data.name, ev_data.level,
        ev_data.coordinate, ev_data.radius, 
        ev_data.priority, actions
    );
    return ev;
}

int EventFactory::InitAll(str folder, unordered_map<str, Event> &eventsMap) {
    int eventCount = 0;
    for (auto &it : fs::directory_iterator(folder)) {
        if (it.path().extension() == ".json") {
            tempData = parser.getData(it.path());
            if (!tempData) continue;
            for (auto it : *tempData) {
                if (eventsMap.find(it.ID) != eventsMap.end()) continue;
                if (isValid(it)) {
                    cout << "event <" << it.ID << "> read." << endl;
                    // Event* ev = Create(it);
                    // eventsMap[it.ID] = *ev;
                    eventCount++;
                } else {
                    cout << "event <" << it.ID << "> not read." << endl;
                    continue;
                }
            }
        }
    }
    return eventCount;
}

void ActionData::set(
    str _subjectID, str _command, str _objectID,
    str _toDiary, str _condition, short _duration) {

    subjectID = _subjectID;
    command = _command;
    objectID = _objectID;
    diaryNote = _toDiary;
    condition = _condition;
    duration = _duration;
}

/* DEBUG_FUNCTION */
void ActionData::PrintActionData() {
    cout << "condition: " << condition << endl;
    cout << "subjectID: " << subjectID << endl;
    cout << "command: " << command << endl;  // Converts in function in run()
    cout << "objectID: " << objectID << endl;  // Item *object in future
    cout << "diaryNote: " << diaryNote << endl;
    cout << "duration: " << duration << endl;
}

void EventData::set(
    str _ID, str _name, short _level, coord _coord,
    short _rad, short _priority, std::vector<ActionData> _actions) {

    ID =_ID;
    name = _name;
    level = _level;
    priority = _priority;
    coordinate = _coord;
    radius = _rad;
    actions = _actions;
}

/* DEBUG_FUNCTION */
void EventData::PrintEventData() {
    cout << "ID: " << ID << endl;
    cout << "name: " << name << endl;
    cout << "level: " << level << endl;
    cout << "coords: " << coordinate.x << ", " << coordinate.y << endl;
    cout << "radius: " << radius << endl;
    for (int i = 0; i < (int)actions.size(); i++) {
        cout << endl;
        actions[i].PrintActionData();
    }
}
