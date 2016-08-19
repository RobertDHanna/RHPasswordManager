# RHPasswordManager
A terminal-interface application for storing and protecting passwords and accounts.

To run the project locally, simply clone the repository and compile the files with a c++11 compiler. g++ -std=c++11 is what I use on Mac.

The project is currently being re factored for better readability and scalability.<br>
The original design had the user interacting with an <b>AccountManager</b> object that was intended to be the "middleman" between all of the <b>Account</b> objects and the user. The code was clunky and only sort of managed to achieve this design. <br>
Recently, a new class has been added: the <b>AccountController</b>. This class receives input from the user and dispatches one of several routines (view Account info, edit an Account, delete/add an Account, etc). The <b>AccountController</b> contains an <b>AccountManager</b> object that contains all of the active <b>Accounts</b>. Using this design, it is easier to change or add new features to the program while also providing better organization.
