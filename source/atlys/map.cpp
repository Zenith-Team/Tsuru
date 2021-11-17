#include "tsuru/atlys/map.h"
#include "dynlibs/os/functions.h"

Atlys::Map::Data::Data(const sead::SafeString& path)
    : header(nullptr)
    , worlds(nullptr)
    , nodes(nullptr)
    , layers(nullptr)
    , sprites(nullptr)
    , loaded(false)
{
    // TODO: Concatenate path with .atlys
    const sead::SafeString& file = path;

    u32 bytesRead = 0;
    sead::FileHandle handle;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, file, sead::FileDevice::FileOpenFlag_ReadOnly, 0);

    // Header
    Header* header = new Header();
    bytesRead = handle.read((u8*) header, sizeof(Header));

    if (bytesRead != sizeof(Header)) {
        LOG("Atlys header read size mismatch, reading file at: %s, expected size: %x, read size: %x", file.cstr(), sizeof(Header), bytesRead);
        return;
    }

    if (header->magic[0] != 'A' || header->magic[1] != 'T' || header->magic[2] != 'L' || header->magic[3] != 'S') {
        LOG("Atlys header magic mismatch, reading file at: %s, expected: ATLS, read: %c%c%c%c", file.cstr(), header->magic[0], header->magic[1], header->magic[2], header->magic[3]);
        return;
    }

    // Worlds
    WorldInfo* worlds = new WorldInfo[header->nodeCount];
    bytesRead = handle.read((u8*) worlds, sizeof(WorldInfo) * header->nodeCount);

    if (bytesRead != sizeof(WorldInfo) * header->nodeCount) {
        LOG("Atlys world read size mismatch, reading file at: %s, expected size: %x, read size: %x", file.cstr(), sizeof(WorldInfo) * header->worldCount, bytesRead);
        return;
    }

    // Nodes
    Node* nodes = new Node[header->nodeCount];
    bytesRead = handle.read((u8*) nodes, sizeof(Node) * header->nodeCount);

    if (bytesRead != sizeof(Node) * header->nodeCount) {
        LOG("Atlys node read size mismatch, reading file at: %s, expected size: %x, read size: %x", file.cstr(), sizeof(Node) * header->nodeCount, bytesRead);
        return;
    }

    // Layers
    Layer* layers = new Layer[header->layerCount];
    bytesRead = handle.read((u8*) layers, sizeof(Layer) * header->layerCount);

    if (bytesRead != sizeof(Layer) * header->layerCount) {
        LOG("Atlys layer read size mismatch, reading file at: %s, expected size: %x, read size: %x", file.cstr(), sizeof(Layer) * header->layerCount, bytesRead);
        return;
    }

    // Sprites
    Sprite* sprites = new Sprite[header->spriteCount];
    bytesRead = handle.read((u8*) sprites, sizeof(Sprite) * header->spriteCount);

    if (bytesRead != sizeof(Sprite) * header->spriteCount) {
        LOG("Atlys sprite read size mismatch, reading file at: %s, expected size: %x, read size: %x", file.cstr(), sizeof(Sprite) * header->spriteCount, bytesRead);
        return;
    }

    this->loaded = true;
}

Atlys::Map::Data::~Data() {
    delete header;  this->header  = nullptr;
    delete worlds;  this->worlds  = nullptr;
    delete nodes;   this->nodes   = nullptr;
    delete layers;  this->layers  = nullptr;
    delete sprites; this->sprites = nullptr;
}

Atlys::Map::Map(const sead::SafeString& path)
    : info(nullptr)
    , worlds(nullptr)
    , nodes(nullptr)
    , layers(nullptr)
    , sprites(nullptr)
{
    Data data(path);
    
    if (!data.loaded) {
        LOG("Map data failed to load");
        return;
    }

    // Allocate
    this->info    = new Data::Header;
    this->worlds  = new WorldInfo[data.header->worldCount];
    this->nodes   = new Node[data.header->nodeCount];
    this->layers  = new Layer[data.header->layerCount];
    this->sprites = new Data::Sprite[data.header->spriteCount];

    // Copy
    OSBlockMove(this->info, data.header, sizeof(Data::Header), 0);                                                                // Header
    for (u32 i = 0; i < data.header->worldCount; i++) this->worlds[i].fillData(data.worlds[i]);                                   // Worlds
    for (u32 i = 0; i < data.header->nodeCount; i++) this->nodes[i].fillData(data.nodes[i]);                                      // Nodes
    for (u32 i = 0; i < data.header->layerCount; i++) this->layers[i].fillData(data.layers[i]);                                   // Layers
    for (u32 i = 0; i < data.header->spriteCount; i++) OSBlockMove(&this->sprites[i], &data.sprites[i], sizeof(Data::Sprite), 0); // Sprites
}

Atlys::Map::~Map() {
    delete this->info;    this->info    = nullptr;
    delete this->worlds;  this->worlds  = nullptr;
    delete this->nodes;   this->nodes   = nullptr;
    delete this->layers;  this->layers  = nullptr;
    delete this->sprites; this->sprites = nullptr;
}
