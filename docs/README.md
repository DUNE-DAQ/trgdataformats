# trgdataformats

## Overview

This package contains definitions of the objects used in the data
selection system (`TriggerPrimitive`, `TriggerActivity` and
`TriggerCandidate`, collectively `TX`) along with corresponding
overlay classes to allow them to be serialized into fragments.
   
## Design

The `TriggerActivity` and `TriggerCandidate` classes are found in
`TriggerObjectOverlay.hpp`. They consist conceptually of two parts:

1. The data fields of the class itself (`time_start`, `algorithm`,
   etc, found in `TriggerCandidateData` and `TriggerActivityData`)
2. The list of input objects (`TriggerPrimitive` for `TriggerActivity`,
   `TriggerActivity` for `TriggerCandidate`) that were used to create this
   TA/TC
