"""Opt-in reproducible state initialization for three audited standalone effects.

Applied by grab after template expansion. The small CLI also updates/checks
already generated headers without fetching the original VST source tree.
"""
from pathlib import Path
import argparse
import re

EFFECTS = {"PurestGain": "utility/purestgain.hpp",
           "ButterComp": "dynamics/buttercomp.hpp",
           "Chamber2": "reverb/chamber2.hpp"}
BEGIN = "    // BEGIN GENERATED SEEDED STATE\n"
END = "    // END GENERATED SEEDED STATE\n"


def add_seeded_state(source: str, name: str) -> str:
    if name not in EFFECTS:
        return source
    source = re.sub(re.escape(BEGIN) + r".*?" + re.escape(END) + r"\n?", "", source, flags=re.S)
    constructor = re.search(r"\b" + name + r"\(\)\s*\{", source)
    if not constructor:
        raise ValueError(f"Missing default constructor: {name}")
    start = constructor.end()
    end, depth = start, 1
    while depth:
        if source[end] == "{": depth += 1
        if source[end] == "}": depth -= 1
        end += 1
    initialization = source[start:end - 1]
    initialization, count = re.subn(
        r"fpd([LR])\s*=\s*1\.0;\s*while\s*\(fpd\1\s*<\s*16386\)\s*\{\s*fpd\1\s*=\s*rand\(\)\s*\*\s*UINT32_MAX;\s*\}",
        r"fpd\1 = next_seed();", initialization)
    if count != 2 or "rand(" in initialization:
        raise ValueError(f"Unreviewed RNG initializer: {name}")
    private = source[source.index("{", source.index("class " + name)) + 1:source.index("public:", source.index("class " + name))]
    private = re.sub(r"//[^\n]*", "", private)
    clear = []
    for declaration in private.split(";"):
        declaration = declaration.strip()
        if not declaration: continue
        match = re.fullmatch(r"(?:uint32_t|double|float|int)\s+(.+)", declaration, flags=re.S)
        if not match: raise ValueError(f"Unreviewed member declaration: {declaration}")
        for member in match[1].split(","):
            member = member.strip()
            array = re.fullmatch(r"(\w+)\[\d+\]", member)
            if array:
                clear.append(f"        for (auto& value : {array[1]}) value = {{}};")
            elif re.fullmatch(r"\w+", member):
                clear.append(f"        {member} = {{}};")
            else: raise ValueError(f"Unreviewed member: {member}")
    support = BEGIN + f"""    explicit {name}(std::uint64_t seed) noexcept {{ reset(seed); }}

    // Restores DSP and parameter defaults, retaining the configured sample rate.
    // SplitMix64 expands the seed into independent, nonzero stereo noise states.
    // No allocation, shared RNG, construction, destruction or retry loop.
    void reset(std::uint64_t seed) noexcept {{
        auto next_seed = [&seed]() noexcept -> std::uint32_t {{
            auto z = (seed += UINT64_C(0x9e3779b97f4a7c15));
            z = (z ^ (z >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
            z = (z ^ (z >> 27)) * UINT64_C(0x94d049bb133111eb);
            z ^= z >> 31;
            return 16386u + static_cast<std::uint32_t>(z % UINT64_C(4294950910));
        }};
""" + "\n".join(clear) + initialization + "    }\n" + END + "\n"
    # Insert immediately before the parameter enum, leaving default construction intact.
    insertion = re.search(r"    enum params", source)
    if not insertion: raise ValueError(f"Missing parameter enum: {name}")
    return source[:insertion.start()] + support + source[insertion.start():]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    for name, relative in EFFECTS.items():
        path = root / "include" / relative
        original = path.read_text()
        result = add_seeded_state(original, name)
        if args.check:
            if result != original: raise SystemExit(f"Stale seeded support: {relative}")
        else:
            path.write_text(result)


if __name__ == "__main__":
    main()
