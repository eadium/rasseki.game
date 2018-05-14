#ifndef THINGS_H
#define THINGS_H

#include <vector>

#include "Item.h"

class Artifact : public Item {
public:
    Artifact(std::string, std::string, short, short);
    short GetPower() const ;
private:
    short power;
};

class Storage {
public:
    Storage(short);
    void AddArtifact(Artifact);
    void RemoveArtifact(std::string);
    Artifact* GetArtifact(std::string);
private:
    std::vector<Artifact> artifacts;
};

#endif //THINGS_H