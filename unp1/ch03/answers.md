## Answers to exercises

1. See `filelock.c`

2. See `reclock.c`

3. Since there's no data to write to in memory, the signal must be sent. For the reader it doesn't happen since it can always wait for a new writer to read data from.

4. See `multibuffer.c`

5. Nothing happens, text data and binary data should be transferred normally

6. ***Insert Image***
