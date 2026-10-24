# Hangman-Game
Play a classical game of hangman made in c code! Done for class work.
1. The secret can be multiple words and can include apostrophes, spaces, and hyphens. An example secret phrase is "don't go in empty-handed".
2. A secret must be provided and have at most 256 characters. (Meaning that the array that stores the string must have one more element—257 total—to fit a possible maximum-length string’s terminating null byte.)
3. If special characters are present (space, ', and -), they will be shown at the start of the game (the player doesn’t need to guess special characters—they are hints). For the secret phrase above, the program would print "___'_ __ __ _____-______".
4. If only special characters are present, the player has already won.
5. The player will guess only one letter at a time followed by the Enter or return key. For example, to guess the letters “a”, “b”, and “c”, the user would type "a" enter "b" enter "c" enter .
6. Do not need to handle errors if the user enters more than one letter. For example, "a b c" enter .
7. If the user enters an invalid secret, print the exact error messages that are printed in the resources binary, and exit with any non-zero exit code
