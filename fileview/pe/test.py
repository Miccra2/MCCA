class Test:
    def __init__(self) -> None:
        self.data = {"a": 0, "b": 1, "c": 2}
    
    def __setitem__(self, key, value) -> None:
        self.data[key] = value

    def __bytes__(self) -> None:
        return int.to_bytes(self[key])

    def __getitem__(self, key) -> int:
        return self.data[key]

    def set(self, value) -> None:
        self["a"] = value

    def get(self) -> dict:
        return self.data

t = Test()
t.set(69)
t["b"] = 420
print(t.get())
print(t["a"], t["b"], t["c"])
