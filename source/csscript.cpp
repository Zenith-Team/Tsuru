#include "game/csscript.h"

/*
    * Course Select Scripts
    * Originally dumped by RoadrunnerWMC for the Cobra project @ https://github.com/RoadrunnerWMC/Cobra
    * Note: This is a modified version of the vanilla CS scripts, find those here: https://pastebin.com/f2MTPneY
*/

typedef CSCommand cmd;

CSScriptCommand Script000[] = {
    {cmd::End, 0}
};

CSScriptCommand Script001[] = {  // Triggered on level enter
    {5, 0},
    {7, 30},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script002[] = {
    {341, 0},
    {40, 0},
    {8, 0},
    {50, 0},
    {41, 0},
    {340, 0},
    {cmd::End, 0}
};

CSScriptCommand Script003[] = {
    {40, 0},
    {9, 0},
    {50, 0},
    {41, 0},
    {cmd::End, 0}
};

CSScriptCommand Script004[] = {  // "Save?" request popup
    {7, 60},
    {10, 0},
    {cmd::End, 0}
};

CSScriptCommand Script005[] = {
    {18, 0},
    {7, 0},
    {16, 0},
    {7, 30},
    {32, 0},
    {7, 60},
    {cmd::End, 0}
};

CSScriptCommand Script006[] = {
    {18, 0},
    {7, 0},
    {16, 0},
    {7, 30},
    {32, 0},
    {cmd::End, 0}
};

CSScriptCommand Script007[] = {  // Triggered on tower level enter (1-T)
    {48, 0},
    {2, 0},
    {42, 0},
    {4, 0},
    {319, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script008[] = {  // Triggered on castle level enter (1-C)
    {48, 0},
    {2, 0},
    {42, 0},
    {4, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script009[] = {
    {48, 0},
    {42, 0},
    {4, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script010[] = {
    {49, 0},
    {7, 10},
    {3, 0},
    {7, 25},
    {320, 0},
    {36, 1},
    {4, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script011[] = {
    {49, 0},
    {7, 10},
    {3, 0},
    {7, 25},
    {36, 1},
    {4, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script012[] = {
    {49, 0},
    {36, 9},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script013[] = {
    {49, 0},
    {7, 10},
    {3, 0},
    {7, 25},
    {36, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script014[] = {  // Triggered on castle exit by win
    {91, 0},
    {36, 8},
    {13, 0},
    {92, 0},
    {1, 0},
    {90, 0},
    {7, 30},
    {315, 0},
    {339, 0},
    {cmd::End, 0}
};

CSScriptCommand Script015[] = {
    {91, 0},
    {36, 8},
    {13, 0},
    {92, 0},
    {7, 30},
    {315, 0},
    {7, 60},
    {339, 0},
    {cmd::End, 0}
};

CSScriptCommand Script016[] = { 
    {49, 0},
    {7, 30},
    {90, 0},
    {7, 60},
    {2, 0},
    {42, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script017[] = {
    {49, 0},
    {7, 10},
    {2, 0},
    {42, 1},
    {4, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script018[] = {
    {49, 0},
    {7, 10},
    {2, 0},
    {42, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script019[] = { 
    {161, 0},
    {12, 0},
    {321, 0},
    {7, 30},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script020[] = {
    {161, 0},
    {12, 0},
    {321, 0},
    {7, 30},
    {2, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script021[] = {
    {49, 2},
    {7, 30},
    {36, 6},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script022[] = {
    {49, 2},
    {36, 9},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script023[] = {
    {48, 0},
    {2, 0},
    {42, 5},
    {4, 0},
    {84, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script024[] = {
    {48, 0},
    {42, 5},
    {4, 0},
    {84, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script025[] = {
    {49, 0},
    {7, 10},
    {3, 0},
    {85, 0},
    {7, 25},
    {36, 1},
    {7, 30},
    {4, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script026[] = {
    {49, 0},
    {7, 10},
    {3, 0},
    {85, 0},
    {7, 25},
    {36, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script027[] = {
    {5, 0},
    {7, 30},
    {86, 0},
    {7, 40},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script028[] = {
    {87, 0},
    {7, 30},
    {45, 0},
    {cmd::End, 0}
};

CSScriptCommand Script029[] = {  // Triggered on level exit by clear/win
    {161, 0},
    {12, 0},
    {247, 0},
    {7, 30},
    {43, 0},
    {7, 15},
    {329, 0},
    {69, 0},
    {61, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script030[] = {  // Triggered on level exit by death
    {161, 0},
    {7, 30},
    {248, 0},
    {249, 0},
    {45, 0},
    {cmd::End, 0}
};

CSScriptCommand Script031[] = {
    {35, 1},
    {17, 0},
    {37, 0},
    {58, 0},
    {cmd::End, 0}
};

CSScriptCommand Script032[] = {
    {35, 1},
    {36, 7},
    {7, 30},
    {cmd::End, 0}
};

CSScriptCommand Script033[] = {
    {58, 0},
    {63, 0},
    {59, 0},
    {64, 0},
    {65, 0},
    {66, 0},
    {cmd::End, 0}
};

CSScriptCommand Script034[] = {
    {11, 0},
    {80, 0},
    {70, 0},
    {73, 0},
    {81, 0},
    {74, 0},
    {cmd::End, 0}
};

CSScriptCommand Script035[] = {
    {11, 0},
    {333, 0},
    {71, 60},
    {7, 60},
    {70, 0},
    {73, 0},
    {334, 0},
    {72, 0},
    {cmd::End, 0}
};

CSScriptCommand Script036[] = {
    {7, 30},
    {82, 0},
    {cmd::End, 0}
};

CSScriptCommand Script037[] = {
    {7, 20},
    {83, 0},
    {58, 0},
    {cmd::End, 0}
};

CSScriptCommand Script038[] = {
    {58, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script039[] = {  // Triggered on toad house win
    {58, 0},
    {51, 60},
    {52, 0},
    {7, 30},
    {54, 0},
    {53, 0},
    {cmd::End, 0}
};

CSScriptCommand Script040[] = {
    {58, 0},
    {7, 15},
    {55, 0},
    {56, 0},
    {cmd::End, 0}
};

CSScriptCommand Script041[] = {
    {58, 0},
    {7, 15},
    {57, 0},
    {56, 0},
    {cmd::End, 0}
};

CSScriptCommand Script042[] = {
    {58, 0},
    {27, 0},
    {28, 0},
    {23, 0},
    {30, 0},
    {7, 30},
    {26, 0},
    {cmd::End, 0}
};

CSScriptCommand Script043[] = {
    {58, 0},
    {23, 0},
    {30, 0},
    {7, 30},
    {26, 0},
    {cmd::End, 0}
};

CSScriptCommand Script044[] = {
    {18, 0},
    {16, 0},
    {7, 30},
    {32, 0},
    {cmd::End, 0}
};

CSScriptCommand Script045[] = {
    {25, 0},
    {cmd::End, 0}
};

CSScriptCommand Script046[] = {
    {36, 7},
    {cmd::End, 0}
};

CSScriptCommand Script047[] = {
    {24, 0},
    {17, 0},
    {cmd::End, 0}
};

CSScriptCommand Script048[] = {
    {29, 0},
    {cmd::End, 0}
};

CSScriptCommand Script049[] = {
    {88, 0},
    {cmd::End, 0}
};

CSScriptCommand Script050[] = {
    {89, 0},
    {cmd::End, 0}
};

CSScriptCommand Script051[] = {
    {314, 0},
    {35, 2},
    {99, 0},
    {102, 0},
    {316, 0},
    {103, 0},
    {105, 0},
    {106, 0},
    {7, 330},
    {42, 4},
    {58, 0},
    {107, 0},
    {208, 0},
    {209, 0},
    {210, 0},
    {110, 0},
    {109, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script052[] = {  // Peach's castle takeover cutscene 1
    {7, 10},
    {134, 0},
    {123, 0},
    {71, 30},
    {243, 30},
    {72, 0},
    {7, 90},
    {124, 0},
    {7, 50},
    {126, 0},
    {7, 50},
    {127, 0},
    {7, 80},
    {125, 0},
    {7, 186},
    {141, 60},
    {130, 0},
    {72, 0},
    {135, 0},
    {cmd::End, 0}
};

CSScriptCommand Script053[] = {
    {7, 10},
    {134, 0},
    {131, 0},
    {71, 30},
    {243, 30},
    {335, 0},
    {72, 0},
    {7, 120},
    {142, 0},
    {7, 560},
    {336, 0},
    {141, 60},
    {337, 0},
    {130, 0},
    {142, 1},
    {72, 0},
    {135, 0},
    {cmd::End, 0}
};

CSScriptCommand Script054[] = {
    {7, 10},
    {134, 0},
    {132, 0},
    {71, 30},
    {243, 30},
    {143, 0},
    {72, 0},
    {7, 90},
    {133, 0},
    {7, 360},
    {143, 1},
    {7, 120},
    {141, 60},
    {130, 0},
    {143, 2},
    {72, 0},
    {135, 0},
    {cmd::End, 0}
};

CSScriptCommand Script055[] = {
    {7, 60},
    {43, 0},
    {7, 15},
    {329, 0},
    {7, 60},
    {71, 30},
    {138, 0},
    {72, 0},
    {7, 60},
    {124, 0},
    {7, 60},
    {126, 0},
    {7, 60},
    {127, 0},
    {7, 120},
    {136, 60},
    {140, 0},
    {72, 0},
    {cmd::End, 0}
};

CSScriptCommand Script056[] = {
    {7, 60},
    {43, 0},
    {7, 15},
    {329, 0},
    {7, 60},
    {71, 30},
    {139, 0},
    {72, 0},
    {7, 60},
    {142, 0},
    {71, 30},
    {140, 0},
    {142, 1},
    {72, 0},
    {cmd::End, 0}
};

CSScriptCommand Script057[] = {
    {7, 60},
    {43, 0},
    {7, 15},
    {329, 0},
    {7, 60},
    {71, 30},
    {139, 0},
    {143, 0},
    {72, 0},
    {7, 60},
    {143, 1},
    {71, 30},
    {140, 0},
    {143, 2},
    {72, 0},
    {cmd::End, 0}
};

CSScriptCommand Script058[] = {
    {233, 0},
    {58, 0},
    {148, 0},
    {144, 2},
    {162, 0},
    {7, 120},
    {150, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script059[] = {
    {161, 0},
    {12, 0},
    {36, 9},
    {7, 30},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script060[] = {
    {161, 0},
    {152, 30},
    {12, 0},
    {36, 11},
    {153, 0},
    {7, 60},
    {315, 0},
    {7, 30},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script061[] = {
    {7, 0},
    {69, 0},
    {7, 30},
    {61, 0},
    {cmd::End, 0}
};

CSScriptCommand Script062[] = {
    {233, 0},
    {58, 0},
    {144, 2},
    {7, 30},
    {163, 0},
    {147, 0},
    {151, 0},
    {7, 60},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script063[] = {
    {161, 0},
    {12, 0},
    {36, 10},
    {7, 30},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script064[] = {
    {161, 0},
    {154, 0},
    {12, 0},
    {36, 11},
    {155, 0},
    {7, 60},
    {315, 0},
    {7, 60},
    {312, 1},
    {156, 0},
    {7, 60},
    {313, 0},
    {7, 60},
    {164, 0},
    {7, 60},
    {69, 0},
    {7, 30},
    {207, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script065[] = {
    {49, 1},
    {7, 60},
    {179, 0},
    {7, 10},
    {7, 4},
    {1, 0},
    {69, 0},
    {7, 30},
    {13, 0},
    {38, 0},
    {58, 1},
    {174, 0},
    {7, 60},
    {cmd::End, 0}
};

CSScriptCommand Script066[] = {
    {13, 0},
    {38, 0},
    {58, 0},
    {174, 0},
    {cmd::End, 0}
};

CSScriptCommand Script067[] = {
    {48, 0},
    {165, 0},
    {42, 0},
    {166, 0},
    {7, 20},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script068[] = {
    {48, 0},
    {42, 0},
    {4, 0},
    {166, 0},
    {6, 0},
    {cmd::End, 0}
};

CSScriptCommand Script069[] = {
    {49, 0},
    {7, 30},
    {165, 0},
    {42, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script070[] = {
    {49, 0},
    {7, 30},
    {165, 0},
    {42, 1},
    {166, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script071[] = {
    {49, 0},
    {7, 30},
    {167, 0},
    {7, 30},
    {36, 1},
    {166, 0},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script072[] = {
    {49, 0},
    {7, 30},
    {167, 0},
    {7, 30},
    {36, 1},
    {13, 0},
    {cmd::End, 0}
};

CSScriptCommand Script073[] = {
    {49, 0},
    {7, 60},
    {7, 60},
    {128, 0},
    {7, 60},
    {129, 0},
    {7, 60},
    {119, 0},
    {cmd::End, 0}
};

CSScriptCommand Script074[] = {
    {121, 0},
    {7, 120},
    {122, 0},
    {cmd::End, 0}
};

CSScriptCommand Script075[] = {
    {7, 10},
    {205, 0},
    {cmd::End, 0}
};

CSScriptCommand Script076[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 0},
    {223, 0},
    {111, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script077[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 0},
    {223, 0},
    {112, 0},
    {115, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script078[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 2},
    {223, 2},
    {114, 0},
    {75, 0},
    {113, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script079[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 3},
    {223, 2},
    {116, 0},
    {64, 0},
    {118, 0},
    {117, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script080[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 0},
    {223, 0},
    {112, 0},
    {115, 0},
    {235, 0},
    {208, 0},
    {209, 0},
    {210, 0},
    {207, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script081[] = {
    {7, 30},
    {144, 1},
    {7, 30},
    {222, 3},
    {223, 2},
    {116, 0},
    {64, 0},
    {118, 0},
    {117, 0},
    {235, 0},
    {208, 0},
    {209, 0},
    {210, 0},
    {207, 0},
    {146, 0},
    {cmd::End, 0}
};

CSScriptCommand Script082[] = {
    {180, 0},
    {cmd::End, 0}
};

CSScriptCommand Script083[] = {
    {180, 1},
    {cmd::End, 0}
};

CSScriptCommand Script084[] = {
    {58, 0},
    {7, 1},
    {188, 2},
    {190, 2},
    {192, 2},
    {194, 2},
    {200, 2},
    {7, 180},
    {198, 5},
    {197, 5},
    {196, 5},
    {7, 30},
    {cmd::End, 0}
};

CSScriptCommand Script085[] = {
    {58, 0},
    {199, 3},
    {cmd::End, 0}
};

CSScriptCommand Script086[] = {
    {201, 10},
    {7, 20},
    {202, 10},
    {cmd::End, 0}
};

CSScriptCommand Script087[] = {
    {201, 10},
    {7, 20},
    {cmd::End, 0}
};

CSScriptCommand Script088[] = {
    {35, 1},
    {7, 10},
    {36, 7},
    {7, 60},
    {cmd::End, 0}
};

CSScriptCommand Script089[] = {
    {204, 0},
    {58, 0},
    {33, 0},
    {7, 90},
    {34, 0},
    {37, 1},
    {cmd::End, 0}
};

CSScriptCommand Script090[] = {
    {204, 0},
    {58, 0},
    {33, 0},
    {7, 90},
    {37, 1},
    {203, 0},
    {cmd::End, 0}
};

CSScriptCommand Script091[] = {
    {7, 15},
    {181, 0},
    {cmd::End, 0}
};

CSScriptCommand Script092[] = {
    {206, 0},
    {50, 0},
    {41, 0},
    {cmd::End, 0}
};

CSScriptCommand Script093[] = {  // Triggered on first time in world (tour cutscene)
    {58, 0},
    {235, 0},
    {144, 1},
    {208, 0},
    {209, 0},
    {210, 0},
    {211, 0},
    {212, 0},
    {318, 0},
    {213, 0},
    {214, 0},
    {215, 0},
    {217, 0},
    {71, 0},
    {130, 0},
    {145, 1},
    {72, 0},
    {207, 0},
    {236, 0},
    {cmd::End, 0}
};

CSScriptCommand Script094[] = {
    {58, 0},
    {235, 0},
    {144, 1},
    {208, 0},
    {209, 0},
    {210, 0},
    {216, 0},
    {217, 0},
    {219, 0},
    {157, 0},
    {217, 0},
    {71, 0},
    {130, 0},
    {145, 1},
    {72, 0},
    {207, 0},
    {236, 0},
    {334, 0},
    {cmd::End, 0}
};

CSScriptCommand Script095[] = {  // Triggered on 2-1 or 5-1 clear (Nabbit cutscene / blast pipes tutorial)
    {233, 0},
    {7, 30},
    {258, 0},
    {7, 30},
    {237, 0},
    {58, 0},
    {238, 0},
    {239, 0},
    {58, 0},
    {240, 0},
    {251, 0},
    {252, 0},
    {271, 0},
    {268, 0},
    {58, 0},
    {269, 0},
    {7, 30},
    {253, 0},
    {268, 0},
    {58, 0},
    {264, 0},
    {274, 0},
    {241, 0},
    {242, 0},
    {244, 0},
    {7, 40},
    {284, 0},
    {245, 0},
    {71, 0},
    {246, 0},
    {260, 0},
    {72, 0},
    {265, 0},
    {266, 0},
    {276, 0},
    {254, 0},
    {58, 0},
    {255, 0},
    {278, 0},
    {267, 0},
    {7, 30},
    {279, 0},
    {280, 0},
    {281, 0},
    {7, 10},
    {282, 0},
    {7, 30},
    {222, 1},
    {223, 1},
    {111, 1},
    {283, 0},
    {7, 30},
    {293, 0},
    {234, 0},
    {226, 0},
    {cmd::End, 0}
};

CSScriptCommand Script096[] = {
    {233, 0},
    {7, 30},
    {258, 0},
    {257, 0},
    {272, 0},
    {262, 0},
    {271, 0},
    {268, 0},
    {58, 0},
    {269, 0},
    {7, 30},
    {273, 0},
    {264, 0},
    {241, 0},
    {242, 0},
    {71, 60},
    {243, 60},
    {72, 0},
    {244, 0},
    {7, 40},
    {284, 0},
    {245, 0},
    {71, 60},
    {246, 0},
    {260, 0},
    {72, 0},
    {265, 0},
    {266, 0},
    {277, 0},
    {275, 0},
    {278, 0},
    {267, 0},
    {7, 30},
    {279, 0},
    {280, 0},
    {281, 0},
    {7, 10},
    {282, 0},
    {7, 30},
    {222, 1},
    {223, 1},
    {111, 1},
    {283, 0},
    {7, 30},
    {293, 0},
    {234, 0},
    {226, 0},
    {cmd::End, 0}
};

CSScriptCommand Script097[] = {
    {289, 0},
    {287, 0},
    {250, 0},
    {244, 0},
    {7, 40},
    {284, 0},
    {290, 0},
    {288, 0},
    {282, 0},
    {cmd::End, 0}
};

CSScriptCommand Script098[] = {
    {89, 0},
    {289, 0},
    {71, 60},
    {286, 0},
    {250, 0},
    {72, 0},
    {244, 0},
    {7, 40},
    {284, 0},
    {290, 0},
    {71, 60},
    {246, 0},
    {282, 0},
    {72, 0},
    {cmd::End, 0}
};

CSScriptCommand Script099[] = {
    {204, 0},
    {58, 0},
    {33, 0},
    {7, 90},
    {37, 1},
    {cmd::End, 0}
};

CSScriptCommand Script100[] = {
    {7, 60},
    {230, 1},
    {299, 0},
    {7, 30},
    {231, 0},
    {338, 0},
    {294, 0},
    {295, 0},
    {301, 0},
    {7, 30},
    {296, 0},
    {297, 0},
    {323, 0},
    {300, 0},
    {7, 30},
    {71, 0},
    {130, 0},
    {72, 0},
    {339, 0},
    {232, 1},
    {7, 30},
    {cmd::End, 0}
};

CSScriptCommand Script101[] = {
    {7, 10},
    {230, 2},
    {299, 0},
    {232, 2},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script102[] = {
    {7, 10},
    {230, 3},
    {299, 0},
    {232, 3},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script103[] = {
    {7, 10},
    {230, 4},
    {299, 0},
    {232, 4},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script104[] = {
    {7, 10},
    {230, 5},
    {299, 0},
    {322, 0},
    {232, 5},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script105[] = {
    {7, 10},
    {230, 0},
    {304, 0},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script106[] = {
    {7, 30},
    {230, 0},
    {304, 0},
    {303, 0},
    {306, 0},
    {308, 0},
    {309, 60},
    {310, 0},
    {7, 30},
    {149, 0},
    {309, 120},
    {303, 0},
    {307, 0},
    {308, 0},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script107[] = {
    {220, 0},
    {309, 60},
    {310, 0},
    {7, 30},
    {149, 0},
    {309, 120},
    {230, 4},
    {299, 0},
    {232, 4},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script108[] = {
    {7, 30},
    {230, 9},
    {305, 0},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script109[] = {
    {7, 30},
    {298, 0},
    {cmd::End, 0}
};

CSScriptCommand Script110[] = {
    {230, 6},
    {302, 0},
    {7, 30},
    {231, 0},
    {cmd::End, 0}
};

CSScriptCommand Script111[] = {  // Triggered on world load, after all other scripts
    {228, 0},
    {cmd::End, 0}
};

CSScriptCommand Script112[] = {
    {228, 0},
    {cmd::End, 0}
};

CSScriptCommand Script113[] = {
    {7, 30},
    {248, 0},
    {249, 0},
    {45, 0},
    {cmd::End, 0}
};

CSScriptCommand Script114[] = {  // Initial miiverse setup tutorial popup (triggered after clearing 1-T or 1-S)
    {89, 0},
    {cmd::End, 0}
};

CSScriptCommand Script115[] = {
    {7, 30},
    {342, 0},
    {45, 0},
    {cmd::End, 0}
};

CSScriptCommand Script116[] = {
    {58, 0},
    {324, 0},
    {331, 0},
    {7, 10},
    {330, 0},
    {7, 20},
    {326, 0},
    {58, 0},
    {cmd::End, 0}
};

CSScriptCommand Script117[] = {  // Triggered on initial baby yoshi meet
    {58, 0},
    {47, 0},
    {58, 0},
    {324, 0},
    {325, 0},
    {330, 0},
    {328, 0},
    {326, 0},
    {58, 0},
    {cmd::End, 0}
};

CSScriptCommand Script118[] = {
    {7, 30},
    {332, 0},
    {cmd::End, 0}
};

CSScriptCommand Script119[] = {
    {291, 0},
    {cmd::End, 0}
};

CSScriptCommand Script120[] = {
    {292, 0},
    {cmd::End, 0}
};

CSScript CSScriptsTable[] = {
    {255, Script000},
    {128, Script001},
    {170, Script002},
    {170, Script003},
    {20, Script004},
    {100, Script005},
    {100, Script006},
    {128, Script007},
    {128, Script008},
    {128, Script009},
    {150, Script010},
    {150, Script011},
    {150, Script012},
    {150, Script013},
    {220, Script014},
    {220, Script015},
    {200, Script016},
    {200, Script017},
    {200, Script018},
    {200, Script019},
    {200, Script020},
    {150, Script021},
    {150, Script022},
    {128, Script023},
    {128, Script024},
    {150, Script025},
    {150, Script026},
    {150, Script027},
    {150, Script028},
    {190, Script029},
    {70, Script030},
    {150, Script031},
    {150, Script032},
    {180, Script033},
    {128, Script034},
    {128, Script035},
    {128, Script036},
    {160, Script037},
    {128, Script038},
    {140, Script039},
    {170, Script040},
    {170, Script041},
    {128, Script042},
    {128, Script043},
    {128, Script044},
    {128, Script045},
    {150, Script046},
    {150, Script047},
    {128, Script048},
    {40, Script049},
    {253, Script050},
    {128, Script051},
    {185, Script052},
    {185, Script053},
    {185, Script054},
    {185, Script055},
    {185, Script056},
    {185, Script057},
    {128, Script058},
    {70, Script059},
    {220, Script060},
    {200, Script061},
    {128, Script062},
    {70, Script063},
    {240, Script064},
    {200, Script065},
    {195, Script066},
    {128, Script067},
    {128, Script068},
    {200, Script069},
    {200, Script070},
    {150, Script071},
    {150, Script072},
    {128, Script073},
    {128, Script074},
    {128, Script075},
    {128, Script076},
    {128, Script077},
    {128, Script078},
    {128, Script079},
    {128, Script080},
    {128, Script081},
    {140, Script082},
    {150, Script083},
    {128, Script084},
    {128, Script085},
    {128, Script086},
    {128, Script087},
    {150, Script088},
    {128, Script089},
    {128, Script090},
    {128, Script091},
    {40, Script092},
    {128, Script093},
    {128, Script094},
    {128, Script095},
    {128, Script096},
    {60, Script097},
    {60, Script098},
    {128, Script099},
    {169, Script100},
    {165, Script101},
    {164, Script102},
    {163, Script103},
    {162, Script104},
    {168, Script105},
    {168, Script106},
    {168, Script107},
    {168, Script108},
    {20, Script109},
    {167, Script110},
    {15, Script111},
    {15, Script112},
    {128, Script113},
    {30, Script114},
    {128, Script115},
    {128, Script116},
    {128, Script117},
    {190, Script118},
    {128, Script119},
    {128, Script120},
};
