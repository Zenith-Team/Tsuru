#pragma once

#include "game/actor/stage/stageactor.h"
#include "game/level/level.h"
#include "sead/safestring.h"
#include <cstring>

const char CHARMAP[64] = {
    '\0', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h',  'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p',  'q', 'r', 's', 't', 'u', 'v', 'w',
    'x',  'y', 'z', '0', '1', '2', '3', '4',
    '5',  'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H',  'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P',  'Q', 'R', 'S', 'T', 'U', 'V', 'W',
    'X',  'Y', 'Z', '6', '7', '8', '9', '_'
};

class strybble {
public:
    // Decodes a null terminated array of strybble charcodes into a proper string.
    // The given array will be mutated with the decoded characters.
    // @param str The array of strybble charcodes to decode.
    // @param charcount The length of the array of charcodes (excluding null terminator).
    static void decode(char* str, u8 charcount) {
        for (u8 i = 0; i < charcount; i++) {
            str[i] = CHARMAP[str[i]];
        }
        str[charcount] = '\0';

        // Remove nulls and process the special underscore characters.
        char newstr[49] = { 0 };
        u8 newcharcount = 0;
        for (u8 i = 0; i < charcount; i++) {
            if (str[i] != '\0') {
                if (str[i] == '_' && str[i + 1] == '_') {
                    if (str[i + 2] == '_') {
                        newstr[newcharcount++] = '.';
                        i += 2;
                    } else {
                        newstr[newcharcount++] = '/';
                        i += 1;
                    }
                } else {
                    newstr[newcharcount++] = str[i];
                }
            }
        }
        newstr[newcharcount] = '\0';
        strncpy(str, newstr, newcharcount + 1);
    };

    // Not implemented.
    static u8* encode(char* str, u8 charcount);

    // Loads a null terminated array of strybble charcodes from a given array of bytes.
    // @param nybbles The array of bytes whose nybbles to load from (must be at least 12 in length).
    // @param charcount The number of charcodes to load in range 1 to 16 (excluding null terminator).
    // @param out The array to load the charcodes into.
    static void loadFromNybbles(u8 nybbles[12], u8 charcount, char* out) {
        if (charcount == 0) return;
        if (charcount > 16) charcount = 16;
        u8 eventID1 = nybbles[0];
        u8 eventID2 = nybbles[1];
        u32 settings1 = nybbles[2] << 24 | nybbles[3] << 16 | nybbles[4] << 8 | nybbles[5];
        u32 settings2 = nybbles[6] << 24 | nybbles[7] << 16 | nybbles[8] << 8 | nybbles[9];
        u8 movementID = nybbles[10];
        u8 linkID = nybbles[11];
        u8 charcodes[17];
        charcodes[0] = eventID1 >> 2 & 63;   // 6 bits (char 1)
        charcodes[1] = (eventID1 & 3) << 4 | eventID2 >> 4 & 15;     // 2 + 4 bits (char 2)
        charcodes[2] = (eventID2 & 15) << 2 | settings1 >> 30 & 3;   // 4 + 2 bits (char 3)
        charcodes[3] = settings1 >> 24 & 63; // 6 bits (char 4)
        charcodes[4] = settings1 >> 18 & 63; // 6 bits (char 5)
        charcodes[5] = settings1 >> 12 & 63; // 6 bits (char 6)
        charcodes[6] = settings1 >> 6 & 63;  // 6 bits (char 7)
        charcodes[7] = settings1 & 63;       // 6 bits (char 8)
        charcodes[8] = settings2 >> 26 & 63; // 6 bits (char 9)
        charcodes[9] = settings2 >> 20 & 63; // 6 bits (char 10)
        charcodes[10] = settings2 >> 14 & 63;// 6 bits (char 11)
        charcodes[11] = settings2 >> 8 & 63; // 6 bits (char 12)
        charcodes[12] = settings2 >> 2 & 63; // 6 bits (char 13)
        charcodes[13] = (settings2 & 3) << 4 | movementID >> 4 & 15; // 2 + 4 bits (char 14)
        charcodes[14] = (movementID & 15) << 2 | linkID >> 6 & 3;    // 4 + 2 bits (char 15)
        charcodes[15] = linkID & 63;         // 6 bits (char 16)
        charcodes[16] = '\0';
        charcodes[charcount] = '\0';
        for (u8 i = 0; i < charcount + 1; i++) out[i] = charcodes[i];
    }

    // Loads a null-terminated array of strybble charcodes from a given actor's nybbles.
    // @param actor The actor whose nybbles to load from.
    // @param charcount The number of charcodes to load in range 1 to 16 (excluding null terminator).
    // @param out The array to load the charcodes into.
    static void loadFromNybbles(StageActor* actor, u8 charcount, char* out) {
        if (charcount == 0) return;
        u8 nybbles[12] = {
            actor->eventID1,
            actor->eventID2,
            actor->settings1 >> 24 & 0xFF,
            actor->settings1 >> 16 & 0xFF,
            actor->settings1 >> 8 & 0xFF,
            actor->settings1 & 0xFF,
            actor->settings2 >> 24 & 0xFF,
            actor->settings2 >> 16 & 0xFF,
            actor->settings2 >> 8 & 0xFF,
            actor->settings2 & 0xFF,
            actor->movementID,
            actor->linkID
        };
        loadFromNybbles(nybbles, charcount, out);
    }

    // Loads a null-terminated array of strybble charcodes from a given Sprite's nybbles.
    // @param sprite The Sprite whose nybbles to load from.
    // @param charcount The number of charcodes to load in range 1 to 16 (excluding null terminator).
    // @param out The array to load the charcodes into.
    static void loadFromNybbles(Level::Area::Sprite* sprite, u8 charcount, char* out) {
        if (charcount == 0) return;
        u8 eventID1 = sprite->eventID1_2 >> 8 & 0xFF;
        u8 eventID2 = sprite->eventID1_2 & 0xFF;
        u8 nybbles[12] = {
            eventID1,
            eventID2,
            sprite->settings1 >> 24 & 0xFF,
            sprite->settings1 >> 16 & 0xFF,
            sprite->settings1 >> 8 & 0xFF,
            sprite->settings1 & 0xFF,
            sprite->settings2 >> 24 & 0xFF,
            sprite->settings2 >> 16 & 0xFF,
            sprite->settings2 >> 8 & 0xFF,
            sprite->settings2 & 0xFF,
            sprite->movementID,
            sprite->linkID
        };
        loadFromNybbles(nybbles, charcount, out);
    }
};
