import hashlib
import os


def get_current_hash(serial):
  return hashlib.sha256(f'cloudypilot:{serial}'.encode()).hexdigest()


def get_authorized_hash():
  return os.getenv("AUTHORIZED_HASH")


def set_authorized_hash(serial):
  os.environ["AUTHORIZED_HASH"] = hashlib.sha256(f'cloudypilot:{serial}'.encode()).hexdigest()
