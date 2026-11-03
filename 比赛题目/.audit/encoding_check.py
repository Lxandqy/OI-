from __future__ import annotations

from pathlib import Path

from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")

for category in ("CSP-J", "NOIP"):
    folder = ROOT / category
    for child in sorted(folder.iterdir()):
        if not (child.is_dir() or child.suffix.lower() == ".zip"):
            continue
        pkg = Package(child)
        try:
            print("##", category, child.name)
            for name in pkg.names:
                if not name.endswith(".cpp"):
                    continue
                if child.is_file():
                    data = pkg._zip.read(pkg._originals[name])  # type: ignore[union-attr]
                else:
                    data = (child / Path(name)).read_bytes()
                try:
                    data.decode("utf-8")
                    status = "utf8"
                except UnicodeDecodeError as exc:
                    status = f"not-utf8 ({exc.start})"
                print(f"{name}: {status}")
        finally:
            pkg.close()
