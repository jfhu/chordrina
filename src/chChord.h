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
    chChord(int* arr, int length);

    vector<string> getNames();
    string getFirstName();
    void printName();
    bool matchName(string name);

private:
    vector<int> chordId;
//    int chordId = -1;

    void initChordId(vector<int>& notes);
    vector<int> getChroma(vector<int>& notes);
    vector<int> matchChroma(vector<int>& chroma);

};



#endif /* defined(__chordrina__chChord__) */
