#include "sequence_generator.h"
#include <algorithm>
#include <random>
#include <exception>
#include <iostream>

Sequence::Sequence(){
    std::vector<Note> temp(12, {0, 0, 0, 0});
    matrix_ = std::vector<std::vector<Note>>(12, temp);
}

Sequence Sequence::GenerateSequence()
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

    return *this;
}

Sequence Sequence::GenerateMatrix(){
    if (sequence_.empty()){
        throw std::logic_error("Sequence is not generated");
    }

    matrix_[0] = sequence_;

    for (int i = 1; i < matrix_.size(); ++i){
        matrix_[i][i] = matrix_[0][0]; //строим главную диагональ 
    }
    for (int y = 1; y < matrix_.size(); ++y){
        int8_t diff = matrix_[y-1][y].freq - matrix_[y][y].freq;
        for (int x = 0; x < matrix_.size(); ++x) {
            matrix_[y][x].freq = matrix_[y-1][x].freq - diff;
        }
    }
    return *this;
}

void Sequence::PrintMatrix() {
    for (int y = 0; y < matrix_.size(); ++y) {
        for (int x = 0; x < matrix_.size(); ++x) {
            std::cout << (int)matrix_[y][x].freq << " "; //нужен фикс
        }
        std::cout << "\n";
    }
}

Sequence Sequence::SetMainTone(uint8_t tone){
    if (tone > 95) {
        throw std::invalid_argument("Введите тон до 96 (C7)");
    }
    tonality_ = tone;
        return *this;
}

Sequence Sequence::SetSequence(std::vector<int> seq) {
    for (int i = 0; i < seq.size(); ++i){
        uint8_t pitch = tonality_ + seq[i];
        Note note{pitch, 95, i, i+1};
        sequence_.push_back(note);
    }
    return *this;
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

