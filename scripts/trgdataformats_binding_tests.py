#!/usr/bin/env python3

import subprocess
import sys
from pathlib import Path

def main() -> int:
    script_dir = Path(__file__).resolve().parent

    scripts = [
        "Types_binding_test.py",
        "TriggerPrimitive_binding_test.py",
        "TriggerActivity_binding_test.py",
        "TriggerCandidate_binding_test.py",
    ]

    failures = 0
    for script in scripts:
        result = subprocess.run([sys.executable, str(script_dir / script)], check=False)
        if result.returncode != 0:
            failures += 1

    print("\n=== Summary ===")
    if failures == 0:
        print("All trgdataformats binding tests passed")
    else:
        print(f"{failures} binding test script(s) failed")

    return failures


if __name__ == "__main__":
    sys.exit(main())
