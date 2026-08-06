#!/usr/bin/env python3

from trgdataformats import TriggerPrimitive


def test_construction_and_sizeof() -> int:
    tp = TriggerPrimitive()
    if tp is None:
        print("FAIL: TriggerPrimitive default construction returned None")
        return 1

    size = TriggerPrimitive.sizeof()
    if size != TriggerPrimitive.s_expected_bytes:
        print(
            "FAIL: TriggerPrimitive.sizeof() and TriggerPrimitive.s_expected_bytes mismatch, "
            f"got {size} vs {TriggerPrimitive.s_expected_bytes}"
        )
        return 1

    print("PASS: TriggerPrimitive construction and sizeof")
    return 0


def test_static_and_default_fields() -> int:
    tp = TriggerPrimitive()

    # Providing this check will provide a nudge for developers to update these tests when the version changes
    if TriggerPrimitive.s_trigger_primitive_version != 2:
        print(
            "FAIL: TriggerPrimitive.s_trigger_primitive_version expected 2, "
            f"got {TriggerPrimitive.s_trigger_primitive_version}"
        )
        return 1

    if tp.version != TriggerPrimitive.s_trigger_primitive_version:
        print(f"FAIL: version mismatch, got {tp.version}")
        return 1

    if tp.flag != 0:
        print(f"FAIL: flag expected 0, got {tp.flag}")
        return 1

    if tp.detid != 2**8 - 1:
        print(f"FAIL: detid expected 2**8 - 1, got {tp.detid}")
        return 1

    if tp.channel != 0xFFFFFF:
        print(f"FAIL: channel expected 0xFFFFFF, got {tp.channel}")
        return 1

    if tp.samples_over_threshold != 2**16 - 1:
        print(
            "FAIL: samples_over_threshold expected 2**16 - 1, "
            f"got {tp.samples_over_threshold}"
        )
        return 1

    if tp.samples_to_peak != 2**16 - 1:
        print(f"FAIL: samples_to_peak expected 2**16 - 1, got {tp.samples_to_peak}")
        return 1

    if tp.time_start != (2**64 - 1):
        print(f"FAIL: time_start expected 2**64-1, got {tp.time_start}")
        return 1

    if tp.adc_integral != 0:
        print(f"FAIL: adc_integral expected 0, got {tp.adc_integral}")
        return 1

    if tp.adc_peak != 0:
        print(f"FAIL: adc_peak expected 0, got {tp.adc_peak}")
        return 1

    expected_channel_invalid = 0xFFFFFF
    if TriggerPrimitive.s_invalid_samples_over_threshold != 2**16 - 1:
        print(
            "FAIL: TriggerPrimitive.s_invalid_samples_over_threshold expected 2**16 - 1, "
            f"got {TriggerPrimitive.s_invalid_samples_over_threshold}"
        )
        return 1

    if TriggerPrimitive.s_invalid_samples_to_peak != 2**16 - 1:
        print(
            "FAIL: TriggerPrimitive.s_invalid_samples_to_peak expected 2**16 - 1, "
            f"got {TriggerPrimitive.s_invalid_samples_to_peak}"
        )
        return 1

    if TriggerPrimitive.s_invalid_tp_channel != expected_channel_invalid:
        print(
            "FAIL: TriggerPrimitive.s_invalid_tp_channel expected 0xFFFFFF, "
            f"got {TriggerPrimitive.s_invalid_tp_channel}"
        )
        return 1

    if TriggerPrimitive.s_expected_bytes != 24:
        print(
            "FAIL: TriggerPrimitive.s_expected_bytes expected 24, "
            f"got {TriggerPrimitive.s_expected_bytes}"
        )
        return 1

    print("PASS: TriggerPrimitive static/default field checks")
    return 0


def test_timestamp_methods_and_ordering() -> int:
    tp_a = TriggerPrimitive()
    tp_b = TriggerPrimitive()

    if tp_a.get_timestamp() != tp_a.time_start:
        print(
            "FAIL: TriggerPrimitive get_timestamp() is inconsistent with time_start, "
            f"got {tp_a.get_timestamp()} vs {tp_a.time_start}"
        )
        return 1

    tp_a.set_timestamp(100)
    if tp_a.get_timestamp() != 100:
        print(f"FAIL: TriggerPrimitive get/set timestamp mismatch, got {tp_a.get_timestamp()}")
        return 1

    tp_b.set_timestamp(200)

    if not (tp_a < tp_b):
        print("FAIL: TriggerPrimitive ordering expected tp_a < tp_b")
        return 1

    if tp_b < tp_a:
        print("FAIL: TriggerPrimitive ordering expected tp_b !< tp_a")
        return 1

    print("PASS: TriggerPrimitive timestamp methods and ordering operator")
    return 0


def main() -> int:
    failures = 0
    failures += test_construction_and_sizeof()
    failures += test_static_and_default_fields()
    failures += test_timestamp_methods_and_ordering()

    if failures == 0:
        print("TriggerPrimitive binding tests passed")
    else:
        print(f"TriggerPrimitive binding tests had {failures} failure(s)")

    return failures


if __name__ == "__main__":
    raise SystemExit(main())
