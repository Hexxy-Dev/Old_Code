from pynput import keyboard
import pynput

def empty_callback():
    return

class KeyManager:
    def __init__(self):
        self.key_info = {}
        self.add_callback("Key.shift")
        self.add_callback("Key.shift_r")
        self.add_callback("Key.ctrl")
        self.add_callback("Key.ctrl_r")
        self.add_callback("Key.alt")
        self.add_callback("Key.alt_r")

    def is_valid(self,key):
        #TODO: add is numpad

        if self.key_info[key]["with_shift"]:
            if self.key_info[keyboard.KeyCode.from_char("Key.shift")]["state"] or self.key_info[keyboard.KeyCode.from_char("Key.shift_r")]["state"]:
                return True
            return False

        if self.key_info[key]["with_ctrl"]:
            if self.key_info[keyboard.KeyCode.from_char("Key.ctrl")]["state"] or self.key_info[keyboard.KeyCode.from_char("Key.ctrl_r")]["state"]:
                return True
            return False

        if self.key_info[key]["with_alt"]:
            if self.key_info[keyboard.KeyCode.from_char("Key.alt")]["state"] or self.key_info[keyboard.KeyCode.from_char("Key.alt_r")]["state"]:
                return True
            return False
        return True

    def on_press(self,key):
        if key == keyboard.Key.esc:
            return False

        if not isinstance(key, pynput.keyboard._xorg.KeyCode):
            key = keyboard.KeyCode.from_char(key)

        if not key in self.key_info  or self.key_info[key]["state"]   or not self.is_valid(key):
            return True
        
        self.key_info[key]["state"] = True
        self.key_info[key]["on_press"]()
        return True

    def on_release(self,key):
        if key == keyboard.Key.esc:
            return False

        if not isinstance(key, pynput.keyboard._xorg.KeyCode):
            key = keyboard.KeyCode.from_char(key)

        if not key in self.key_info   or not self.key_info[key]["state"]   or not self.is_valid(key):
            return True

        self.key_info[key]["state"] = False
        self.key_info[key]["on_release"]()
        return True

    def add_callback(self,key,on_press=empty_callback,on_release=empty_callback,
                    is_numpad=False,with_shift=False,with_ctrl=False,with_alt=False):
        self.key_info[keyboard.KeyCode.from_char(key)] = {
            "on_press": on_press, "on_release": on_release, "state": False,
            "is_numpad":is_numpad,"with_shift":with_shift,"with_ctrl":with_ctrl,"with_alt":with_alt
            }

    def start(self,loop_callback):
        listener = keyboard.Listener(on_press=self.on_press, on_release=self.on_release)
        listener.start()

        while listener.running:
            loop_callback()

        listener.stop()