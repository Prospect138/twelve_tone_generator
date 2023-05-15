#include <string>
#include <fstream>
#include <iostream> 

#include "midi_track.h"
#include "sequence_generator.h"

int main() {
    MidiTrack track;
    Sequence seq;
    std::ofstream file1("test666.mid", std::ios::binary);
    seq.SetTonality(23);
    seq.GenerateSequence();
    track.AddEvents(seq.ConvertToMidi());
    track.SerializeTrack(file1);
}