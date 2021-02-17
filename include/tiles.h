#pragma once

namespace TileId {

enum TileIdType
{
    Invalid = -1,
    Null = 0,

    InvBlockSolid,
    InvVineStopper,
    InvBlockCoin,
    InvBlockFireFlower,
    InvBlockStar,
    InvBlock1UP,
    InvBlockVine,
    InvBlockMiniMushroom,
    InvBlockPropeller,
    InvBlockPenguin,
    InvBlockSolidOnTop,
    InvBlockSolidHalf,
    InvBlockIceFlower,
    InvClimbablePole,
    InvRope, // Not functional?
    InvBlockAcorn = 29,
    InvMuncher = 45,

    BrickBlockFireFlower = 16,
    BrickBlockStar,
    BrickBlock1UP,
    BrickBlockVine,
    BrickBlockMiniMushroom,
    BrickBlockPropeller,
    BrickBlockPenguin,
    BrickBlockIceFlower,
    BrickBlockAcorn,
    BrickBlockYoshiEgg,
    BrickBlockCoin,
    BrickBlockCoin10,
    BrickBlock = 48,

    CoinDashMultiplayer = 28,
    Coin = 30,
    CoinDash,

    QBlockFireFlower,
    QBlockStar,
    QBlockCoinStar,
    QBlockVine,
    QBlockMiniMushroom,
    QBlockPropeller,
    QBlockPenguin,
    QBlockIceFlower,
    QBlockAcorn,
    QBlockYoshiEgg,
    QBlockSpring,
    QBlock = 49,

    Bridge = 43,
    MiniPassage,

    BlueCoin = 46,
    BlueCoin_CoreCoin,

    BlockUsed = 50,
    BlockWood,
    BlockStone,
    BlockBlue,
    BlockDonutLift,
    BlockRed = 208,

    Fragment_BrickBlock_0 = 55,
    Fragment_BrickBlock_1,
    Fragment_BrickBlock_2,

    Fragment_QBlock_0,
    Fragment_QBlock_1,
    Fragment_QBlock_2,

    Fragment_BlockRed_0,
    Fragment_BlockRed_1,
    Fragment_BlockRed_2,

    Fragment_BlockUsed_0 = 71,
    Fragment_BlockUsed_1,
    Fragment_BlockUsed_2,

    Fragment_BlockWood_0,
    Fragment_BlockWood_1,
    Fragment_BlockWood_2,

    Fragment_BlockStone_0,
    Fragment_BlockStone_1,
    Fragment_BlockStone_2,

    // ...

    ConveyorRight_0 = 144,
    ConveyorRight_1,
    ConveyorRight_2,

    ConveyorLeft_0,
    ConveyorLeft_1,
    ConveyorLeft_2,

    ConveyorRightFast_0 = 160,
    ConveyorRightFast_1,
    ConveyorRightFast_2,

    ConveyorLeftFast_0,
    ConveyorLeftFast_1,
    ConveyorLeftFast_2,

    // ...

    Num_Pa0Tiles = 256,
    Num_Pa1Tiles = Num_Pa0Tiles + 256,
    Num_Pa2Tiles = Num_Pa1Tiles + 256,
    Num_Pa3Tiles = Num_Pa2Tiles + 256
};

}
