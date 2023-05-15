#pragma once

#include <string>
#include <vector>
#include <memory>

//Event in track chunk
class Event {
public:
    void Serialize(std::ostream& outfile);
    void Parse(std::istream& infile);
    void Set(uint8_t status, uint8_t pitch, uint8_t velocity);
    uint8_t delta_time;
private:
    uint8_t status_byte;
    uint8_t data_byte1; //pitch 
    uint8_t data_byte2; //velocity
};

class MidiTrack {
public: 
    void SetTrack();
    //void ProcessBinData();
    void SerializeTrack(std::ofstream& file);
    //void AddNote()
    void AddEvents(std::vector<Event> events);
    std::vector<Event>* GetEvents();

private:
    std::vector<Event> midi_events_;
};
