import cv2
import os
import math
import numpy as np
from shutil import rmtree
from PIL import Image

LED_COUNT = 16
DEG_STEP = 1
DIV_COUNT = len(range(0, 360, DEG_STEP))


def img2dat(img):
    w, h, c = img.shape
    radius = min(h, w) // 2
    ret = []
    for deg in range(0, 360, DEG_STEP):
        degree = deg * np.pi/180
        line = []
        for i in range(LED_COUNT):
            x = int(radius * i/LED_COUNT * math.cos(degree) + h//2)
            y = int(radius * i/LED_COUNT * math.sin(degree) + w//2)
            b, g, r = map(lambda x: 64*x//255, img[y, x])
            #if b==0 and g==0 and r==0: line.append([64, 64, 64])
            line.append([r, g, b])
        ret.append(line)
    return ret


def virtual_versawrite(data, radius):
    img = np.zeros((2*radius, 2*radius, 3), dtype='uint8')
    for i in range(DIV_COUNT):
        degree = (i*DEG_STEP) * np.pi/180
        for j in range(LED_COUNT):
            x = int(radius * j/LED_COUNT * math.cos(degree) + radius)
            y = int(radius * j/LED_COUNT * math.sin(degree) + radius)
            for nx in range(x-radius//90, x+radius//90):
                for ny in range(y-radius//90, y+radius//90):
                    if nx<0 or 2*radius<=nx or ny<0 or 2*radius<=ny: continue
                    for k in range(3):
                        img[ny, nx, k] = 255*data[i][j][2-k]//64
    cv2.imshow('versa', img)
    cv2.waitKey(0)


def main():
    filename = input('input file name without .gif: ')

    # load data for each frame
    gif = cv2.VideoCapture('input_gifs/' + filename + '.gif')
    frame_cnt = 0
    data = []
    dir_name = "screen_caps"
    if not os.path.exists(dir_name):
        os.mkdir(dir_name)
    while True:
        is_success, frame = gif.read()
        if not is_success: break
        img_name = str(frame_cnt) + ".jpg"
        img_path = os.path.join(dir_name, img_name)
        data.append(img2dat(frame))
        cv2.imwrite(img_path, frame)
        frame_cnt += 1

    # ---- DEBUG PRINT ----
    for i in range(frame_cnt):
        img = cv2.imread('screen_caps/' + str(i) + '.jpg')
        cv2.imshow('original', img)
        virtual_versawrite(data[i], min(img.shape[0], img.shape[1])//2)
    # ---- END DEBUG ----
    rmtree('./screen_caps/')

    # output header file
    f = open('writeLight/headers/' + filename + '.h', 'w')
    f.write('#define Frame ' + str(frame_cnt) + '\n')
    f.write('#define DEG_CNT ' + str(DIV_COUNT) + '\n' + '\n')
    f.write('#define NUMPIXELS ' + str(LED_COUNT) + '\n')
    f.write('const uint32_t pic [Frame][DEG_CNT][NUMPIXELS][3] = {' + '\n')
    for i in range(frame_cnt):
        f.write('\t{\n')
        for j in range(DIV_COUNT):
            f.write('\t\t{')
            for k in range(LED_COUNT):
                f.write('{' + ','.join(map(str,data[i][j][k])) + '}');
                if k==LED_COUNT-1: f.write('}')
                else: f.write(', ')
            if j==DIV_COUNT-1: f.write('\n\t}')
            else: f.write(',\n')
        if i==frame_cnt-1: f.write('};\n')
        else: f.write(',\n')


if __name__=='__main__': main()
