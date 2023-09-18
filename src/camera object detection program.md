import cv2
import numpy as np

# Specifying upper and lower ranges of color to detect in HSV format
green_lower = np.array([34, 75, 94])
green_upper = np.array([80, 182, 161])

red_lower = np.array([117, 75, 0])
red_upper = np.array([179, 255, 255])

webcam_video = cv2.VideoCapture(0)

while True:
    success, video = webcam_video.read()

    img = cv2.cvtColor(video, cv2.COLOR_BGR2HSV)

    green_mask = cv2.inRange(img, green_lower, green_upper)
    green_contours, _ = cv2.findContours(green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    red_mask = cv2.inRange(img, red_lower, red_upper)
    red_contours, _ = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    frame_height, frame_width = video.shape[:2]

    blue_line_one_fourth = int(frame_width / 4)
    blue_line_three_fourths = int(frame_width * 3 / 4)
    success_message = ""

    if len(green_contours) != 0:
        for green_contour in green_contours:
            if cv2.contourArea(green_contour) > 500:
                M = cv2.moments(green_contour)
                if M["m00"] != 0:
                    cX = int(M["m10"] / M["m00"])
                    cY = int(M["m01"] / M["m00"])
                else:
                    cX, cY = 0, 0

                if cX > blue_line_three_fourths:
                    success_message = "Success: Green object passed the line on the right"

                x, y, w, h = cv2.boundingRect(green_contour)
                cv2.rectangle(video, (x, y), (x + w, y + h), (0, 255, 0), 3)
                cv2.putText(video, "green", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                cv2.circle(video, (cX, cY), 4, (0, 255, 0), -1)

                # Draw the y-axis that intersects the centroid
                cv2.line(video, (cX, 0), (cX, frame_height), (0, 255, 0), 2)

    if len(red_contours) != 0:
        for red_contour in red_contours:
            if cv2.contourArea(red_contour) > 500:
                M = cv2.moments(red_contour)
                if M["m00"] != 0:
                    cX = int(M["m10"] / M["m00"])
                    cY = int(M["m01"] / M["m00"])
                else:
                    cX, cY = 0, 0

                if cX < blue_line_one_fourth:
                    success_message = "Success: Red object passed the line on the left"

                x, y, w, h = cv2.boundingRect(red_contour)
                cv2.rectangle(video, (x, y), (x + w, y + h), (0, 0, 255), 3)
                cv2.putText(video, "red", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
                cv2.circle(video, (cX, cY), 4, (0, 0, 255), -1)

                # Draw the y-axis that intersects the centroid
                cv2.line(video, (cX, 0), (cX, frame_height), (0, 0, 255), 2)

    # Draw the vertical lines
    cv2.line(video, (blue_line_one_fourth, 0), (blue_line_one_fourth, frame_height), (255, 0, 0), 2)
    cv2.line(video, (blue_line_three_fourths, 0), (blue_line_three_fourths, frame_height), (255, 0, 0), 2)

    if success_message:
        cv2.putText(video, success_message, (30, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 255), 2)

    cv2.imshow("Green Mask", green_mask)
    cv2.imshow("Red Mask", red_mask)
    cv2.imshow("Window", video)

    key = cv2.waitKey(1)
    if key == 27:  # Press 'Esc' to exit
        break

webcam_video.release()
cv2.destroyAllWindows()
