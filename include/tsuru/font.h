#pragma once

#include "agl/utl/devtools.h"
#include "tsuru/gtx.h"

class BitmapFont {
public:
    struct CharMapping {
        const u8 row;
        const u8 column;
        const char character;
    } aligned(4);

    BitmapFont() : loaded(false), cursor(0.0f) {};
    BitmapFont(const char* fontFile, u32 identity, u32 charWidthPixels, u32 charHeightPixels, const CharMapping charmap[] = nullptr) {
        this->load(fontFile, identity, charWidthPixels, charHeightPixels, charmap);
    }

    // @param fontFile: The path of the GTX font texture file to load (Starting at ./content/Common)
    // @param identity: The number of characters in the main diagonal line of the font texture,
    // or the number of characters in a row, which must be the same as in a column.
    //
    // @warning Fonts with a different number of characters in a row and column are NOT supported.
    void load(const char* fontFile, u32 identity, u32 charWidthPixels, u32 charHeightPixels, const CharMapping charmap[] = nullptr) {
        this->cursor = 0.0f;
        this->gtx.load(fontFile);
        this->identity = identity;
        this->uvOffset = identity / 2.0f + 0.5f;
        this->uvScale = 1.0f / identity;
        this->charWidth = charWidthPixels;
        this->charHeight = charHeightPixels;
        this->charcount = identity * identity;
        this->charmap = charmap;
        this->loaded = true;
    };

    Vec2f getUVForCharAt(u8 row, u8 column) {
        // Yes it is meant to be inverted from the args
        return Vec2f(column - this->uvOffset, row - this->uvOffset);
    }

    Vec2f getUVForChar(char character) {
        if (this->charmap != nullptr) {
            for (u32 i = 0; i < this->charcount; i++) {
                if (this->charmap[i].character == character) {
                    return this->getUVForCharAt(this->charmap[i].row, this->charmap[i].column);
                }
            }
        }
        return Vec2f(NAN());
    }

    void renderText(Mtx44& viewProjection, const char* text) {
        u32 len = strlen(text);
        u32 cursor = 0;
        Mtx34 qmtx;

        for (u32 i = 0; i < len; i++) {
            Vec2f charUV = this->getUVForChar(text[i]);
            qmtx.makeSRT(Vec2f(this->charWidth, this->charHeight), 0, Vec3f(this->cursor.x + this->charWidth * cursor, this->cursor.y, 0.0f));
            agl::utl::DevTools::drawTextureTexCoord(this->gtx.texture, qmtx, viewProjection, this->uvScale, 0, charUV);
            cursor++;
        }
        this->cursor.x += this->charWidth * cursor;
    }

    void renderText(Mtx44& viewProjection, const char* text, Vec2f pos) {
        u32 len = strlen(text);
        u32 cursor = 0;
        Mtx34 qmtx;

        for (u32 i = 0; i < len; i++) {
            Vec2f charUV = this->getUVForChar(text[i]);
            qmtx.makeSRT(Vec2f(this->charWidth, this->charHeight), 0, Vec3f(pos.x + this->charWidth * cursor, pos.y, 0.0f));
            agl::utl::DevTools::drawTextureTexCoord(this->gtx.texture, qmtx, viewProjection, this->uvScale, 0, charUV);
            cursor++;
        }
        this->cursor = pos;
        this->cursor.x += this->charWidth * cursor;
    }

    void prevline(f32 startMargin = 0.0f) {
        this->cursor.x = startMargin;
        this->cursor.y += this->charHeight;
    }
    void newline(f32 startMargin = 0.0f) {
        this->cursor.x = startMargin;
        this->cursor.y -= this->charHeight;
    }

    void renderBitmap(Mtx44& viewProjection, Vec2f pos = Vec2f(0.0f)) {
        u32 cursor = 0;
        u32 line = 0;
        Mtx34 qmtx;

        for (u32 r = 1; r <= this->identity; r++) {
            for (u32 c = 1; c <= this->identity; c++) {
                Vec2f charUV = this->getUVForCharAt(r, c);
                qmtx.makeSRT(Vec2f(this->charWidth, this->charHeight), 0, Vec3f(pos.x + this->charWidth * cursor, pos.y - (this->charHeight * line), 0.0f));
                agl::utl::DevTools::drawTextureTexCoord(this->gtx.texture, qmtx, viewProjection, this->uvScale, 0, charUV);
                cursor++;
            }
            line++;
            cursor = 0;
        }
    }

    void __debugPrint() {
        if (this->charmap != nullptr) {
            for (u32 i = 0; i < this->charcount; i++) {
                char c = this->charmap[i].character;
                PRINT("<code: ", (u32)c, " + char: ", c, " + uv: ", this->getUVForChar(c), ">");
            }
        }
    }

    agl::TextureSampler texture() { return this->gtx.texture; }
    u32 rows() { return this->identity; }
    u32 columns() { return this->identity; }
    u32 charW() { return this->charWidth; }
    u32 charH() { return this->charHeight; }

    Vec2f cursor;

protected:
    GTX gtx;
    u32 identity;
    f32 uvOffset;
    f32 uvScale;
    u32 charWidth;
    u32 charHeight;
    u32 charcount;
    const CharMapping* charmap;
    bool loaded;
};
