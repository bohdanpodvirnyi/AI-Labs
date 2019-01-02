import numpy as np
import cv2

filename = "5"
ext = ".jpg"

img = cv2.imread(filename + ext, -1)

### image filtering

kernel = np.ones((7, 7), np.uint8)
rgb_planes = cv2.split(img)
result_norm_planes = []
for plane in rgb_planes:
    dilated_img = cv2.dilate(plane, kernel, iterations=3)
    bg_img = cv2.medianBlur(dilated_img, 25)
    diff_img = 255 - cv2.absdiff(plane, dilated_img)
    norm_img = np.copy(diff_img) * 0
    cv2.normalize(diff_img, norm_img, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8UC1)
    result_norm_planes.append(norm_img)

result_norm = cv2.merge(result_norm_planes)

cv2.imwrite(filename + "-1_shadow_removed" + ext, result_norm)

binary = cv2.cvtColor(result_norm, cv2.COLOR_BGR2GRAY)

lsd_img = np.zeros(img.shape, np.uint8)
lsd = cv2.createLineSegmentDetector(0)
lines = lsd.detect(binary)[0]
for l in lines:
    x0, y0, x1, y1 = l.flatten()
    cv2.line(lsd_img, (x0, y0), (x1, y1), (255, 255, 255), 5)

cv2.imwrite(filename + "-2_lsd" + ext, lsd_img)

lsd_img = cv2.cvtColor(lsd_img, cv2.COLOR_BGR2GRAY)
dilated_img = cv2.dilate(lsd_img, kernel, iterations=3)

cv2.imwrite(filename + "-3_dilate" + ext, dilated_img)

### finding lines

d = 5
theta = np.pi / 360
threshold = 25
min_line_length = 300
max_line_gap = 130
line_img = np.copy(img) * 0

lines = cv2.HoughLinesP(dilated_img, d, theta, threshold, np.array([]), min_line_length, max_line_gap)

for line in lines:
    for x1, y1, x2, y2 in line:
        cv2.line(line_img, (x1, y1), (x2, y2), (0, 255, 0), 15)

cv2.imwrite(filename + "-4_result" + ext, line_img)

### finding contours

binary = cv2.cvtColor(line_img, cv2.COLOR_BGR2GRAY)

_, contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

filtered_contours = list(filter(lambda contour: cv2.contourArea(contour) > 50000.0, contours))
contours_img = np.copy(img) * 0
for i in range(0, len(filtered_contours)):
    cv2.drawContours(contours_img, filtered_contours, i, (255, 0, 0), 5)

cv2.imwrite(filename + "-5_contours" + ext, contours_img)

### calc area

if len(filtered_contours) == 4:
    first_area = (cv2.contourArea(filtered_contours[0]) + cv2.contourArea(filtered_contours[1])) / 2
    second_area = (cv2.contourArea(filtered_contours[2]) + cv2.contourArea(filtered_contours[3])) / 2
    print(first_area/second_area)


