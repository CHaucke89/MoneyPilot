cloudypilot Version 0.1.0 (2026-xx-xx)
========================
* What's Changed (sunnypilot/sunnypilot)
  * ui: update gates for certain toggles by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1830
  * release: ignore upstream IsReleaseBranch by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1831
  * manager: disable DEVELOPMENT_ONLY reset by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1833
  * sunnylink: fix max time offroad values by @nayan8teen in https://github.com/sunnypilot/sunnypilot/pull/1835
  * ui: show default model name by @nayan8teen in https://github.com/sunnypilot/sunnypilot/pull/1837
  * sunnylink: add CarParams fallback for brand-specific capabilities by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1839
  * sunnylink SDUI: tweak DisableUpdate param for clarity by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1842
  * Revert "DM: Lancia Delta HF Integrale model" by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1849
  * modeld_v2: safe model validation by @Discountchubbs in https://github.com/sunnypilot/sunnypilot/pull/1855
  * Revert "deprecate `carState.brake`" for Honda Gas Interceptor by @mvl-boston in https://github.com/sunnypilot/sunnypilot/pull/1860
  * sunnylink: deprecate legacy params metadata by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1862
  * ui: reset Enforce Torque Control and NNLC if both are enabled by @sunnyhaibin in https://github.com/sunnypilot/sunnypilot/pull/1863
* What's Changed (sunnypilot/opendbc)
  * Rivian: suppress ACM hold-the-wheel warning during MADS-only lateral by @lukasloetkolben in https://github.com/sunnypilot/opendbc/pull/465
  * Sync: `commaai/opendbc:master` → `sunnypilot/opendbc:master` by @sunnyhaibin in https://github.com/sunnypilot/opendbc/pull/479
  * safety: add option to ignore frequency check for RX checks by @sunnyhaibin in https://github.com/sunnypilot/opendbc/pull/480
  * Revert "deprecate carState.brake" for Honda Gas Interceptor by @mvl-boston in https://github.com/sunnypilot/opendbc/pull/481
* New Contributors (sunnypilot/sunnypilot)
  * @mvl-boston made their first contribution in https://github.com/sunnypilot/sunnypilot/pull/1860
* Full Changelog: https://github.com/sunnypilot/sunnypilot/compare/v2026.001.007...v2026.002.000
************************
* Synced with commaai's openpilot (v0.11.1)
  * master commit 69e2c321e49760e52f7983eaa0a5f77cb95de637 (June 02, 2026)
* New driver monitoring model
* Improved image processing pipeline for driver camera
* Improved thermal policy for comma four
* Acura MDX 2022-24 support thanks to mvl-boston!
* Rivian R1S and R1T 2025 support thanks to lukasloetkolben!
