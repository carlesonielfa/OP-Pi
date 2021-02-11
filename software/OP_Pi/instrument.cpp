#include "instrument.h"
#include <numeric>

using namespace OP_Pi;
using namespace std;
// Call when key is pressed
void Instrument::NoteOn(int noteNumber, double timeOn){
    noteNumber+=octave*12;
    muxNotes.lock();
    auto noteFound = find_if(vecNotes.begin(), vecNotes.end(), [&noteNumber](Note const& item) { return item.number == noteNumber; });


    // Note not found in vector
    if (noteFound == vecNotes.end())
    {
        //Create a new note
        Note n;
        n.number = noteNumber;
        n.on = timeOn;
        n.active = true;

        // Add note to vector
        vecNotes.emplace_back(n);
    }
    // Note exists in vector
    else
    {
        // Key has been pressed again during release phase
        if (noteFound->off > noteFound->on)
        {
            
            noteFound->on = timeOn;
            noteFound->off = 0;
            noteFound->active = true;
        }
        // Key is still held, so do nothing

    }

    muxNotes.unlock();
}

// Call when key is released
void Instrument::NoteOff(int noteNumber, double timeOff){
    noteNumber+=octave*12;
    muxNotes.lock();
    auto noteFound = find_if(vecNotes.begin(), vecNotes.end(), [&noteNumber](Note const& item) { return item.number == noteNumber;});

    if (noteFound != vecNotes.end())
    {
        // Key has been released, so switch off
        if (noteFound->off < noteFound->on)
            noteFound->off = timeOff;
    }
    muxNotes.unlock();
}
void Instrument::GenerateNoteSounds(double time, float *outputs, int nSamples, Note n, bool &noteFinished) {
    for(int i=0; i<nSamples; i++){
        outputs[i] += GenerateNoteSound(time+1.0*i/sampleRate,n,noteFinished);
    }
    ApplyEffects(outputs,nSamples);

}
void Instrument::PlayNotes(double time, float *outputs, int nSamples) {
    unique_lock<mutex> lm(muxNotes);
    // Iterate through all active notes, and mix together
	for (auto &n : vecNotes)
	{
		bool noteFinished = false;
		//double noteSound = 0;

		// Get sample for this note by using the correct instrument and envelope
        //sound = n.channel->sound(dTime, n, noteFinished);
        GenerateNoteSounds(time, outputs, nSamples, n, noteFinished);
        
		if (noteFinished) // Flag note to be removed
			n.active = false;
        
	}
	safe_remove<vector<Note>>(vecNotes, [](Note const& item) { return item.active; });

    //Calculate output level mean of the recent 10 instrumentOutputs
    lastOutput=0;
    for(int i=0; i<nSamples;i++){
        lastOutput+=abs(outputs[i])/nSamples;
    }
}

char *Instrument::GetPresetName() {
    return instrumentDef->name;
}

Envelope *Instrument::GetEnvelope() {
    return instrumentDef->env;
}

Instrument::Instrument(int sampleRate) {
    this->sampleRate = sampleRate;
}

void Instrument::ApplyEffects(float *outputs, int nSamples) {
    for(Effect* e:effects){
        e->ApplyEffect(outputs,nSamples);
    }
}

Instrument::~Instrument() {
    effects.clear();
}
            