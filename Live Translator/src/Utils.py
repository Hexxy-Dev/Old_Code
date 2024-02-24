import sys
import io

class Utils:
    def force_print(*args):
        for arg in args:
            sys.stdout.write(str(arg))
        sys.stdout.flush()

    def force_console_utf8():
        sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')