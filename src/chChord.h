//
//  chChord.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/18/13.
//
//

#ifndef __chordrina__chChord__
#define __chordrina__chChord__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class chChord {
public:
    static void initTemplate();
    static bool templateInitialized;

    chChord(vector<int>& notes);

    vector<string> getNames();
    void printName();

private:
    vector<int> chordId;
//    int chordId = -1;

    void initChordId(vector<int>& notes);
    vector<int> getChroma(vector<int>& notes);
    vector<int> matchChroma(vector<int>& chroma);

};



#endif /* defined(__chordrina__chChord__) */
