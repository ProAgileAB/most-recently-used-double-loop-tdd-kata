Recently Used List Kata
=======================
A popular feature of graphical editors of all kinds (text, graphics, spreadsheets, ..) is the Recent file list. It is often found as a sub-menu of the file menu in the GUI of the program.

Use TDD to grow this kind of behaviour. Some examples of the behaviour is
- When the program is run for the first time, the list is empty
- When a file is opened, it is added to the recent file list
- If an opened file already exists in the recent file list, it is bumped to the top, not duplicated in the list
- If the recent file list gets full (max is 10 items), the oldest item is removed when a new item is added


Stepping stones
---------------

1. Start by coming up with scratch notes (a test list) with 3-5 things you want to test. This ensures you understand the problem well enough to start coding.

2. Double loop step 1: start by writing an integration test, which will help you design the overall solution. Try to pick a GREEN PATH (a valid, common path that does something useful, rather than an error condition). This test will of course fail - so disable it. See it as a vision - sketch for the future!

3. Micro tests / TDD: pick a simple small test to begin with, and grow the solution from there.

4. Make the GREEN PATH integration test pass, possibly by changing it a lot. It is alive!

