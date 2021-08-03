
from smbus import SMBus
import numpy as np
import cv2
import time


''' Make a smbus setup function later'''
addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1



# Should probably check the FOV values.
H_FOV = 62.2 # degrees
V_FOV = 48.8 # degrees

IMG_HEIGHT = 240
IMG_WIDTH = 320


def cam_setup():
    cap = cv2.VideoCapture(0)    
    cap.set(3, IMG_WIDTH)                       # Set the width
    cap.set(4, IMG_HEIGHT)                      # Set the height
    cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0.25)                    	
    cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0.01)
    cap.set(cv2.CAP_PROP_BRIGHTNESS, 0.5)
    cap.set(cv2.CAP_PROP_BUFFERSIZE,1)
    return cap


def get_hsv_image(frame):   
    frame = cv2.GaussianBlur(frame, (3,3), 0)
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    return hsv_frame


def find_ball(hsv_frame):
    ball_max = (194, 234, 137)
    ball_min = (130, 165, 59)
    kernel = np.ones((3,3))
    r_min = 2

    # Binarise the image (Find the "ball" pixels)
    img_binary = cv2.inRange(hsv_frame, ball_min, ball_max)

    # Reduce the effects of noise/innacurate thresholding.
    img_binary = cv2.dilate(img_binary, kernel)

    # Find ball candidates
    contours = cv2.findContours(img_binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) [-2]

    ball = None
    if len(contours) > 0:
        circle = max(contours, key = cv2.contourArea)
        #((x,y), r) = cv2.minEnclosingCircle(circle)
        x,y,w,h = cv2.boundingRect(circle)
        moments = cv2.moments(circle)
        #if moments["m00"] > 0 and r >= r_min:
        #    ball = cv2.minEnclosingCircle(circle) #((x,y),r)
        ball = ((x,y),(w,h))
    return ball


def get_ball_angles(ball):
    ((x,y),r) = ball

    # get angles assuming center of image is (0,0)
    H_angle = (x - IMG_WIDTH/2) /  (IMG_WIDTH /H_FOV)
    V_angle = (y - IMG_HEIGHT/2) / (IMG_HEIGHT/V_FOV)

    # Convert so that center of image is (90,90)
    #H_angle = 90 - H_angle # Sign is probably due to servo configuration
    #V_angle = 90 + V_angle
    H_angle = 0 - H_angle # Sign is probably due to servo configuration
    V_angle = 0 + V_angle

    return (H_angle,V_angle)


def print_angles(angles):
    for angle in angles:
        print(angle)
    print('\n')


def display_ball_on_frame(frame,ball):
    (coords,radius) = ball
    #coords = [int(round(i)) for i in coords]
    x,y = coords
    w,h = radius
    #cv2.circle(frame, tuple(coords), int(round(radius)), (0,255,0))
    #cv2.putText(frame, "Ball", (mid[0],(mid[1]+40)), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))
    cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0))
    cv2.imshow("cam", frame) # NOTE: image won't be displayed if there is no waitkey command later.


def is_quit_triggered():
    key = cv2.waitKey(1000) # This command will get the imshow to actually display.
    if key == ord('q'):
        return True
    # Other quitting conditions can be added in.

    return False




current_H_angle = 0
current_V_angle = 0

Kph, Kih, Kdh = 0.3, 0, 0
Kpv, Kiv, Kdv = 0.005, 0, 0
Hint, Vint = 0,0
Hlast, Vlast = 0,0
tlast = None

def send_data(angles):
    global current_H_angle
    global current_V_angle
    global Hlast
    global Vlast
    global Hint
    global Vint

    
    H,V = (20,20)
    angle_thresh = 2



    new_time = time.process_time()

    tdiff = new_time - tlast

    Hdiff = (H-Hlast)/tdiff
    Vdiff = (V-Vlast)/tdiff

    Hint = Hint + (H-Hlast)
    Vint = Vint + (V-Vlast)

    desired_H = current_H_angle + (H * Kph + Hint*Kih + Hdiff*Kdh   )
    desired_V = current_V_angle + (V * Kpv + Vint*Kiv + Vdiff*Kdv   )
    print(desired_V)
    if abs(H) > angle_thresh or abs(V) > angle_thresh:
        bus.write_i2c_block_data(addr, 1, [round(H + 90), round(V+90)])
        #bus.write_i2c_block_data(addr, 1, [90, 120])
        current_H_angle = desired_H
        current_V_angle = desired_V
        print(current_H_angle)
        print(current_V_angle)
    print('\n')
    
    '''
    if abs(current_H_angle - H) > angle_thresh or abs(current_V_angle - V) > angle_thresh:
        bus.write_i2c_block_data(addr, 1, [round(H), round(V)])
        current_H_angle = H
        current_V_angle = V
    '''



