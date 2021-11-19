import numpy as np
import cv2

img = cv2.imread('sidepic.png')
h, w, c = img.shape
DEG_STEP = 120

data = []
f = open('writeLight/headers/side.h', 'w')
for i in range(120):
    line = []
    for j in range(8):
        b, g, r = map(lambda x: 128*x//255, img[h*j//8, w*i//DEG_STEP])
        line.append([r, g, b])
    data.append(line)

tmp = np.zeros((h, w, c), dtype='uint8')
for i in range(DEG_STEP):
    for j in range(8):
        x, y = w*i//DEG_STEP, h*j//8
        for nx in range(x-w//180, x+w//180):
            for ny in range(y-h//180, y+h//180):
                if nx<0 or w<=nx or ny<0 or h<=ny: continue
                for k in range(3): tmp[ny, nx, k] = 255*data[i][j][2-k]//128
cv2.imshow('versa', tmp)
cv2.waitKey(0)

f.write('const uint32_t sidepic[' + str(DEG_STEP) + '][8][3] = {\n')
for i in range(DEG_STEP):
    f.write('\t{')
    for j in range(8):
        f.write('{' + ','.join(map(str, data[i][j])) + '}')
        if j==7: f.write('}')
        else: f.write(', ')
    if i==DEG_STEP-1: f.write('};\n')
    else: f.write(',\n')
f.close()
