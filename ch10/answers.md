## Answers to questions
1. With the left arrow `<-` operator, you can use `c <- "message"` to send data to the channel and `msg := <- c` to receive data from it
2. See `sleep`
3. A buffered channel is an asynchronous channel. You can create one like this `c := make(chan int, 20)`