if __name__ == '__main__':
    cap = cam_setup()
    tlast = time.process_time() # initialise time stuff
    send_data((0,0))
    while not is_quit_triggered():
        _, frame = cap.read()
        hsv_frame = get_hsv_image(frame)
        ball = find_ball(hsv_frame)
        if ball is not None:
            angles = get_ball_angles(ball)

            #print_angles(angles)

            display_ball_on_frame(frame, ball)
        
            send_data(angles)
        else:
            cv2.imshow("cam", frame)
    
    # Clean up
    cv2.destroyAllWindows()
    cap.release()

'''
latest_image = None
def continuous_camera_read():
    cap = cam_setup()
    while True:
        latest_image = cap.read()



if __name__ == '__main__':
    #cap = cam_setup()
    threading.start_new_thread(continuous_camera_read)
    while not is_quit_triggered():
        #_, frame = cap.read()
        if latest_image is not None:
            frame = latest_image
            hsv_frame = get_hsv_image(frame)
            ball = find_ball(hsv_frame)
            if ball is not None:
                angles = get_ball_angles(ball)

                print_angles(angles)

                display_ball_on_frame(frame, ball)
            
                send_data(angles)
            else:
                cv2.imshow("cam", frame)
    
    # Clean up
    cv2.destroyAllWindows() 

'''




'''	
while True:

    #start_time = time.time()
    
    _, frame = cap.read()
    fil = cv2.GaussianBlur(frame.copy(), (3,3),0)
    hsv_frame = cv2.cvtColor(fil, cv2.COLOR_BGR2HSV)


## BALL
    A = None
    d = None
    #high_orange = (17, 255, 255)
    #low_orange = (0, 59, 112)
    #high_orange = (5, 254, 255)
    #low_orange = (0, 159, 133)
    #high_orange = (95, 255, 255)
    #low_orange = (0, 117, 124)
    high_orange = (189, 255, 255)
    low_orange = (0, 145, 129)

    r_min = 2 
    _, frame = cap.read()
    img_binary = cv2.inRange(hsv_frame.copy(), low_orange, high_orange)
    
    img_binary = cv2.dilate(img_binary, None, iterations = 1)

    # Finding Center of Object
    img_contours = img_binary.copy()
    contours = cv2.findContours(img_contours, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) [-2]

    # Finding largest contour and locating x,y values and radius
    mid = None 
    r = 0
    if len(contours) > 0:
        circle = max(contours, key = cv2.contourArea)
        ((x,y), r) = cv2.minEnclosingCircle(circle)
        this = cv2.moments(circle)
        if this["m00"] > 0:
            mid = (int(this["m10"] / this["m00"]), int(this["m01"] / this["m00"]))
            ## Focal Length = (radius@10cm * 10cm)/actual radius
            #d= (2*360)/r
            #A = (x / (320/108)) - 54
            A_x = ((x / (320/108))-54)/2
            A_y = ((y / (240/108))-54)/2


            #error_x =  abs(old_A_x - A_x)
            #intergral_x = intergral_x + (error_x*0.5)
            #derivative_x = (error_x - old_error_x)/0.1
            #output_x = Kp_x*error_x + Ki_x*intergral_x + Kd_x*derivative_x


            pos_x = 90 - (A_x)# - (0.05 * output_x))
            pos_y = 90 + A_y

            print(pos_x)
            print('\n')
            print(pos_y)#0.005*output_x)
            print('\n')
            print('\n')

            #old_A_x = A_x
            #old_A_y = A_y
            #old_error_x = error_x
	    
            if r < r_min:
                mid = None

    # Draw a circle around the ball
    if mid != None:
        #pass
        cv2.circle(frame, mid, int(round(r)), (0,255,0))
        #cv2.putText(frame, str(d), mid, cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))
        #cv2.putText(frame, str(A), (mid[0],(mid[1]+20)), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))
        #cv2.putText(frame, "Ball", (mid[0],(mid[1]+40)), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0))
        

    
    cv2.imshow("cam", frame)
       
    
    key = cv2.waitKey(1) 
    if key == 27:
        break

    if abs(old_pos_x - pos_x) > 15 or abs(old_pos_y - pos_y) > 15:
        bus.write_i2c_block_data(addr, 1, [round(pos_x), round(pos_y)])
        old_pos_x = pos_x
        old_pos_y = pos_y
'''
