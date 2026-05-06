#!/usr/bin/env python3
"""Watch live liveTorqueParameters speedBin values from a running replay."""
import cereal.messaging as messaging

sm = messaging.SubMaster(['liveTorqueParameters'])
while True:
  sm.update(1000)
  ltp = sm['liveTorqueParameters']
  print('centers:  ', list(ltp.speedBinCenters))
  print('latAccel: ', list(ltp.speedBinLatAccelFactors))
  print('friction: ', list(ltp.speedBinFrictions))
  print('valid:    ', list(ltp.speedBinValid))
  print('---')
