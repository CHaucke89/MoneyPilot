# THIS IS AN "UNSAFE" FORK AND WILL GET YOUR DEVICE BANNED FROM COMMA'S SERVERS
This is a personal fork of [sunnypilot](https://github.com/sunnypilot/sunnypilot) specifically made for my Kia EV6 that very much falls under the [Bad/Unsafe Forks category](https://github.com/commaai/openpilot/wiki/Forks#badunsafe-forks). If you do not want to be banned from comma connect, do NOT use this with uploads enabled and be sure to delete all rlogs before switching back to a safe fork and re-enabling uploads. If you do not use comma connect or use an alternative like konik.ai, then you have nothing to worry about...except your life while letting this fork operate a motor vehicle with you in it.

Just kidding, it's not that bad.
Some of the features/changes (in no particular order):

### Toggleable:
- Always-Off Driver Monitoring (mutually exclusive with Always-On Driver Monitoring)
- Dynamic "damp factor" based on speed for HKG CAN-FD vehicles when using stock longitudinal control
- Dynamic maximum steering torque & steer deltas based on speed for HKG CAN-FD vehicles
- Use Imperial units (feet) in the on-road developer UI rather than SI units (meters)

### Other Stuff:
- Increased maximum steering torque and steer deltas with dynamic torque turned off
- Many UI changes
- Git LFS removed/not used (all files are present in the repo)
- I'm frequently adding and removing things, so any number of branches may be broken at any time

Use at your own risk!



# Licensing

"This project uses software from Haibin Wen and SUNNYPILOT LLC and is licensed under a custom license requiring permission for use."

Just as sunnypilot is a heavily modified version of openpilot, MoneyPilot is a heavily modified version of sunnypilot. Credit for the vast majority of the codebase goes to the openpilot and sunnypilot developers.

sunnypilot is released under the MIT License. This repository includes original work as well as significant portions of code derived from openpilot by comma.ai, which is also released under the MIT license with additional disclaimers.

The original openpilot license notice, including comma.ai’s indemnification and alpha software disclaimer, is reproduced below as required:

openpilot is released under the MIT license. Some parts of the software are released under other licenses as specified.

Any user of this software shall indemnify and hold harmless Comma.ai, Inc. and its directors, officers, employees, agents, stockholders, affiliates, subcontractors and customers from and against all allegations, claims, actions, suits, demands, damages, liabilities, obligations, losses, settlements, judgments, costs and expenses (including without limitation attorneys’ fees and costs) which arise out of, relate to or result from any use of this software by user.

THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT. YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS. NO WARRANTY EXPRESSED OR IMPLIED.

For full license terms, please see the LICENSE file.