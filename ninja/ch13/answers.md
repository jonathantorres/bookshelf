## Surviving events

#### Answer #1
If adding tasks into the task queue was part of the event loop, then any events triggered while JavaScript code is executed would be ignored.
***

#### Answer #2
Since rendering is done at the end of the event loop, each iteration should not last more than 16ms in order to keep the browser from rendering less than 60 times per second.
***

#### Answer #3
Option b)
***

#### Answer #4
Option c)
***

#### Answer #5
Option c)
***


