from pathlib import Path
import hashlib
import json
import re
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.seeded_state import add_seeded_state, EFFECTS, BEGIN, END


class Generation(unittest.TestCase):
    def test_original_behavior_and_reproducibility(self):
        baselines = json.loads((ROOT / "test/legacy_header_checksums.json").read_text())
        for name, relative in EFFECTS.items():
            source = (ROOT / "include" / relative).read_text()
            self.assertEqual(source, add_seeded_state(source, name))
            legacy = re.sub(re.escape(BEGIN) + r".*?" + re.escape(END) + r"\n?", "", source, flags=re.S)
            self.assertEqual(hashlib.sha256(legacy.encode()).hexdigest(), baselines[relative])
            self.assertEqual(source, add_seeded_state(legacy, name))

    def test_unreviewed_rng_rejected(self):
        source = (ROOT / "include/utility/purestgain.hpp").read_text()
        with self.assertRaises(ValueError):
            add_seeded_state(source.replace("rand()", "another_rng()"), "PurestGain")

    def test_other_effect_untouched(self):
        self.assertEqual(add_seeded_state("opaque text", "Other"), "opaque text")


if __name__ == "__main__":
    unittest.main()
