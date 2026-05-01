import serial
import keyboard
import time

PORT = "COM5"
BAUDRATE = 115200

ser = serial.Serial(PORT, BAUDRATE, timeout=1)
time.sleep(2)

print("Connected")
print("Rotate encoder = volume up/down")
print("Press encoder = mute/unmute")

while True:
    line = ser.readline().decode("utf-8", errors="ignore").strip()

    if line:
        print("Received:", line)

    if line == "TOGGLE_SOUND":
        keyboard.press_and_release("volume mute")
        print("Mute/unmute")

    elif line == "VOLUME_UP":
        keyboard.press_and_release("volume up")
        print("Volume up")

    elif line == "VOLUME_DOWN":
        keyboard.press_and_release("volume down")
        print("Volume down")