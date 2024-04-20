!!!This solution is done on Bosnian language but code can be easily translated!!! <br>
Tinkercad link: https://www.tinkercad.com/things/1e9Dcp66szJ-z1256us <br>
This embedded Solution represents door unlock system using password and is backed up with alarm. <br>
On the picture below is shown the Circuit View of the system- prompting user to enter password. <br>
![Circuit View](us1 pic/111111111.png) <br>
The application code consists of multiple functions, but the most prominent one is the function Otvori() (open).
This function serves as the main role of the system - checking the correctness of the entered password and either triggering the alarm if the password is incorrect or opening the door if the password is correct. Opening the door is done using the OtvoriServo() function, closing it by pressing the '#' button and using the ZatvoriServo() function defined earlier in the code. The alarm is triggered using the reproducirajAlarm() function. The ocistiPodatke() function is used to delete entered data and enable new input.
