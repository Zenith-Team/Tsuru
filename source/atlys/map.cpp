#include "tsuru/atlys/map.h"
#include "dynlibs/os/functions.h"
#include "sead/heapmgr.h"
#include "sead/heap.h"
#include "log.h"

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

    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, file, sead::FileDevice::FileOpenFlag_ReadWrite, 0);

    LOG("Reading header");
    this->header = new(nullptr, sead::FileDevice::sBufferMinAlignment) Header;
    u32 bytesRead = handle.read((u8*) this->header, sizeof(Header));

    if (!handle.device) {
        LOG("File does not exist");
        return;
    }

    if (bytesRead != sizeof(Header)) {
        LOG("Header size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(Header));
        return;
    }

    LOG("Reading %u worlds", this->header->worldCount);

    void* worldBuffer = new(nullptr, sead::FileDevice::sBufferMinAlignment) u8[sizeof(WorldInfo) * this->header->worldCount];
    this->worlds = (WorldInfo*) worldBuffer;
    bytesRead = handle.read((u8*) this->worlds, sizeof(WorldInfo) * this->header->worldCount);

    if (bytesRead != sizeof(WorldInfo) * this->header->worldCount) {
        LOG("World info size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(WorldInfo) * this->header->worldCount);
        return;
    }

    LOG("Reading %u nodes", this->header->nodeCount);

    void* nodeBuffer = new(nullptr, sead::FileDevice::sBufferMinAlignment) u8[sizeof(Node) * this->header->nodeCount];
    this->nodes = (Node*) nodeBuffer;
    bytesRead = handle.read((u8*) this->nodes, sizeof(Node) * this->header->nodeCount);

    if (bytesRead != sizeof(Node) * this->header->nodeCount) {
        LOG("Node size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(Node) * this->header->nodeCount);
        return;
    }

    LOG("Reading %u layers", this->header->layerCount);

    void* layerBuffer = new(nullptr, sead::FileDevice::sBufferMinAlignment) u8[sizeof(Layer) * this->header->layerCount];
    this->layers = (Layer*) layerBuffer;
    bytesRead = handle.read((u8*) this->layers, sizeof(Layer) * this->header->layerCount);

    if (bytesRead != sizeof(Layer) * this->header->layerCount) {
        LOG("Layer size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(Layer) * this->header->layerCount);
        return;
    }

    LOG("Reading %u sprites", this->header->spriteCount);

    void* spriteBuffer = new(nullptr, sead::FileDevice::sBufferMinAlignment) u8[sizeof(Sprite) * this->header->spriteCount];
    this->sprites = (Sprite*) spriteBuffer;
    bytesRead = handle.read((u8*) this->sprites, sizeof(Sprite) * this->header->spriteCount);

    if (bytesRead != sizeof(Sprite) * this->header->spriteCount) {
        LOG("Sprite size mismatch, read size: 0x%x, expected size: 0x%x", bytesRead, sizeof(Sprite) * this->header->spriteCount);
        return;
    }

    this->loaded = true;
}

Atlys::Map::Data::~Data() {
    delete this->header;    this->header  = nullptr;
    delete[] this->worlds;  this->worlds  = nullptr;
    delete[] this->nodes;   this->nodes   = nullptr;
    delete[] this->layers;  this->layers  = nullptr;
    delete[] this->sprites; this->sprites = nullptr;
}

Atlys::Map::Map(const sead::SafeString& path)
    : info(nullptr)
    , worlds(nullptr)
    , nodes(nullptr)
    , layers(nullptr)
    , sprites(nullptr)
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
    if (data.header->worldCount > 0) this->worlds = new WorldInfo[data.header->worldCount];
    if (data.header->nodeCount  > 0) this->nodes  = new Node[data.header->nodeCount];
    if (data.header->layerCount > 0) this->layers = new Layer[data.header->layerCount];
    if (data.header->spriteCount > 0) this->sprites = new Data::Sprite[data.header->spriteCount];

    LOG("Allocated dynamic data");

    // Copy
    OSBlockMove(this->info, data.header, sizeof(Data::Header), 0);                                                                   // Header
    for (u32 i = 0; i < data.header->worldCount; i++)  OSBlockMove(&this->worlds[i],  &data.worlds[i],  sizeof(Data::WorldInfo), 0); // Worlds
    for (u32 i = 0; i < data.header->nodeCount; i++)   OSBlockMove(&this->nodes[i],   &data.nodes[i],   sizeof(Data::Node), 0);      // Nodes
    for (u32 i = 0; i < data.header->layerCount; i++)  OSBlockMove(&this->layers[i],  &data.layers[i],  sizeof(Data::Layer), 0);     // Layers
    for (u32 i = 0; i < data.header->spriteCount; i++) OSBlockMove(&this->sprites[i], &data.sprites[i], sizeof(Data::Sprite), 0);    // Sprites

    LOG("Map \"%s\" loaded and ready to go!", path.cstr());
}

Atlys::Map::~Map() {
    delete this->info;    this->info    = nullptr;
    delete[] this->worlds;  this->worlds  = nullptr;
    delete[] this->nodes;   this->nodes   = nullptr;
    delete[] this->layers;  this->layers  = nullptr;
    delete[] this->sprites; this->sprites = nullptr;
}

Atlys::Map::Node* Atlys::Map::findNodeByID(u32 id) {
    for (u32 i = 0; i < this->info->nodeCount; i++) {
        if (this->nodes[i].id == id)
            return &this->nodes[i];
    }

    // Couldn't find node :(
    return nullptr;
}
