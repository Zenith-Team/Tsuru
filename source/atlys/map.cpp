#include "tsuru/atlys/map.h"
#include "ghs.h"
#include "dynlibs/os/functions.h"
#include "sead/filedevice.h"
#include "sead/heapmgr.h"
#include "sead/heap.h"
#include "log.h"

// Reduce clutter
#define LOAD_MAP_SECTOR(SECTOR, COUNT, TARGET)                                                                  \
    {                                                                                                           \
        void* buffer = new(nullptr, sead::FileDevice::sBufferMinAlignment) u8[sizeof(SECTOR) * COUNT];          \
        TARGET = (SECTOR*) buffer;                                                                              \
        u32 bytesRead = handle.read((u8*) TARGET, sizeof(SECTOR) * COUNT);                                      \
                                                                                                                \
        if (bytesRead != sizeof(SECTOR) * COUNT) {                                                              \
            LOG("Read size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(SECTOR) * COUNT); \
            return;                                                                                             \
        }                                                                                                       \
    }

Atlys::Map::Data::Data(const sead::SafeString& path)
    : header(nullptr)
    , worlds(nullptr)
    , nodes(nullptr)
    , layers(nullptr)
    , sprites(nullptr)
    , animTexs(nullptr)
    , loaded(false)
{
    const sead::SafeString& file = path;

    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, file, sead::FileDevice::FileOpenFlag_ReadWrite, 0);

    LOAD_MAP_SECTOR(Header, 1, this->header);
    LOAD_MAP_SECTOR(WorldInfo, this->header->worldCount, this->worlds);
    LOAD_MAP_SECTOR(Node, this->header->nodeCount, this->nodes);
    LOAD_MAP_SECTOR(Layer, this->header->layerCount, this->layers);
    LOAD_MAP_SECTOR(Sprite, this->header->spriteCount, this->sprites);
    LOAD_MAP_SECTOR(AnimTex, this->header->animTexCount, this->animTexs);

    this->loaded = true;
}

Atlys::Map::Data::~Data() {
    if (this->header)   delete         this->header;   this->header = nullptr;
    if (this->worlds)   delete[] (u8*) this->worlds;   this->worlds = nullptr;
    if (this->nodes)    delete[] (u8*) this->nodes;    this->nodes = nullptr;
    if (this->layers)   delete[] (u8*) this->layers;   this->layers = nullptr;
    if (this->sprites)  delete[] (u8*) this->sprites;  this->sprites = nullptr;
    if (this->animTexs) delete[] (u8*) this->animTexs; this->animTexs = nullptr;
}

Atlys::Map::Map(const sead::SafeString& path)
    : info(nullptr)
    , worlds(nullptr)
    , nodes(nullptr)
    , layers(nullptr)
    , sprites(nullptr)
    , animTexs(nullptr)
{
    LOG("Loading map: %s", path.cstr());
    Data data(path);

    if (!data.loaded) {
        LOG("Map data failed to load");
        return;
    }

    LOG("Loaded map file, dynamicizing... (If we crash here then the file is not a valid map)");

    // Allocate
    this->info = new Data::Header;
    if (data.header->worldCount > 0)   this->worlds   = new WorldInfo[data.header->worldCount];
    if (data.header->nodeCount  > 0)   this->nodes    = new Node[data.header->nodeCount];
    if (data.header->layerCount > 0)   this->layers   = new Layer[data.header->layerCount];
    if (data.header->spriteCount > 0)  this->sprites  = new Data::Sprite[data.header->spriteCount];
    if (data.header->animTexCount > 0) this->animTexs = new AnimTex[data.header->animTexCount];

    LOG("Allocated dynamic data");

    // Copy
    OSBlockMove(this->info, data.header, sizeof(Data::Header), 0);                                                                      // Header
    for (u32 i = 0; i < data.header->worldCount; i++)   OSBlockMove(&this->worlds[i],   &data.worlds[i],   sizeof(Data::WorldInfo), 0); // Worlds
    for (u32 i = 0; i < data.header->nodeCount; i++)    OSBlockMove(&this->nodes[i],    &data.nodes[i],    sizeof(Data::Node),      0); // Nodes
    for (u32 i = 0; i < data.header->layerCount; i++)   OSBlockMove(&this->layers[i],   &data.layers[i],   sizeof(Data::Layer),     0); // Layers
    for (u32 i = 0; i < data.header->spriteCount; i++)  OSBlockMove(&this->sprites[i],  &data.sprites[i],  sizeof(Data::Sprite),    0); // Sprites
    for (u32 i = 0; i < data.header->animTexCount; i++) OSBlockMove(&this->animTexs[i], &data.animTexs[i], sizeof(AnimTex),         0); // AnimTexs

    // Additional setup

    for (u32 i = 0; i < data.header->nodeCount; i++) {
        for (u32 j = 0; j < 4; j++) {
            if (this->nodes[i].type == Node::Type_Normal) {
                if (this->nodes[i].Normal_connections[j].flags & Node::Connection::Flag_AlwaysUnlocked)
                    this->findNodeByID(this->nodes[i].Normal_connections[j].node)->unlocked = true;
            } else if (this->nodes[i].type == Node::Type_Level) {
                if (this->nodes[i].Level_connections[j].flags & Node::Connection::Flag_AlwaysUnlocked)
                    this->findNodeByID(this->nodes[i].Level_connections[j].node)->unlocked = true;
            }
        }
    }

    for (u32 i = 0; i < data.header->layerCount; i++) {
        this->layers[i].gtx.texture.magFilter = this->layers[i].scaleFilter;
        this->layers[i].gtx.texture.minFilter = this->layers[i].scaleFilter;
    }

    LOG("Map \"%s\" loaded and ready to go!", path.cstr());
}

Atlys::Map::~Map() {
    if (this->info)     delete   this->info;     this->info    = nullptr;
    if (this->worlds)   delete[] this->worlds;   this->worlds  = nullptr;
    if (this->nodes)    delete[] this->nodes;    this->nodes   = nullptr;
    if (this->layers)   delete[] this->layers;   this->layers  = nullptr;
    if (this->sprites)  delete[] this->sprites;  this->sprites = nullptr;
    if (this->animTexs) delete[] this->animTexs; this->animTexs = nullptr;
}

Atlys::Map::Node* Atlys::Map::findNodeByID(u32 id) {
    for (u32 i = 0; i < this->info->nodeCount; i++) {
        if (this->nodes[i].id == id)
            return &this->nodes[i];
    }

    // Couldn't find node :(
    return nullptr;
}
