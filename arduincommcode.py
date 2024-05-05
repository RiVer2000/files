from pynput import keyboard

while(1):
    with keyboard.Events() as events:
        # Block for as much as possible
        event = events.get(1e6)
        if event.key == keyboard.KeyCode.from_char('a'):
            print("s")
        elif event.key == keyboard.KeyCode.from_char('w'):
            print("n")
