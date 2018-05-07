#ifndef EVENT
#define EVENT

#include "item.h"
#include "location.h"
#include "units.h"

class EventFactory;  // forward declaration
class Action {
public:
    void run() const;
    /* DEBUG_FUNCTION */ void printAction();
    friend EventFactory;
private:
    Action(Creature*, str, Item*, str, str, short);
    Creature *subject;
    str command;  // Converts to function in run()
    Item *object;
    str diaryNote;
    str condition;  // Converts to if { ... } in run()
    short duration;
};

class Event : public Item, public Located {
public:
    short getRadius();
    short getPriority();
    void runEvent() const;
    /* DEBUG_FUNCTION */ void printEvent() const;
    friend EventFactory;
private:
    Event(str, str, short, coord, short, short, std::vector<Action>);
    short radius, priority;
    std::vector<Action> actions;
};

#endif  // EVENT