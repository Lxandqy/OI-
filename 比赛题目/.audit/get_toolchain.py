from __future__ import annotations

import json
import sys
import urllib.request
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

OUT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\tools")
API = "https://api.github.com/repos/skeeto/w64devkit/releases/latest"


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    req = urllib.request.Request(API, headers={"User-Agent": "codex-audit"})
    with urllib.request.urlopen(req, timeout=30) as response:
        data = json.load(response)
    print(data["tag_name"])
    for asset in data["assets"]:
        print(asset["name"], asset["size"], asset["browser_download_url"])


if __name__ == "__main__":
    main()
