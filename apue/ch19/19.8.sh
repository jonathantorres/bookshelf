#! /bin/sh
( echo "Script started on" `date`;
  pty "${SHELL:~/bin/sh}";
  echo "Script done on " `date` ) | tee typescript
