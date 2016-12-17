//
// Created by zp on 2016/12/13.
//

//CDPS, Content Description Properties Set
#ifndef UCL_CDPS_H
#define UCL_CDPS_H

#include <cstdint>
#include <vector>
#include "UCLPropertyBase.h"

class CDPSAuthor:public UCLPropertyBase{
public:
	CDPSAuthor();

	//the category of keywords
	bool setCategory(uint8_t category=0x1);
};

class CDPSKeyWords:public UCLPropertyBase{
public:
	CDPSKeyWords();

	//the category of keywords
	bool setCategory(uint8_t category=0x2);

	//the amount of keywords
    bool setNumsOfKeyWords(uint8_t numsOfKeyWords);
    uint8_t getNumsOfKeyWords() const;
	
	vector<string> getKeyWords() const;
	bool setKeyWords(const vector<string> &keyWords);
};
#endif //UCL_CDPS_H
