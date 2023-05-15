#include "midi_track.h"

#include <iostream>
#include <iomanip>
#include <fstream>


auto swap32 = [](uint32_t n) {
    return 
    (
    ((n >> 24) & 0xff) | 
    ((n << 8) & 0xff0000) | 
    ((n >> 8) & 0xff00) | //тут может быть баг
    ((n << 24) & 0xff000000)
    );
};

auto swap16 = [](uint16_t n){
    return (n >> 8 | n << 8);
};

void MidiTrack::SetTrack()
{
    int bpm;
    int num_of_mtrk;
    std::cout << "Write bpm: ";
    std::cin >> bpm;
    std::cout << "\nWrite number of midi tracks: ";
    std::cin >> num_of_mtrk;
}

void MidiTrack::SerializeTrack(std::ofstream &file)
{
    char shapka[14] = {0x4D, 0x54, 0x68, 0x64, 
    0x00, 0x00, 0x00, 0x06, 
    0x00, 0x00, 
    0x00, 0x01,
    0x00, 0x75};
    file.write(shapka, 14);

    //header for single track
    uint8_t lng = midi_events_.size() * 4 + 3;
    char track_shapka[8] = {0x4D, 0x54, 0x72, 0x6B, 
    0x00, 0x00, 0x00, lng};
    file.write(track_shapka, 8);

    ////meta event for track instrument
    //char instrument_msg[3] = {0x00, 0xC0, 0x27};
    //file.write(instrument_msg, 3);

    for (auto event : midi_events_){
        event.Serialize(file);
    }

    char eof[3] = {static_cast<char>(0xFF), 0x2F, 0x00};
    file.write(eof, 3);
    file.close();
}

void MidiTrack::AddEvents(std::vector<Event> events)
{
    for (auto event : events) {
        midi_events_.push_back(event);
    }
}

std::vector<Event>* MidiTrack::GetEvents()
{
    return &midi_events_;
}

void Event::Serialize(std::ostream &outfile)
{
    const char chunk[4] = {delta_time, status_byte, data_byte1, data_byte2};
    outfile.write(chunk, 4);
}

void Event::Parse(std::istream &infile)
{

}

void Event::Set(uint8_t status, uint8_t pitch, uint8_t velocity)
{
    status_byte = status;
    data_byte1 = pitch;
    data_byte2 = velocity;
}