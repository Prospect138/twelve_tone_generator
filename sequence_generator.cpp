#include "sequence_generator.h"
#include <algorithm>
#include <random>

void Sequence::GenerateSequence()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> seq = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    std::shuffle(seq.begin(), seq.end(), g);

    for (int i = 0; i < seq.size(); ++i){
        uint8_t pitch = tonality_ + seq[i];
        Note note{pitch, 95, i, i+1};
        sequence_.push_back(note);
    }

}

void Sequence::SetTonality(uint8_t tone){
    tonality_ = tone;
}

std::vector<Note> Sequence::GetSequence()
{
    return std::vector<Note>();
}

uint8_t Sequence::GetTonality()
{
    return tonality_;
}

std::vector<Event> Sequence::ConvertToMidi(){
    std::vector<Event> sequence;
    for (int i = 0; i < sequence_.size(); ++i){
        uint8_t pitch = tonality_ + sequence_[i].freq;
        Event note_on;
        note_on.Set(0x90, pitch, 95);
        note_on.delta_time = 0;
        Event note_off;
        note_off.Set(0x80, pitch, 95);
        note_off.delta_time = 48;
        sequence.push_back(note_on);
        sequence.push_back(note_off);
    }
    return sequence;
}

