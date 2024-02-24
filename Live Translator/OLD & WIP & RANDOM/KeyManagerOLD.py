import keyboard

class KeyManager:
    def __init__(self):
        self.key_info = {}

    def on_press(self,key):
        if self.key_info[key]["state"]:
            return
        self.key_info[key]["state"] = True
        self.key_info[key]["on_press"]()

    def on_release(self,key):
        if not self.key_info[key]["state"]:
            return
        self.key_info[key]["state"] = False
        self.key_info[key]["on_release"]()

    def add_callback(self,key,on_press,on_release):
        self.key_info[key] = {"on_press": on_press, "on_release": on_release, "state": False}

    def add_hotkey(self,hotkey,callback):
        keyboard.add_hotkey(hotkey, callback)

    def start(self):
        keyboard.wait()

    def create_callbacks(self):
        for key,callbacks in self.key_info.items():
            keyboard.on_press_key(key, callbacks["on_press"])
            keyboard.on_release_key(key, callbacks["on_release"])

