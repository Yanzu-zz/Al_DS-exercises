#! -*- encoding=utf-8 -*-
# LFU 最不经常使用缓存算法

from computer_principle.DoubleLinkedList import DoubleLinkedList, Node


class LFUNode(Node):
    def __init__(self, key, value):
        self.freq = 0
        super(LFUNode, self).__init__(key, value)


class LFUCache(object):
    def __init__(self, capacity):
        self.capacity = capacity
        self.map = {}
        # 保存相同使用频率的结点 map，淘汰结点时寻找最低频率的map进行 FIFO 淘汰即可
        self.freq_map = {}
        self.size = 0

    # 更新结点频率的操作
    def __update_freq(self, node):
        freq = node.freq
        # 使用过后要到最前面，故先删除，下面在 append 到头部
        node = self.freq_map[freq].remove(node)
        if self.freq_map[freq].size == 0:
            del self.freq_map[freq]

        # 且使用频率要增加 1
        freq += 1
        node.freq = freq
        if freq not in self.freq_map:  # 没有对应的频率链表的话要创建一个
            self.freq_map[freq] = DoubleLinkedList()
        self.freq_map[freq].append(node)

    def get(self, key):
        if key not in self.map:
            return -1
        node = self.map.get(key)
        self.__update_freq(node)
        return node.value

    def put(self, key, value):
        if self.capacity == 0:
            return

        # 缓存命中情况（即缓存里有该结点）
        if key in self.map:
            node = self.map.get(key)
            node.value = value
            self.__update_freq(node)
        else:
            # 如果缓存已满，则需要淘汰使用频率链表中的头结点
            if self.capacity == self.size:
                min_freq = min(self.freq_map)
                node = self.freq_map[min_freq].pop()
                del self.map[node.key]
                self.size -= 1

            # 下面就是通用插入逻辑
            node = LFUNode(key, value)
            node.freq = 1
            self.map[key] = node
            if node.freq not in self.freq_map:
                self.freq_map[node.freq] = DoubleLinkedList()
            node = self.freq_map[node.freq].append(node)
            self.size += 1

    def print(self):
        print('***********************')
        for k, v in self.freq_map.items():
            print('Freq = %d ' %  k)
            self.freq_map[k].print()
        print('***********************')
        print()


if __name__ == '__main__':
    cache = LFUCache(4)
    cache.put(1, 1)
    cache.print()
    cache.put(2, 2)
    cache.print()
    print(cache.get(1))
    cache.print()
    cache.put(3, 3)
    cache.print()
    print(cache.get(2))
    cache.print()
    cache.put(4, 4)
    cache.print()
    print(cache.get(1))
    cache.print()
    print(cache.get(3))
    cache.print()
    print(cache.get(4))
    cache.print()
