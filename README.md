# PasswordManager

Password Manager is a console line application which allows users to store passwords with corresponding keys and retrieve them later. It does this by first verifying the user using a salted SHA256 hash to verify a password, then retrieving passwords based on user command. It stores the passwords in files on a directory in the user computer. To ensure that another malicious user who has access to the computer cannot easily view the passwords in plain text, the passwords are all encrypted, currently with XOR encryption.

The SHA256 hash header file is not my own. It can be found at https://github.com/okdshin/PicoSHA2/blob/master/picosha2.h.
