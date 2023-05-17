#include <string>
#include <fstream>
#include <iostream> 

#include "midi_track.h"
#include "sequence_generator.h"

int main() {
    MidiTrack track;
    Sequence seq;
    std::ofstream file1("test22.mid", std::ios::binary);
    seq.SetMainTone(60);
    //seq.SetSequence({3, 7, 8, 1, 9, 11, 2, 4, 5, 0, 10, 6});
    seq.GenerateSequence();
    seq.GenerateMatrix();
    seq.PrintMatrix();
    track.AddEvents(seq.ConvertToMidi());
    track.SerializeTrack(file1);
}