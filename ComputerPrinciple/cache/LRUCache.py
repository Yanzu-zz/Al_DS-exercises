#! -*- encoding=utf-8 -*-
# LRU 最近最少使用缓存算法

from computer_principle.DoubleLinkedList import DoubleLinkedList, Node


class LRUCache(object):
    def __init__(self, capacity):
        self.capacity = capacity
        self.map = {}
        self.list = DoubleLinkedList(self.capacity)

    # 使用（或获取）一个结点，此时它就是最近使用的，故要提前
    def get(self, key):
        if key in self.map:
            node = self.map[key]
            self.list.remove(node)
            self.list.append_front(node)
            return node.value
        else:
            return -1

    def put(self, key, value):
        # 已存在结点
        if key in self.map:
            node = self.map.get(key)
            self.list.remove(node)
            node.value = value
            self.list.append_front(node)
        else:  # 新结点
            node = Node(key, value)
            # 缓存已满的话先删掉末尾的元素
            if self.list.size >= self.capacity:
                old_node = self.list.remove()
                self.map.pop(old_node.key)

            self.list.append_front(node)
            self.map[key] = node

    def print(self):
        self.list.print()


if __name__ == '__main__':
    cache = LRUCache(2)
    cache.put(2, 2)
    cache.print()
    cache.put(1, 1)
    cache.print()
    cache.put(3, 3)
    cache.print()
    print(cache.get(1))
    cache.print()
    print(cache.get(2))
    cache.print()
    print(cache.get(3))
