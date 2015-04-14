import numpy as np
import cv2

# initialize playstation eye
cap = cv2.VideoCapture(0)

# import templates as grayscale images
img_rgb = cv2.imread('template1.png')
temp = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)
template1 = temp
template2 = cv2.flip(temp,0)
template3 = cv2.flip(temp,1)
template4 = cv2.flip(temp,-1)
i = 0

while(True):
    i = i + 1
    # Capture frame-by-frame
    ret, frame = cap.read()

    # get grayscale image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)    

    # transform the image to black / white
    gray, blackWhite = cv2.threshold(gray,50,255,cv2.THRESH_BINARY)    

    if i==30:
      # compare to template 1 to get e1 
      match1 = cv2.matchTemplate(blackWhite,template1,cv2.TM_CCOEFF)
      min_val, e1, min_loc, max_loc = cv2.minMaxLoc(match1)
           
      # compare to template 2 to get e2
      match2 = cv2.matchTemplate(blackWhite,template2,cv2.TM_CCOEFF)
      min_val, e2, min_loc, max_loc = cv2.minMaxLoc(match2)

      # compare to template 3 to get e3
      match3 = cv2.matchTemplate(blackWhite,template3,cv2.TM_CCOEFF)
      min_val, e3, min_loc, max_loc = cv2.minMaxLoc(match3)

      # compare to template 4 to get e4
      match4 = cv2.matchTemplate(blackWhite,template4,cv2.TM_CCOEFF)
      min_val, e4, min_loc, max_loc = cv2.minMaxLoc(match4)

      best = max([e1,e2,e3,e4])    
      # largest error represents best fit
      if best < 100000000:
          mesg = "0"
      else:
          if e1 == best:
                  mesg = "1"
          if e2 == best:
                  mesg = "2"
          if e3 == best:
                  mesg = "3"
          if e4 == best:
                  mesg = "4"
          print("Image orientation =" + mesg);
      i = 0


    # Display the resulting frame
    cv2.imshow('frame',blackWhite)
    # should we quit?
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
