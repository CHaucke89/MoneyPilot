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
- I'm frequently adding and removing things, so any number of branches may be broken at any time

Use at your own risk!
