#pragma once

namespace sead {

class IDelegate {
public:
    virtual void invoke() = 0;

    void operator()() {
        return this->invoke();
    }

    virtual IDelegate* clone(Heap*) const = 0;
};

template <typename A1, typename A2>
class IDelegate2 {
public:
    virtual void invoke(A1 a1, A2 a2) = 0;

    void operator()(A1 a1, A2 a2) {
        return this->invoke(a1, a2);
    }
};

}
