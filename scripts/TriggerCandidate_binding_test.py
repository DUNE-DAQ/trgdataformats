#!/usr/bin/env python3

from trgdataformats import (
    TriggerCandidate,
    TriggerCandidateData,
    string_to_trigger_candidate_type,
    trigger_candidate_type_to_string,
)


def test_trigger_candidate_data_defaults() -> int:
    tc = TriggerCandidateData()

    if tc is None:
        print("FAIL: TriggerCandidateData default construction returned None")
        return 1

    size = TriggerCandidateData.sizeof()
    if size != 48:
        print(f"FAIL: TriggerCandidateData.sizeof() returned {size}, expected 48")
        return 1

    if TriggerCandidateData.s_trigger_candidate_version != 3:
        print(
            "FAIL: TriggerCandidateData.s_trigger_candidate_version expected 3, "
            f"got {TriggerCandidateData.s_trigger_candidate_version}"
        )
        return 1

    if tc.version != 3:
        print(f"FAIL: TriggerCandidateData.version expected 3, got {tc.version}")
        return 1

    if tc.version != TriggerCandidateData.s_trigger_candidate_version:
        print(
            "FAIL: TriggerCandidateData.version should match s_trigger_candidate_version, "
            f"got {tc.version} vs {TriggerCandidateData.s_trigger_candidate_version}"
        )
        return 1

    if tc.time_start != (2**64 - 1):
        print(f"FAIL: TriggerCandidateData.time_start expected 2**64-1, got {tc.time_start}")
        return 1

    if tc.time_end != (2**64 - 1):
        print(f"FAIL: TriggerCandidateData.time_end expected 2**64-1, got {tc.time_end}")
        return 1

    if tc.time_candidate != (2**64 - 1):
        print(
            "FAIL: TriggerCandidateData.time_candidate expected 2**64-1, "
            f"got {tc.time_candidate}"
        )
        return 1

    if tc.detid != 2**8 - 1:
        print(f"FAIL: TriggerCandidateData.detid expected 2**8 - 1, got {tc.detid}")
        return 1

    if tc.type != TriggerCandidateData.Type.kUnknown:
        print(f"FAIL: TriggerCandidateData.type expected kUnknown, got {tc.type}")
        return 1

    if tc.algorithm != TriggerCandidateData.Algorithm.kUnknown:
        print(f"FAIL: TriggerCandidateData.algorithm expected kUnknown, got {tc.algorithm}")
        return 1

    print("PASS: TriggerCandidateData default checks")
    return 0


def test_trigger_candidate_enum_and_conversion() -> int:
    if trigger_candidate_type_to_string(TriggerCandidateData.Type.kTiming) != "kTiming":
        print("FAIL: trigger_candidate_type_to_string(kTiming) mismatch")
        return 1

    if string_to_trigger_candidate_type("kTiming") != TriggerCandidateData.Type.kTiming:
        print("FAIL: string_to_trigger_candidate_type('kTiming') mismatch")
        return 1

    if string_to_trigger_candidate_type("notAType") != TriggerCandidateData.Type.kUnknown:
        print("FAIL: string_to_trigger_candidate_type('notAType') should return kUnknown")
        return 1

    # Spot-check long-tail enum entries added recently.
    for expected in [
        TriggerCandidateData.Type.kCTBOffSpillSnapshot,
        TriggerCandidateData.Type.kCTBCustomPulseTrain,
        TriggerCandidateData.Type.kSSPLEDCalibration,
    ]:
        as_str = trigger_candidate_type_to_string(expected)
        if string_to_trigger_candidate_type(as_str) != expected:
            print(f"FAIL: conversion roundtrip mismatch for enum value '{as_str}'")
            return 1

    print("PASS: TriggerCandidateData enum conversion checks")
    return 0


def test_trigger_candidate_holder_from_bytes() -> int:
    payload = bytes(TriggerCandidateData.sizeof() + 8)  # 8 for the uint64_t n_inputs in TriggerCandidate
    tc = TriggerCandidate(payload)

    if tc.sizeof() != len(payload):
        print(f"FAIL: TriggerCandidate sizeof mismatch, got {tc.sizeof()}, expected {len(payload)}")
        return 1

    if len(tc) != 0:
        print(f"FAIL: TriggerCandidate expected length 0 for zero payload, got {len(tc)}")
        return 1

    if tc.n_inputs() != 0:
        print(f"FAIL: TriggerCandidate n_inputs expected 0 for zero payload, got {tc.n_inputs()}")
        return 1

    if len(tc.get_bytes()) != len(payload):
        print("FAIL: TriggerCandidate get_bytes length mismatch")
        return 1

    print("PASS: TriggerCandidate holder bytes roundtrip with zero-input payload")
    return 0


def main() -> int:
    failures = 0
    failures += test_trigger_candidate_data_defaults()
    failures += test_trigger_candidate_enum_and_conversion()
    failures += test_trigger_candidate_holder_from_bytes()

    if failures == 0:
        print("TriggerCandidate binding tests passed")
    else:
        print(f"TriggerCandidate binding tests had {failures} failure(s)")

    return failures


if __name__ == "__main__":
    raise SystemExit(main())
