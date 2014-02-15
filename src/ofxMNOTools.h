//
//  ofxMNOTools.h
//  HoldTheLineExhibition
//
//  Created by shakemno on 5/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef HoldTheLineExhibition_ofxMNOTools_h
#define HoldTheLineExhibition_ofxMNOTools_h

#include "ofMain.h"

typedef struct{
    string character;
    string code;
}charSubstitution;

static charSubstitution chars[] = { 
    {"À","\xC0"}, {"Á","\xC1"}, {"Â","\xC2"}, {"Ã","\xC3"}, {"Ä","\xC4"}, {"Å","\xC5"}, {"Æ","\xC6"},
    {"à","\xE0"}, {"á","\xE1"}, {"â","\xE2"}, {"ã","\xE3"}, {"ä","\xE4"}, {"å","\xE5"}, {"æ","\xE6"},
    {"Ç","\xC7"},
    {"ç","\xE7"},
    {"È","\xC8"}, {"É","\xC9"}, {"Ê","\xCA"}, {"Ë","\xCB"},
    {"è","\xE8"}, {"é","\xE9"}, {"ê","\xEA"}, {"ë","\xEB"},
    {"Ì","\xCC"}, {"Í","\xCD"}, {"Î","\xCE"}, {"Ï","\xCF"},
    {"ì","\xEC"}, {"í","\xED"}, {"î","\xEE"}, {"ï","\xEF"},
    {"Ñ","\xD1"},
    {"ñ","\xF1"},
    {"Ò","\xD2"}, {"Ó","\xD3"}, {"Ô","\xD4"}, {"Õ","\xD5"}, {"Ö","\xD6"}, {"Ø","\xD8"},
    {"ò","\xF2"}, {"ó","\xF3"}, {"ô","\xF4"}, {"õ","\xF5"}, {"ö","\xF6"}, {"ø","\xF8"},
    {"ß","\xDF"},
    {"Ù","\xD9"}, {"Ú","\xDA"}, {"Û","\xDB"}, {"Ü","\xDC"},
    {"ù","\xF9"}, {"ú","\xFA"}, {"û","\xFB"}, {"ü","\xFC"},
    {"ÿ","\xFF"}
};

class ofxMNOTools
{
public:
    static void fixStringEncoding(string &_orig);
    static ofRectangle scaleToFitKeepRatio(float orgWidth, float orgHeight);
    static ofRectangle scaleToFitKeepRatio(float orgWidth, float orgHeight, float toFitWidth, float toFitHeight);
    static ofRectangle scaleToFillKeepRatio(float orgWidth, float orgHeight);
    static void roundedRect(float x, float y, float w, float h, float r);
    static void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);
};

#endif
