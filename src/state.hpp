//
//#pragma    once
//#include    "__common.hpp"
//
// namespace p201 {
//
// enum    direction_state : uint32_t
//{
//    left = 0x0,
//    right = 0x1,
//    up = 0x2,
//    down = 0x3,
//};
// enum    movement_state : uint32_t
//{
//    idle = 0x4,
//    walk = 0x5,
//    run = 0x6,
//    dash = 0x7,
//};
// enum    attack_state : uint32_t
//{
//    neutral = 0x8,
//    melee = 0x9,
//    ranged = 0xa,
//};
// class    state
//{
// public:
//    friend bool     operator ==(const state& __a, const state& __b);
//    friend bool     operator !=(const state& __a, const state& __b);
//    friend state    operator &(const state& __a, const state& __b);
//    friend state    operator |(const state& __a, const state& __b);
//    friend state    operator ^(const state& __a, const state& __b);
//    friend struct   std::hash<class state>;
// protected:
//    std::bitset<32>    bitset;
// public:
//    state() = default;
//    state(const std::bitset<32>& bitset) : bitset(bitset) {  }
//    template    <typename ... types>
//    state(types&& ... args)
//    {
//        static_assert(sizeof...(args) <= 32);
//        std::initializer_list<uint32_t>    __ilist = { args... };
//        for (auto& i : __ilist)
//        {
//            bitset.set(i);
//        }
//    }
//    constexpr bool  operator [](size_t pos) const
//    {
//        return bitset[pos];
//    }
//    auto    operator [](size_t pos)
//    {
//        return bitset[pos];
//    }
//    state&  operator &=(const state& other)
//    {
//        bitset &= other.bitset;
//        return *this;
//    }
//    state&  operator |=(const state& other)
//    {
//        bitset |= other.bitset;
//        return *this;
//    }
//    state&  operator ^=(const state& other)
//    {
//        bitset ^= other.bitset;
//        return *this;
//    }
//    state  operator ~() const
//    {
//        return state(~bitset);
//    }
//    state   operator <<(size_t pos) const
//    {
//        return state(bitset << pos);
//    }
//    state&  operator <<=(size_t pos)
//    {
//        bitset <<= pos;
//        return *this;
//    }
//    state   operator >>(size_t pos) const
//    {
//        return state(bitset >> pos);
//    }
//    state&  operator >>=(size_t pos)
//    {
//        bitset >>= pos;
//        return *this;
//    }
//};
//
// bool    operator ==(const state& __a, const state& __b)
//{
//    return (__a.bitset == __b.bitset);
//}
// bool    operator !=(const state& __a, const state& __b)
//{
//    return !(__a == __b);
//}
// state   operator &(const state& __a, const state& __b)
//{
//    return state(__a.bitset & __b.bitset);
//}
// state   operator |(const state& __a, const state& __b)
//{
//    return state(__a.bitset | __b.bitset);
//}
// state   operator ^(const state& __a, const state& __b)
//{
//    return state(__a.bitset ^ __b.bitset);
//}
//
//
//
//} //namespace p201
//
// namespace std
//{
//    template    <>
//    class    std::hash<p201::state>
//    {
//    public:
//        const size_t    operator()(const p201::state& state) const
//        {
//            return std::hash<std::bitset<32>>()(state.bitset);
//        }
//    };
//}
