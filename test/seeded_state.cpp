#include "utility/purestgain.hpp"
#include "dynamics/buttercomp.hpp"
#include "reverb/chamber2.hpp"
#include <array>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <chrono>
#include <new>

static bool guarded = false;
static std::size_t allocations = 0, destructions = 0;
void* operator new(std::size_t n) {
    if (guarded) ++allocations;
    if (auto* p = std::malloc(n ? n : 1)) return p;
    throw std::bad_alloc();
}
void operator delete(void* p) noexcept {
    if (guarded && p) ++destructions;
    std::free(p);
}
void* operator new[](std::size_t n) { return ::operator new(n); }
void operator delete[](void* p) noexcept { ::operator delete(p); }
void operator delete(void* p, std::size_t) noexcept { ::operator delete(p); }
void operator delete[](void* p, std::size_t) noexcept { ::operator delete(p); }

template<class E>
#if defined(_MSC_VER)
__declspec(noinline)
#else
__attribute__((noinline))
#endif
void measured_reset(E* effect, std::uint64_t seed) { effect->reset(seed); }

template<class E> void check() {
    auto a = std::make_unique<E>(12345);
    auto b = std::make_unique<E>(12345);
    auto other = std::make_unique<E>(67890);
    for (auto* e : {a.get(), b.get(), other.get()}) e->setSampleRate(48000);
    std::array<float, 257> left{}, right{}, al{}, ar{}, bl{}, br{};
    for (int pass = 0; pass < 64; ++pass) {
        left[0] = pass == 0 ? 0.8f : 0.0f;
        right[3] = pass == 0 ? -0.6f : 0.0f;
        float* in[]{left.data(), right.data()};
        float* ao[]{al.data(), ar.data()};
        float* bo[]{bl.data(), br.data()};
        guarded = true;
        a->process(in, ao, 257);
        other->process(in, bo, 257);
        b->process(in, bo, 257);
        guarded = false;
        assert(al == bl && ar == br);
    }
    guarded = true;
    a->reset(12345);
    guarded = false;
    assert(a->getSampleRate() == 48000);
    b = std::make_unique<E>(12345);
    b->setSampleRate(48000);
    left[0] = 0.6f;
    float* in[]{left.data(), right.data()};
    float* ao[]{al.data(), ar.data()};
    float* bo[]{bl.data(), br.data()};
    a->process(in, ao, 257);
    b->process(in, bo, 257);
    assert(al == bl && ar == br);
    // Explicit construction/reset must not advance the application's global RNG.
    std::srand(123);
    const auto expected = std::rand();
    std::srand(123);
    a = std::make_unique<E>(0);
    a->reset(0);
    assert(std::rand() == expected);
    // Existing construction remains available, with unchanged parameter defaults.
    auto legacy = std::make_unique<E>();
    for (int i = 0; i < E::kNumParameters; ++i)
        assert(a->get_parameter_value(i) == legacy->get_parameter_value(i));
    const auto before = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; ++i) measured_reset(a.get(), static_cast<std::uint64_t>(i));
    const auto elapsed = std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - before).count();
    std::cout << "state_bytes=" << sizeof(E) << " reset_mean_us=" << elapsed / 100.0 << '\n';
    assert(allocations == 0 && destructions == 0);
}
int main() {
    check<airwindohhs::purestgain::PurestGain<float>>();
    check<airwindohhs::buttercomp::ButterComp<float>>();
    check<airwindohhs::chamber2::Chamber2<float>>();
    std::cout << "seeded state: passed\n";
}
