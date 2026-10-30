# https://contest.yandex.ru/contest/100803/run-report/169904276/
import sys


class Node:
    __slots__ = ("key", "height", "left", "right")

    def __init__(self, key):
        self.key = key
        self.height = 1
        self.left = None
        self.right = None


def height(node):
    return node.height if node is not None else 0


def update_height(node):
    node.height = 1 + max(height(node.left), height(node.right))


def balance_factor(node):
    return height(node.right) - height(node.left)


def rotate_left(node):
    new_root = node.right
    node.right = new_root.left
    new_root.left = node

    update_height(node)
    update_height(new_root)
    return new_root


def rotate_right(node):
    new_root = node.left
    node.left = new_root.right
    new_root.right = node

    update_height(node)
    update_height(new_root)
    return new_root


def balance(node):
    update_height(node)
    factor = balance_factor(node)

    if factor == 2:
        if balance_factor(node.right) < 0:
            node.right = rotate_right(node.right)
        return rotate_left(node)

    if factor == -2:
        if balance_factor(node.left) > 0:
            node.left = rotate_left(node.left)
        return rotate_right(node)

    return node


def add(node, key):
    if node is None:
        return Node(key)

    if key < node.key:
        node.left = add(node.left, key)
    elif key > node.key:
        node.right = add(node.right, key)
    else:
        return node

    return balance(node)


def erase(node, key):
    if node is None:
        return None

    if key < node.key:
        node.left = erase(node.left, key)
    elif key > node.key:
        node.right = erase(node.right, key)
    else:
        if node.left is None:
            return node.right
        if node.right is None:
            return node.left

        # Заменяем ключ минимумом правого поддерева.
        successor = node.right
        while successor.left is not None:
            successor = successor.left

        node.key = successor.key
        node.right = erase(node.right, successor.key)

    return balance(node)


def exists(node, key):
    while node is not None:
        if key == node.key:
            return True
        node = node.left if key < node.key else node.right

    return False


def next_key(node, key):
    answer = None

    while node is not None:
        if node.key >= key:
            answer = node.key
            node = node.left
        else:
            node = node.right

    return answer


def prev_key(node, key):
    answer = None

    while node is not None:
        if node.key <= key:
            answer = node.key
            node = node.right
        else:
            node = node.left

    return answer


def preorder(node, result):
    if node is None:
        return

    result.append(str(node.key))
    preorder(node.left, result)
    preorder(node.right, result)


def main():
    read_line = sys.stdin.buffer.readline
    first_line = read_line()
    if not first_line:
        return

    command_count = int(first_line)
    root = None
    output = []

    for _ in range(command_count):
        parts = read_line().split()
        command = parts[0]

        if command == b"add":
            root = add(root, int(parts[1]))

        elif command == b"del":
            root = erase(root, int(parts[1]))

        elif command == b"exists":
            output.append(
                "YES" if exists(root, int(parts[1])) else "NO"
            )

        elif command == b"next":
            answer = next_key(root, int(parts[1]))
            output.append("None" if answer is None else str(answer))

        elif command == b"prev":
            answer = prev_key(root, int(parts[1]))
            output.append("None" if answer is None else str(answer))

        elif command == b"root":
            output.append("Empty" if root is None else str(root.key))

        elif command == b"height":
            output.append(str(height(root)))

        elif command == b"print":
            keys = []
            preorder(root, keys)
            output.append(" ".join(keys) if keys else "Empty")

    if output:
        sys.stdout.write("\n".join(output) + "\n")


if __name__ == "__main__":
    main()
