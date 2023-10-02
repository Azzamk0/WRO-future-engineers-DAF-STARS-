```
Start
  |
  |--> Initialize variables and sensors
  |       |
  |       |--> Start Serial Communication
  |       |
  |       |--> Initialize HuskyLens, Servos, Motors and sensors
  |
  |
  |--> Enter main loop
          |
          |--> Count < 6?
          |       |
          |       |--> Yes: Continue
          |       |
          |       |--> No: Exit program
          |
          |--> Request Blocks from HuskyLens
                  |
                  |--> Yes: Continue
                  |
                  |--> No: Measure distance, update Gyro sensor, calculate correction factor, adjust servo position
                  |
                  |--> Found ID?
                          |
                          |--> ID = -1: Measure distance, update Gyro sensor, calculate correction factor, adjust servo position
                          |
                          |--> ID = 1: Adjust servo position to 60, print "I see Red"
                          |
                          |--> ID = 2: Adjust servo position to 120, print "I see Green"
End
```

