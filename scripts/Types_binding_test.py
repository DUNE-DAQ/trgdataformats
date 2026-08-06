#!/usr/bin/env python3

from trgdataformats import TypeDefaults, g_whole_detector


def test_type_defaults_constants() -> int:
    if TypeDefaults.s_invalid_timestamp != (2**64 - 1):
        print(
            "FAIL: TypeDefaults.s_invalid_timestamp expected 2**64-1, "
            f"got {TypeDefaults.s_invalid_timestamp}"
        )
        return 1

    if TypeDefaults.s_invalid_detid != (2**8 - 1):
        print(
            "FAIL: TypeDefaults.s_invalid_detid expected 2**8 - 1, "
            f"got {TypeDefaults.s_invalid_detid}"
        )
        return 1

    if TypeDefaults.s_invalid_trigger_number != (2**64 - 1):
        print(
            "FAIL: TypeDefaults.s_invalid_trigger_number expected 2**64-1, "
            f"got {TypeDefaults.s_invalid_trigger_number}"
        )
        return 1

    print("PASS: TypeDefaults constants")
    return 0


def test_whole_detector_constant() -> int:
    if g_whole_detector != (TypeDefaults.s_invalid_detid - 1):
        print(
            "FAIL: g_whole_detector expected invalid_detid-1, "
            f"got {g_whole_detector}"
        )
        return 1

    print("PASS: g_whole_detector constant")
    return 0


def main() -> int:
    failures = 0
    failures += test_type_defaults_constants()
    failures += test_whole_detector_constant()

    if failures == 0:
        print("Types binding tests passed")
    else:
        print(f"Types binding tests had {failures} failure(s)")

    return failures


if __name__ == "__main__":
    raise SystemExit(main())
