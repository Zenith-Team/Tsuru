#pragma once

#include "sead/safestring.h"
#include "agl/shaderprogram.h"

namespace agl {

class ShaderLocation {
public:
    ShaderLocation()
        : vs(-1)
        , ps(-1)
        , gs(-1)
    { }

    s16 vs;
    s16 ps;
    s16 gs;
};

static_assert(sizeof(ShaderLocation) == 0x6, "agl::ShaderLocation size mismatch");

class UniformLocation : public sead::INamable, public ShaderLocation {
public:
    UniformLocation()
        : sead::INamable("Undefined")
    { }

    explicit UniformLocation(const sead::SafeString& name)
        : sead::INamable(name)
    { }

    UniformLocation(const sead::SafeString& name, const ShaderProgram& program)
        : sead::INamable(name)
    {
        this->search(program);
    }

    UniformLocation& operator=(const UniformLocation& rhs) {
        this->setName(rhs.getName());
        ShaderLocation::operator=(static_cast<const ShaderLocation&>(rhs));
        return *this;
    }

    void search(const ShaderProgram& program);
};

class UniformBlockLocation : public sead::INamable, public ShaderLocation {
public:
    UniformBlockLocation()
        : sead::INamable("Undefined")
    { }

    explicit UniformBlockLocation(const sead::SafeString& name)
        : sead::INamable(name)
    { }

    UniformBlockLocation(const sead::SafeString& name, const ShaderProgram& program)
        : sead::INamable(name)
    {
        this->search(program);
    }

    UniformBlockLocation& operator=(const UniformBlockLocation& rhs) {
        this->setName(rhs.getName());
        ShaderLocation::operator=(static_cast<const ShaderLocation&>(rhs));
        return *this;
    }

    void search(const ShaderProgram& program);
};

class SamplerLocation : public sead::INamable, public ShaderLocation {
public:
    SamplerLocation()
        : sead::INamable("Undefined")
    { }

    explicit SamplerLocation(const sead::SafeString& name)
        : sead::INamable(name)
    { }

    SamplerLocation(const sead::SafeString& name, const ShaderProgram& program)
        : sead::INamable(name)
    {
        this->search(program);
    }

    SamplerLocation& operator=(const SamplerLocation& rhs) {
        this->setName(rhs.getName());
        ShaderLocation::operator=(static_cast<const ShaderLocation&>(rhs));
        return *this;
    }

    void search(const ShaderProgram& program);
};

class AttributeLocation : sead::INamable, ShaderLocation {
public:
    AttributeLocation()
        : sead::INamable("Undefined")
    { }

    explicit AttributeLocation(const sead::SafeString& name)
        : sead::INamable(name)
    { }

    AttributeLocation(const sead::SafeString& name, const ShaderProgram& program)
        : sead::INamable(name)
    {
        this->search(program);
    }

    AttributeLocation& operator=(const AttributeLocation& rhs) {
        this->setName(rhs.getName());
        ShaderLocation::operator=(static_cast<const ShaderLocation&>(rhs));
        return *this;
    }

    void search(const ShaderProgram& program);

    s32 getVertexLocation() const { return this->vs; }

private:
    s16 vs;
};

}
