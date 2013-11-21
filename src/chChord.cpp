//
//  chChord.cpp
//  chordrina
//

#include "chChord.h"
#include <cassert>

#define numChords 72
#define numQuality 5
int chordTemplate[numChords][12];
bool chChord::templateInitialized = false;

std::string chordList[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
std::string qualityList[6] = { "Maj", "Min", "Aug", "Dim", "Mm7", "mm7" };

void buildChordRow(int index[], int length, int rowBegin){
    for (int i = rowBegin; i < rowBegin + 12; i++){
        for (int j = 0; j < length; j++){
            chordTemplate[i][index[j]] = 1;
            index[j] = (index[j] + 1) % 12;
        }
    }
}

// Create chord template: a 24*12 matrix
// Each row is a binary template
// Row 1 - 12 is Major Chords from C to B
// Row 13 - 24 is Minor Chords from c to b
// For example
// C C# D D# E F F# G G# A A# B
// 1 0  0 0  1 0 0  1 0  0 0  0
// is the C-Major Chord
void chChord::initTemplate() {
    if (templateInitialized) {
        std::cerr << "Warning: template already init'd." << std::endl;
    }
    
    // 0. Initialize
    memset(chordTemplate,0,sizeof(int)*12*numChords);
    
    int row = 0;
    
    // 1. Create row 0-11 for Major Chords starting with C E G (0 4 7) for C-Maj
    int index[] = {0,4,7};
    buildChordRow(index,3,row);
    row += 12;
    
    // 2. Create row 12-23 for Minor Chords starting with C Eb G (0 3 7) for C-Minor
    int index2[] = {0,3,7};
    buildChordRow(index2,3,row);
    row += 12;
    
    // 3. Create row 24-35 for Augmented Chords starting with C E G# (0 4 8) for C-Aug
    int index3[] = {0,4,8};
    buildChordRow(index3,3,row);
    row += 12;
    
    // 4. Create row 36-47 for Diminished Chords starting with C bE bG (0 3 6) for C-dim
    int index4[] = {0,3,6};
    buildChordRow(index4,3,row);
    row += 12;
    
    // 5. Create row 48-59 for Dominant Seventh Chords starting with C E G bB for C-M7
    int index5[] = {0,4,7,10};
    buildChordRow(index5,4,row);
    row += 12;
    
    // 6 .Create row 60-71 for Diminish Seventh Chords starting with C bE bG bbB for C-dim7
    int index6[] = {0,3,6,9};
    buildChordRow(index6,4,row);
    row += 12;
    
    
    templateInitialized = true;
}

chChord::chChord(std::vector<int>& notes) {
    if (!chChord::templateInitialized) {
        chChord::initTemplate();
    }
    
    initChordId(notes);
}

std::string chChord::getName() {
    if (chordId < 0)
        return "?";
    
    // 12 different root
    std::string res = chordList[ chordId % 12 ];
    
    // Every 12 chords, the quality is different.
    res = res + " " + qualityList[ chordId / 12 ];
    
    return res;
}

void chChord::printName() {
    std::cout << getName() << std::endl;
}

void chChord::initChordId(std::vector<int>& notes) {
    // User must play at least 3 notes
    if (notes.size() < 3) {
        chordId = -1;
        return;
    }
    // Step 1 + 2: Get chroma
    std::vector<int> myChroma = getChroma(notes);
    // Step 3: Match with the chord templates
    chordId = matchChroma(myChroma);
}

std::vector<int> chChord::getChroma(std::vector<int>& notes) {
    // Step 1: Map into one octave
    // 0:C 1:C# 2:D 3:D# 4:E 5:F 6:F# 7:G 8:G# 9:A 10:A# 11:B
    for (int i = 0; i < notes.size(); i++){
        notes[i] = notes[i] %12;
//        std::cout << "note: " << notes[i] << " ";
    }
//    std::cout << std::endl;
    
    // Step 2: get chroma information
    std::vector<int> myChroma(12);

    // Get Chroma
    for (int i = 0; i < notes.size(); i++){
        // Way 1: A simpler method
        myChroma[notes[i]] = 1;
        // Way 2: TO-DO, combine with velocity and frequentness
        //myChroma[note[i]] += 1;
    }
    return myChroma;
}


// Find an index that maximizing the fitness vector, so that to find the chord Id
int findMaxIndex(int fitness_vector[numChords]){
    int maxIndex = -1;
    int maxVal = 0;
    
    for (int i = 0; i < numChords;i ++){
        if (fitness_vector[i] > maxVal){
            maxVal = fitness_vector[i];
            maxIndex = i;
        }
    }
//    std::cout << "maxChordId: " << maxIndex << std::endl;
    return maxIndex;
}



// A rudimentary chord matching
int chChord::matchChroma(std::vector<int>& chroma) {
    // Get a fitness matrix through matrix multiplication, and find the minimum distance
    // Dot product of the numChords * 12 template, and the 12 * 1 chroma vector
    
    // 1. Create an empty fitness vector and initialize to 0
    int fitness_vector[numChords];
    memset(fitness_vector,0,sizeof(int)*numChords);
    
    // 2. Matrix Multiplication
    for (int i = 0; i < numChords; i++){
        for (int j = 0; j < 12; j++){
            fitness_vector[i] += chordTemplate[i][j] * chroma[j];
        }
    }
    //    std::cout << "fitness vector: " << std::endl;
    //for (int i = 0; i < numChords; i++){
    //    std::cout << fitness_vector[i] << std::endl;
    //}
    
    // Pick up the template that maximize the fitness vector
    return findMaxIndex(fitness_vector);
    
}
