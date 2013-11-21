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

class chChord {
public:
    static void initTemplate();
    static bool templateInitialized;

    chChord(std::vector<int>& notes);

    std::string getName();
    void printName();

private:
    int chordId = -1;

    void initChordId(std::vector<int>& notes);
    std::vector<int> getChroma(std::vector<int>& notes);
    int matchChroma(std::vector<int>& chroma);

};



#endif /* defined(__chordrina__chChord__) */
