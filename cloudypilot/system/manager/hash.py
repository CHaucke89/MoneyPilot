import hashlib
import os


class Hash:
  @staticmethod
  def get_device_hash(serial):
    return hashlib.sha256(f'cloudypilot:{serial}'.encode()).hexdigest()

  @staticmethod
  def compare_hashes(device_hash, authorized_hash):
    if device_hash == authorized_hash:
      print(f"{device_hash} == {authorized_hash}")
      print("Authorized serial number hash found. Continuing.")
    else:
      print(f"{device_hash} != {authorized_hash}")
      raise RuntimeError("This branch is locked to a specific device. Please install the master branch of cloudypilot instead.")

