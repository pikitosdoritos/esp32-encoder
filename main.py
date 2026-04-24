import serial
from pynput.keyboard import Controller, Key

ser = serial.Serial("COM5", 115200)
keyboard = Controller()

while True:
    line = ser.readline().decode().strip()

    if line == "UP":
        keyboard.press(Key.media_volume_up)
        keyboard.release(Key.media_volume_up)

    elif line == "DOWN":
        keyboard.press(Key.media_volume_down)
        keyboard.release(Key.media_volume_down)

    elif line == "MUTE":
        keyboard.press(Key.media_volume_mute)
        keyboard.release(Key.media_volume_mute)

    print(line)