from copy import deepcopy
from typing import Tuple, List

import os
import sys
import cv2
import numpy as np
from PIL import Image
from xmltodict3 import XmlTextToDict


class Drawer:
    def __init__(self, paths, obstacles, width, height):
        self.canvas = np.ones((1080*3, 1920*3, 3), np.uint8) * 255
        self.paths = paths
        self.obstacles = obstacles
        self.width = width
        self.height = height
        self.colours = self.assign_colour(len(self.paths))
        self.scale = 30
        self.draw_grid()
        self.draw_obstacles()
        self.frames = []

    def draw_grid(self):
        for i in range(self.width + 1):
            cv2.line(self.canvas, (self.scale // 2, i * self.scale + self.scale // 2),
                     (self.height * self.scale + self.scale // 2, i * self.scale + self.scale // 2), thickness=1,
                     color=(0, 0, 0))

        for i in range(self.height + 1):
            cv2.line(self.canvas, (i * self.scale + self.scale // 2, self.scale // 2),
                     (i * self.scale + self.scale // 2, self.width * self.scale + self.scale // 2), thickness=1,
                     color=(0, 0, 0))

    def draw_obstacles(self):
        for x, y in self.obstacles:
            self.fill_obstacle(x + 1, y + 1)

    def fill_obstacle(self, x, y):
        cv2.rectangle(self.canvas, (x * self.scale - self.scale // 2, y * self.scale - self.scale // 2),
                      (x * self.scale + self.scale // 2, y * self.scale + self.scale // 2), color=(0, 0, 0),
                      thickness=-1)

    def start(self):
        try:
            maxlen = max(map(len, self.paths))
            for i in range(0, maxlen):
                frame = deepcopy(self.canvas)
                for j in range(0, len(self.paths)):
                    x, y = self.paths[j][i]
                    try:
                        x, y = self.paths[j][i]
                    except:
                        pass
                    cv2.circle(frame, ((int(y) + 1) * self.scale, (int(x) + 1) * self.scale), 3, self.colours[j], 5)
                self.frames.append(frame)
        except Exception as e:
            raise e

    def save_gif(self, path, duration):
        images = []
        for frame in self.frames:
            images.append(Image.fromarray(frame))
        images[0].save(
            path,
            save_all=True,
            append_images=images[1:],
            optimize=True,
            duration=duration,
            loop=0
        )

    @staticmethod
    def assign_colour(num):
        def colour(x):
            x = hash(str(x + 42))
            return x & 0xFF, (x >> 8) & 0xFF, (x >> 16) & 0xFF

        colours = dict()
        for i in range(num):
            colours[i] = colour(i)
        return colours


def main():
    xml_file_path = os.path.join(os.path.dirname(__file__), sys.argv[1])
    gif_file_path = os.path.join(os.path.dirname(__file__), sys.argv[2])
    with open(xml_file_path, 'r') as f:
        text = f.read()
    xml = XmlTextToDict(text, ignore_namespace=True).get_dict()
    paths = parsePaths(xml)

    obstacles = parseObstacles(xml)

    drawer = Drawer(paths, obstacles, *parseSize(xml))
    drawer.start()
    drawer.save_gif(gif_file_path, 450)


def parsePaths(xml) -> List[List[Tuple[int, int]]]:
    paths = []
    for path in xml['root']['log']['lplevel']:
        cur_path = []
        for node in path['node']:
            cur_path.append((node['@x'], node['@y']))
        paths.append(cur_path)
    return paths


def parseObstacles(xml) -> List[Tuple[int, int]]:
    obstacles = []
    j = 0
    for row in xml['root']['map']['grid']['row']:
        row = list(map(int, row.split(' ')))
        for i, elem in enumerate(row):
            if elem == 1:
                obstacles.append((i, j))
        j += 1
    return obstacles


def parseSize(xml) -> Tuple[int, int]:
    return int(xml['root']['map']['width']), int(xml['root']['map']['height'])


if __name__ == '__main__':
    main()
