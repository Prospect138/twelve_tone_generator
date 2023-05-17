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
    Sequence();
    Sequence GenerateSequence();
    Sequence GenerateMatrix();
    Sequence SetMainTone(uint8_t tone);
    Sequence SetSequence(std::vector<int> seq);
    std::vector<Event> ConvertToMidi();
    
    std::vector<Note> GetSequence();

    uint8_t GetTonality();

    void PrintMatrix();

private:
    std::vector<Note> sequence_;
    std::vector<std::vector<Note>> matrix_;
    //uint8_t channel; //пригодится позже
    uint8_t tonality_;
};