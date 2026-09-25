"""Check advertised subtask conditions in the rebuilt suites."""

from collections import Counter
from pathlib import Path
import re


ROOT = Path(__file__).parent / "built"
checked = 0


def cases7t3(tokens):
    t = int(tokens[0])
    pos = 1
    result = []
    for _ in range(t):
        n = int(tokens[pos])
        pos += 1
        edges = [(tokens[pos + 2 * j], tokens[pos + 2 * j + 1]) for j in range(n)]
        pos += 2 * n
        result.append(edges)
    assert pos == len(tokens)
    return result


def roots_and_depth(edges):
    children = {b for _, b in edges}
    roots = {a for a, _ in edges} - children
    graph = {}
    for a, b in edges:
        graph.setdefault(a, []).append(b)
    seen = set()
    max_depth = 0
    for root in roots:
        queue = [(root, 1)]
        for node, depth in queue:
            assert node not in seen
            seen.add(node)
            max_depth = max(max_depth, depth)
            queue.extend((child, depth + 1) for child in graph.get(node, []))
    assert seen == {name for edge in edges for name in edge}
    return roots, max_depth, graph


for suite in (4, 6, 7):
    for task in range(1, 5):
        folder = ROOT / f"suite{suite}_full" / f"T{task}" / "data"
        for path in folder.glob("*.in"):
            point = int(path.stem)
            tokens = path.read_text(encoding="utf-8").split()
            values = None
            if (suite, task) not in ((4, 3), (4, 4), (6, 4), (7, 1), (7, 3)):
                values = list(map(int, tokens))
            if (suite, task) == (4, 1):
                n, a = values[0], values[1:]
                assert point > 2 or n <= 100
                assert point not in (3, 4) or len(set(a)) == 1
                assert point not in (5, 6, 7) or max(a) <= 1000
            elif (suite, task) == (4, 2):
                n, k = values[:2]
                assert point > 2 or n <= 2000
                assert point not in (3, 4, 5) or k <= 100000
            elif (suite, task) == (4, 3):
                n, s = int(tokens[0]), tokens[1]
                assert point > 2 or n == 10
                assert point not in (3, 4) or n == 1000
                assert point not in (5, 6) or len(set(s)) == 1
                assert point not in (7, 8) or len(set(s)) <= 2
            elif (suite, task) == (4, 4):
                s = tokens[0]
                nums = list(map(int, re.findall(r"\d+", s)))
                assert point > 2 or len(s) <= 10
                assert point not in (3, 4) or all(x == 1 for x in nums)
                assert point not in (5, 6) or max(nums) <= 9
                assert point not in (7, 8, 9, 10) or "*" not in s
                assert point not in (11, 12) or "+" not in s
                assert point not in (13, 14) or len(s) <= 1000
            elif (suite, task) == (6, 1):
                n, k = values[:2]
                counts = Counter(a % k for a in values[2:])
                assert point > 2 or len(counts) == 1
                assert point not in (3, 4, 5, 6) or len(set(counts.values())) == len(counts)
            elif (suite, task) == (6, 2):
                n, x = values[:2]
                assert point > 2 or n <= 20
                assert point not in (3, 4) or x == 1
                assert point not in (5, 6) or x == 2
                assert point not in (7, 8) or x == 3
            elif (suite, task) == (6, 3):
                n = values[0]
                assert point > 4 or n <= 1000
                if point <= 2:
                    triples = [values[1 + 3 * i:4 + 3 * i] for i in range(n)]
                    raw = sum(c * d for i, (a, b, c) in enumerate(triples)
                              for aa, bb, d in triples[i:]
                              if 2 * min(a + aa, b + bb) <= max(a + aa, b + bb))
                    assert raw < 1000000007
            elif (suite, task) == (6, 4):
                n, k = map(int, tokens[:2])
                a = list(map(int, tokens[2:]))
                assert point > 2 or (n <= 10 and k <= 10)
                assert point > 6 or (n <= 100 and k <= 100 and max(a) <= 100000)
            elif (suite, task) == (7, 1):
                assert point > 3 or len(tokens[0]) <= 3
            elif (suite, task) == (7, 2):
                n = values[0]
                assert point > 2 or n <= 20
                assert point > 5 or n <= 800
            elif (suite, task) == (7, 3):
                for edges in cases7t3(tokens):
                    roots, depth, graph = roots_and_depth(edges)
                    if point <= 4:
                        assert len(roots) == 1 and depth == 3
                        assert re.fullmatch(r"[A-Za-z]+[0-9]+", next(iter(roots)))
                    if point <= 2 or point in (5, 6):
                        assert depth == 3
                        assert all(re.fullmatch(r"[A-Za-z]+[0-9]+", root) for root in roots)
                        for root in roots:
                            for topic in graph.get(root, []):
                                assert re.fullmatch(r"[A-Za-z]+", topic)
                                assert graph.get(topic) == [topic + ".cpp"]
            elif (suite, task) == (7, 4):
                t, pos = values[0], 1
                answers = path.with_suffix(".out").read_text(encoding="utf-8").splitlines()
                assert len(answers) == t
                for case in range(t):
                    n = values[pos]
                    pos += 1
                    degrees = [0] * (n + 1)
                    for _ in range(n - 1):
                        u, v = values[pos:pos + 2]
                        pos += 2
                        degrees[u] += 1
                        degrees[v] += 1
                    assert point != 1 or (t == 1 and n <= 100)
                    assert point != 2 or n <= 1000
                    assert point != 3 or max(degrees) <= 2
                    assert point != 4 or answers[case].split()[1] == "1"
                assert pos == len(values)
            checked += 1
        print(f"S{suite}T{task}: scoring claims checked", flush=True)

print(f"PASS: {checked} official cases satisfy their advertised subtask limits")
