# member_counter
The project purpuse is to count people, for example, who goes in/out to your store, and with the data in the end of the day, you could just devide the number with 2, and you get how many people was in your store.

# Steps to Reproduce
1. Get any microcontroller, a ultrasonic sensor and a 4 digit (or could be longer/shorter too) 7 segment display or a lcd panel (I used ESP32-S3-N16R8, 4 digit 7 segment display)
2. Open the <img width="1024" height="438" alt="image" src="https://github.com/user-attachments/assets/269d25db-4293-4149-9fd3-a1f4d6db558f" /> to know which pin to connect
3. Connect the pins with the microcontroller recommendation: A - 4, B - 5, C - 6, D - 7, E - 15, F - 16, G - 17, D1 - 9, D2 - 10, D3 - 11, D4 - 12 (you can use any pins, exept: 46, 20, 45, 0, 35, 36, 37)
4. Open the <img width="600" height="396" alt="image" src="https://github.com/user-attachments/assets/c5842eb5-40ca-4426-ab96-f06ff846bcc8" /> to know which pin to connect
5. Connect the pins with the microcontroller recommendation: trig - 8, echo - 18
6. Test the 7 segment display, to know, the common pin is a cathode or a anode. If you send a HIGH signal to the digit 1 (D1) and a HIGH signal to A, and it's on, than the common pin is a anode, so you HAVE TO change my code, but if it's off, than you don't have to change my code.
7. Now, you can upload my code to your microcontroller and have fun :D

# The final circuit


<img width="737" height="536" alt="image" src="https://github.com/user-attachments/assets/1104b683-ba97-4957-a569-36d5a96f9c10" />
