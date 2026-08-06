#!/usr/bin/env python3

from trgdataformats import TriggerActivity, TriggerActivityData


def test_trigger_activity_data_defaults() -> int:
    ta = TriggerActivityData()

    if ta is None:
        print("FAIL: TriggerActivityData default construction returned None")
        return 1

    size = TriggerActivityData.sizeof()
    if size != 80:
        print(f"FAIL: TriggerActivityData.sizeof() returned {size}, expected 80")
        return 1

    if TriggerActivityData.s_trigger_activity_version != 2:
        print(
            "FAIL: TriggerActivityData.s_trigger_activity_version expected 2, "
            f"got {TriggerActivityData.s_trigger_activity_version}"
        )
        return 1

    if TriggerActivityData.s_invalid_channel != (2**32 - 1):
        print(
            "FAIL: TriggerActivityData.s_invalid_channel expected 2**32-1, "
            f"got {TriggerActivityData.s_invalid_channel}"
        )
        return 1

    if ta.version != 2:
        print(f"FAIL: TriggerActivityData.version expected 2, got {ta.version}")
        return 1

    if ta.version != TriggerActivityData.s_trigger_activity_version:
        print(
            "FAIL: TriggerActivityData.version should match s_trigger_activity_version, "
            f"got {ta.version} vs {TriggerActivityData.s_trigger_activity_version}"
        )
        return 1

    if ta.time_start != (2**64 - 1):
        print(f"FAIL: TriggerActivityData.time_start expected 2**64-1, got {ta.time_start}")
        return 1

    if ta.time_end != (2**64 - 1):
        print(f"FAIL: TriggerActivityData.time_end expected 2**64-1, got {ta.time_end}")
        return 1

    if ta.time_peak != (2**64 - 1):
        print(f"FAIL: TriggerActivityData.time_peak expected 2**64-1, got {ta.time_peak}")
        return 1

    if ta.time_activity != (2**64 - 1):
        print(
            "FAIL: TriggerActivityData.time_activity expected 2**64-1, "
            f"got {ta.time_activity}"
        )
        return 1

    if ta.channel_start != TriggerActivityData.s_invalid_channel:
        print(
            "FAIL: TriggerActivityData.channel_start expected invalid channel, "
            f"got {ta.channel_start}"
        )
        return 1

    if ta.channel_end != TriggerActivityData.s_invalid_channel:
        print(
            "FAIL: TriggerActivityData.channel_end expected invalid channel, "
            f"got {ta.channel_end}"
        )
        return 1

    if ta.channel_peak != TriggerActivityData.s_invalid_channel:
        print(
            "FAIL: TriggerActivityData.channel_peak expected invalid channel, "
            f"got {ta.channel_peak}"
        )
        return 1

    if ta.adc_integral != 0:
        print(f"FAIL: TriggerActivityData.adc_integral expected 0, got {ta.adc_integral}")
        return 1

    if ta.adc_peak != 0:
        print(f"FAIL: TriggerActivityData.adc_peak expected 0, got {ta.adc_peak}")
        return 1

    if ta.detid != 2**8 - 1:
        print(f"FAIL: TriggerActivityData.detid expected 2**8 - 1, got {ta.detid}")
        return 1

    if ta.type != TriggerActivityData.Type.kUnknown:
        print(f"FAIL: TriggerActivityData.type expected kUnknown, got {ta.type}")
        return 1

    if ta.algorithm != TriggerActivityData.Algorithm.kUnknown:
        print(f"FAIL: TriggerActivityData.algorithm expected kUnknown, got {ta.algorithm}")
        return 1

    print("PASS: TriggerActivityData default checks")
    return 0


def test_trigger_activity_data_enums() -> int:
    # Confirm expected enum names are available through bindings.
    enum_checks = [
        TriggerActivityData.Type.kUnknown,
        TriggerActivityData.Type.kTPC,
        TriggerActivityData.Type.kPDS,
        TriggerActivityData.Algorithm.kUnknown,
        TriggerActivityData.Algorithm.kSupernova,
        TriggerActivityData.Algorithm.kSWIFT,
    ]

    if any(value is None for value in enum_checks):
        print("FAIL: TriggerActivityData enum exposure appears incomplete")
        return 1

    print("PASS: TriggerActivityData enum exposure")
    return 0


def test_trigger_activity_holder_from_bytes() -> int:
    payload = bytes(TriggerActivityData.sizeof() + 8)
    ta = TriggerActivity(payload)

    if ta.sizeof() != len(payload):
        print(f"FAIL: TriggerActivity sizeof mismatch, got {ta.sizeof()}, expected {len(payload)}")
        return 1

    if len(ta) != 0:
        print(f"FAIL: TriggerActivity expected length 0 for zero payload, got {len(ta)}")
        return 1

    if ta.n_inputs() != 0:
        print(f"FAIL: TriggerActivity n_inputs expected 0 for zero payload, got {ta.n_inputs()}")
        return 1

    if len(ta.get_bytes()) != len(payload):
        print("FAIL: TriggerActivity get_bytes length mismatch")
        return 1

    print("PASS: TriggerActivity holder bytes roundtrip with zero-input payload")
    return 0


def main() -> int:
    failures = 0
    failures += test_trigger_activity_data_defaults()
    failures += test_trigger_activity_data_enums()
    failures += test_trigger_activity_holder_from_bytes()

    if failures == 0:
        print("TriggerActivity binding tests passed")
    else:
        print(f"TriggerActivity binding tests had {failures} failure(s)")

    return failures


if __name__ == "__main__":
    raise SystemExit(main())
