## Answers to exercises

1. See `tftp_cli` and `tftp_srv`

2. It would have to be re-sent, we can do so by implementing our own mechanism to acknowledge the arrival of packets, with TCP we wouldn't have to worry about it since the protocol already handles that for us. See `tftp_cli` and `tftp_srv`

3. Not much code, only the code that does the acknowledgment of the data transmission, we can let TCP handle it for us
