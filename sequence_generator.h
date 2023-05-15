#pragma once

#include <vector>
#include <stdint.h>
#include <memory>

#include "midi_track.h"


struct Note {
    int8_t freq;
    int8_t velocity; 
    double start;
    double end;
};

class Sequence {
public:
    void GenerateSequence();
    void SetTonality(uint8_t tone);
    std::vector<Event> ConvertToMidi();
    
    std::vector<Note> GetSequence();

    uint8_t GetTonality();

private:
    std::vector<Note> sequence_;
    //uint8_t channel; //пригодится позже
    uint8_t tonality_;
};